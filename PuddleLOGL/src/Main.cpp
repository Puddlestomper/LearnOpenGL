#include "pudpch.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Camera.h"
#include "Texture.h"

float prevTime = 0.0f;
float dTime = 0.0f;

int screenWidth = 800, screenHeight = 600;

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
glm::vec3 lightColour(1.0f);

//#######################################
//Camera
//#######################################

Camera cam((float)screenWidth/screenHeight);

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	screenWidth = width;
	screenHeight = height;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	cam.OnMouseMoved(xpos, ypos);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	cam.OnMouseScrolled(xoffset, yoffset);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	cam.OnUpdate(window, dTime);
}

int main()
{
	std::cout << "Init!\n";
	
	//GLFW Init
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Create the Window
	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//GLAD Init
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD\n";
		return -1;
	}

	glViewport(0, 0, screenWidth, screenHeight);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//Set Callbacks
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	//#######################################
	//Load Texture
	//#######################################

	//setVFlip();

	//unsigned int textures[2];
	//textures[0] = loadTexture("assets/textures/container.jpg", GL_RGB, 0);
	//textures[1] = loadTexture("assets/textures/awesomeface.png", GL_RGBA, 1);

	//#######################################
	//Make Box
	//#######################################

	Shader objShader("assets/shaders/LitMVP.vs", "assets/shaders/FlatColourLit.fs");
	Shader lightShader("assets/shaders/BaseMVP.vs", "assets/shaders/FlatColour.fs");

	//Vertices

	float cubeVertices[] =
	{
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

	glm::vec3 cubePositions[] =
	{
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

	unsigned int VBO[1], VAO[2];
	glGenVertexArrays(2, VAO);
	glGenBuffers(1, VBO);

	//Bind Vertex Array Object first so that it tracks other binds
	glBindVertexArray(VAO[1]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//Link Vertex Attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Light VAO
	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	//Unbind EBO
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//#######################################
	//Render Loop
	//#######################################

	cam.Translate(glm::vec3(0.0f, 1.5f, 1.5f));

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	prevTime = glfwGetTime();

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float time = glfwGetTime();
		dTime = time - prevTime;

		//#######################################
		//Model, View, Projection
		//#######################################

		glm::mat4 model(1.0f);
		
		glm::mat4 view = cam.GetView();

		glm::mat4 projection = cam.GetProjection();

		//#######################################
		//Do the Cube First
		//#######################################

		glBindVertexArray(VAO[1]);

		//#######################################
		//Set Uniforms
		//#######################################

		model = glm::mat4(1.0f);

		objShader.Use();

		//int uniColourLocation = glGetUniformLocation(shaderProgram, "uniColour");
		//glUniform4f(uniColourLocation, 0.0f, green, 0.0f, 1.0f);
		
		objShader.SetMat4f("model", model);
		objShader.SetMat4f("view", view);
		objShader.SetMat4f("projection", projection);

		objShader.SetFloat3("objectColour", glm::vec3(1.0f, 0.5f, 0.31f));

		objShader.SetFloat3("lightColour", lightColour);
		objShader.SetFloat3("lightPos", lightPos);

		objShader.SetFloat3("viewPos", cam.GetPosition());

		glDrawArrays(GL_TRIANGLES, 0, 36);

		//#######################################
		//Do the Light Second
		//#######################################

		glBindVertexArray(VAO[0]);

		//#######################################
		//Set Uniforms
		//#######################################

		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));
		
		lightShader.Use();

		//int uniColourLocation = glGetUniformLocation(shaderProgram, "uniColour");
		//glUniform4f(uniColourLocation, 0.0f, green, 0.0f, 1.0f);

		lightShader.SetMat4f("model", model);
		lightShader.SetMat4f("view", view);
		lightShader.SetMat4f("projection", projection);

		lightShader.SetFloat3("lightColour", lightColour);

		glDrawArrays(GL_TRIANGLES, 0, 36);

		//glBindVertexArray(0);
		
		glfwSwapBuffers(window);
		glfwPollEvents();

		prevTime = time;
	}

	//De-allocate when done
	glDeleteVertexArrays(2, VAO);
	glDeleteBuffers(1, VBO);
	//glDeleteBuffers(1, &EBO);

	//GLFW Destruction
	glfwTerminate();

	std::cout << "Goodbye!\n";

	return 0;
}