#pragma once
#include <string>

namespace abstracting_opengl_application
{
	void Run();
	std::string parseShader(const std::string& filepath);
	unsigned int compileShader(unsigned int type, const std::string& source);
	unsigned int createShaders(const std::string& vertexShader, const std::string& fragmentShader);
};

