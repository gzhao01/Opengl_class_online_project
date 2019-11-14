//TODO week3

/*
	encapsulation
*/
#include "pch.h"

#include <iostream>
//GLEW
#define GLEW_STATIC//使用静态库，静态库效率更高
#include <GL/glew.h>
//GLFW
#include <GLFW/glfw3.h>

#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#include "glm/glm/gtc/type_ptr.hpp"
#include "glm/glm/gtx/rotate_vector.hpp"

#include "Shader.h"
#include "Camera.h"
#include "Light.h"
#include "Model.h"
#include "Mesh.h"

//set size of the window
//use prefix GL for basic data type & gl for function
//record the operations on the keyboard
void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mode);
//construct a camera
Camera camera(glm::vec3(0.0f, 0.0f, 2.0f));

void MouseCallBack(GLFWwindow *window, double xPos, double yPos);
void ScrollCallBack(GLFWwindow *window, double xOffset, double yOffset);
void doMovement();

bool keys[1024];
const GLint WIDTH = 800, HEIGHT = 600;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 0.0f);
GLfloat lastX = WIDTH / 2;
GLfloat lastY = HEIGHT / 2;
GLfloat lastZoom = 45.0f;
bool firstMouse = true;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//主版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//副版本号
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//核心模式
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // must for Mac
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "H17000621", nullptr,
		nullptr);//create the window

	// next two lines are for mac retina display
	int screenWidth, screenHeight;
	//获取屏幕尺寸   并   储存在sreenWidth 和 screenHeight里
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
	//glViewport(0, 0, screenWidth, screenHeight);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();//end glfw
		return -1;//end the program
	}
	//使window变成当前窗口
	glfwMakeContextCurrent(window);
	//register the keyboard operation functions
	glfwSetKeyCallback(window, keyCallBack);
	glfwSetCursorPosCallback(window,MouseCallBack);
	glfwSetScrollCallback(window, ScrollCallBack);
	//init glew
	glewExperimental = GL_TRUE;
	//if init success, return 0, else return 1;   that's opposite to glfw
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialise GLEW" << std::endl;
		return -1;
	}
	//视图（利用真缓存的信息，将图形映射到终端设备上的过程）
	//startX, startY, width, height;
	//start from left bottom

	/*
		blend to realise opacity effect
	*/
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	/*
		open the depth test
	*/
	glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);
	glDepthFunc(GL_LEQUAL);

	Shader lightShader = Shader("res/shaders/light.vs", "res/shaders/light.frag");

	Light light = Light();

	Shader shader = Shader("res/shaders/core.vs", "res/shaders/core.frag");

	Model robot("res/models/nanosuit.obj");

	GLfloat vertices_two[] = {
		//使用索引									法向量
		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,	0.0f, 0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,	0.0f, 0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,	0.0f, 0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 0.0f,0.0f,	0.0f, 0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,	0.0f, 0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f,	0.0f, 0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,	0.0f, 0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,	0.0f, 0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,	0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,	0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f,	0.0f, 0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,	-1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f,	-1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,	-1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,	-1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,	-1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,	-1.0f, 0.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,	1.0f, 0.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,	1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,	1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,	1.0f, 0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,	1.0f, 0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,	1.0f, 0.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f,	0.0f, -1.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,	0.0f, -1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,	0.0f, -1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,	0.0f, -1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f,	0.0f, -1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f,	0.0f, -1.0f, 0.0f,

		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 1.0f,	0.0f, 1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,	0.0f, 1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,	0.0f, 1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,	0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 1.0f,	0.0f, 1.0f,	0.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 1.0f,	0.0f, 1.0f, 0.0f
	};

	//transfer the data
	GLuint VAO, VBO;// vertex array  object & vertext buffer object
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//bind
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_two), vertices_two, GL_STATIC_DRAW);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GL_FLOAT), (GLvoid*)0); //read the position
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT))); //read the color
	//glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GL_FLOAT), (GLvoid*)(6 * sizeof(GL_FLOAT))); //read the color
	glEnableVertexAttribArray(2);

	//解绑定
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//game loop
	while (!glfwWindowShouldClose(window))
	{
		GLfloat currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		//glfw always watch the events done by keyboard, mouse or others, but it will never do anything unless use glfwPollEvents
		glfwPollEvents();
		doMovement();
		//0~1   RGB opacity
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glViewport(0, 0, screenWidth, screenHeight);

		//refresh the depth
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//glUseProgram(shaderProgram);
		lightShader.Use();

		glm::mat4 view = glm::mat4(1.0f);//diagonal matrix
		//perspective projection but not rectangular projection
		glm::mat4 projection = glm::perspective(camera.GetZoom()
			, static_cast<GLfloat>(screenWidth) / static_cast<GLfloat>(screenHeight)
			, 0.1f, 1000.0f);

		glm::mat4 transform = glm::mat4(1.0f);
		transform = glm::scale(transform, glm::vec3(0.1f, 0.1f, 0.1f));//shrink
		lightPos = glm::vec3(20.0f, 0.0f, 0.0f);//translate
		lightPos = glm::rotate(lightPos,
			glm::radians(20.0f)*static_cast<GLfloat>(glfwGetTime()),
			glm::vec3(1.0f, 1.0f, 1.0f));//rotate 20 degree on xyz axis
		transform = glm::translate(transform, lightPos);
		view = camera.getViewMatrix();
		glUniformMatrix4fv(glGetUniformLocation(lightShader.program, "model"),
			1, GL_FALSE, glm::value_ptr(transform));
		glUniformMatrix4fv(glGetUniformLocation(lightShader.program, "view"),
			1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(lightShader.program, "projection"),
			1, GL_FALSE, glm::value_ptr(projection));
		light.Draw();

		shader.Use();
		//4X4 matrix
		transform = glm::mat4(1.0f);
		transform = glm::scale(transform, glm::vec3(0.2f, 0.2f, 0.2f));//scale

		GLuint transLoc = glGetUniformLocation(shader.program, "model");
		//4 float vector
		glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(transform));

		glUniformMatrix4fv(glGetUniformLocation(shader.program, "view"),
			1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(shader.program, "projection"),
			1, GL_FALSE, glm::value_ptr(projection));
	
		glUniform1f(glGetUniformLocation(shader.program, "materail.shiniess"), 64.0f);
		glUniform3f(glGetUniformLocation(shader.program, "LightPos"), lightPos.x, lightPos.y, lightPos.z);

		glUniform3f(glGetUniformLocation(shader.program, "ViewPos"),
			camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		robot.Draw(shader);

		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		//双缓存模式
		glfwSwapBuffers(window);
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	//release the source
	glfwTerminate();
	return 0;
}


void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS) {
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE) {
			keys[key] = false;
		}
	}
}

void doMovement() {
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP]) {
		camera.processKeyboard(FORWARD, deltaTime);
	}
	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN]) {
		camera.processKeyboard(BACKWARD, deltaTime);
	}
	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT]) {
		camera.processKeyboard(LEFT, deltaTime);
	}
	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT]) {
		camera.processKeyboard(RIGHT, deltaTime);
	}
}

//mouse control move
void MouseCallBack(GLFWwindow *window, double xPos, double yPos) {
	if (firstMouse) {
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}
	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}

//mouse control zoom
void ScrollCallBack(GLFWwindow *window, double xOffset, double yOffset) {
	camera.ProcessMouseZoom(yOffset);
}
