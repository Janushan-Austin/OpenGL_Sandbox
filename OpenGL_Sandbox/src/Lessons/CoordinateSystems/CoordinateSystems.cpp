#include <iostream>
#include "OpenGLUtils/OpenGLUtils.h"

glm::mat4 createPerspectiveProjection(float fov, float width, float height, float znear, float zfar);

// Lesson Getting Familar with Shaders and creating a shader class
int CoordinateSystems() {

	InitGLFW(3, 3);

	//Create a window for glfw
	GLFWwindow* window = glfwCreateWindow(2560, 1440, "LearnOpenGL Transformations", NULL, NULL);
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

	//set openGL to take into consideration the depth buffer before drawing a pixel
	glEnable(GL_DEPTH_TEST);

	//Declare and compile shaders
	Shader shader("res/shaders/BasicShaders/TransformationShaders/MVP.vert", "res/shaders/BasicShaders/TransformationShaders/TransformationShader.frag");

	//cube
	//float vertices[] = {
	//	//positions				//colors			//texture coords
	//	 0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right front
	//	 0.5f, -0.5f, 0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right front 
	//	-0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left front
	//	-0.5f,  0.5f, 0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,  // top left front

	//	 0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f, // top left back (if you are looking at the cube from the back)
	//	 0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f, // bottom left back 
	//	-0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f, // bottom right back
	//	-0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,   1.0f, 1.0f,  // top right back
	//};

	//unit cube not using index buffering
	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	//used for translating multiple cube objects into the world
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

	unsigned int indices[] = {
		0, 1, 3, // first triangle front face
		1, 2, 3,  // second triangle front face

		7, 6, 4, // first triangle back face
		6, 5, 4,  // second triangle back face

		4, 5, 0, // first triangle right face
		5, 1, 0,  // second triangle right face

		3, 2, 7, // first triangle left face
		2, 6, 7,  // second triangle left face

		4, 0, 7, // first triangle top face
		0, 3, 7,  // second triangle top face

		1, 5, 2, // first triangle bottom face
		5, 6, 2,  // second triangle bottom face
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(vertices[0]), (void*)0);
	glEnableVertexAttribArray(0);

	/*glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(vertices[0]), (void*)(3 * sizeof(vertices[0])));
	glEnableVertexAttribArray(1);*/

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(vertices[0]), (void*)(3 * sizeof(vertices[0])));
	glEnableVertexAttribArray(2);


	//Create a texture object for OpenGL
	// Load textures from image files
	unsigned int textureContainer = loadTexture("res/Textures/container.jpg");
	unsigned int textureSmileyFace = loadTexture("res/Textures/awesomeface.png");


	//we can now safely unbind the vertex buffer object since it has been associated with out vertex array object
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//unbind VertexArray for consistency
	glBindVertexArray(0);

	//now that the vertexArray is unbound we can unbind its Element buffer object since the VAO is no longer tracking the active EBO
	//the VAO does not save the EBO the same way as it does the VBO. Saves EBO by state-tracking while it is active
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	shader.Bind();

	//Bind our texture before drawing
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureContainer);
	shader.SetInt1("texture1", 0);

	//Bind our texture before drawing
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textureSmileyFace);
	shader.SetInt1("texture2", 1);

	while (!glfwWindowShouldClose(window)) {
		//check input
		processInput(window);

		//rendering commands here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//set our shader program to be the active shader for OpenGL
		shader.Bind();

		//transformationMat * glm::mat4(1.0f);
		glm::mat4 theirPerspective = glm::perspective(glm::radians(90.0f), 800.0f / 600, 0.1f, 100.0f);

		glm::mat4 myPerspective = createPerspectiveProjection(glm::radians(90.0f), 800, 600, 0.1f, 100.0f);
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));

		unsigned int numberCubes = sizeof(cubePositions) / sizeof(cubePositions[0]);

		shader.SetMat4("view", view);
		shader.SetMat4("projection", theirPerspective);

		

		//set the vertex array to our vertex array with the triangle information
		glBindVertexArray(VertexArrayObject);

		for (unsigned int i = 0; i < numberCubes; i++) {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			model = glm::rotate(model, (float)glfwGetTime()* glm::radians(20.0f*i), glm::vec3(0.5f, 1.0f, 0.0f));
			shader.SetMat4("model", model);


			//OpenGL function to draw the data in the currently active vertex array using the Element Buffer Object
			//glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, 0);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}




		// check and call events and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

//create my own perspective projection matrix
glm::mat4 createPerspectiveProjection(float fov, float width, float height, float znear, float zfar) {
	assert(fov > 0);
	assert(width > 0);
	assert(height > 0);

	glm::mat4 result(0.0f);
	//using cotangent(fov/2) by simplifying 2n/r-l when l = -r we get 2n/2r where r = aspectration * scale * n
	//following through the simplification you will end up with (1/aspectratio) * (1/tan(fov/2) -> (height/width) * cot
	float coScale = 1.0f / std::tan(fov*0.5f);
	float heightScale = coScale;
	float widthScale = coScale * height / width;

	result[0][0] = widthScale;

	result[1][1] = heightScale;

	result[2][2] = -(zfar + znear) / (zfar - znear);
	result[2][3] = -1;

	result[3][2] = -(2 * zfar * znear) / (zfar - znear);

	return result;
}