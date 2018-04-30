#include <fstream>
#include <iostream>
#include <OpenGL/gl3.h>

std::string		get_shaderSource(const std::string& ShaderFile);
GLuint			enable_shader(GLenum type, std::string filename);

GLuint shaderProgram(std::string filename)
{
	
	GLint link_status;
	GLuint shaders[2];
	GLuint program;

	if(0 == (shaders[0] = enable_shader(GL_VERTEX_SHADER, filename + ".vs"))
	|| 0 == (shaders[1] = enable_shader(GL_FRAGMENT_SHADER, filename + ".fs")))
	{
		fprintf(stderr, "ONE SHADER IS NULL\n");
		exit(1);
	}
	if(0 == (program = glCreateProgram()))
	{
		glDeleteShader(shaders[0]);
		glDeleteShader(shaders[1]);
		fprintf(stderr, "ONE SHADER IS NULL\n");
		exit(1);
	}
	glAttachShader(program, shaders[0]);
	glAttachShader(program, shaders[1]);

	//glBindAttribLocation(program, 0, "position");
	//glBindAttribLocation(program, 1, "color");

	glLinkProgram(program);
	link_status = GL_TRUE;
	glGetProgramiv(program, GL_LINK_STATUS, &link_status);
	if(link_status != GL_TRUE)
	{
		char *log;
		GLsizei log_size;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_size);
		if(0 == (log = (char*)malloc(log_size + 1)))
		{
			fprintf(stderr, "Cannot allocate shader log\n");
			exit(1);
		}
		memset(log, '\0', log_size + 1);
		glGetProgramInfoLog(program, log_size, &log_size, log);
		fprintf(stderr, "-->[Program]--> %s\n", log);
		free(log);
		glDetachShader(program, shaders[0]);
		glDeleteShader(shaders[0]);
		glDetachShader(program, shaders[1]);
		glDeleteShader(shaders[1]);
		glDeleteProgram(program);
		exit(1);
	}
	//glValidateProgram(m_program);
	//glDetachShader(program, shaders[0]);
	glDetachShader(program, shaders[1]);
	//glDeleteShader(shaders[0]);
	glDeleteShader(shaders[1]);
	return (program);
}
