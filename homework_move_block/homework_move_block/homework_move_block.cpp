//TODO week3

/*
	encapsulation
*/
#include "pch.h"
#include <iostream>
#include <windows.h> 
//GLEW
#define GLEW_STATIC//使用静态库，静态库效率更高
#include <GL/glew.h>
//GLFW
#include <GLFW/glfw3.h>

#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#include "glm/glm/gtc/type_ptr.hpp"

#include "Shader.h"
#include "Camera.h"
//set size of the window
//use prefix GL for basic data type & gl for function
//record the operations on the keyboard
void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mode);
//construct a camera
Camera camera(glm::vec3(0.0f, 0.0f, 10.0f));

//cemra movement
void doMovement();
//block movement
void moveBlock(GLfloat* moveRight, GLfloat* jump, GLFWwindow* window);
//replay

//register the key operations 
bool keys[100000][1024];
bool pressed[100000];

int keysCount = 0;
int max = 0;

const GLint WIDTH = 800, HEIGHT = 600;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

//每次跳跃开始时间
GLfloat beginTime = 0;
int isJumping = 0;
int marker = 0;
//record the operation
//int records[10000];
//GLfloat recordTime[10000];
//GLfloat recordEndTime[10000];
//int records_count = 0;
//GLfloat startTime = 0;

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

	Shader shader = Shader("res/shaders/core.vs", "res/shaders/core.frag");

	GLfloat vertices_two[] = {
		//使用索引
		-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 0.0f,0.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 1.0f
	};

	//transfer the data
	GLuint VAO, VBO;// vertex array  object & vertext buffer object
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//bind
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_two), vertices_two, GL_STATIC_DRAW);

	//location=0;  3; GL_FLOAT(vec3, the type of location); GL_FALSE;  the gap to gain address; head of address 
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (GLvoid*)0); //read the position
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(GL_FLOAT),(GLvoid*)(3*sizeof(GL_FLOAT))); //read the color
	//glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (GLvoid*)0); //read the position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT))); //read the color
	glEnableVertexAttribArray(1);

	//解绑定
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glm::mat4 view = glm::mat4(1.0f);//diagonal matrix

	//perspective projection but not rectangular projection
	glm::mat4 projection = glm::perspective(camera.GetZoom()
		, static_cast<GLfloat>(screenWidth) / static_cast<GLfloat>(screenHeight)
		, 0.1f, 1000.0f);

	GLfloat moveRightStep = 0;
	GLfloat jumpStep = 0;
	//game loop
	while (!glfwWindowShouldClose(window))
	{
		GLfloat currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		//glfw always watch the events done by keyboard, mouse or others, but it will never do anything unless use glfwPollEvents
		glfwPollEvents();

		//control the camera
		//doMovement();
		
		//0~1   RGB opacity
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glViewport(0, 0, screenWidth, screenHeight);

		//refresh the depth
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//glUseProgram(shaderProgram);
		shader.Use();
		//4X4 matrix
		glm::mat4 transform = glm::mat4(1.0f);
		transform = glm::scale(transform, glm::vec3(0.2f, 0.2f, 0.2f));
		transform = glm::rotate(transform, glm::radians(20.0f)*static_cast<GLfloat>(glfwGetTime()), glm::vec3(1.0f, 1.0f, 1.0f));
		transform = glm::translate(transform, glm::vec3(3.0f, 0.0f, 0.0f));

		GLuint transLoc = glGetUniformLocation(shader.program, "model");
		//4 float vector
		glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(transform));

		view = camera.getViewMatrix();
		glUniformMatrix4fv(glGetUniformLocation(shader.program, "view"),
			1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(shader.program, "projection"),
			1, GL_FALSE, glm::value_ptr(projection));
		//glUniformMatrix4fv(glGetUniformLocation(shader.program,"model"),
		//					1, GL_FALSE, glm::value_ptr(model));


		GLfloat moveRight = glGetUniformLocation(shader.program, "moveRight");
		GLfloat jump = glGetUniformLocation(shader.program, "jump");

		moveBlock(&moveRightStep, &jumpStep,window);
		glUniform1f(moveRight, moveRightStep);
		glUniform1f(jump, jumpStep);
		
		if (keysCount == max && max != 0) {
			max = 0;
		}
		keysCount++;


		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
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
	if (key >= 0 && key < 1024 && max == 0) {
		if (action == GLFW_PRESS) {
			pressed[key] = true;
		}
		else if (action == GLFW_RELEASE) {
			pressed[key] = false;
		}
		keys[keysCount][key] = pressed[key];
	}
}

//void doMovement() {
//	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP]) {
//		camera.processKeyboard(FORWARD, deltaTime);
//	}
//	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN]) {
//		camera.processKeyboard(BACKWARD, deltaTime);
//	}
//	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT]) {
//		camera.processKeyboard(LEFT, deltaTime);
//	}
//	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT]) {
//		camera.processKeyboard(RIGHT, deltaTime);
//	}
//}

void moveBlock(GLfloat* moveRightStep, GLfloat* jumpStep, GLFWwindow* window) {
	GLfloat time_count = 0;
	//if (startTime == 0) {
	//	startTime = glfwGetTime();
	//}
	if (keys[keysCount][GLFW_KEY_D] || keys[keysCount][GLFW_KEY_RIGHT]) {
		*moveRightStep += deltaTime * 6.0f;
		//camera.processKeyboard(RIGHT, deltaTime);

		//records[records_count] = GLFW_KEY_D;
		//recordTime[records_count++] = glfwGetTime()-startTime;
	}
	if (keys[keysCount][GLFW_KEY_A] || keys[keysCount][GLFW_KEY_LEFT]) {
		*moveRightStep -= deltaTime * 6.0f;
		//camera.processKeyboard(LEFT, deltaTime);

		//records[records_count] = GLFW_KEY_A;
		//recordTime[records_count++] = glfwGetTime() - startTime;
	}

	if (keys[keysCount][GLFW_KEY_SPACE]) {
		//不在跳跃但按下去了
		if (!isJumping) {
			isJumping = 1;
			beginTime = glfwGetTime();
			//records[records_count] = GLFW_KEY_SPACE;
			//recordTime[records_count++] = glfwGetTime() - startTime;
		}
		//在跳跃但按下去了
		else {
			//do nothing
		}
	}
	//如果正在跳跃
	if (isJumping) {
		marker = 1;
		time_count = glfwGetTime()-beginTime;
		*jumpStep = 3.0f*time_count - 0.5f*5.0f*pow(time_count, 2);
	}
	//如果跳跃回到水平线
	if (marker==1&&(*jumpStep-0)<0.000001f) {
		isJumping = 0;
		marker = 0;
	}
	if (keys[keysCount][GLFW_KEY_R]) {
		*moveRightStep = 0;
		*jumpStep = 0;
		max = keysCount;
		keysCount = 0;
	}

	//if (glfwGetKey(window,GLFW_KEY_A) == GLFW_RELEASE || glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE || glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {

	//	recordEndTime[records_count++] = glfwGetTime() - startTime;
	//}
}
//





//fail 

//void replay(Shader& shader) {
//	if (keys[GLFW_KEY_R]) {
//		GLfloat moveRightStep = 0;
//		GLfloat jumpStep = 0;
//		GLfloat moveRight = glGetUniformLocation(shader.program, "moveRight");
//		GLfloat jump = glGetUniformLocation(shader.program, "jump");
//		glUniform1f(moveRight, moveRightStep);
//		glUniform1f(jump, jumpStep);
//		std::cout << jumpStep;
//		//GLfloat replayStartTime = glfwGetTime();
//		//int replayCount = 0;
//		//GLfloat moveRightStep = 0;
//		//GLfloat jumpStep = 0;
//		//GLfloat moveRight = glGetUniformLocation(shader.program, "moveRight");
//		//GLfloat jump = glGetUniformLocation(shader.program, "jump");
//		//glUniform1f(moveRight, moveRightStep);
//		//glUniform1f(jump, jumpStep);
//		//while (records[replayCount]) {
//		//	GLfloat currentTime = glfwGetTime();
//		//	deltaTime = currentTime - lastTime;
//		//	lastTime = currentTime;
//		//	GLfloat moveRight = glGetUniformLocation(shader.program, "moveRight");
//		//	GLfloat jump = glGetUniformLocation(shader.program, "jump");
//		//	if (abs(glfwGetTime() - replayStartTime - recordTime[replayCount])<0.01f) {
//		//			std::cout << recordTime[replayCount] << "---";
//		//			std::cout << glfwGetTime() - replayStartTime<<"\n";
//		//			replayMoveBlock(&moveRightStep, &jumpStep, records[replayCount]);
//		//			glUniform1f(moveRight, moveRightStep);
//		//			glUniform1f(jump, jumpStep);
//		//		replayCount++;
//
//		//	}
//		//}
//	}
//	if (keys[GLFW_KEY_C]) {
//		//清零
//		startTime = 0;
//		records_count = 0;
//		memset(records, 0, sizeof(records));
//	}
//}
//
//void replayMoveBlock(GLfloat* moveRightStep, GLfloat* jumpStep,int key) {
//	GLfloat time_count = 0;
//	if (startTime == 0) {
//		startTime = glfwGetTime();
//	}
//	if (key==GLFW_KEY_D || key==GLFW_KEY_RIGHT) {
//		*moveRightStep += deltaTime * 6.0f;
//		//camera.processKeyboard(RIGHT, deltaTime);
//	}
//	if (key==GLFW_KEY_A || key==GLFW_KEY_LEFT) {
//		*moveRightStep -= deltaTime * 6.0f;
//		//camera.processKeyboard(LEFT, deltaTime);
//	}
//
//	if (key==GLFW_KEY_SPACE) {
//		//不在跳跃但按下去了
//		if (!isJumping) {
//			isJumping = 1;
//			beginTime = glfwGetTime();
//		}
//		//在跳跃但按下去了
//		else {
//			//do nothing
//		}
//	}
//	//如果正在跳跃
//	if (isJumping) {
//		marker = 1;
//		time_count = glfwGetTime() - beginTime;
//		*jumpStep = 3.0f*time_count - 0.5f*5.0f*pow(time_count, 2);
//	}
//	//如果跳跃回到水平线
//	if (marker == 1 && (*jumpStep - 0) < 0.000001f) {
//		isJumping = 0;
//		marker = 0;
//	}
//}


////方法二
////TODO week3
//
/////*
////	encapsulation
////*/
//#include "pch.h"
//#include <iostream>
//#include <windows.h> 
////GLEW
//#define GLEW_STATIC//使用静态库，静态库效率更高
//#include <GL/glew.h>
////GLFW
//#include <GLFW/glfw3.h>
//
//#include "glm/glm/glm.hpp"
//#include "glm/glm/gtc/matrix_transform.hpp"
//#include "glm/glm/gtc/type_ptr.hpp"
//
//#include "SOIL2/SOIL2.h"
//#include "SOIL2/stb_image.h"
//
//#include "Shader.h"
//#include "Camera.h"
////set size of the window
////use prefix GL for basic data type & gl for function
////record the operations on the keyboard
//void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mode);
////construct a camera
//Camera camera(glm::vec3(0.0f, 0.0f, 10.0f));
//
////cemra movement
//void doMovement();
////block movement
//void moveBlock(GLfloat* moveRight, GLfloat* jump, GLFWwindow* window);
////replay
//void replay(Shader& shader, GLuint VAO, GLFWwindow* window, GLuint screenWidth, GLuint screenHeight);
//void replayMoveBlock(GLfloat* moveRightStep, GLfloat* jumpStep, int key);
//
////register the key operations 
//bool keys[1024];
//
//const GLint WIDTH = 800, HEIGHT = 600;
//
//GLfloat deltaTime = 0.0f;
//GLfloat lastTime = 0.0f;
//
////每次跳跃开始时间
//GLfloat beginTime = 0;
//int isJumping = 0;
//int marker = 0;
////record the operation
//int records[10000];
//GLfloat recordTime[10000];
//GLfloat recordEndTime[10000];
//int records_count = 0;
//GLfloat startTime = 0;
//
//GLfloat moveRightStep = 0;
//GLfloat jumpStep = 0;
//
//int main()
//{
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//主版本号
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//副版本号
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//核心模式
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // must for Mac
//	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
//	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "H17000621", nullptr,
//		nullptr);//create the window
//
//	// next two lines are for mac retina display
//	int screenWidth, screenHeight;
//	//获取屏幕尺寸   并   储存在sreenWidth 和 screenHeight里
//	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
//	//glViewport(0, 0, screenWidth, screenHeight);
//
//	if (nullptr == window)
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();//end glfw
//		return -1;//end the program
//	}
//	//使window变成当前窗口
//	glfwMakeContextCurrent(window);
//	//register the keyboard operation functions
//	glfwSetKeyCallback(window, keyCallBack);
//
//	//init glew
//	glewExperimental = GL_TRUE;
//	//if init success, return 0, else return 1;   that's opposite to glfw
//	if (GLEW_OK != glewInit())
//	{
//		std::cout << "Failed to initialise GLEW" << std::endl;
//		return -1;
//	}
//	//视图（利用真缓存的信息，将图形映射到终端设备上的过程）
//	//startX, startY, width, height;
//	//start from left bottom
//
//	/*
//		blend to realise opacity effect
//	*/
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	/*
//		open the depth test
//	*/
//	glEnable(GL_DEPTH_TEST);
//	//glDepthFunc(GL_LESS);
//	glDepthFunc(GL_LEQUAL);
//
//	Shader shader = Shader("res/shaders/core.vs", "res/shaders/core.frag");
//
//	GLfloat vertices_two[] = {
//		//使用索引
//		-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
//		0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
//		0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
//		0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
//		-0.5f,  0.5f, -0.5f, 1.0f, 0.0f,0.0f,
//		-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
//
//		-0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
//		0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
//		0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
//		0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
//		-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
//		-0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
//
//		-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
//		-0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
//		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
//		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
//		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
//		-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
//
//		0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
//		0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
//		0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
//		0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
//		0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
//		0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
//
//		-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f,
//		0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
//		0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
//		0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
//		-0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f,
//		-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f,
//
//		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
//		0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
//		0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
//		0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
//		-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
//		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 1.0f
//	};
//
//	//transfer the data
//	GLuint VAO, VBO;// vertex array  object & vertext buffer object
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//
//	//bind
//	glBindVertexArray(VAO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//
//	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_two), vertices_two, GL_STATIC_DRAW);
//
//	//location=0;  3; GL_FLOAT(vec3, the type of location); GL_FALSE;  the gap to gain address; head of address 
//	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (GLvoid*)0); //read the position
//	//glEnableVertexAttribArray(0);
//	//glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(GL_FLOAT),(GLvoid*)(3*sizeof(GL_FLOAT))); //read the color
//	//glEnableVertexAttribArray(1);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (GLvoid*)0); //read the position
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT))); //read the color
//	glEnableVertexAttribArray(1);
//
//	//解绑定
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
//
//	glm::mat4 view = glm::mat4(1.0f);//diagonal matrix
//
//	//perspective projection but not rectangular projection
//	glm::mat4 projection = glm::perspective(camera.GetZoom()
//		, static_cast<GLfloat>(screenWidth) / static_cast<GLfloat>(screenHeight)
//		, 0.1f, 1000.0f);
//
//
//	//game loop
//	while (!glfwWindowShouldClose(window))
//	{
//		GLfloat currentTime = glfwGetTime();
//		deltaTime = currentTime - lastTime;
//		lastTime = currentTime;
//
//		//glfw always watch the events done by keyboard, mouse or others, but it will never do anything unless use glfwPollEvents
//		glfwPollEvents();
//
//		//control the camera
//		//doMovement();
//
//		//0~1   RGB opacity
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//		glViewport(0, 0, screenWidth, screenHeight);
//
//		//refresh the depth
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		//glUseProgram(shaderProgram);
//		shader.Use();
//		//4X4 matrix
//		glm::mat4 transform = glm::mat4(1.0f);
//		transform = glm::scale(transform, glm::vec3(0.2f, 0.2f, 0.2f));
//		transform = glm::rotate(transform, glm::radians(20.0f)*static_cast<GLfloat>(glfwGetTime()), glm::vec3(1.0f, 1.0f, 1.0f));
//		transform = glm::translate(transform, glm::vec3(3.0f, 0.0f, 0.0f));
//
//		GLuint transLoc = glGetUniformLocation(shader.program, "model");
//		//4 float vector
//		glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(transform));
//
//		view = camera.getViewMatrix();
//		glUniformMatrix4fv(glGetUniformLocation(shader.program, "view"),
//			1, GL_FALSE, glm::value_ptr(view));
//		glUniformMatrix4fv(glGetUniformLocation(shader.program, "projection"),
//			1, GL_FALSE, glm::value_ptr(projection));
//		//glUniformMatrix4fv(glGetUniformLocation(shader.program,"model"),
//		//					1, GL_FALSE, glm::value_ptr(model));
//
//
//		GLfloat moveRight = glGetUniformLocation(shader.program, "moveRight");
//		GLfloat jump = glGetUniformLocation(shader.program, "jump");
//
//		moveBlock(&moveRightStep, &jumpStep, window);
//		glUniform1f(moveRight, moveRightStep);
//		glUniform1f(jump, jumpStep);
//
//		replay(shader, VAO, window,screenWidth,screenHeight);
//
//		glBindVertexArray(VAO);
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//		glBindVertexArray(0);
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//
//		//双缓存模式
//		glfwSwapBuffers(window);
//	}
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);
//
//	//release the source
//	glfwTerminate();
//	return 0;
//}
//
//
//void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mode)
//{
//	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
//		glfwSetWindowShouldClose(window, GL_TRUE);
//	}
//	if (key >= 0 && key < 1024 ) {
//		if (action == GLFW_PRESS) {
//			keys[key] = true;
//		}
//		else if (action == GLFW_RELEASE) {
//			keys[key] = false;
//		}
//	}
//}
//
////void doMovement() {
////	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP]) {
////		camera.processKeyboard(FORWARD, deltaTime);
////	}
////	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN]) {
////		camera.processKeyboard(BACKWARD, deltaTime);
////	}
////	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT]) {
////		camera.processKeyboard(LEFT, deltaTime);
////	}
////	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT]) {
////		camera.processKeyboard(RIGHT, deltaTime);
////	}
////}
//
//void moveBlock(GLfloat* moveRightStep, GLfloat* jumpStep, GLFWwindow* window) {
//	GLfloat time_count = 0;
//	//if (startTime == 0) {
//	//	startTime = glfwGetTime();
//	//}
//	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT]) {
//		*moveRightStep += deltaTime * 6.0f;
//		//camera.processKeyboard(RIGHT, deltaTime);
//
//		records[records_count] = GLFW_KEY_D;
//		recordTime[records_count++] = glfwGetTime()-startTime;
//	}
//	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT]) {
//		*moveRightStep -= deltaTime * 6.0f;
//		//camera.processKeyboard(LEFT, deltaTime);
//
//		records[records_count] = GLFW_KEY_A;
//		recordTime[records_count++] = glfwGetTime() - startTime;
//	}
//
//	if (keys[GLFW_KEY_SPACE]) {
//		//不在跳跃但按下去了
//		if (!isJumping) {
//			isJumping = 1;
//			beginTime = glfwGetTime();
//			records[records_count] = GLFW_KEY_SPACE;
//			recordTime[records_count++] = glfwGetTime() - startTime;
//		}
//		//在跳跃但按下去了
//		else {
//			//do nothing
//		}
//	}
//	//如果正在跳跃
//	if (isJumping) {
//		marker = 1;
//		time_count = glfwGetTime() - beginTime;
//		*jumpStep = 3.0f*time_count - 0.5f*5.0f*pow(time_count, 2);
//	}
//	//如果跳跃回到水平线
//	if (marker == 1 && (*jumpStep - 0) < 0.000001f) {
//		isJumping = 0;
//		marker = 0;
//	}
//
//	//if (glfwGetKey(window,GLFW_KEY_A) == GLFW_RELEASE || glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE || glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
//
//	//	recordEndTime[records_count++] = glfwGetTime() - startTime;
//	//}
//}
//
//
//
//
//
//
////fail 
//
//void replay(Shader& shader, GLuint VAO, GLFWwindow* window, GLuint screenWidth, GLuint screenHeight) {
//	if (keys[GLFW_KEY_R]) {
//		//moveRightStep = 0;
//		//jumpStep = 0;
//		//GLfloat moveRight = glGetUniformLocation(shader.program, "moveRight");
//		//GLfloat jump = glGetUniformLocation(shader.program, "jump");
//		//glUniform1f(moveRight, moveRightStep);
//		//glUniform1f(jump, jumpStep);
//		//std::cout << jumpStep;
//		GLfloat replayStartTime = glfwGetTime();
//		int replayCount = 0;
//		moveRightStep = 0;
//		jumpStep = 0;
//		GLfloat moveRight = glGetUniformLocation(shader.program, "moveRight");
//		GLfloat jump = glGetUniformLocation(shader.program, "jump");
//		glUniform1f(moveRight, moveRightStep);
//		glUniform1f(jump, jumpStep);
//		while (records[replayCount]) {
//			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//			glClear(GL_COLOR_BUFFER_BIT);
//			glViewport(0, 0, screenWidth, screenHeight);
//			//refresh the depth
//			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//			GLfloat currentTime = glfwGetTime();
//			deltaTime = currentTime - lastTime;
//			lastTime = currentTime;
//			GLfloat moveRight = glGetUniformLocation(shader.program, "moveRight");
//			GLfloat jump = glGetUniformLocation(shader.program, "jump");
//			if (abs(glfwGetTime() - replayStartTime - recordTime[replayCount])<0.01f) {
//					std::cout << records[replayCount] << "---";
//					std::cout << glfwGetTime() - replayStartTime<<"---";
//					replayMoveBlock(&moveRightStep, &jumpStep, records[replayCount]);
//					glUniform1f(moveRight, moveRightStep);
//					glUniform1f(jump, jumpStep);
//				replayCount++;
//			}
//			glBindVertexArray(VAO);
//			glDrawArrays(GL_TRIANGLES, 0, 36);
//			glBindVertexArray(0);
//			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//			glfwSwapBuffers(window);
//		}
//	}
//	if (keys[GLFW_KEY_C]) {
//		//清零
//		startTime = 0;
//		records_count = 0;
//		memset(records, 0, sizeof(records));
//	}
//}
//
//void replayMoveBlock(GLfloat* moveRightStep, GLfloat* jumpStep,int key) {
//	GLfloat time_count = 0;
//	if (startTime == 0) {
//		startTime = glfwGetTime();
//	}
//	if (key==GLFW_KEY_D || key==GLFW_KEY_RIGHT) {
//		*moveRightStep += deltaTime * 6.0f;
//		//camera.processKeyboard(RIGHT, deltaTime);
//		//std::cout << "moveRightStep"<<moveRightStep <<"\n";
//	}
//	if (key==GLFW_KEY_A || key==GLFW_KEY_LEFT) {
//		*moveRightStep -= deltaTime * 6.0f;
//		//camera.processKeyboard(LEFT, deltaTime);
//	}
//
//	if (key==GLFW_KEY_SPACE) {
//		//不在跳跃但按下去了
//		if (!isJumping) {
//			isJumping = 1;
//			beginTime = glfwGetTime();
//		}
//		//在跳跃但按下去了
//		else {
//			//do nothing
//		}
//	}
//	//如果正在跳跃
//	if (isJumping) {
//		marker = 1;
//		time_count = glfwGetTime() - beginTime;
//		*jumpStep = 3.0f*time_count - 0.5f*5.0f*pow(time_count, 2);
//	}
//	//如果跳跃回到水平线
//	if (marker == 1 && (*jumpStep - 0) < 0.000001f) {
//		isJumping = 0;
//		marker = 0;
//	}
//}