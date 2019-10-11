//#include "pch.h"
//#include <iostream>
////GLEW
//#define GLEW_STATIC//使用静态库，静态库效率更高
//#include <GL/glew.h>
////GLFW
//#include <GLFW/glfw3.h>
////set size of the window
////use prefix GL for basic data type & gl for function
//const GLint WIDTH = 800, HEIGHT = 600;
//
//const GLchar*  vertexShaderSource = "#version 330 core \n"//version
//"layout(location = 0) in vec3 position;\n"
//"void main()\n"
//"{\n"
//"gl_Position = vec4(position.x,position.y,position.z, 1.0f);\n"
//"}";
//
//const GLchar* fragmentShaderSource = "#version 330 core\n"
//"out vec4 color;\n"
//"void main()\n"
//"{\n"
//"color = vec4(1.0f,0.5f,0.2f,1.0f);\n"
//"}";
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
//	if (nullptr == window)
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();//end glfw
//		return -1;//end the program
//	}
//	//使window变成当前窗口
//	glfwMakeContextCurrent(window);
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
//	glViewport(0, 0, screenWidth, screenHeight);
//
//	
//	//compile shader
//	//创造一个储存的文件
//	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
//	//将源代码放入文件
//	glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
//	//进行编译
//	glCompileShader(vertexShader);
//
//	//check whether compile succeed
//	GLint success;
//	GLchar infoLog[512];
//	glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
//	if (!success) {
//		glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
//		std::cout << "ERROE::SHADER::VERTEX::COMPILATION_FAILED\N" << infoLog << std::endl;
//	}
//
//		//创造一个储存的文件
//	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//	//将源代码放入文件
//	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//	//进行编译
//	glCompileShader(fragmentShader);
//
//	//check whether compile succeed
//	GLint fragment_success;
//	GLchar fragment_infoLog[512];
//	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragment_success);
//	if (!fragment_success) {
//		glGetShaderInfoLog(fragmentShader, 512, NULL, fragment_infoLog);
//		std::cout << "ERROE::SHADER::FRAGMENT::COMPILATION_FAILED\N" << fragment_infoLog << std::endl;
//	}
//
//	//create a link and link the code
//	GLuint shaderProgram = glCreateProgram();
//	glAttachShader(shaderProgram,vertexShader);
//	glAttachShader(shaderProgram,fragmentShader);
//	glLinkProgram(shaderProgram);
//
//	//check whether link succeed
//	GLint link_success;
//	GLchar link_infoLog[512];
//	glGetProgramiv(shaderProgram, GL_COMPILE_STATUS, &link_success);
//	if (!link_success) {
//		glGetProgramInfoLog(shaderProgram, 512, NULL, link_infoLog);
//		std::cout << "ERROE::SHADER::PROGRAM::LINKING_FAILED\N" << link_infoLog << std::endl;
//	}
//	glDeleteShader(vertexShader);
//	glDeleteShader(fragmentShader);
//
//	//the vertex info
//	GLfloat vertices[] = {
//		-0.5f,-0.5f,0.0f,
//		0.5f,-0.5f,0.0f,
//		0.0f,0.5f,0.0f
//	};
//	
//	//transfer the data
//	GLuint VAO, VBO;// vertex array  object & vertext buffer object
//	glGenVertexArrays(1,&VAO);
//	glGenBuffers(1,&VBO);
//
//	//bind
//	glBindVertexArray(VAO);
//	glBindBuffer(GL_ARRAY_BUFFER,VBO);
//
//	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
//
//	//location=0;  3; GL_FLOAT(vec3, the type of location); GL_FALSE;  the gap to gain address; head of address 
//	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(GL_FLOAT),(GLvoid*)0);
//	glEnableVertexAttribArray(0);
//
//	//解绑定
//	glBindBuffer(GL_ARRAY_BUFFER,0);
//	glBindVertexArray(0);
//
//
//	//game loop
//	while (!glfwWindowShouldClose(window))
//	{
//		//glfw always watch the events done by keyboard, mouse or others, but it will never do anything unless use glfwPollEvents
//		glfwPollEvents();
//		//0~1   RGB opacity
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		glUseProgram(shaderProgram);
//		glBindVertexArray(VAO);
//		glDrawArrays(GL_TRIANGLES,0,3);
//		glBindVertexArray(0);
//
//		//双缓存模式
//		glfwSwapBuffers(window);
//	}
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1,&VBO);
//
//	//release the source
//	glfwTerminate();
//	return 0;
//}



//---------------------------------------------------------------
////practice
//#include "pch.h"
//#include <iostream>
//
//#define GLEW_STATIC
//#include <GL/glew.h>
//
//#include <GLFW/glfw3.h>
//
//const GLint WIDTH = 800, HEIGHT = 600;
//void processInput(GLFWwindow *window);
//int main(){
//	//initialze glfw
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
//	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
//
//	GLFWwindow* window = glfwCreateWindow(WIDTH,HEIGHT,"H17000621",nullptr,nullptr);
//
//	int screenWidth, screenHeight;
//	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
//	if (nullptr == window) {
//		std::cout << "failed to create GLFW window" << std::endl;
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//	//initialize glew
//	glewExperimental = GL_TRUE;
//	if (GLEW_OK != glewInit()) {
//		std::cout << "failed to initialise GLEW" << std::endl;
//		return -1;
//	}
//	glViewport(0,0,screenWidth,screenHeight);
//
//	while (!glfwWindowShouldClose(window)) {
//		processInput(window);
//		glfwPollEvents();
//		glClearColor(0.2f,0.3f,0.3f,1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//		glfwSwapBuffers(window);
//	}
//	glfwTerminate();
//	return 0;
//}
//void processInput(GLFWwindow* window) {
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE)==GLFW_PRESS) {
//		glfwSetWindowShouldClose(window, true);
//	}
//}
//-----------------------------------------------------------------

//#include "pch.h"
//#include <iostream>
//#define GLEW_STATIC
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void processInput(GLFWwindow* window);
//
//const GLuint SCR_WIDTH = 800;
//const GLuint SCR_HEIGHT = 600;
//
//const char *vertexShaderSource = "#version 330 core\n"
//"layout (location = 0) in vec3 aPos;\n"
//"void main()\n"
//"{\n"
//" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//"}\0";
//
//const char* fragmentShaderSource = "#version 330 core\n"
//"out vec4 FragColor;\n"
//"void main()\n"
//"{\n"
//" FragColor = vec4(1.0f,0.5f,0.2f,1.0f);\n"
//"}\n\0";
//
//int main() {
//	//init glfw
//	//--------
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	//mac need
//	//----------
//#ifdef _APPLE_
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#endif 
//
//	//glfw window creation
//	//--------------------
//	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH,SCR_HEIGHT, "learn opengl project1",nullptr,nullptr);
//	int screen_width, screen_height;
//	glfwGetFramebufferSize(window, &screen_width, &screen_height);
//	if (window == nullptr) {
//		std::cout << "failed to create glfw window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//	//initialize glew
//	glewExperimental = GL_TRUE;
//	if (GLEW_OK!=glewInit()) {
//		std::cout << "failed to initialize GLEW" << std::endl;
//		return -1;
//	}
//
//	//build and compile shader program
//	//--------------------------------
//	//vertex shader
//	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
//	glShaderSource(vertexShader,1,&vertexShaderSource,nullptr);
//	glCompileShader(vertexShader);
//	//check for shader compile errors
//	int success;
//	char infoLog[512];
//	glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
//	if (!success) {
//		glGetShaderInfoLog(vertexShader,512,nullptr,infoLog);
//		std::cout << "ERROR::SHADER::VERTE::COMPILATION_FAILED\N"<<std::endl;
//	}
//
//	//f+/	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fragmentShader,1,&fragmentShaderSource,nullptr);
//	glCompileShader(fragmentShader);
//	//check for shader compile errors
//	glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&success);
//	if (!success) {
//		glGetShaderInfoLog(fragmentShader,512,NULL,infoLog);
//		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\N" << std::endl;
//	}
//	//link shaders
//	int shaderProgram = glCreateProgram();
//	glAttachShader(shaderProgram, vertexShader);
//	glAttachShader(shaderProgram, fragmentShader);
//	glLinkProgram(shaderProgram);
//	//check for linking errors
//	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//	if (!success) {
//		glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
//		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\N" << infoLog;
//	}
//	glDeleteShader(vertexShader);
//	glDeleteShader(fragmentShader);
//
//	/*
//	set up vertex data and configure vertex attributes
//	*/
//	float vertices[] = {
//		// first triangle
//		-0.9f, -0.5f, 0.0f,  // left 
//		-0.0f, -0.5f, 0.0f,  // right
//		-0.45f, 0.5f, 0.0f,  // top 
//		// second triangle
//		 0.0f, -0.5f, 0.0f,  // left
//		 0.9f, -0.5f, 0.0f,  // right
//		 0.45f, 0.5f, 0.0f   // top 
//	};
//	GLuint indices[] = {
//		0,1,3,
//		1,2,3
//	};
//	GLuint VBO, VAO;
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//	//glGenBuffers(1, &EBO);
//	//bind vertex arrays
//	glBindVertexArray(VAO);
//
//	//bind and set vertex buffer, then configure attribute
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),vertices,GL_STATIC_DRAW);
//	
//	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
//
//	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
//	glEnableVertexAttribArray(0);
//	//unbind
//	glBindBuffer(GL_ARRAY_BUFFER,0);
//	glBindVertexArray(0);
//
//	/*
//	render loop
//	*/
//	while (!glfwWindowShouldClose(window)) {
//		processInput(window);
//		glClearColor(0.2f,0.3f,0.3f,1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		//draw 
//		glUseProgram(shaderProgram);
//		glBindVertexArray(VAO);
//		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
//		glDrawArrays(GL_TRIANGLES,0,6);
//
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//	glDeleteVertexArrays(1,&VAO);
//	glDeleteBuffers(1,&VBO);
//	//glDeleteBuffers(1, &EBO);
//
//	glfwTerminate();
//	return 0;
//}
//void processInput(GLFWwindow* window) {
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE == GLFW_PRESS)) {
//		glfwSetWindowShouldClose(window, true);
//	}
//}
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
//	int screen_width, screen_height;
//	glfwGetFramebufferSize(window, &screen_width, &screen_height);
//	glViewport(0,0,screen_width,screen_height);
//}

////---------------------------------------------------
//#include "pch.h"
//#include <iostream>
//#define GLEW_STATIC
//#include "GL/glew.h"
//#include "GLFW/glfw3.h"
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void processInput(GLFWwindow* window);
//
//const GLuint SRC_WIDTH = 800, SRC_HEIGHT = 600;
//
//const char* vertexShaderSource = "#version 330 core\n"
//"layout (location = 0) in vec3 aPos;\n"
//"void main()\n"
//"{\n"
//"	gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
//"}\0";
//
//const char* fragmentShader1Source = "#version 330 core\n"
//"out vec4 FragColor;\n"
//"void main()\n"
//"{\n"
//"	FragColor = vec4(1.0f,0.5f,0.2f,1.0f);\n"
//"}\n\0";
//
//const char* fragmentShader2Source = "#version 330 core\n"
//"out vec4 FragColor;\n"
//"void main()\n"
//"{\n"
//"	FragColor = vec4(1.0f,1.0f,0.0f,1.0f);\n"
//"}\n\0";
//
//int main() {
//	/*
//		initialize glfw
//	*/
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
//
//#ifdef _APPLE_
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT);
//#endif // _APPLE_
//	/*
//		glfw window creation
//	*/
//	int screen_width, screen_height;
//	GLFWwindow* window = glfwCreateWindow(SRC_WIDTH,SRC_HEIGHT,"learnOPENGL_two shader",nullptr,nullptr);
//	glfwGetFramebufferSize(window,&screen_width,&screen_height);
//	if (window == nullptr) {
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;//end the program
//	}
//	glfwMakeContextCurrent(window);
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//	/*
//		initialize glew
//	*/
//	glewExperimental = GL_TRUE;
//	if (GLEW_OK != glewInit()) {
//		std::cout << "Failed to initialize GLEW" << std::endl;
//		return -1;
//	}
//
//	/*
//		build and compile shader program
//	*/
//	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
//	GLuint fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER);
//	GLuint fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
//	GLuint shaderProgramOrange = glCreateProgram();
//	GLuint shaderProgramYellow = glCreateProgram();
//	glShaderSource(vertexShader,1,&vertexShaderSource,nullptr);
//	glCompileShader(vertexShader);
//	GLint success;
//	GLchar infoLog[512];
//	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//	if (!success) {
//		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//		std::cout << "ERROE::SHADER::VERTEX::COMPILATION_FAILED\N" << infoLog << std::endl;
//	}
//
//
//	glShaderSource(fragmentShaderOrange,1,&fragmentShader1Source,nullptr);
//	glCompileShader(fragmentShaderOrange);
//
//	glGetShaderiv(fragmentShaderOrange, GL_COMPILE_STATUS, &success);
//	if (!success) {
//		glGetShaderInfoLog(fragmentShaderOrange, 512, NULL, infoLog);
//		std::cout << "ERROE::SHADER::VERTEX::COMPILATION_FAILED\N" << infoLog << std::endl;
//	}
//
//
//
//	glShaderSource(fragmentShaderYellow, 1, &fragmentShader2Source, nullptr);
//	glCompileShader(fragmentShaderYellow);
//
//	glGetShaderiv(fragmentShaderYellow, GL_COMPILE_STATUS, &success);
//	if (!success) {
//		glGetShaderInfoLog(fragmentShaderYellow, 512, NULL, infoLog);
//		std::cout << "ERROE::SHADER::VERTEX::COMPILATION_FAILED\N" << infoLog << std::endl;
//	}
//	//link
//	glAttachShader(shaderProgramOrange,vertexShader);
//	glAttachShader(shaderProgramOrange, fragmentShaderOrange);
//	glLinkProgram(shaderProgramOrange);
//
//	glAttachShader(shaderProgramYellow, vertexShader);
//	glAttachShader(shaderProgramYellow, fragmentShaderYellow);
//	glLinkProgram(shaderProgramYellow);
//
//	/*
//		set up vertex data and configure vertex attrib
//	*/
//	float firstTriangle[] = {
//		-0.9f, -0.5f, 0.0f,  // left 
//		-0.0f, -0.5f, 0.0f,  // right
//		-0.45f, 0.5f, 0.0f,  // top 
//	};
//	float secondTriangle[] = {
//		0.0f, -0.5f, 0.0f,  // left
//		0.9f, -0.5f, 0.0f,  // right
//		0.45f, 0.5f, 0.0f   // top 
//	};
//	GLuint VBOs[2], VAOs[2];
//	glGenVertexArrays(2, VAOs);
//	glGenBuffers(2, VBOs);
//	//first triangle setup
//	glBindVertexArray(VAOs[0]);
//	glBindBuffer(GL_ARRAY_BUFFER,VBOs[0]);
//	glBufferData(GL_ARRAY_BUFFER,sizeof(firstTriangle),firstTriangle,GL_STATIC_DRAW);
//	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(GL_FLOAT),(void*)0);
//	glEnableVertexAttribArray(0);
//	//second
//	glBindVertexArray(VAOs[1]);
//	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);
//	glEnableVertexAttribArray(0);
//
//
//	while (!glfwWindowShouldClose(window)) {
//		processInput(window);
//		glClearColor(0.2f,0.3f,0.3f,1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//		//draw the first triangle
//		glUseProgram(shaderProgramOrange);
//		glBindVertexArray(VAOs[0]);
//		glDrawArrays(GL_TRIANGLES,0,3);
//		//the second
//		glUseProgram(shaderProgramYellow);
//		glBindVertexArray(VAOs[1]);
//		glDrawArrays(GL_TRIANGLES, 0, 3);
//
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//	glDeleteVertexArrays(2, VAOs);
//	glDeleteBuffers(2,VBOs);
//	glfwTerminate();
//	return 0;
//}
//
//void processInput(GLFWwindow* window) {
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
//		glfwSetWindowShouldClose(window, true);
//	}
//}
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
//	glViewport(0,0,width,height);
//}




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
#include "Shader.h"
//set size of the window
//use prefix GL for basic data type & gl for function
const GLint WIDTH = 800, HEIGHT = 600;

//const GLchar*  vertexShaderSource = "#version 330 core \n"//version
//"layout(location = 0) in vec3 position;\n"
//"layout(location = 1) in vec3 color;\n"
//"out vec3 outColor;\n"
//"void main()\n"
//"{\n"
//"gl_Position = vec4(position.x,position.y,position.z, 1.0f);\n"
//"outColor = color;\n"
//"}";
//
//const GLchar* fragmentShaderSource = "#version 330 core\n"
//"out vec4 color;\n"
//"in vec3 outColor;\n"
//"void main()\n"
//"{\n"
////color = vec4(outColor.r,outColor.g,outColor.b,1.0f);
//"color = vec4(outColor,1.0f);\n"
//"}";

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
	glViewport(0, 0, screenWidth, screenHeight);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();//end glfw
		return -1;//end the program
	}
	//使window变成当前窗口
	glfwMakeContextCurrent(window);
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

	Shader shader = Shader("res/shaders/core.vs","res/shaders/core.frag");

	

	//the vertex info
	//GLfloat vertices[] = {
	//	//pos                  //color
	//	-0.5f,-0.5f,0.0f,   1.0f, 0.0f,0.0f,
	//	0.5f,-0.5f,0.0f,    0.0f,1.0f,0.0f,
	//	0.0f,0.5f,0.0f,     0.0f,0.0f,1.0f
	//};
	//
	GLfloat vertices_two[] = {
		////anticlockwise
		////first triangle
		//0.5f,0.5f,0.0f,
		//-0.5f,0.5f,0.0f,
		//-0.5f,-0.5f,0.0f,
		////second triangle
		//0.5f,0.5f,0.0f,
		//-0.5f,-0.5f,0.0f,
		//0.5f,-0.5f,0.0f,
		//使用索引
		0.5f,0.5f,0.0f,
		-0.5f,0.5f,0.0f,
		-0.5f,-0.5f,0.0f,
		0.5f,-0.5f,0.0f
	};

	unsigned int indices[] = {
		0,1,2,
		0,2,3
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0); //read the position
	glEnableVertexAttribArray(0);

	/*
		EBO(element buffer)
	*/
	GLuint EBO;
	glGenBuffers(1,&EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);


	//解绑定
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	//game loop
	while (!glfwWindowShouldClose(window))
	{
		//glfw always watch the events done by keyboard, mouse or others, but it will never do anything unless use glfwPollEvents
		glfwPollEvents();
		//0~1   RGB opacity
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//glViewport(0, 0, screenWidth, screenHeight);

		//glUseProgram(shaderProgram);
		shader.Use();
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		//双缓存模式
		glfwSwapBuffers(window);
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1,&EBO);

	//release the source
	glfwTerminate();
	return 0;
}