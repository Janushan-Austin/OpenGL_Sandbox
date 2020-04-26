#include "HelloTriangleEx2.h"
#include <iostream>
#include "OpenGLUtils/OpenGLUtils.h"

extern const char* vertexShaderSource;
extern const char* fragmentShaderSource;

//create two triangles next to each other using glDrawArrays and two seperate VAOs and VBOs
int HelloTriangleEx2() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

	//Decalre and Compile shaders
	Shader shader("res/shaders/BasicShader.vs", "res/shaders/BasicShader.fs");

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
	unsigned int VertexArrayObject1 = 0;
	glGenVertexArrays(1, &VertexArrayObject1);
	glBindVertexArray(VertexArrayObject1);

	//create vertex buffer to store data of vertices in GPU
	unsigned int VertexBufferObject1 = 0;
	//Generate ID for Vertex Buffer
	glGenBuffers(1, &VertexBufferObject1);

	//Bind Vertex Buffer and pass data to GPU
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices)/2, vertices, GL_STATIC_DRAW);

	//tell GPU how to process data in the array
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(vertices[0]), (void*)0);
	glEnableVertexAttribArray(0);

	//we can now safely unbind the vertex buffer object since it has been associated with out vertex array object
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//unbind VertexArray for consistency
	glBindVertexArray(0);

	//could of implemented second vertex array and buffer using an array instead of seperate variable
	unsigned int VertexArrayObject2 = 0;
	glGenVertexArrays(1, &VertexArrayObject2);
	glBindVertexArray(VertexArrayObject2);

	//create vertex buffer to store data of vertices in GPU
	unsigned int VertexBufferObject2 = 0;
	//Generate ID for Vertex Buffer
	glGenBuffers(1, &VertexBufferObject2);

	//Bind Vertex Buffer and pass data to GPU
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) / 2, vertices + sizeof(vertices) / 2 / sizeof(vertices[0]), GL_STATIC_DRAW);

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
		shader.Bind();

		//set the vertex array to our vertex array with the triangle information
		glBindVertexArray(VertexArrayObject1);

		//OpenGL function to draw the data in the currently active vertex array using the Element Buffer Object
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(VertexArrayObject2);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// check and call events and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}