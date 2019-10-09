#include "pudpch.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

//mix(texture(texture0, TexCoord), texture(texture1, TexCoord), 0.2)

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
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
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
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

	glViewport(0, 0, 800, 600);

	//Set Callbacks
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//#######################################
	//Vector stuff
	//#######################################
	{
		glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
		glm::mat4 transTest(1.0f);
		transTest = glm::translate(transTest, glm::vec3(1.0f, 1.0f, 0.0f));
		vec = transTest * vec;
		std::cout << "TransTest: " << vec.x << " " << vec.y << " " << vec.z << '\n';
	}
	//#######################################
	//Box Transform
	//#######################################

	glm::mat4 trans(1.0f);
	//trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	//trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));

	//#######################################
	//Load Texture
	//#######################################

	stbi_set_flip_vertically_on_load(true);

	unsigned int textures[2];
	glGenTextures(2, textures);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textures[0]);

	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char* tData0;
	int tWidth0, tHeight0, tChannels0;
	tData0 = stbi_load("assets/container.jpg", &tWidth0, &tHeight0, &tChannels0, 0);

	if (tData0)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tWidth0, tHeight0, 0, GL_RGB, GL_UNSIGNED_BYTE, tData0);
		glGenerateMipmap(textures[0]);
	}
	else std::cerr << "Failed To Load Texture 0!\n";

	stbi_image_free(tData0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textures[1]);

	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char* tData1;
	int tWidth1, tHeight1, tChannels1;
	tData1 = stbi_load("assets/awesomeface.png", &tWidth1, &tHeight1, &tChannels1, 0);

	if (tData1)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tWidth1, tHeight1, 0, GL_RGBA, GL_UNSIGNED_BYTE, tData1);
		glGenerateMipmap(textures[1]);
	}
	else std::cerr << "Failed To Load Texture 0!\n";

	stbi_image_free(tData1);

	//#######################################
	//Make Triangle
	//#######################################

	Shader shader("assets/vShader.vs", "assets/fShader.fs");

	//Vertices
	
	float vertices[] =
	{
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	};

	unsigned int indices[] =
	{
		3, 0, 1, //First triangle
		1, 2, 3  //Second triangle
	};
	

	/*
	float vertices[] =
	{
		// positions         // colors
		0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
	   -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
		0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top
	};

	unsigned int indices[] =
	{
		0, 1, 2
	};*/

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//Bind Vertex Array Object first so that it tracks other binds
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//Link Vertex Attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	shader.Use();
	shader.SetInt("texture0", 0);
	shader.SetInt("texture1", 1);

	//Unbind EBO
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glm::vec3 pos(0.0f, 0.0f, 0.0f);
	glm::vec3 velocity(0.4f, 0.25f, 0.0f);

	//#######################################
	//Render Loop
	//#######################################

	float prevTime = glfwGetTime();

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		float time = glfwGetTime();
		float green = (sin(time) / 2.0f) + 0.5f;

		glBindVertexArray(VAO);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textures[1]);
		
		shader.Use();

		//int uniColourLocation = glGetUniformLocation(shaderProgram, "uniColour");
		//glUniform4f(uniColourLocation, 0.0f, green, 0.0f, 1.0f);

		trans = glm::mat4(1.0f);
		trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
		trans = glm::rotate(trans, time, glm::vec3(0.0f, 0.0f, 1.0f));
		
		shader.SetMat4f("transform", trans);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		trans = glm::mat4(1.0f);
		trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.0f));
		float scale = abs(sin(time));
		trans = glm::scale(trans, glm::vec3(scale, scale, 1.0f));

		shader.SetMat4f("transform", trans);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		float delta = time - prevTime;
		pos += delta * velocity;

		if (pos.x >= 0.75f || pos.x <= -0.75f)
		{
			//std::cout << "X-BOUNCE\n";
			velocity.x = -velocity.x;
			//pos.x += velocity.x * delta;
		}
		if (pos.y >= 0.75f || pos.y <= -0.75f)
		{
			//std::cout << "Y-BOUNCE\n";
			velocity.y = -velocity.y;
			//pos.y += velocity.y * delta;
		}

		trans = glm::mat4(1.0f);
		trans = glm::translate(trans, pos);
		trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));

		shader.SetMat4f("transform", trans);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//glBindVertexArray(0);
		
		glfwSwapBuffers(window);
		glfwPollEvents();

		prevTime = time;
	}

	//De-allocate when done
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	//GLFW Destruction
	glfwTerminate();

	std::cout << "Goodbye!\n";

	return 0;
}