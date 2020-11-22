#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>



namespace create_window
{
	void run();

	void createWindowTest();
	void processInput(GLFWwindow* window);
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);

}