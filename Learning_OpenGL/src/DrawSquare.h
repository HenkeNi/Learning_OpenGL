#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

namespace draw_square
{
	void drawSquare();

	std::string parseShader(const std::string& filepath);
	unsigned int compileShader(unsigned int type, const std::string& source);
	unsigned int createShaders(const std::string& vertexShader, const std::string& fragmentShader);
	void processInput(GLFWwindow* window);
}