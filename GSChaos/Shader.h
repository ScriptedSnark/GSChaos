#ifdef SHADER_H_RECURSE_GUARD
#error Recursive header files inclusion detected in Shader.h
#else //SHADER_H_RECURSE_GUARD

#define SHADER_H_RECURSE_GUARD

#ifndef SHADER_H_GUARD
#define SHADER_H_GUARD
#pragma once

#ifdef __cplusplus

extern bool g_bActivatedShader;

namespace OpenGLShader
{
	GLuint CreateVertexShader(const std::string& fileName);
	GLuint CreateFragmentShader(const std::string& fileName);
	GLuint CreateProgram(GLuint vertexShader, GLuint fragmentShader);
	void Cleanup(GLuint vertexShader, GLuint fragmentShader);
};

#else //!__cplusplus
#error C++ compiler required to compile Shader.h
#endif //__cplusplus

#endif //SHADER_H_GUARD

#undef SHADER_H_RECURSE_GUARD
#endif //SHADER_H_RECURSE_GUARD