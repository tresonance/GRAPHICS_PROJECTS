#include <fstream>
#include <iostream>
#include <OpenGL/gl3.h>

std::string		get_shaderSource(const std::string& ShaderFile);
GLuint			enable_shader(GLenum type, std::string filename);


GLuint			enable_shader(GLenum type, std::string filename)
{
	GLuint		shader;
	std::string src;
	GLint  compile_status;

	if(0 == (shader = glCreateShader(type)))
	{
		fprintf(stderr, "Shader is NUll\n");
		exit(1);
	}
	src = get_shaderSource(filename);
	if(src.c_str() == 0)
	{
		fprintf(stderr, "Shader is NUll\n");
		exit(1);
	}
	const GLchar *shaderSource = src.c_str();
	GLint shaderSourceSize = src.length();
	glShaderSource(shader, 1, &shaderSource, &shaderSourceSize);
	glCompileShader(shader);
	compile_status = GL_TRUE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);
	if(compile_status != GL_TRUE)
	{
		char *log;
		GLsizei log_size;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_size);
		if(0 == (log = (char*)malloc(log_size + 1)))
		{
			fprintf(stderr, "Cannot allocate shader log\n");
			exit(1);
		}
		memset(log, '\0', log_size + 1);
		glGetShaderInfoLog(shader, log_size, &log_size, log);
		fprintf(stderr, "-->[shader] ==> %s\n", log);
		free(log);
		glDeleteShader(shader);
		exit(1);
	}
	return (shader);
}
