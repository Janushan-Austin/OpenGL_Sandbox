#include <iostream>
#include "OpenGLUtils/OpenGLUtils.h"

// Lesson Getting Familar with Shaders and creating a shader class
int SimpleColorLighting() {
	const int initialScreenWidth = 2560;
	const int initialScreenHeight = 1440;

	glm::mat4 projection;
	glm::mat4 view;

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
	Shader lightingShader("res/shaders/Lighting/SimpleColorLighting.vert", "res/shaders/Lighting/SimpleColorLighting.frag");
	Shader lampShader("res/shaders/Lighting/SimpleLightSource.vert", "res/shaders/Lighting/SimpleLightSource.frag");

	
	

	float deltaTime = 0;
	float lastFrame = (float)glfwGetTime();

	glm::vec3 objectColor(1.0f, 0.5f, 0.31f);

	glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
	glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
	glm::vec3 lightScale(0.2f, 0.2f, 0.2f);

	projection = glm::perspectiveFov(glm::radians(fpsCamera.FOV()), (float)fpsCamera.Width(), (float)fpsCamera.Height(), 0.1f, 100.0f);

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

	//create Vertex Array Object to store state dependent details about vertex buffer states
	unsigned int CubeVAO = 0;
	glGenVertexArrays(1, &CubeVAO);
	glBindVertexArray(CubeVAO);

	//create vertex buffer to store data of vertices in GPU
	unsigned int VertexBufferObject = 0;
	//Generate ID for Vertex Buffer
	glGenBuffers(1, &VertexBufferObject);

	//Bind Vertex Buffer and pass data to GPU
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);	

	//tell GPU how to process data in the array
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(vertices[0]), (void*)0);
	glEnableVertexAttribArray(0);

	//creating a second Vertex Array object specificly for our light source
	unsigned int LightVAO = 0;
	glGenVertexArrays(1, &LightVAO);
	glBindVertexArray(LightVAO);

	//light source is using same vertex data as our cube's
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);

	//tell GPU how to process data in the array
	//needs the same attributes on how to process the data inside the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(vertices[0]), (void*)0);
	glEnableVertexAttribArray(0);


	//we can now safely unbind the vertex buffer object since it has been associated with out vertex array object
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//unbind VertexArray for consistency
	glBindVertexArray(0);

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
		lightingShader.Bind();

		float radius = 10.0f;
		float camX = sin(currentTime) * radius;
		float camZ = cos(currentTime) * radius;

		view = fpsCamera.GenerateViewMatrix();

		unsigned int numberCubes = sizeof(cubePositions) / sizeof(cubePositions[0]);

		lightingShader.SetMat4("view", view);
		lightingShader.SetMat4("projection", projection);
		lightingShader.SetFloat3("objectColor", objectColor.x, objectColor.y, objectColor.z);
		lightingShader.SetFloat3("lightColor", lightColor.x, lightColor.y, lightColor.z);



		//set the vertex array to our vertex array with the triangle information
		glBindVertexArray(CubeVAO);

		for (unsigned int i = 0; i < numberCubes; i++) {
			glm::mat4 model(1.0f);
			model = glm::translate(model, cubePositions[i]);
			model = glm::rotate(model, (float)glfwGetTime()* glm::radians(20.0f*i), glm::vec3(0.5f, 1.0f, 0.0f));
			lightingShader.SetMat4("model", model);


			//OpenGL function to draw the data in the currently active vertex array using the Element Buffer Object
			//glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, 0);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		lampShader.Bind();
		lampShader.SetMat4("view", view);
		lampShader.SetMat4("projection", projection);
		lampShader.SetFloat3("lightColor", lightColor.x, lightColor.y, lightColor.z);

		glm::mat4 model = glm::translate(glm::mat4(1.0f), lightPos);
		model = glm::scale(model, lightScale);
		lampShader.SetMat4("model", model);


		glBindVertexArray(CubeVAO);
		glDrawArrays(GL_TRIANGLES,0, 36);



		// check and call events and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}