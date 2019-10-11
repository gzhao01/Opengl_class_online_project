/*#ifndef Shader_h
#define Shader_h
#endif // Shader_h
*/

//只编译一次
#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
//#define GLEW_STATIC
#include <GL/glew.h>

class Shader {


	GLuint vertex, fragment;

	public:
		GLuint Program;
		//constructor
		/*parameter:
				vertexPath, fragmentPath    store the path of the file to be read
		*/
		Shader(const GLchar *vertexPath, const GLchar* fragmentPath) {
			/*io stream*/
			std::string vertexCode;
			std::string fragmentCode;
			std::ifstream vShaderFile;
			std::ifstream fShaderFile;

			vShaderFile.exceptions(std::ifstream::badbit);
			fShaderFile.exceptions(std::ifstream::badbit);
			try {
				//open the file
				vShaderFile.open(vertexPath);
				fShaderFile.open(fragmentPath);
				std::stringstream vShaderStream, fShaderStream;
				vShaderStream << vShaderFile.rdbuf();
				fShaderStream << fShaderFile.rdbuf();

				//close the file
				vShaderFile.close();
				fShaderFile.close();

				//Convert the data type  from C string to C++ string
				vertexCode = vShaderStream.str();
				fragmentCode = fShaderStream.str();
			}
			catch(std::ifstream::failure e){
				std::cout << "ERROE::SHADER::FILE_NOT_SUCCESS SFULLY_READ"<<std::endl;
			}
			const GLchar* vShaderCode = vertexCode.c_str();
			const GLchar* fShaderCode = fragmentCode.c_str();

			/*
				compile the shaders
			*/
		    vertex = glCreateShader(GL_VERTEX_SHADER);
			//将源代码放入文件
			glShaderSource(vertex, 1, &vShaderCode, NULL);
			//进行编译
			glCompileShader(vertex);

			//check whether compile succeed
			GLint success;
			GLchar infoLog[512];
			glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(vertex, 512, NULL, infoLog);
				std::cout << "ERROE::SHADER::VERTEX::COMPILATION_FAILED\N" << infoLog << std::endl;
			}

			//创造一个储存的文件
			fragment = glCreateShader(GL_FRAGMENT_SHADER);
			//将源代码放入文件
			glShaderSource(fragment, 1, &fShaderCode, NULL);
			//进行编译
			glCompileShader(fragment);

			//check whether compile succeed
			GLint fragment_success;
			GLchar fragment_infoLog[512];
			glGetShaderiv(fragment, GL_COMPILE_STATUS, &fragment_success);
			if (!fragment_success) {
				glGetShaderInfoLog(fragment, 512, NULL, fragment_infoLog);
				std::cout << "ERROE::SHADER::FRAGMENT::COMPILATION_FAILED\N" << fragment_infoLog << std::endl;
			}

			//create a link and link the code
			this->Program = glCreateProgram();
			glAttachShader(this->Program, vertex);
			glAttachShader(this->Program, fragment);
			glLinkProgram(this->Program);

			//check whether link succeed
			GLint link_success;
			GLchar link_infoLog[512];
			glGetProgramiv(this->Program, GL_LINK_STATUS, &link_success);
			if (!link_success) {
				glGetProgramInfoLog(this->Program, 512, NULL, link_infoLog);
				std::cout << "ERROE::SHADER::PROGRAM::LINKING_FAILED\N" << link_infoLog << std::endl;
			}
		}
		//deconstructor
		~Shader() {
			glDetachShader(this->Program, vertex);
			glDetachShader(this->Program, fragment);
			glDeleteShader(vertex);
			glDeleteShader(fragment);
			glDeleteProgram(this->Program);
		}
		void Use() {
			glUseProgram(this->Program);
		}

};


