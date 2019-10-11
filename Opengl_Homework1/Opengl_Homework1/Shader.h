#pragma once

#define GLEW_STATIC
#include "GL/glew.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
	//program of the program
	unsigned int program;
	//store the code
	GLuint vertex, fragment;
	//constructor,read the vertex and fragment code
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	//deconstuctor
	~Shader();
	//active the program
	void Use();
	//uniform tool function
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
private:
	void checkCompileErrors(const GLuint &shader, std::string type);
};

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath) {
	/*
		read the file
	*/
	//read the code from the file
	std::string vertexCode, fragmentCode;
	std::ifstream vShaderFile, fShaderFile;
	//catch the exception
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		//open the file
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		//read to buffer
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		//close
		vShaderFile.close();
		fShaderFile.close();
		//convert stream into string 
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	/*
		complie shader
	*/

	//vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, nullptr);
	glCompileShader(vertex);
	checkCompileErrors(vertex, "VERTEX");
	//fragment shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, nullptr);
	glCompileShader(fragment);
	checkCompileErrors(fragment, "FRAGMENT");
	//shader program
	program = glCreateProgram();
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	glLinkProgram(program);
	checkCompileErrors(program, "PROGRAM");

}

Shader::~Shader() {
	glDetachShader(this->program, vertex);//???
	glDetachShader(this->program, fragment);
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	glDeleteProgram(program);
}

void Shader::Use() {
	glUseProgram(program);
}

void Shader::checkCompileErrors(const GLuint &shader, std::string type) {
	int success;
	char infoLog[512];
	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 512, nullptr, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR " << std::endl;
		}
	}
	else {
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shader, 512, nullptr, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR" << std::endl;
		}
	}
}

// utility uniform functions
// ------------------------------------------------------------------------
void Shader::setBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(program, name.c_str()), (int)value);
}
// ------------------------------------------------------------------------
void Shader::setInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(program, name.c_str()), value);
}
// ------------------------------------------------------------------------
void Shader::setFloat(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(program, name.c_str()), value);
}