#include "DrawTriangle.h"

#include <GL/glew.h>	// NOTE: glew must be included before GLFW!
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

#include <iostream>

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
    }


    void run()
    {
        GLFWwindow* window;

        /* Initialize the library */
        if (!glfwInit())
            return;

        /* Create a windowed mode window and its OpenGL context */
        window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            return;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(window);

        if (glewInit() != GLEW_OK)
            std::cout << "ERROR: glewInit() failed";



        // SPECIFY POSITION FOR VERTICES (each line represents the position (x,y) for one vertex
        float positions[6] = {
            -0.5f, -0.5f,
             0.0f,  0.5f,
             0.5f, -0.5f,
        };


        // CREATE A VERTEX BUFFER (memory space on the GPU):
        unsigned int buffer;      // stores the id of the vertex buffer
        glGenBuffers(1, &buffer); // 1st param; how many vertex buffers - 2nd param; rather than returning an id, the second param takes the memory address of an unsigned integer and writes into that integers memory 


        // SELECT BUFFER 
        glBindBuffer(GL_ARRAY_BUFFER, buffer);  // bind (or select) buffer (through id) to specify which buffer to use to render the triangle


        // PROVIDE BUFFER WITH DATA (note: don't have to specify the data it contains, only size?)
        glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW); // (1: taget, 2: size of buffer (or how big the data is), 3: pointer to data, 4: usage patter)



        // ENABLE VERTEX ATTRIBUTE (takes in the index we want to enable)
        glEnableVertexAttribArray(0);

        // TELL OPENGL HOW THE DATA SPECIFIED IS LAID OUT
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0); 
        /*  1st param: index, start index of attribute?? position could start at index 1 if you want?!
            2nd param: size - how many floats in position (2 for 2d, 3 for 3d), 
            3rd param: type of each component in the array, 
            4th param: (bool) normalized (a color value (0 - 255) needs  to be normalized (0-0 - 1.0), 
            5th param: stride - amount of bytes between each vertex; in this case each vertex only consist of 2 floats
            6th param: pointer - offset of each attribute in bytes? (position is the very first byte (0), 12 bytes forward would be the beginning of the texture coordinate attribute (12), finally 8 bytes into that we get the vertex normal (20) - NOTE: use MACRO offsetOf instead of writing hardcoded bytes
                                                                               
         */

        // writing the shader?
        std::string vertexShader =
            "#version 330 core\n"
            "\n"
            "layout(location = 0) in vec4 position;"
            "\n"
            "void main()\n"
            "{\n"
            "   gl_Position = position;\n"
            "}\n";

        std::string fragmentShader =
            "#version 330 core\n"
            "\n"
            "layout(location = 0) out vec4 color;"
            "\n"
            "void main()\n"
            "{\n"
            "   color = vec4(1.0, 0.0, 0.0, 1.0);\n"
            "}\n";


        unsigned int shader = createShader(vertexShader, fragmentShader);
        glUseProgram(shader);


        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);


            // ISSUE DRAW CALL FOR BUFFER (will draw the binded buffer)
            glDrawArrays(GL_TRIANGLES, 0, 3); // (1st param; what primitive you're trying to draw. 2nd param; specifies starting index of the array (could start at index/elemnt 1). 3nd param; number of indices to be rendered 


            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

        glDeleteProgram(shader);

        glfwTerminate();
    }











    void drawTriangleTest()
    {
        GLFWwindow* window;

        /* Initialize the library */
        if (!glfwInit())
            return;

        /* Create a windowed mode window and its OpenGL context */
        window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            return;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(window);

        if (glewInit() != GLEW_OK)
            std::cout << "ERROR: glewInit() failed";




        // SPECIFY POSITION FOR VERTICES (each line represents the position (x,y,z) for one vertex
        float vertexPositions[] = {
            -0.7f, -0.7f, 0.0f,
             0.8f,  0.8f, 0.0f,
             0.9f, -0.9f, 0.0f
        };


        // CREATE A VERTEX BUFFER (memory space on the GPU):
        unsigned int buffer;      // stores the id of the vertex buffer
        glGenBuffers(1, &buffer); // 1st param; how many vertex buffers - 2nd param; rather than returning an id, the second param takes the memory address of an unsigned integer and writes into that integers memory 


        // SELECT BUFFER 
        glBindBuffer(GL_ARRAY_BUFFER, buffer);  // bind (or select) buffer (through id) to specify which buffer to use to render the triangle


        // PROVIDE BUFFER WITH DATA (note: don't have to specify the data it contains, only size?)
        glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), vertexPositions, GL_STATIC_DRAW); // (1: taget, 2: size of buffer (or how big the data is), 3: pointer to data, 4: usage patter)



        // ENABLE VERTEX ATTRIBUTE (takes in the index we want to enable)
        glEnableVertexAttribArray(0);

        // TELL OPENGL HOW THE DATA SPECIFIED IS LAID OUT
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
        /*  1st param: index, start index of attribute?? position could start at index 1 if you want?!
            2nd param: size - how many floats in position (2 for 2d, 3 for 3d),
            3rd param: type of each component in the array,
            4th param: (bool) normalized (a color value (0 - 255) needs  to be normalized (0-0 - 1.0),
            5th param: stride - amount of bytes between each vertex; in this case each vertex only consist of 2 floats
            6th param: pointer - offset of each attribute in bytes? (position is the very first byte (0), 12 bytes forward would be the beginning of the texture coordinate attribute (12), finally 8 bytes into that we get the vertex normal (20) - NOTE: use MACRO offsetOf instead of writing hardcoded bytes

         */

         // writing the shader?
        std::string vertexShader =
            "#version 330 core\n"
            "\n"
            "layout(location = 0) in vec4 position;"
            "\n"
            "void main()\n"
            "{\n"
            "   gl_Position = position;\n"
            "}\n";

        std::string fragmentShader =
            "#version 330 core\n"
            "\n"
            "layout(location = 0) out vec4 color;"
            "\n"
            "void main()\n"
            "{\n"
            "   color = vec4(1.0, 1.0, 0.0, 1.0);\n"
            "}\n";


        unsigned int shader = createShader(vertexShader, fragmentShader);
        glUseProgram(shader);


        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);


            // ISSUE DRAW CALL FOR BUFFER (will draw the binded buffer)
            glDrawArrays(GL_TRIANGLES, 0, 3); // (1st param; what primitive you're trying to draw. 2nd param; specifies starting index of the array (could start at index/elemnt 1). 3nd param; number of indices to be rendered 


            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

        glDeleteProgram(shader);

        glfwTerminate();



    }

}