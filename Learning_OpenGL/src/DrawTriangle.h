#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

namespace draw_triangle
{
	void run();

	void drawTriangleTest();

	void drawTriangle2();

	

	std::string parseShader(const std::string& filepath);
	unsigned int compileShader(unsigned int type, const std::string& source);
	unsigned int createShaders(const std::string& vertexShader, const std::string& fragmentShader);
	void processInput(GLFWwindow* window);
	void drawTriangle();




	void drawTwoTrianglesv1();
	void drawTwoTrianglesv1p2();

	void drawTwoTrianglesv2();



	void drawTwoTrianglesDifferentShaders();
}