#include <iostream>
#include "OpenGLUtils/OpenGLUtils.h"

static glm::mat4 CreateLookAtMatrix(glm::vec3 cameraPos, glm::vec3 cameraTarget, glm::vec3 up) {
	glm::vec3 cameraForward = glm::normalize(cameraPos - cameraTarget);
	// point right hand fingers in direction of first vector then curl fingers towards other vector and thumb points in the direction the cross vector points
	glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraForward)); 
	glm::vec3 cameraUp = (glm::cross(cameraForward, cameraRight));

	glm::mat4 result(1.0);
	
	result[0][0] = cameraRight.x; result[1][0] = cameraRight.y; result[2][0] = cameraRight.z; result[3][0] = -glm::dot(cameraPos, cameraRight);
	result[0][1] = cameraUp.x; result[1][1] = cameraUp.y; result[2][1] = cameraUp.z; result[3][1] = -glm::dot(cameraPos, cameraUp);
	result[0][2] = cameraForward.x; result[1][2] = cameraForward.y; result[2][2] = cameraForward.z; result[3][2] = -glm::dot(cameraPos, cameraForward);

	return result;
}

// Lesson Getting Familar with Shaders and creating a shader class
int CameraLesson() {
	const int initialScreenWidth = 2560;
	const int initialScreenHeight = 1440;

	glm::mat4 projection;

	glm::vec3 cameraPos(0.0f, 0.0f, 5.0f);
	FlyingFPSCamera fpsCamera(cameraPos, glm::vec3(0.0f, 1.0f, 0.0f), initialScreenWidth, initialScreenHeight, 90.0f, -90.0f);

	// setting up callback listeners since OpenGL allows for only one registered callback function at a time
	framebufferResizeEvent += std::bind(&FlyingFPSCamera::WindowResizeEvent, &fpsCamera, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

	framebufferResizeEvent += [&projection, &fpsCamera](GLFWwindow* window, int width, int height) {
		projection = (glm::mat4)glm::perspectiveFov(glm::radians(fpsCamera.FOV()), (float)width, (float)height, 0.1f, 100.0f);
	};

	mouseMovementEvent += std::bind(&FlyingFPSCamera::MouseMovementEvent, &fpsCamera, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	mouseScrollEvent += std::bind(&FlyingFPSCamera::MouseScrollEvent, &fpsCamera, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	mouseScrollEvent += [&projection, &fpsCamera](GLFWwindow* window, double xOffset, double yOffset) {
		projection = glm::perspectiveFov(glm::radians(fpsCamera.FOV()), (float)fpsCamera.Width(), (float)fpsCamera.Height(), 0.1f, 100.0f);
	};

	InitGLFW(3, 3);

	//Create a window for glfw
	GLFWwindow* window = glfwCreateWindow(initialScreenWidth, initialScreenHeight, "LearnOpenGL Cameras", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window\n";
		glfwTerminate();
		return -1;
	}
	else {
		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		glfwSetCursorPosCallback(window, mouse_Movement_Callback);
		glfwSetScrollCallback(window, mouse_Scroll_Callback);
	}

	//Initialize GLAD (load all OpenGL function pointers)
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD!\n";
		return -1;
	}

	//set openGL to take into consideration the depth buffer before drawing a pixel
	glEnable(GL_DEPTH_TEST);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

	float deltaTime = 0;
	float lastFrame = (float)glfwGetTime();

	while (!glfwWindowShouldClose(window)) {
		//check input
		float currentTime = (float)glfwGetTime();
		deltaTime = currentTime - lastFrame;
		lastFrame = currentTime;
		processInput(window);
		//processCameraInput(window, cameraPos, cameraFront, cameraUp, 0.5, deltaTime);
		processCameraInput(window, fpsCamera, deltaTime);

		//rendering commands here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//set our shader program to be the active shader for OpenGL
		shader.Bind();

		//transformationMat * glm::mat4(1.0f);
		projection = glm::perspectiveFov(glm::radians(fpsCamera.FOV()), (float)fpsCamera.Width(), (float)fpsCamera.Height(), 0.1f, 100.0f);

		float radius = 10.0f;
		float camX = sin(currentTime) * radius;
		float camZ = cos(currentTime) * radius;
		glm::mat4 view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));//glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
		glm::mat4 myView;// = CreateLookAtMatrix(cameraPos, cameraPos + cameraFront, cameraUp);
		myView = fpsCamera.GenerateViewMatrix();

		unsigned int numberCubes = sizeof(cubePositions) / sizeof(cubePositions[0]);

		shader.SetMat4("view", myView);
		shader.SetMat4("projection", projection);



		//set the vertex array to our vertex array with the triangle information
		glBindVertexArray(VertexArrayObject);

		for (unsigned int i = 0; i < numberCubes; i++) {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			//model = glm::rotate(model, (float)glfwGetTime()* glm::radians(20.0f*i), glm::vec3(0.5f, 1.0f, 0.0f));
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