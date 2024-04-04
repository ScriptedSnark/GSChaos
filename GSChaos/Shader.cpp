#include "includes.h"

namespace OpenGLShader
{
	std::string loadShaderFromFile(const std::string& fileName)
	{
		std::ifstream shaderFile(fileName);
		std::stringstream shaderStream;
		shaderStream << shaderFile.rdbuf();
		return shaderStream.str();
	}

	GLuint CreateVertexShader(const std::string& fileName)
	{
		std::string shaderSource = loadShaderFromFile(fileName);
		const char* shaderSourceCStr = shaderSource.c_str();

		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &shaderSourceCStr, NULL);
		glCompileShader(vertexShader);

		// checking for errors
		GLint success;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			printf("Error compiling vertex shader: %s\n", infoLog);
			return 0;
		}

		return vertexShader;
	}

	GLuint CreateFragmentShader(const std::string& fileName)
	{
		std::string shaderSource = loadShaderFromFile(fileName);
		const char* shaderSourceCStr = shaderSource.c_str();

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &shaderSourceCStr, NULL);
		glCompileShader(fragmentShader);

		// checking for errors
		GLint success;
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			printf("Error compiling fragment shader: %s\n", infoLog);
			return 0;
		}

		return fragmentShader;
	}

	GLuint CreateProgram(GLuint vertexShader, GLuint fragmentShader)
	{
		// shader program creation
		GLuint shaderProgram = glCreateProgram();

		if (vertexShader)
			glAttachShader(shaderProgram, vertexShader);

		if (fragmentShader)
			glAttachShader(shaderProgram, fragmentShader);

		glLinkProgram(shaderProgram);

		// checking for compiler & linker errors
		GLint success;
		GLchar infoLog[512];

		if (vertexShader)
		{
			glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

			if (!success)
			{
				glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
				printf("Error compiling vertex shader: %s\n", infoLog);
			}
		}

		if (fragmentShader)
		{
			glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

			if (!success)
			{
				glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
				printf("Error compiling fragment shader: %s\n", infoLog);
			}
		}

		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

		if (!success)
		{
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			printf("Error linking shader program: %s\n", infoLog);
		}

		return shaderProgram;
	}

	void Cleanup(GLuint vertexShader, GLuint fragmentShader)
	{
		// cleaning up shaders
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}
};