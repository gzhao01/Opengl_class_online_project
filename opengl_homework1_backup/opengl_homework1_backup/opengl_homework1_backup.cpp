//H17000621 赵国懿
/*
	use the class to encapsulate vertex code
*/
#include "pch.h"
#include "Shader.h"
#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <cmath>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, GLint width, GLint height);
void processInput(GLFWwindow* window);

const GLuint SRC_WIDTH = 800, SRC_HEIGHT = 600;

int main()
{
	/*
		glfw initial
	*/
	//--------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef _APPLE_
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	/*
		glfw window creation
	*/
	//-----------------------------
	GLFWwindow* window = glfwCreateWindow(SRC_WIDTH, SRC_HEIGHT, "H17000621", nullptr, nullptr);
	if (window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	//---------------------------------------
	//TODO   可以实现窗口大小的改变
	//---------------------------------------
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	/*
		glew
	*/
	//------------------------
	glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initial GLEW" << std::endl;
		return -1;
	}
	Shader shader("res/shaders/core.vs", "res/shaders/core.frag");
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	/*
		set up vertex data(and buffer) and configure vertex attribute
	*/
	//-------------------------------------------
	//float vertices[] = {
	//	//position             //color
	//	0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,      //TRIANGLE WITH COLOR
	//	-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   
	//	 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f
	//};

	float a = 0.9 / 8;

	float vertices[] = {
		//position              //color
		//-0.6f,0.3f,0.0f,		1.0f,0.0f,0.0f,
		//-0.9f,0.0f,0.0f,		1.0f,0.0f,0.0f,
		//-0.3f,0.0f,0.0f,		1.0f,0.0f,0.0f,
		//-0.9f,-0.6f,0.0f,		1.0f,0.0f,0.0f,
		//-0.3f,-0.6f,0.0f,		1.0f,0.0f,0.0f,

		//0.3f,0.0f,0.0f,			1.0f,0.0f,0.0f,
		//0.3f,-0.6f,0.0f,		1.0f,0.0f,0.0f,
		//0.6f,-0.3f,0.0f,		1.0f,0.0f,0.0f,
		//0.9f,0.0f,0.0f,			1.0f,0.0f,0.0f,
		//0.9f,-0.6f,0.0f,		1.0f,0.0f,0.0f

		//rectangle
		0.0f,0.8f,0.0f,		1.0f,0.0f,0.0f,0.5f,
		-0.3f,0.0f,0.0f,	1.0f,0.0f,0.0f,0.5f,
		0.3f,0.0f,0.0f,	1.0f,0.0f,0.0f,0.5f,
		
		0.0f,-0.8f,0.0f,	1.0f,0.0f,0.0f,0.5f,
		(float)(-a),0.5f,0.0f, 1.0f,0.0f,0.0f,0.5f,
		-0.5f,0.5f,0.0f,			1.0f,0.0f,0.0f,0.5f,
		
		0.5f,0.5f,0.0f, 1.0f,0.0f,0.0f,0.5f,
		(float)(a),0.5f,0.0f,	1.0f,0.0f,0.0f,0.5f,

		-0.5f,-0.5f,0.0f,	1.0f,0.0f,0.0f,0.5f,
		(float)(-a),-0.5f,0.0f,	1.0f,0.0f,0.0f,0.5f,

		(float)(a),-0.5f,0.0f,	1.0f,0.0f,0.0f,0.5f,
		0.5f,-0.5f,0.0f,		1.0f,0.0f,0.0f,0.5f
	};

	int indices[] = {
		//0,1,2,
		//1,3,4,
		//2,1,4,

		//5,6,7,
		//8,7,9,
		//7,6,9
		0,1,2,
		4,5,1,
		6,7,2,

		2,1,3,
		1,8,9,
		2,10,11
	};
	//VAO,VBO
	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//bind vertex first
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GL_FLOAT), (void*)0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GL_FLOAT)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	//EBO
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	/*
		render loop
	*/
	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//render with line

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		//use program
		shader.Use();
		//shader.setColorByTime();
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//glDrawArrays(GL_TRIANGLES,0,3);   //Use VAO to Draw
		glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	glfwTerminate();
	return 0;
}



void framebuffer_size_callback(GLFWwindow* window, GLint width, GLint height) {
	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
	//screenWidth = 0.5*screenWidth;
	//screenHeight = 0.5*screenHeight;
	glViewport(0, 0, screenWidth, screenHeight);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}