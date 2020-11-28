#include "DrawTriangle.h"

#include <GL/glew.h>	// NOTE: glew must be included before GLFW!
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

namespace draw_triangle
{
    /*
    *   Basic Concept of drawing a triangle:
    *       define a bunch of data that represents the triangle, and put that data into the GPU's v-ram. And then issue a draw call (a draw command) - read the data 
    *       stored i v-ram, and draw it on the screen. The GPU also needs to be told how to read an interpret that data and how to put it on to the screen.
    * 
    *   Other take on it:
    *       supply our graphics card with data, we store some kind of memory on the GPU which contains the data we want to draw. When the use a shader (a program that runs on
    *       the GPU) to read that data and display it on the screen. 
    * 
    *   VERTEX BUFFER:
    *       "A buffer, an blob/array of memory, into which we can push bytes. It's a buffer in OpenGL which means that is one the GPU (V-RAM or vidoe-ram) rather then CPU"
    *        
    *   SHADER:
    *       "A program that runs on the GPU, and is reponsible for reading and interpret the buffer.
    * 
    * 
    *   VERTEX ATTRIBUTES:
    *       "When the Shader starts to read the buffer (the blob of memory) it needs to know the layout of that memory. What is actually contained in the buffer, is it
    *          just some floats that dictate the position of each vertex, does it contain texture coordinates, etc..
    *       Vertex attributes; position, texture coordinates, etc... needed for the Shader to be able to interpret the buffer - need to be able to tell OpenGL "the first 12 bytes are floats and is the position"
    *       
    *       A position is an attribute, a color is an attribute, a texture coordinate is an attribute, etc..
    */



    /*
	
    static unsigned int compileShader(unsigned int type, const std::string& source)
    {
        unsigned int id = glCreateShader(type);
        const char* src = source.c_str(); // same as &source[0]
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        // ERROR HANDLING:
        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);

        if (result == GL_FALSE)
        {
            int length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            char* message = (char*)alloca(length * sizeof(char)); // same as char message = new char[length] but without allocating on the heap?? - alloca (from C) allocate on the stack
            glGetShaderInfoLog(id, length, &length, message);
            std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << '\n';
            std::cout << message << '\n';
            glDeleteShader(id);
            return 0;
        }

        return id;
    }


    static unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader)
    {
        unsigned int program = glCreateProgram();
        unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
        unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glLinkProgram(program);
        glValidateProgram(program);

        glDeleteShader(vs);
        glDeleteShader(fs);

        return program;
    }*/


    //void run()
    //{
    //    GLFWwindow* window;

    //    /* Initialize the library */
    //    if (!glfwInit())
    //        return;

    //    /* Create a windowed mode window and its OpenGL context */
    //    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    //    if (!window)
    //    {
    //        glfwTerminate();
    //        return;
    //    }

    //    /* Make the window's context current */
    //    glfwMakeContextCurrent(window);

    //    if (glewInit() != GLEW_OK)
    //        std::cout << "ERROR: glewInit() failed";



    //    // SPECIFY POSITION FOR VERTICES (each line represents the position (x,y) for one vertex
    //    float positions[6] = {
    //        -0.5f, -0.5f,
    //         0.0f,  0.5f,
    //         0.5f, -0.5f,
    //    };


    //    // CREATE A VERTEX BUFFER (memory space on the GPU):
    //    unsigned int buffer;      // stores the id of the vertex buffer
    //    glGenBuffers(1, &buffer); // 1st param; how many vertex buffers - 2nd param; rather than returning an id, the second param takes the memory address of an unsigned integer and writes into that integers memory 


    //    // SELECT BUFFER 
    //    glBindBuffer(GL_ARRAY_BUFFER, buffer);  // bind (or select) buffer (through id) to specify which buffer to use to render the triangle


    //    // PROVIDE BUFFER WITH DATA (note: don't have to specify the data it contains, only size?)
    //    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW); // (1: taget, 2: size of buffer (or how big the data is), 3: pointer to data, 4: usage patter)



    //    // ENABLE VERTEX ATTRIBUTE (takes in the index we want to enable)
    //    glEnableVertexAttribArray(0);

    //    // TELL OPENGL HOW THE DATA SPECIFIED IS LAID OUT
    //    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0); 
    //    /*  1st param: index, start index of attribute?? position could start at index 1 if you want?!
    //        2nd param: size - how many floats in position (2 for 2d, 3 for 3d), 
    //        3rd param: type of each component in the array, 
    //        4th param: (bool) normalized (a color value (0 - 255) needs  to be normalized (0-0 - 1.0), 
    //        5th param: stride - amount of bytes between each vertex; in this case each vertex only consist of 2 floats
    //        6th param: pointer - offset of each attribute in bytes? (position is the very first byte (0), 12 bytes forward would be the beginning of the texture coordinate attribute (12), finally 8 bytes into that we get the vertex normal (20) - NOTE: use MACRO offsetOf instead of writing hardcoded bytes
    //                                                                           
    //     */

    //    // writing the shader?
    //    std::string vertexShader =
    //        "#version 330 core\n"
    //        "\n"
    //        "layout(location = 0) in vec4 position;"
    //        "\n"
    //        "void main()\n"
    //        "{\n"
    //        "   gl_Position = position;\n"
    //        "}\n";

    //    std::string fragmentShader =
    //        "#version 330 core\n"
    //        "\n"
    //        "layout(location = 0) out vec4 color;"
    //        "\n"
    //        "void main()\n"
    //        "{\n"
    //        "   color = vec4(1.0, 0.0, 0.0, 1.0);\n"
    //        "}\n";


    //    unsigned int shader = createShader(vertexShader, fragmentShader);
    //    glUseProgram(shader);


    //    /* Loop until the user closes the window */
    //    while (!glfwWindowShouldClose(window))
    //    {
    //        /* Render here */
    //        glClear(GL_COLOR_BUFFER_BIT);


    //        // ISSUE DRAW CALL FOR BUFFER (will draw the binded buffer)
    //        glDrawArrays(GL_TRIANGLES, 0, 3); // (1st param; what primitive you're trying to draw. 2nd param; specifies starting index of the array (could start at index/elemnt 1). 3nd param; number of indices to be rendered 


    //        /* Swap front and back buffers */
    //        glfwSwapBuffers(window);

    //        /* Poll for and process events */
    //        glfwPollEvents();
    //    }

    //    glDeleteProgram(shader);

    //    glfwTerminate();
    //}








   
    //void drawTriangleTest()
    //{
    //    GLFWwindow* window;

    //    /* Initialize the library */
    //    if (!glfwInit())
    //        return;

    //    /* Create a windowed mode window and its OpenGL context */
    //    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    //    if (!window)
    //    {
    //        glfwTerminate();
    //        return;
    //    }

    //    /* Make the window's context current */
    //    glfwMakeContextCurrent(window);

    //    if (glewInit() != GLEW_OK)
    //        std::cout << "ERROR: glewInit() failed";




    //    // SPECIFY POSITION FOR VERTICES (each line represents the position (x,y,z) for one vertex
    //    float vertexPositions[] = {
    //        -0.7f, -0.7f, 0.0f,
    //         0.8f,  0.8f, 0.0f,
    //         0.9f, -0.9f, 0.0f
    //    };


    //    // CREATE A VERTEX BUFFER (memory space on the GPU):
    //    unsigned int buffer;      // stores the id of the vertex buffer
    //    glGenBuffers(1, &buffer); // 1st param; how many vertex buffers - 2nd param; rather than returning an id, the second param takes the memory address of an unsigned integer and writes into that integers memory 


    //    // SELECT BUFFER 
    //    glBindBuffer(GL_ARRAY_BUFFER, buffer);  // bind (or select) buffer (through id) to specify which buffer to use to render the triangle


    //    // PROVIDE BUFFER WITH DATA (note: don't have to specify the data it contains, only size?)
    //    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), vertexPositions, GL_STATIC_DRAW); // (1: taget, 2: size of buffer (or how big the data is), 3: pointer to data, 4: usage patter)



    //    // ENABLE VERTEX ATTRIBUTE (takes in the index we want to enable)
    //    glEnableVertexAttribArray(0);

    //    // TELL OPENGL HOW THE DATA SPECIFIED IS LAID OUT
    //    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
    //    /*  1st param: index, start index of attribute?? position could start at index 1 if you want?!
    //        2nd param: size - how many floats in position (2 for 2d, 3 for 3d),
    //        3rd param: type of each component in the array,
    //        4th param: (bool) normalized (a color value (0 - 255) needs  to be normalized (0-0 - 1.0),
    //        5th param: stride - amount of bytes between each vertex; in this case each vertex only consist of 2 floats
    //        6th param: pointer - offset of each attribute in bytes? (position is the very first byte (0), 12 bytes forward would be the beginning of the texture coordinate attribute (12), finally 8 bytes into that we get the vertex normal (20) - NOTE: use MACRO offsetOf instead of writing hardcoded bytes

    //     */

    //     // writing the shader?
    //    std::string vertexShader =
    //        "#version 330 core\n"
    //        "\n"
    //        "layout(location = 0) in vec4 position;"
    //        "\n"
    //        "void main()\n"
    //        "{\n"
    //        "   gl_Position = position;\n"
    //        "}\n";

    //    std::string fragmentShader =
    //        "#version 330 core\n"
    //        "\n"
    //        "layout(location = 0) out vec4 color;"
    //        "\n"
    //        "void main()\n"
    //        "{\n"
    //        "   color = vec4(1.0, 1.0, 0.0, 1.0);\n"
    //        "}\n";


    //    unsigned int shader = createShader(vertexShader, fragmentShader);
    //    glUseProgram(shader);


    //    /* Loop until the user closes the window */
    //    while (!glfwWindowShouldClose(window))
    //    {
    //        /* Render here */
    //        glClear(GL_COLOR_BUFFER_BIT);


    //        // ISSUE DRAW CALL FOR BUFFER (will draw the binded buffer)
    //        glDrawArrays(GL_TRIANGLES, 0, 3); // (1st param; what primitive you're trying to draw. 2nd param; specifies starting index of the array (could start at index/elemnt 1). 3nd param; number of indices to be rendered 


    //        /* Swap front and back buffers */
    //        glfwSwapBuffers(window);

    //        /* Poll for and process events */
    //        glfwPollEvents();
    //    }

    //    glDeleteProgram(shader);

    //    glfwTerminate();



    //}










    //const char* vertexShaderSource =
    //    "#version 330 core\n"
    //    "layout (location = 0) in vec3 aPos;\n"
    //    "void main()\n"
    //    "{\n"
    //    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    //    "}\n\0";

    //const char* fragmentShaderSource =
    //    "#version 330 core\n"
    //    "out vec4 FragColor;\n"
    //    "void main()\n"
    //    "{\n"
    //    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    //    "}\n\0";



    //void drawTriangle2()
    //{

    //    glfwInit();
    //    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //    GLFWwindow* window = glfwCreateWindow(600, 800, "Draw Triangle", NULL, NULL);
    //    if (window == NULL)
    //    {
    //        glfwTerminate();
    //        return;
    //    }

    //    glfwMakeContextCurrent(window);
    //    
    //    if (glewInit() != GLEW_OK)
    //        std::cout << "ERROR: glewInit() failed";
    //    
    //    // build and compile shader program
    //    
    //    // vertex shader
    //    int vertexShader = glCreateShader( X_SHADER);
    //    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    //    glCompileShader(vertexShader);

    //    // check for shader compile errors
    //    int success;
    //    char infoLog[512];
    //    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    //    if (!success)
    //    {
    //        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    //    }

    //    // fragment shader
    //    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    //    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    //    glCompileShader(fragmentShader);

    //    // check for compile erros
    //    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    //    if (!success)
    //        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);

    //    // link shaders
    //    int shaderProgram = glCreateProgram();
    //    glAttachShader(shaderProgram, vertexShader);
    //    glAttachShader(shaderProgram, fragmentShader);
    //    glLinkProgram(shaderProgram);

    //    // check for linking errors...
    //    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    //    if (!success)
    //    {
    //        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    //    }
    //    glDeleteShader(vertexShader);
    //    glDeleteShader(fragmentShader);



    //    float vertices[] = {
    //        -0.5f, -0.5f, 0.0f,
    //         0.5f, -0.5f, 0.0f,
    //         0.0f,  0.5f, 0.0f
    //    };


    //    unsigned int VBO;
    //    glGenBuffers(1, &VBO);

    //    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    //    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
    //    glEnableVertexAttribArray(0);


    //    while (!glfwWindowShouldClose(window))
    //    {
    //        glClearColor(0.9f, 0.2f, 0.8f, 1.0f);
    //        glClear(GL_COLOR_BUFFER_BIT);

    //        glUseProgram(shaderProgram);
    //        glDrawArrays(GL_TRIANGLES, 0, 3);

    //        glfwSwapBuffers(window);
    //        glfwPollEvents();
    //    }

    //    glDeleteBuffers(1, &VBO);
    //    glDeleteProgram(shaderProgram);

    //    glfwTerminate();
    //    return;

    //}




    //











  

   


    void drawTriangle()
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
        float vertexPositions[] = {
            -0.5f, -0.5f, 0.0f, // left corner
             0.5f, -0.5f, 0.0f, // right corner
             0.0f,  0.5f, 0.0f  // top corner
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
            glDrawArrays(GL_TRIANGLES, 0, 3); // 

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
        
        std::cout << "SOURCE CODE: " << src << '\n';

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
















    void drawTwoTrianglesv1()
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
        float vertexPositions[] = {
            // first triangle
            -0.9f, -0.5f, 0.0f,
            -0.0f, -0.5f, 0.0f,
             -0.45f,  0.5f, 0.0f,

             // second triangle
             0.0f, -0.5f, 0.0f,
             0.9f, -0.5f, 0.0f,
             0.45f, 0.5f, 0.0f
        };


        unsigned int VBO, VAO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO); // Binds or select the buffer
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW); // 1. type of buffer, 2. size of the data, 3. The actual data, 4. How it should be drawn

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // 1. The vertex attribute to configure (check vertex shader!), 2. Size of vertex attribute (vec3 so 3 values), 3. Type of data, 4. If it should be normalized, 5. Stride - the space between consecutive vertex attributes, 6. Offset of where the position data begins
        glEnableVertexAttribArray(0); // enable attribute (disabled by default!)

        glBindBuffer(GL_ARRAY_BUFFER, 0);

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
            glDrawArrays(GL_TRIANGLES, 0, 6);  

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









    void drawTwoTrianglesv1p2()
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
        float firstTriangle[] = {
            // first triangle
            -0.9f, -0.5f, 0.0f,
            -0.0f, -0.5f, 0.0f,
             -0.45f,  0.5f, 0.0f,
        };

        float secondTriangle[] = {
            0.0f, -0.5f, 0.0f,
            0.9f, -0.5f, 0.0f,
            0.45f, 0.5f, 0.0f
        };


        unsigned int VBOs[2], VAOs[2];
        glGenVertexArrays(2, VAOs); // possible to generate multiple VAOs or buffers at the same time
        glGenBuffers(2, VBOs);


        // First Triangle Setup
        glBindVertexArray(VAOs[0]);
        glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]); // Binds or select the buffer
        glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW); 

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // 1. The vertex attribute to configure (check vertex shader!), 2. Size of vertex attribute (vec3 so 3 values), 3. Type of data, 4. If it should be normalized, 5. Stride - the space between consecutive vertex attributes, 6. Offset of where the position data begins
        glEnableVertexAttribArray(0); // enable attribute (disabled by default!)


        // glBindVertexArray(0); - no need to unbind at all as we directly bind a different VAO the next few lines



        // Second Triangle Setup
        glBindVertexArray(VAOs[1]); // Binding a different VAO now
        glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]); // and a different VBO
        glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(0);



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
            glBindVertexArray(VAOs[0]);
            glDrawArrays(GL_TRIANGLES, 0, 3); // draw call

            glBindVertexArray(VAOs[1]);
            glDrawArrays(GL_TRIANGLES, 0, 3); // draw call

            /* Swap front and back buffers */
            glfwSwapBuffers(window);


            /* Poll for and process events */
            glfwPollEvents();
        }

        glDeleteVertexArrays(2, VAOs);
        glDeleteBuffers(2, VBOs);
        glDeleteProgram(shaderProgram);

        glfwTerminate();
        return;
    }
















    void drawTwoTrianglesv2()
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
        float vertexPositions[] = {
            -0.75f, 0.0f, 0.0f, // left corner
             0.75f, 0.0f, 0.0f, // right corner
             0.0f,  0.75f, 0.0f,  // top corner
             0.0f, -0.75f, 0.0f      // bottom corner
        };

        unsigned int indices[] = {
            0, 1, 2,
            0, 1, 3
        };

        unsigned int VBO, VAO, EBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO); 
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO); // Binds or select the buffer
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW); // 1. type of buffer, 2. size of the data, 3. The actual data, 4. How it should be drawn

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        
        // tell OpenGL how it should interpret the data
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // 1. The vertex attribute to configure (check vertex shader!), 2. Size of vertex attribute (vec3 so 3 values), 3. Type of data, 4. If it should be normalized, 5. Stride - the space between consecutive vertex attributes, 6. Offset of where the position data begins
        glEnableVertexAttribArray(0); // enable attribute (disabled by default!)


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
            glDrawElements(GL_TRIANGLES,6, GL_UNSIGNED_INT, 0); // 

            /* Swap front and back buffers */
            glfwSwapBuffers(window);


            /* Poll for and process events */
            glfwPollEvents();
        }

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
        glDeleteProgram(shaderProgram);

        glfwTerminate();
        return;
    }







































         
    const char* vertexShaderSrc =
        "#version 330 core\n"
        "\n"
        "layout(location = 0) in vec4 position;"
        "\n"
        "void main()\n"
        "{\n"
        "   gl_Position = position;\n"
        "}\n";

    const char* fragmentShader1Src =
        "#version 330 core\n"
        "\n"
        "layout(location = 0) out vec4 color;"
        "\n"
        "void main()\n"
        "{\n"
        "   color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n";

    const char* fragmentShader2Src =
        "#version 330 core\n"
        "\n"
        "layout(location = 0) out vec4 color;"
        "\n"
        "void main()\n"
        "{\n"
        "   color = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
        "}\n";


    void drawTwoTrianglesDifferentShaders()
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
        float firstTriangle[] = {
            // first triangle
            -0.9f, -0.5f, 0.0f,
            -0.0f, -0.5f, 0.0f,
             -0.45f,  0.5f, 0.0f,
        };

        float secondTriangle[] = {
            0.0f, -0.5f, 0.0f,
            0.9f, -0.5f, 0.0f,
            0.45f, 0.5f, 0.0f
        };


        unsigned int VBOs[2], VAOs[2];
        glGenVertexArrays(2, VAOs); // possible to generate multiple VAOs or buffers at the same time
        glGenBuffers(2, VBOs);


        // First Triangle Setup
        glBindVertexArray(VAOs[0]);
        glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]); // Binds or select the buffer
        glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // 1. The vertex attribute to configure (check vertex shader!), 2. Size of vertex attribute (vec3 so 3 values), 3. Type of data, 4. If it should be normalized, 5. Stride - the space between consecutive vertex attributes, 6. Offset of where the position data begins
        glEnableVertexAttribArray(0); // enable attribute (disabled by default!)


        // glBindVertexArray(0); - no need to unbind at all as we directly bind a different VAO the next few lines



        // Second Triangle Setup
        glBindVertexArray(VAOs[1]); // Binding a different VAO now
        glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]); // and a different VBO
        glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(0);



        // Build and compile shaders...
        // ----------------------------
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        unsigned int fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER);
        unsigned int fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);

  
        unsigned int shaderProgramOrange = glCreateProgram(); // Shaders for first triangle
        unsigned int shaderProgramYellow = glCreateProgram(); // Shaders for second triangle

        // Compile vertex Shader
        glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
        glCompileShader(vertexShader);

        // Compile first fragment shader
        glShaderSource(fragmentShaderOrange, 1, &fragmentShader1Src, NULL);
        glCompileShader(fragmentShaderOrange);

        // Compile second fragment shader
        glShaderSource(fragmentShaderYellow, 1, &fragmentShader2Src, NULL);
        glCompileShader(fragmentShaderYellow);


        // link first program
        glAttachShader(shaderProgramOrange, vertexShader);
        glAttachShader(shaderProgramOrange, fragmentShaderOrange);
        glLinkProgram(shaderProgramOrange);

        // link second program
        glAttachShader(shaderProgramYellow, vertexShader);
        glAttachShader(shaderProgramYellow, fragmentShaderYellow);
        glLinkProgram(shaderProgramYellow);




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
            glUseProgram(shaderProgramOrange);
            glBindVertexArray(VAOs[0]);
            glDrawArrays(GL_TRIANGLES, 0, 3); // draw call

            glUseProgram(shaderProgramYellow);
            glBindVertexArray(VAOs[1]);
            glDrawArrays(GL_TRIANGLES, 0, 3); // draw call

            /* Swap front and back buffers */
            glfwSwapBuffers(window);


            /* Poll for and process events */
            glfwPollEvents();
        }

        glDeleteVertexArrays(2, VAOs);
        glDeleteBuffers(2, VBOs);
        glDeleteProgram(shaderProgramOrange);
        glDeleteProgram(shaderProgramYellow);

        glfwTerminate();
        return;
    }


}