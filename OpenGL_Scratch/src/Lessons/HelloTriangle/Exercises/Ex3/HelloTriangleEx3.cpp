#include "HelloTriangleEx3.h"
#include <iostream>
#include "SharedOpenGLFunctions/SharedOpenGL.h"

extern const char* vertexShaderSource;
extern const char* fragmentShaderSource;

const char* fragmentShaderYellowSource = 
R"(#version 330 core
out vec4 FragColor;
void main()
{
	FragColor = vec4(1.0, 1.0, 0.0, 1.0);
})";

//create two triangles with one triangle using a different shader
int HelloTriangleEx3() {
	InitGLFW(3, 3);

	//Create a window for glfw
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL Again", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window\n";
		glfwTerminate();
		return -1;
	}
	else {
		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	}

	//Initialize GLAD (load all OpenGL function pointers)
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD!\n";
		return -1;
	}

	glViewport(0, 0, 800, 600);

	//compile shaders
	//vertex shader compilation
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	//check for vertex shader successful compilation
	int shaderCompilationSuccess;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &shaderCompilationSuccess);
	if (!shaderCompilationSuccess) {
		char infoLog[512];
		glGetShaderInfoLog(vertexShader, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERROR:: SHADDER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//fragment shader compilation
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//check for fragment shader successful compilation
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &shaderCompilationSuccess);
	if (!shaderCompilationSuccess) {
		char infoLog[512];
		glGetShaderInfoLog(fragmentShader, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERROR:: SHADDER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//shader program creation
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	//check for shader program successful linking
	glGetShaderiv(shaderProgram, GL_COMPILE_STATUS, &shaderCompilationSuccess);
	if (!shaderCompilationSuccess) {
		char infoLog[512];
		glGetShaderInfoLog(shaderProgram, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERROR:: SHADDER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	unsigned int fragmentShaderYellow;
	fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderYellow, 1, &fragmentShaderYellowSource, NULL);
	glCompileShader(fragmentShaderYellow);

	//check for fragment shader successful compilation
	glGetShaderiv(fragmentShaderYellow, GL_COMPILE_STATUS, &shaderCompilationSuccess);
	if (!shaderCompilationSuccess) {
		char infoLog[512];
		glGetShaderInfoLog(fragmentShaderYellow, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERROR:: SHADDER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//shader program for yellow Frag shader creation
	unsigned int shaderProgramYellow;
	shaderProgramYellow = glCreateProgram();

	glAttachShader(shaderProgramYellow, vertexShader);
	glAttachShader(shaderProgramYellow, fragmentShaderYellow);
	glLinkProgram(shaderProgramYellow);

	//check for shader program successful linking
	glGetShaderiv(shaderProgramYellow, GL_COMPILE_STATUS, &shaderCompilationSuccess);
	if (!shaderCompilationSuccess) {
		char infoLog[512];
		glGetShaderInfoLog(shaderProgramYellow, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERROR:: SHADDER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	

	//delete vertex and fragment shaders since they have now been linked to the shader program
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteShader(fragmentShaderYellow);

	//create data and store data in a vertex buffer
	//hello triangle exercise 1 vertices
	float vertices[] = {
		-0.5, 0.0, 0.0,
		-0.25, 0.0, 0.0,
		-0.375, 0.5, 0.0,
		0.25, 0.0, 0.0,
		0.5, 0.0, 0.0,
		0.375, 0.5, 0.0
	};

	//create Vertex Array Object to store state dependent details about vertex buffer states
	unsigned int VertexArrayObject = 0;
	glGenVertexArrays(1, &VertexArrayObject);
	glBindVertexArray(VertexArrayObject);

	//create vertex buffer to store data of vertices in GPU
	unsigned int VertexBufferObject = 0;
	//Generate ID for Vertex Buffer
	glGenBuffers(1, &VertexBufferObject);

	//Bind Vertex Buffer and pass data to GPU
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//tell GPU how to process data in the array
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(vertices[0]), (void*)0);
	glEnableVertexAttribArray(0);

	//we can now safely unbind the vertex buffer object since it has been associated with out vertex array object
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//unbind VertexArray for consistency
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window)) {
		//check input
		processInput(window);

		//rendering commands here
		glClearColor(0.2, 0.3, 0.3, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		//set our shader program to be the active shader for OpenGL
		glUseProgram(shaderProgram);

		//set the vertex array to our vertex array with the triangle information
		glBindVertexArray(VertexArrayObject);

		//OpenGL function to draw the data in the currently active vertex array using the Element Buffer Object
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(shaderProgramYellow);
		glDrawArrays(GL_TRIANGLES, 3, 3);

		// check and call events and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}