#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int WIDTH = 1200;
const unsigned int HEIGHT = 800;

int main()
{
	/*---------------Create The Window-------------*/
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Mohammed Abd El-Kareem(20102181)", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Falied to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to intialize GLAD" << std::endl;
		return -1;
	}

	/*------------------Build And Compile Shader------------------*/
	Shader shader("4.6.VertexShader.vert", "4.6.FragmentShader.frag");

	/*------------------Draw Vertices-------------------*/
	float firstTriangle[] = 
	{	//position			//color
		-0.9f, 0.5f, 0.0f,   1.0f,0.0f,0.0f,  // left 
		-0.7f, 0.5f, 0.0f,   1.0f,0.0f,0.0f,// right
		-0.8f, 0.8f, 0.0f,   1.0f,0.0f,0.0f// top 
	};

	float secondTriangle[] =
	{
		 0.5f, 0.0f, 0.0f, // left
		 0.7f, 0.0f, 0.0f, // right
		 0.6f, 0.3f, 0.0f  // top
	};
	
	float square[] =
	{
		 -0.3f, 0.5f, 0.0f,  // right bottom
		 -0.3f, 0.8f, 0.0f,  // right top
		 -0.5f, 0.8f, 0.0f,  // left top
		 -0.5f, 0.5f, 0.0f   // left bottom
	};

	float rectangle[] =
	{
		 0.4f,0.5f,0.0f, // right bottom
		 0.4f,0.8f,0.0f, // right top
		-0.1f,0.8f,0.0f, // left top
		-0.1f,0.5f,0.0f  // left bottom
	};

	float trapezoid[] =
	{
		0.5f,0.5f,0.0f, // left bottom
		0.6f,0.5f,0.0f, // middle
		0.55f,0.8f,0.0f, // top left
		0.66f,0.8f,0.0f, // top right
		0.7f,0.5f,0.0f  // right bottom
	};

	float pentagon[] =
	{
		 -0.5f,-0.5f,0.0f, // bottom left triangle 1
		 -0.2f,-0.5f,0.0f, // bottom right triangle 1 2
		 -0.3f,-0.2f,0.0f, // top triangles

		 -0.1f,-0.1f,0.0f, // triangle 2
		 -0.34f, 0.1f,0.0f, // triangle 3
		 -0.6f,-0.1f,0.0f  // triangle 4
	};

	unsigned int indices[] =
	{
		0,1,3,
		1,2,3
	};

	unsigned int indices2[] =
	{
		0,1,2,
		1,3,2,
		3,4,2,
		4,5,2,
		5,0,2
	};

	unsigned int indices3[] =
	{
		0,1,2,
		2,3,0,
		4,0,3
	};

	unsigned int VBO[6];
	unsigned int VAO[6];
	unsigned int EBO[4];
	
	glGenVertexArrays(6, VAO);
	glGenBuffers(6, VBO);
	glGenBuffers(4, EBO);

	/*-----------------First triangle---------------*/
	glBindVertexArray(VAO[0]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);

	//Position Attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Color Attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	/*-----------------Square---------------*/
	glBindVertexArray(VAO[1]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(square), square, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//Position Attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	/*-----------------rectangle---------------*/
	glBindVertexArray(VAO[2]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectangle), rectangle, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//Position Attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	/*-----------------Pentagon---------------*/
	glBindVertexArray(VAO[3]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pentagon), pentagon, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);

	//Position Attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	/*-----------------trapezoid---------------*/
	glBindVertexArray(VAO[4]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[4]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(trapezoid), trapezoid, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[3]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices3), indices3, GL_STATIC_DRAW);

	//Position Attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	/*-----------------secondTriangle---------------*/
	glBindVertexArray(VAO[5]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[5]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);

	//Position Attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	/*-------------------------Rendering----------------------------*/
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		
		/*------------Color Buffer-----------------*/
		glClearColor(0.3f, 0.6f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		/*------------Activate The Shader-----------------*/
		shader.use();

		glm::mat4 trans = glm::mat4(1.0f);
		unsigned int transformLoc = glGetUniformLocation(shader.ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &trans[0][0]);
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		trans = glm::mat4(1.0f);
		trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
		transformLoc = glGetUniformLocation(shader.ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
		glBindVertexArray(VAO[1]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		trans = glm::mat4(1.0f);
		transformLoc = glGetUniformLocation(shader.ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &trans[0][0]);
		glBindVertexArray(VAO[2]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		trans = glm::mat4(1.0f);
		transformLoc = glGetUniformLocation(shader.ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &trans[0][0]);
		glBindVertexArray(VAO[3]);
		glDrawElements(GL_TRIANGLES, 15, GL_UNSIGNED_INT, 0);

		trans = glm::mat4(1.0f);
		transformLoc = glGetUniformLocation(shader.ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &trans[0][0]);
		glBindVertexArray(VAO[4]);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		trans = glm::mat4(1.0f);
		trans = glm::translate(trans, glm::vec3(0.0f, sin((float)glfwGetTime()), 0.0f));
		transformLoc = glGetUniformLocation(shader.ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &trans[0][0]);
		glBindVertexArray(VAO[5]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		/*----------Swap Buffers------------*/
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}