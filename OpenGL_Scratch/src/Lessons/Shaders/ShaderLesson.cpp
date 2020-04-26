#include <iostream>
#include <cmath>
#include "ShaderLesson.h"
#include "OpenGLUtils/OpenGLUtils.h"

//first we drew a single triangle on the screen then we drew a rectangle by constructing two triangles
int ShaderLesson() {
	
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

	//Declare and compile shaders
	Shader shaderTest("res/shaders/BasicShader.vert", "res/shaders/BasicUniforms.frag");

	//create data and store data in a vertex buffer
	//hello triangle lesson vertices
	float vertices[] = {
	-0.5f, -0.5f, 0.0f, //bottom left
	 0.5f, -0.5f, 0.0f, // bottom right
	 0.5f,  0.5f, 0.0f, // top right
	-0.5f,  0.5f, 0.0f // top left
	};

	unsigned int indices[] = {  // note that we start from 0!
	0, 1, 3,   // first triangle
	1, 2, 3    // second triangle
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

	//create Element Buffer Object to tell OpenGL the ordering of my vertices and how triangles should be constructed
	unsigned int ElementBufferObject = 0;
	glGenBuffers(1, &ElementBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//tell GPU how to process data in the array
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(vertices[0]), (void*)0);
	glEnableVertexAttribArray(0);

	//we can now safely unbind the vertex buffer object since it has been associated with out vertex array object
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//unbind VertexArray for consistency
	glBindVertexArray(0);

	//now that the vertexArray is unbound we can unbind its Element buffer object since the VAO is no longer tracking the active EBO
	//the VAO does not save the EBO the same way as it does the VBO. Saves EBO by state-tracking while it is active
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);



	while (!glfwWindowShouldClose(window)) {
		//check input
		processInput(window);

		float time = glfwGetTime();
		float greenValue = std::sin(time) / 2.0 + 0.5;

		//rendering commands here
		glClearColor(0.2, 0.3, 0.3, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		//set our shader program to be the active shader for OpenGL
		//glUseProgram(shaderProgram);
		shaderTest.Bind();

		//set the vertex array to our vertex array with the triangle information
		glBindVertexArray(VertexArrayObject);

		//OpenGL function to draw the data in the currently active vertex array using the Element Buffer Object
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, 0);

		// check and call events and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}