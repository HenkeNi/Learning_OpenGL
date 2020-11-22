#include "CreateWindow.h"
#include "DrawTriangle.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) glClearError();x;ASSERT(glLogCall(#x, __FILE__, __LINE__))

// TODO: Create separate files for vertex and fragment shader files


// Clear errors (clears error buffer?)
static void glClearError()
{
	// while there is errors to fetch...
	while (glGetError() != GL_NO_ERROR);
}


// print all the errors that occur
static bool glLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << ") << function << " " << file << ':' << line << \n";
		return false;
	}
	return true;
}


struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};





// reads shader from file
static ShaderProgramSource parseShader(const std::string& filepath)
{
	std::ifstream stream(filepath); // opens file

	enum class ShaderType
	{
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1,
	};


	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;


	// while there are lines to read in the file
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}
	return { ss[0].str(), ss[1].str() };
}





static unsigned int compileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str(); // &source[0] also works?
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);


	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

		// maybe better to create heap allocated?!
		// char* message = new char[length];
		// alloc allows to allocate on the stack
		char* message = (char*)alloca(length * sizeof(char));

		glGetShaderInfoLog(id, length, &length, message);

		std::cout << "Failed to compile " <<
			(type == GL_VERTEX_SHADER ? "vertex" : "fragment")
			<< " shader!\n" <<
			message << '\n';

		glDeleteShader(id);

		return 0;
	}
	return id;
}





// SHADER

static unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	// Possible to use GLuint instead of unsigned int
	unsigned int program = glCreateProgram();
	unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);     // attaches shaders?
	glLinkProgram(program);          // links program

	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);


	return program;
}



int main(void)
{
	//create_window::createWindowTest();
	//create_window::run();
	//draw_triangle::run();
	draw_triangle::drawTriangleTest();





	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	// sets openGL version to 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // major version
 	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // minor version (result? v3.3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // setting openGL profile to be core


	
	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}



	/* Make the window's context current */
	glfwMakeContextCurrent(window);


	glfwSwapInterval(1);


	// Needs to be after glfwMakeContextCurrent...
	if (glewInit() != GLEW_OK)
		std::cout << "Failed to load  glew";

	std::cout << glGetString(GL_VERSION) << '\n'; // print verion of gl


	float positions[] = {
		-0.5f,  -0.5f,   // 0
		 0.5f,   -0.5f,  // 1
		 0.5f,   0.5f,   // 2
		 -0.5f,   0.5f,  // 3
	};



	// index buffer?
	unsigned int indices[] = {
		0, 1, 2, // first triangle
		2, 3, 0  // second triangle
	};



	//
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);



	/*float positions[6] = {
		-0.5f,  -0.5f, // each line is an actual vertex (so 3 vertex positions (x, y - coordinates)
		 0.0f,   0.5f,
		 0.5f,  -0.5f,
	};*/



	unsigned int buffer;                        // Create id for buffer (?)
	glGenBuffers(1, &buffer);                   // Creates (1) buffer and returns an id that is stored in buffer (which is used to refer to the buffer)
	glBindBuffer(GL_ARRAY_BUFFER, buffer);      // Binds (or select) the buffer                                 
	glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), positions, GL_STATIC_DRAW);  // put data into the buffer
	 //glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);  // put data into the buffer



	 // enable
	glEnableVertexAttribArray(0);

	// tell openGL about the layout of the data (how it should be interpreted)  - size in this case is x and y
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0); // 1: index of attribute (position, color etc), 2: size of the component (in this case its a float with x and y)


	unsigned int IBO;                        // index buffer object
	glGenBuffers(1, &IBO);                   // Creates (1) buffer and returns an id that is stored in buffer (which is used to refer to the buffer)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);      // Binds (or select) the buffer                                 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);  // put data into the buffer



	ShaderProgramSource src = parseShader("res/shaders/Basic.shader");
	std::cout << "VERTEX:\n" << src.VertexSource << '\n';
	std::cout << "FRAGMENT:\n" << src.FragmentSource << '\n';


	unsigned int shader = createShader(src.VertexSource, src.FragmentSource);
	glUseProgram(shader);



	int location = glGetUniformLocation(shader, "u_Color"); // retrieve location of variable
	//ASSERT(location != -1);
	glUniform4f(location, 0.2f, 0.3f, 0.8f, 1.0f);    // 1 param is the location of the variable, 


	float r = 0.0f;
	float increment = 0.05f;



	// unbind 
	glBindVertexArray(0);
	glUseProgram(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{

		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);



		glUseProgram(shader); // TEST
		glUniform4f(location, r, 0.3f, 0.8f, 1.0f);    // change color
	

		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);							    // TEST



		//glClearError(); // clears all error
		GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
		//ASSERT(glLogCall()); // prints errors...

		//glDrawArrays(GL_TRIANGLES, 0, 6); // if no index buffer use glDrawArrays()..
		//glDrawArrays(GL_TRIANGLES, 0, 3); // if no index buffer use glDrawArrays()...
		// glDrawElements(GL_TRIANGLES, 3, null) - with index buffer


		if (r > 1.0f)
			increment = -0.05f;
		else if (r < 0.0f)
			increment = 0.05f;

		r += increment;



		/* Swap front and back buffers */
		glfwSwapBuffers(window);


		/* Poll for and process events */
		glfwPollEvents();

	}

	glDeleteProgram(shader);

	glfwTerminate();

	return 0;

}





