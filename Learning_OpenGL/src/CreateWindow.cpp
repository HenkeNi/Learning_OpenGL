#include "CreateWindow.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace create_window
{




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

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

        glfwTerminate();
        return;
	}


    void createWindowTest()
    {
        GLFWwindow* window;

        /* Initialize the library */
        if (!glfwInit())
            return;


        // sets openGL version to 3.3
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // setting openGL profile to be core


        /* Create a windowed mode window and its OpenGL context */
        window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            return;
        }




        /* Make the window's context current */
        glfwMakeContextCurrent(window);


        // TEST:  whenever the window size changed (by OS or user resize) this callback function executes
        glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) { std::cout << "Updating window size!\n"; glViewport(0, 0, width, height); });
        // glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); -- other way...

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {

            // process input test...
            processInput(window);


            // Change clear color...
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);


            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

        glfwTerminate();
        return;
    }

  

    void processInput(GLFWwindow* window)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true); // close window if escape is pressed

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            std::cout << "Pressing w!\n";
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            std::cout << "Pressing s!\n";
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            std::cout << "Pressing a!\n";
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            std::cout << "Pressing d!\n";
    }


    //  whenever the window size changed (by OS or user resize) this callback function executes
    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        // make sure the viewport matches the new window dimensions; note that width and 
        // height will be significantly larger than specified on retina displays.

        glViewport(0, 0, width, height); // glViewport tells OpenGL the size of the rendering window
        /*
        *   2 first param; location of lower left corner of the window
        *   last 2 sets the width and height
        */
    }

}

