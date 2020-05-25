#include <iostream>
#include <functional>
#include "OpenGLUtils/OpenGLUtils.h"

// Lesson Getting Familar with using lighting materials
//still a wip
int ModelLoadingLesson() {
	const int initialScreenWidth = 2560;
	const int initialScreenHeight = 1440;

	glm::mat4 projection;
	glm::mat4 view;

	glm::vec3 cameraPos(0.0f, 0.0f, 5.0f);
	FlyingFPSCamera fpsCamera(cameraPos, glm::vec3(0.0f, 1.0f, 0.0f), initialScreenWidth, initialScreenHeight, 90.0f, -90.0f);
	//FlyingCamera fpsCamera(cameraPos, initialScreenWidth, initialScreenHeight, 90.0f, -90.0f);

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
	GLFWwindow* window = glfwCreateWindow(initialScreenWidth, initialScreenHeight, "LearnOpenGL Model Loading", NULL, NULL);
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

	// tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
	stbi_set_flip_vertically_on_load(true);

	//Declare and compile shaders
	Shader shader("res/shaders/BasicShaders/TransformationShaders/MVP.vert", "res/shaders/BasicShaders/SimpleTexture.frag");
	Model  backpackModel((char*)"res/Models/Backpack/backpack.obj");

	float deltaTime = 0;
	float lastFrame = (float)glfwGetTime();

	projection = glm::perspectiveFov(glm::radians(fpsCamera.FOV()), (float)fpsCamera.Width(), (float)fpsCamera.Height(), 0.1f, 100.0f);

	while (!glfwWindowShouldClose(window)) {
		//check input
		float currentTime = (float)glfwGetTime();
		deltaTime = currentTime - lastFrame;
		lastFrame = currentTime;

		processInput(window);
		processCameraInput(window, fpsCamera, deltaTime);

		//rendering commands here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//set our shader program to be the active shader for OpenGL
		shader.Bind();

		view = fpsCamera.GenerateViewMatrix();

		shader.SetMat4("view", view);
		shader.SetMat4("projection", projection);
		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(0.0, 0.0, -5.0));

		shader.SetMat4("model", model);
		backpackModel.Draw(shader,  "material");

		// check and call events and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}