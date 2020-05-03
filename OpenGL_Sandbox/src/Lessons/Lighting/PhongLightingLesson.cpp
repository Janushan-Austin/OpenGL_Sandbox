#include <iostream>
#include "OpenGLUtils/OpenGLUtils.h"


static glm::mat4 projection;


// Lesson Getting Familar with Shaders and creating a shader class
int PhongLightingLesson() {
	const int initialScreenWidth = 2560;
	const int initialScreenHeight = 1440;

	glm::vec3 cameraPos(0.0f, 0.0f, 5.0f);
	FlyingFPSCamera fpsCamera(cameraPos, glm::vec3(0.0f, 1.0f, 0.0f), initialScreenWidth, initialScreenHeight, 90.0f, -90.0f);


	framebufferResizeEvent += &Camera::WindowResizeEvent;
	framebufferResizeEvent += [](GLFWwindow* window, int width, int height) {
		projection = glm::perspectiveFov(glm::radians(Camera::GetActiveCamera()->FOV()), (float)width, (float)height, 0.1f, 100.0f);
	};
	mouseMovementEvent += &Camera::MouseMovementEvent;
	mouseScrollEvent += &Camera::MouseScrollEvent;
	mouseScrollEvent += [](GLFWwindow* window, double xOffset, double yOffset) {
		projection = glm::perspectiveFov(glm::radians(Camera::GetActiveCamera()->FOV()), (float)Camera::GetActiveCamera()->Width(), (float)Camera::GetActiveCamera()->Height(), 0.1f, 100.0f);
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
		//setup necessary callback functions
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
	Shader lightingShader("res/shaders/Lighting/Phong/PhongShadingWorld.vert", "res/shaders/Lighting/Phong/PhongShadingWorld.frag");
	Shader lampShader("res/shaders/Lighting/SimpleLightSource.vert", "res/shaders/Lighting/SimpleLightSource.frag");

	float deltaTime = 0;
	float lastFrame = glfwGetTime();

	glm::vec3 objectColor(1.0f, 0.5f, 0.31f);

	glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
	glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
	glm::vec3 lightScale(0.2f, 0.2f, 0.2f);

	float test = (float)fpsCamera.Width();

	projection = glm::perspectiveFov(glm::radians(fpsCamera.FOV()), (float)fpsCamera.Width(), (float)fpsCamera.Height(), 0.1f, 100.0f);
	glm::mat4 view;

	//unit cube not using index buffering with normals for each vertex
	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(vertices[0]), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(vertices[0]), (void*)(3 * sizeof(vertices[0])));
	glEnableVertexAttribArray(1);

	//creating a second Vertex Array object specificly for our light source
	unsigned int LightVAO = 0;
	glGenVertexArrays(1, &LightVAO);
	glBindVertexArray(LightVAO);

	//light source is using same vertex data as our cube's
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);

	//tell GPU how to process data in the array
	//needs the same attributes on how to process the data inside the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(vertices[0]), (void*)0);
	glEnableVertexAttribArray(0);


	//we can now safely unbind the vertex buffer object since it has been associated with out vertex array object
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//unbind VertexArray for consistency
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window)) {
		//check input
		deltaTime = glfwGetTime() - lastFrame;
		lastFrame = glfwGetTime();
		processInput(window);
		//processCameraInput(window, cameraPos, cameraFront, cameraUp, 0.5, deltaTime);
		processCameraInput(window, fpsCamera, deltaTime);

		//rendering commands here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//set our shader program to be the active shader for OpenGL
		lightingShader.Bind();

		//lightPos.x = cosf(glfwGetTime());
		//lightPos.y = cosf(glfwGetTime()) * sinf(glfwGetTime());
		//lightPos.z = sinf(glfwGetTime());

		view = fpsCamera.GenerateViewMatrix();

		unsigned int numberCubes = sizeof(cubePositions) / sizeof(cubePositions[0]);

		lightingShader.SetUniformMat4("view", view);
		lightingShader.SetUniformMat4("projection", projection);
		lightingShader.SetUniform3f("objectColor", objectColor.x, objectColor.y, objectColor.z);
		lightingShader.SetUniform3f("lightPos", lightPos.x, lightPos.y, lightPos.z);
		//lightingShader.SetUniform3f("worldLightPos", lightPos.x, lightPos.y, lightPos.z);
		lightingShader.SetUniform3f("lightColor", lightColor.x, lightColor.y, lightColor.z);
		lightingShader.SetUniform3f("viewPos", fpsCamera.Position().x, fpsCamera.Position().y, fpsCamera.Position().z);



		//set the vertex array to our vertex array with the triangle information
		glBindVertexArray(CubeVAO);

		for (unsigned int i = 0; i < numberCubes; i++) {
			glm::mat4 model(1.0f);
			model = glm::translate(model, cubePositions[i]);
			model = glm::rotate(model, (float)glfwGetTime()* glm::radians(20.0f*i), glm::vec3(0.5f, 1.0f, 0.0f));
			lightingShader.SetUniformMat4("model", model);


			//OpenGL function to draw the data in the currently active vertex array using the Element Buffer Object
			//glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, 0);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		lampShader.Bind();
		lampShader.SetUniformMat4("view", view);
		lampShader.SetUniformMat4("projection", projection);
		lampShader.SetUniform3f("lightColor", lightColor.x, lightColor.y, lightColor.z);

		glm::mat4 model = glm::translate(glm::mat4(1.0f), lightPos);
		model = glm::scale(model, lightScale);
		lampShader.SetUniformMat4("model", model);


		glBindVertexArray(CubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);



		// check and call events and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}