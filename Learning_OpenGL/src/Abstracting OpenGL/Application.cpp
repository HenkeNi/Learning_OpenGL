#include "Application.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>


namespace abstracting_opengl_application
{

    void Run()
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


        {
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




            unsigned int VAO;
            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);


            VertexArray VA;
            VertexBuffer VB{ vertexPositions, 4 * 3 * sizeof(float) };

            VertexBufferLayout layout;
            layout.Push<float>(3); // VAR 2 INNAN!!!
            VA.AddBuffer(VB, layout);

           

            IndexBuffer IB{ indices, 6 };

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
            glUseProgram(0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


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
                //processInput(window);



                glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
                /* Render here */
                glClear(GL_COLOR_BUFFER_BIT);

                // draw triangle
                glUseProgram(shaderProgram);
                VA.Bind();
                IB.Bind();

                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

                /* Swap front and back buffers */
                glfwSwapBuffers(window);


                /* Poll for and process events */
                glfwPollEvents();
            }

            glDeleteVertexArrays(1, &VAO);
            //glDeleteBuffers(1, &VBO);
            glDeleteProgram(shaderProgram);
        }
        glfwTerminate();
        return;

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