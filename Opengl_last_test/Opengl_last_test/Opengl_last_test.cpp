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

#include "SOIL2/SOIL2.h"
#include "SOIL2/stb_image.h"

#include "Shader.h"
#include "Camera.h"
#include "Light.h"

//set size of the window
//use prefix GL for basic data type & gl for function
//record the operations on the keyboard
void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mode);
//construct a camera
Camera camera(glm::vec3(0.0f, 0.0f, 2.0f));

void doMovement();

bool keys[1024];
const GLint WIDTH = 800, HEIGHT = 600;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 positionChange = glm::vec3(0.0f, 0.0f, 0.0f);

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

	Shader lightShader = Shader("res/shaders/light.vs", "res/shaders/light.frag");
	Shader shader = Shader("res/shaders/core.vs", "res/shaders/core.frag");

	Light light = Light();

	//use color
	//GLfloat vertices_two[] = {
	//	//使用索引									法向量
	//	-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 
	//	0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,	0.0f, 0.0f, -1.0f,
	//	0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,	0.0f, 0.0f, -1.0f,
	//	0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,	0.0f, 0.0f, -1.0f,
	//	-0.5f,  0.5f, -0.5f, 1.0f, 0.0f,0.0f,	0.0f, 0.0f, -1.0f,
	//	-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,	0.0f, 0.0f, -1.0f,

	//	-0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f,	0.0f, 0.0f, 1.0f,
	//	0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,	0.0f, 0.0f, 1.0f,
	//	0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,	0.0f, 0.0f, 1.0f,
	//	0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,	0.0f, 0.0f, 1.0f,
	//	-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,	0.0f, 0.0f, 1.0f,
	//	-0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f,	0.0f, 0.0f, 1.0f,

	//	-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,	-1.0f, 0.0f, 0.0f,
	//	-0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f,	-1.0f, 0.0f, 0.0f,
	//	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,	-1.0f, 0.0f, 0.0f,
	//	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,	-1.0f, 0.0f, 0.0f,
	//	-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,	-1.0f, 0.0f, 0.0f,
	//	-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,	-1.0f, 0.0f, 0.0f,

	//	0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,	1.0f, 0.0f, 0.0f,
	//	0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,	1.0f, 0.0f, 0.0f,
	//	0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,	1.0f, 0.0f, 0.0f,
	//	0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,	1.0f, 0.0f, 0.0f,
	//	0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,	1.0f, 0.0f, 0.0f,
	//	0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,	1.0f, 0.0f, 0.0f,

	//	-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f,	0.0f, -1.0f, 0.0f,
	//	0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,	0.0f, -1.0f, 0.0f,
	//	0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,	0.0f, -1.0f, 0.0f,
	//	0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,	0.0f, -1.0f, 0.0f,
	//	-0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f,	0.0f, -1.0f, 0.0f,
	//	-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f,	0.0f, -1.0f, 0.0f,

	//	-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 1.0f,	0.0f, 1.0f, 0.0f,
	//	0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,	0.0f, 1.0f, 0.0f,
	//	0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,	0.0f, 1.0f, 0.0f,
	//	0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,	0.0f, 1.0f, 0.0f,
	//	-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 1.0f,	0.0f, 1.0f,	0.0f,
	//	-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 1.0f,	0.0f, 1.0f, 0.0f
	//};

	//use map
	GLfloat vertices_two[] = {
		//position					normal			map
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, -1.0f,	 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,		0.0f, 0.0f, -1.0f,	 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f,		0.0f, 0.0f, -1.0f,	 1.0f, 1.0f,
		0.5f, 0.5f, -0.5f,		0.0f, 0.0f, -1.0f,	 1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f,		0.0f, 0.0f, -1.0f,	 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, -1.0f,	 0.0f, 0.0f,

		-0.5f, -0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	0.0f, 0.0f,
		0.5f, -0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	1.0f, 0.0f,
		0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	1.0f, 1.0f,
		0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	1.0f, 1.0f,
		-0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	0.0f, 0.0f,

		-0.5f, 0.5f, 0.5f,		-1.0f, 0.0f, 0.0f,	 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f,		-1.0f, 0.0f, 0.0f,	 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	-1.0f, 0.0f, 0.0f,	 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	-1.0f, 0.0f, 0.0f,	 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f,		-1.0f, 0.0f, 0.0f,	 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f,		-1.0f, 0.0f, 0.0f,	 1.0f, 0.0f,

		0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	1.0f, 0.0f,
		0.5f, 0.5f, -0.5f,		1.0f, 0.0f, 0.0f,	1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 0.0f,	0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 0.0f,	0.0f, 1.0f,
		0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	0.0f, 0.0f,
		0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,	0.0f, -1.0f, 0.0f,	 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,		0.0f, -1.0f, 0.0f,	 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f,		0.0f, -1.0f, 0.0f,	 1.0f, 0.0f,
		0.5f, -0.5f, 0.5f,		0.0f, -1.0f, 0.0f,	 1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f,		0.0f, -1.0f, 0.0f,	 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, -1.0f, 0.0f,	 0.0f, 1.0f,

		-0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	0.0f, 1.0f,
		0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	1.0f, 1.0f,
		0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
		0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	0.0f, 1.0f
	};
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)0); //read the position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT))); //read the color
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(6 * sizeof(GL_FLOAT))); //read the color
	glEnableVertexAttribArray(2);

	//解绑定
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//TEXTURE BIND
	GLuint texture[2];

	int width[2], height[2];

	//generate texture using array
	glGenTextures(1, texture);

	//Texture1
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char *image = SOIL_load_image("res/images/image1.jpg", &width[0], &height[0], 0, SOIL_LOAD_RGBA);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width[0], height[0], 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	//texture2
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char *image2 = SOIL_load_image("res/images/image2.jpg", &width[1], &height[1], 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width[1], height[1], 0, GL_RGBA, GL_UNSIGNED_BYTE, image2);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image2);
	glBindTexture(GL_TEXTURE_2D, 0);

	//game loop
	while (!glfwWindowShouldClose(window))
	{
		GLfloat currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		positionChange.x += deltaTime*6.0f;

		//camera.processKeyboard(RIGHT,deltaTime);
		//camera.positionChange(positionChange);

		//glfw always watch the events done by keyboard, mouse or others, but it will never do anything unless use glfwPollEvents
		glfwPollEvents();
		doMovement();
		//0~1   RGB opacity
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glViewport(0, 0, screenWidth, screenHeight);

		//refresh the depth
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//perspective projection but not rectangular projection
		glm::mat4 projection = glm::perspective(camera.GetZoom()
			, static_cast<GLfloat>(screenWidth) / static_cast<GLfloat>(screenHeight)
			, 0.1f, 1000.0f);
		glm::mat4 view = glm::mat4(1.0f);//diagonal matrix

		//glUseProgram(shaderProgram);
		lightShader.Use();

		glm::mat4 transform = glm::mat4(1.0f);
		transform = glm::scale(transform, glm::vec3(0.1f, 0.1f, 0.1f));//shrink
		//lightPos
		lightPos = glm::vec3(0.0f, 0.0f, 4.0f)+positionChange;//translate
		//lightPos = glm::rotate(lightPos,
		//			glm::radians(20.0f)*static_cast<GLfloat>(glfwGetTime()),
		//			glm::vec3(1.0f,1.0f,1.0f));//rotate 20 degree on xyz axis
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
		//texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		GLuint texLoc = glGetUniformLocation(shader.program, "texture1");
		glUniform1i(texLoc, 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture[1]);
		texLoc = glGetUniformLocation(shader.program, "texture2");
		glUniform1i(texLoc, 1);
		//light color
		glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
		lightColor.x = sin(glfwGetTime() * 2.0f);
		lightColor.y = sin(glfwGetTime() * 0.7f);
		lightColor.z = sin(glfwGetTime() * 1.3f);
		glUniform3f(glGetUniformLocation(shader.program, "lightColor"),
			lightColor.x, lightColor.y, lightColor.z);


		glBindVertexArray(VAO);
		// calculate the model matrix for each object and pass it to shader before drawing
		for (unsigned int i = 0; i < 10; i++)
		{
			//4X4 matrix
			transform = glm::mat4(1.0f);
			transform = glm::scale(transform, glm::vec3(0.5f, 0.5f, 0.5f));//scale
			//transform = glm::rotate(transform,
			//			glm::radians(20.0f)*static_cast<GLfloat>(glfwGetTime()),
			//			glm::vec3(1.0f,1.0f,1.0f));//rotate 20 degree on xyz axis
			//transform = glm::translate(transform, glm::vec3(3.0f,0.0f,0.0f)); //translate 3,0,0
			transform = glm::translate(transform, cubePositions[i]+positionChange);
			float angle = 20.0f * i;
			//transform = glm::rotate(transform, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

			GLuint transLoc = glGetUniformLocation(shader.program, "model");
			//4 float vector
			glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(transform));

			glUniformMatrix4fv(glGetUniformLocation(shader.program, "view"),
				1, GL_FALSE, glm::value_ptr(view));
			glUniformMatrix4fv(glGetUniformLocation(shader.program, "projection"),
				1, GL_FALSE, glm::value_ptr(projection));
			//glUniformMatrix4fv(glGetUniformLocation(shader.program,"model"),
			//					1, GL_FALSE, glm::value_ptr(model));

			glUniform1f(glGetUniformLocation(shader.program, "p"), 64.0f);
			glUniform3f(glGetUniformLocation(shader.program, "LightPos"), lightPos.x, lightPos.y, lightPos.z);

			glUniform3f(glGetUniformLocation(shader.program, "ViewPos"),
				camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);


			glDrawArrays(GL_TRIANGLES, 0, 36); 
		}
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		//双缓存模式
		glfwSwapBuffers(window);
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteTextures(sizeof(texture), texture);
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