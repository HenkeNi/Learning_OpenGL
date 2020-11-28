#include "DrawSquare.h"

#include <GL/glew.h>	// NOTE: glew must be included before GLFW!
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

namespace draw_square
{




    void drawSquare()
    {

        GLFWwindow* window;

        /* Initialize the library */
        if (!glfwInit())
            return;


        // sets openGL version to 3.3 (and core)
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // If apple computer
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif // __APPLE__



        /* Create a windowed mode window and its OpenGL context */
        window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            return;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(window);

        // Make sure viewport matches the new window dimensions
        glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); });

        if (glewInit() != GLEW_OK)
            std::cout << "Failed to load  glew";


        // set up vertex data (and buffer(s)) and configure vertex attributes
        // ------------------------------------------------------------------
        /*float vertexPositions[] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f, 
             0.5f,  0.5f, 0.0f,

             0.5f,  0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f
        };*/

        // Remove duplicate vertex positions:
        float vertexPositions[] = {
           -0.5f, -0.5f, 0.0f, // 0
            0.5f, -0.5f, 0.0f, // 1 
            0.5f,  0.5f, 0.0f, // 2
           -0.5f,  0.5f, 0.0f, // 3
        };

        unsigned int indices[] = {
            0, 1, 2, // FIRST TRIANGLE
            2, 3, 0 // SECOND TRIANGLE
        };




        // vertex buffer object & vertex array object
        unsigned int VBO, VAO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO); // generates a buffer (writes an id into VBO)

        // bind the vertex array first, then bind and set vertex buffer(s), and then configure vertex attribute(s)
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO); // Binds or select the buffer

        // copies data into the buffer's memory
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW); // 1. type of buffer, 2. size of the data, 3. The actual data, 4. How it should be drawn

        // tell OpenGL how it should interpret the data
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // 1. The vertex attribute to configure (check vertex shader!), 2. Size of vertex attribute (vec3 so 3 values), 3. Type of data, 4. If it should be normalized, 5. Stride - the space between consecutive vertex attributes, 6. Offset of where the position data begins
        glEnableVertexAttribArray(0); // enable attribute (disabled by default!)


        unsigned int IBO; // index buffer object
        glGenBuffers(1, &IBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);



        // Okey to unbind buffer since the call to glVertexAttribPointer registered VBO as the vertex attribute's 
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // unbind VAO so other VAO calls won't accidentally modify this VAO. (not necessary?)
        glBindVertexArray(0);



        // Build and compile shaders...
        // ----------------------------
        std::string vertexShaderSource{ parseShader("res/shaders/VertexShader.shader") };
        std::string fragmentShaderSource{ parseShader("res/shaders/FragmentShader.shader") };

        unsigned int shaderProgram = createShaders(vertexShaderSource, fragmentShaderSource);







        // render loop
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            // Handle input
            processInput(window);



            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            // draw triangle
            glUseProgram(shaderProgram);
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr); // NOTE: not glDrawArrays(); !!

            /* Swap front and back buffers */
            glfwSwapBuffers(window);


            /* Poll for and process events */
            glfwPollEvents();
        }

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteProgram(shaderProgram);

        glfwTerminate();
        return;
    }

    void processInput(GLFWwindow* window)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }


    std::string parseShader(const std::string& filepath)
    {
        std::ifstream stream(filepath); // this opens/reads from the file

        if (!stream)
            throw std::runtime_error("File couldn't be opened!");

        std::string line;
        std::stringstream shaderSource;

        // While there are still "lines to read"
        while (getline(stream, line))
        {
            shaderSource << line << '\n';
        }
        return shaderSource.str();
    }



    unsigned int compileShader(unsigned int type, const std::string& source)
    {
        unsigned int shaderId = glCreateShader(type); // enum == unsigned int(?)
        const char* src = source.c_str(); // &source[0] also works?


        glShaderSource(shaderId, 1, &src, nullptr);
        glCompileShader(shaderId);

        int success;
        char infoLog[512];
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::" << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") << "COMPILATION_FAILED!" << infoLog << '\n';

            glDeleteShader(shaderId);
            return 0;
        }
        return shaderId;
    }

    unsigned int createShaders(const std::string& vertexShader, const std::string& fragmentShader)
    {
        unsigned int program = glCreateProgram();
        unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
        unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);


        // Link shaders
        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glLinkProgram(program);

        //glValidateProgram(program); // does what?

        glDeleteShader(vs);
        glDeleteShader(fs);


        return program;
    }
}