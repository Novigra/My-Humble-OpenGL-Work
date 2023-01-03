#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

//Window Resolution
const unsigned int WIDTH = 1200;
const unsigned int HEIGHT = 700;

//Camera Initial Values
float fov = 45.0f;
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

//Balance Speed
float deltaTime = 0.0f; //Time between 2 frames (current and last frames)
float lastFrame = 0.0f; //Last frame time

//Initialize Mouse Position
bool firstMouse = true;
float lastX = 400.0f;
float lastY = 300.0f;

//Initialize Yaw And Pitch
float yaw = -90.0f;
float pitch = 0.0f;

//Initialize Car Position
bool startPosition = true;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "My Engine - 20102181", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Falied to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to intialize GLAD" << std::endl;
		return -1;
	}
	/*------------------Hide The Cursor And Centerlize it-------------------*/
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	/*------------------Enable Depth-------------------*/
	glEnable(GL_DEPTH_TEST);

	/*------------------Build And Compile Shader------------------*/
	Shader shader("4.6.VertexShader.vert", "4.6.FragmentShader.frag");

	/*------------------Draw Vertices-------------------*/
	GLfloat RoadVertices[] =
	{
		-10.0f, -0.5f, -0.5f,  0.5f, 0.5f, 0.5f,
		 0.5f, -0.5f, -0.5f,  0.5f, 0.5f, 0.5f,
		 0.5f,  0.5f, -0.5f,  0.5f, 0.5f, 0.5f,
		 0.5f,  0.5f, -0.5f,  0.5f, 0.5f, 0.5f,
		-10.0f,  0.5f, -0.5f,  0.5f, 0.5f, 0.5f,
		-10.0f, -0.5f, -0.5f,  0.5f, 0.5f, 0.5f,

		-10.0f, -0.5f,  0.5f,  0.5f, 0.5f, 0.5f,
		 0.5f, -0.5f,  0.5f,  0.5f, 0.5f, 0.5f,
		 0.5f,  0.5f,  0.5f,  0.5f, 0.5f, 0.5f,
		 0.5f,  0.5f,  0.5f,  0.5f, 0.5f, 0.5f,
		-10.0f,  0.5f,  0.5f,  0.5f, 0.5f, 0.5f,
		-10.0f, -0.5f,  0.5f,  0.5f, 0.5f, 0.5f,

		-10.0f,  0.5f,  0.5f,  0.5f, 0.5f, 0.5f,
		-10.0f,  0.5f, -0.5f,  0.5f, 0.5f, 0.5f,
		-10.0f, -0.5f, -0.5f,  0.5f, 0.5f, 0.5f,
		-10.0f, -0.5f, -0.5f,  0.5f, 0.5f, 0.5f,
		-10.0f, -0.5f,  0.5f,  0.5f, 0.5f, 0.5f,
		-10.0f,  0.5f,  0.5f,  0.5f, 0.5f, 0.5f,

		 0.5f,  0.5f,  0.5f,  0.5f, 0.5f, 0.5f,
		 0.5f,  0.5f, -0.5f,  0.5f, 0.5f, 0.5f,
		 0.5f, -0.5f, -0.5f,  0.5f, 0.5f, 0.5f,
		 0.5f, -0.5f, -0.5f,  0.5f, 0.5f, 0.5f,
		 0.5f, -0.5f,  0.5f,  0.5f, 0.5f, 0.5f,
		 0.5f,  0.5f,  0.5f,  0.5f, 0.5f, 0.5f,

		-10.0f, -0.5f, -0.5f,  0.5f, 0.5f, 0.5f,
		 0.5f, -0.5f, -0.5f,  0.5f, 0.5f, 0.5f,
		 0.5f, -0.5f,  0.5f,  0.5f, 0.5f, 0.5f,
		 0.5f, -0.5f,  0.5f,  0.5f, 0.5f, 0.5f,
		-10.0f, -0.5f,  0.5f,  0.5f, 0.5f, 0.5f,
		-10.0f, -0.5f, -0.5f,  0.5f, 0.5f, 0.5f,

		-10.0f,  0.5f, -0.5f,  0.5f, 0.5f, 0.5f,
		 0.5f,  0.5f, -0.5f,  0.5f, 0.5f, 0.5f,
		 0.5f,  0.5f,  0.5f,  0.5f, 0.5f, 0.5f,
		 0.5f,  0.5f,  0.5f,  0.5f, 0.5f, 0.5f,
		-10.0f,  0.5f,  0.5f,  0.5f, 0.5f, 0.5f,
		-10.0f,  0.5f, -0.5f,  0.5f, 0.5f, 0.5f
	};

	GLfloat StripsVertices[] =
	{
		-10.0f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
		-10.0f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
		-10.0f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,

		-10.0f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
		-10.0f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
		-10.0f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,

		-10.0f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
		-10.0f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
		-10.0f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
		-10.0f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
		-10.0f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
		-10.0f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,

		-10.0f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
		-10.0f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
		-10.0f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,

		-10.0f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
		-10.0f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
		-10.0f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f
	};

	GLfloat MetalVertices[] =
	{
		-10.0f, -0.5f, -0.5f,  0.8f, 0.8f, 0.8f,
		 0.5f, -0.5f, -0.5f,  0.8f, 0.8f, 0.8f,
		 0.5f,  0.5f, -0.5f,  0.8f, 0.8f, 0.8f,
		 0.5f,  0.5f, -0.5f,  0.8f, 0.8f, 0.8f,
		-10.0f,  0.5f, -0.5f,  0.8f, 0.8f, 0.8f,
		-10.0f, -0.5f, -0.5f,  0.8f, 0.8f, 0.8f,

		-10.0f, -0.5f,  0.5f,  0.8f, 0.8f, 0.8f,
		 0.5f, -0.5f,  0.5f,  0.8f, 0.8f, 0.8f,
		 0.5f,  0.5f,  0.5f,  0.8f, 0.8f, 0.8f,
		 0.5f,  0.5f,  0.5f,  0.8f, 0.8f, 0.8f,
		-10.0f,  0.5f,  0.5f,  0.8f, 0.8f, 0.8f,
		-10.0f, -0.5f,  0.5f,  0.8f, 0.8f, 0.8f,

		-10.0f,  0.5f,  0.5f,  0.8f, 0.8f, 0.8f,
		-10.0f,  0.5f, -0.5f,  0.8f, 0.8f, 0.8f,
		-10.0f, -0.5f, -0.5f,  0.8f, 0.8f, 0.8f,
		-10.0f, -0.5f, -0.5f,  0.8f, 0.8f, 0.8f,
		-10.0f, -0.5f,  0.5f,  0.8f, 0.8f, 0.8f,
		-10.0f,  0.5f,  0.5f,  0.8f, 0.8f, 0.8f,

		 0.5f,  0.5f,  0.5f,  0.8f, 0.8f, 0.8f,
		 0.5f,  0.5f, -0.5f,  0.8f, 0.8f, 0.8f,
		 0.5f, -0.5f, -0.5f,  0.8f, 0.8f, 0.8f,
		 0.5f, -0.5f, -0.5f,  0.8f, 0.8f, 0.8f,
		 0.5f, -0.5f,  0.5f,  0.8f, 0.8f, 0.8f,
		 0.5f,  0.5f,  0.5f,  0.8f, 0.8f, 0.8f,

		-10.0f, -0.5f, -0.5f,  0.8f, 0.8f, 0.8f,
		 0.5f, -0.5f, -0.5f,  0.8f, 0.8f, 0.8f,
		 0.5f, -0.5f,  0.5f,  0.8f, 0.8f, 0.8f,
		 0.5f, -0.5f,  0.5f,  0.8f, 0.8f, 0.8f,
		-10.0f, -0.5f,  0.5f,  0.8f, 0.8f, 0.8f,
		-10.0f, -0.5f, -0.5f,  0.8f, 0.8f, 0.8f,

		-10.0f,  0.5f, -0.5f,  0.8f, 0.8f, 0.8f,
		 0.5f,  0.5f, -0.5f,  0.8f, 0.8f, 0.8f,
		 0.5f,  0.5f,  0.5f,  0.8f, 0.8f, 0.8f,
		 0.5f,  0.5f,  0.5f,  0.8f, 0.8f, 0.8f,
		-10.0f,  0.5f,  0.5f,  0.8f, 0.8f, 0.8f,
		-10.0f,  0.5f, -0.5f,  0.8f, 0.8f, 0.8f
	};

	GLfloat CarVertices[] =
	{
		-10.0f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		-10.0f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		-10.0f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,

		-10.0f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
		-10.0f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
		-10.0f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,

		-10.0f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
		-10.0f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		-10.0f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		-10.0f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		-10.0f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
		-10.0f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,

		-10.0f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
		-10.0f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
		-10.0f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,

		-10.0f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
		-10.0f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
		-10.0f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f
	};

	GLfloat CubeVertices[] =
	{
		-10.0f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		-10.0f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		-10.0f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,

		-10.0f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
		-10.0f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
		-10.0f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,

		-10.0f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
		-10.0f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		-10.0f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		-10.0f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		-10.0f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
		-10.0f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,

		-10.0f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
		-10.0f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
		-10.0f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,

		-10.0f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
		-10.0f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
		-10.0f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f
	};

	GLfloat stopVertices[] =
	{
		-10.0f, -0.5f, -0.5f,  1.0f, 0.5f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.5f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 0.5f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 0.5f, 0.0f,
		-10.0f,  0.5f, -0.5f,  1.0f, 0.5f, 0.0f,
		-10.0f, -0.5f, -0.5f,  1.0f, 0.5f, 0.0f,

		-10.0f, -0.5f,  0.5f,  1.0f, 0.5f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.5f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.5f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.5f, 0.0f,
		-10.0f,  0.5f,  0.5f,  1.0f, 0.5f, 0.0f,
		-10.0f, -0.5f,  0.5f,  1.0f, 0.5f, 0.0f,

		-10.0f,  0.5f,  0.5f,  1.0f, 0.5f, 0.0f,
		-10.0f,  0.5f, -0.5f,  1.0f, 0.5f, 0.0f,
		-10.0f, -0.5f, -0.5f,  1.0f, 0.5f, 0.0f,
		-10.0f, -0.5f, -0.5f,  1.0f, 0.5f, 0.0f,
		-10.0f, -0.5f,  0.5f,  1.0f, 0.5f, 0.0f,
		-10.0f,  0.5f,  0.5f,  1.0f, 0.5f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.5f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 0.5f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.5f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.5f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.5f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.5f, 0.0f,

		-10.0f, -0.5f, -0.5f,  1.0f, 0.5f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.5f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.5f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.5f, 0.0f,
		-10.0f, -0.5f,  0.5f,  1.0f, 0.5f, 0.0f,
		-10.0f, -0.5f, -0.5f,  1.0f, 0.5f, 0.0f,

		-10.0f,  0.5f, -0.5f,  1.0f, 0.5f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 0.5f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.5f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.5f, 0.0f,
		-10.0f,  0.5f,  0.5f,  1.0f, 0.5f, 0.0f,
		-10.0f,  0.5f, -0.5f,  1.0f, 0.5f, 0.0f
	};

	/*------------------Draw Multiple Objects-------------------*/
	glm::vec3 CarPosition[] =
	{
		glm::vec3(3.0f,0.5f,0.7f),
		glm::vec3(2.5f,1.0f,0.7f),
		glm::vec3(1.7f,1.0f,0.7f)
	};
	glm::vec3 newCarPosition[] =
	{
		glm::vec3(3.0f,0.5f,0.7f)
	};

	glm::vec3 CubePosition[] =
	{
		glm::vec3(1.65f,1.0f,0.7f),
		glm::vec3(2.3f,0.9f,0.9f),
		glm::vec3(2.3f,0.9f,0.5f)
	};

	glm::vec3 RoadPosition[] =
	{
		glm::vec3(3.0f,0.0f,0.0f)
	};

	glm::vec3 StripsPositions[] =
	{
		glm::vec3(3.0f,0.0f,0.0f),
		glm::vec3(1.0f,0.0f,0.0f),
		glm::vec3(-1.0f,0.0f,0.0f),
		glm::vec3(-3.0f,0.0f,0.0f)
	};

	glm::vec3 MetalPositions[] =
	{
		glm::vec3(3.0f,0.5f,1.5f),
		glm::vec3(1.5f,0.5f,1.5f),
		glm::vec3(-1.0f,0.5f,1.5f),
		glm::vec3(-3.0f,0.5f,1.5f),

		glm::vec3(3.0f,0.5f,-1.5f),
		glm::vec3(1.5f,0.5f,-1.5f),
		glm::vec3(-1.0f,0.5f,-1.5f),
		glm::vec3(-3.0f,0.5f,-1.5f)
	};

	glm::vec3 stopPositions[] =
	{
		glm::vec3(3.3f,1.0f,1.5f),
		glm::vec3(3.3f,1.0f,1.5f)
	};

	unsigned int VBO[6];
	unsigned int VAO[6];
	unsigned int EBO;

	glGenVertexArrays(6, VAO);
	glGenBuffers(6, VBO);
	glGenBuffers(1, &EBO);

	/*------------------Road-------------------*/
	glBindVertexArray(VAO[0]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(RoadVertices), RoadVertices, GL_STATIC_DRAW);

	//Position Attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Color Attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	/*------------------Road Strips-------------------*/
	glBindVertexArray(VAO[1]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(StripsVertices), StripsVertices, GL_STATIC_DRAW);

	//Position Attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Color Attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	/*------------------Metal-------------------*/
	glBindVertexArray(VAO[2]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(MetalVertices), MetalVertices, GL_STATIC_DRAW);

	//Position Attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Color Attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	/*------------------Car-------------------*/
	glBindVertexArray(VAO[3]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(CarVertices), CarVertices, GL_STATIC_DRAW);

	//Position Attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Color Attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	/*------------------Cube-------------------*/
	glBindVertexArray(VAO[4]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[4]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(CubeVertices), CubeVertices, GL_STATIC_DRAW);

	//Position Attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Color Attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	/*------------------Stop-------------------*/
	glBindVertexArray(VAO[5]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[5]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(stopVertices), stopVertices, GL_STATIC_DRAW);

	//Position Attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Color Attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	/*-----------------Texture---------------------*/
	
	//Generate the texture one
	/*unsigned int texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	
	//Set texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	//Texture filtering(Setting MIPMAPS)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Load the image
	int width, height, nrChannels;
	unsigned char* data = stbi_load("fire.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load the textures" << std::endl;
	}
	stbi_image_free(data);
	
	//Generate the texture two
	unsigned int texture2;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	//Set texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	//Texture filtering(Setting MIPMAPS)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Load the image	
	data = stbi_load("Kermit.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load the textures" << std::endl;
	}
	stbi_image_free(data);*/
	
	//Activate the shader
	shader.use();

	/*-------------------------Rendering----------------------------*/
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		
		/*------------Color Buffer-----------------*/
		glClearColor(0.3f, 0.6f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/*------------------------Setting Up World Coordinates-----------------------*/
		const float radius = 10.0f;
		float camX = sin(glfwGetTime()) * radius;
		float camZ = cos(glfwGetTime()) * radius;

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);

		

		int viewLoc = glGetUniformLocation(shader.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		int projectionLoc = glGetUniformLocation(shader.ID, "projection");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));


		/*------------------------Road-----------------------*/
		glBindVertexArray(VAO[0]);
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, RoadPosition[0]);
		float angle = 0.0f;
		model = glm::rotate(model, glm::radians(angle), glm::vec3(0.5f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.7, 0.1, 3.0));
		int modelLoc = glGetUniformLocation(shader.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		/*------------------------Road Strips-----------------------*/
		for (int i = 0; i < 4; i++)
		{
			glBindVertexArray(VAO[1]);
			model = glm::mat4(1.0f);
			model = glm::translate(model, StripsPositions[i]);
			angle = 0.0f;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(0.5f, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(0.1, 0.15, 0.1));
			modelLoc = glGetUniformLocation(shader.ID, "model");
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		/*------------------------Metal-----------------------*/
		for (int i = 0; i < 8; i++)
		{
			glBindVertexArray(VAO[2]);
			if (i == 0 || i == 4)
			{
				model = glm::mat4(1.0f);
				model = glm::translate(model, MetalPositions[i]);
				angle = 0.0f;
				model = glm::rotate(model, glm::radians(angle), glm::vec3(0.5f, 1.0f, 0.0f));
				model = glm::scale(model, glm::vec3(0.7, 0.15, 0.1));
				modelLoc = glGetUniformLocation(shader.ID, "model");
				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
			else
			{
				model = glm::mat4(1.0f);
				model = glm::translate(model, MetalPositions[i]);
				angle = 90.0f;
				model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
				model = glm::scale(model, glm::vec3(0.1, 0.15, 0.1));
				modelLoc = glGetUniformLocation(shader.ID, "model");
				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
			
		}

		/*------------------------Car-----------------------*/
		for (int i = 0; i < 3; i++)
		{
			if (startPosition)
			{
				startPosition = false;

				if (i == 0)
				{
					glBindVertexArray(VAO[3]);
					model = glm::mat4(1.0f);
					model = glm::translate(model, CarPosition[i]);
					angle = 0.0f;
					model = glm::rotate(model, glm::radians(angle), glm::vec3(0.5f, 1.0f, 0.0f));
					model = glm::scale(model, glm::vec3(0.2, 0.5, 1.0));
					modelLoc = glGetUniformLocation(shader.ID, "model");
					glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
					glDrawArrays(GL_TRIANGLES, 0, 36);
				}
				else if (i == 1)
				{
					glBindVertexArray(VAO[3]);
					model = glm::mat4(1.0f);
					model = glm::translate(model, CarPosition[i]);
					angle = 0.0f;
					model = glm::rotate(model, glm::radians(angle), glm::vec3(0.5f, 1.0f, 0.0f));
					model = glm::scale(model, glm::vec3(0.1, 0.5, 1.0));
					modelLoc = glGetUniformLocation(shader.ID, "model");
					glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
					glDrawArrays(GL_TRIANGLES, 0, 36);
				}
				else if (i == 2)
				{
					glBindVertexArray(VAO[3]);
					model = glm::mat4(1.0f);
					model = glm::translate(model, CarPosition[i]);
					angle = 60.0f;
					model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
					model = glm::scale(model, glm::vec3(0.05, 0.5, 1.0));
					modelLoc = glGetUniformLocation(shader.ID, "model");
					glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
					glDrawArrays(GL_TRIANGLES, 0, 36);
				}
			}
		}

		for (int i = 0; i < 3; i++)
		{
			if (!startPosition)
			{
				if (i == 0)
				{
					glBindVertexArray(VAO[3]);
					model = glm::mat4(1.0f);
					newCarPosition[0] = newCarPosition[0] + glm::vec3(glfwGetTime(), 0.0f, 0.0f);
					
					//std::cout << glm::to_string(newCarPosition[0]) << std::endl;
					std::cout << glfwGetTime() << std::endl;

					model = glm::translate(model, CarPosition[i] + glm::vec3(glfwGetTime(), 0.0f, 0.0f));
					angle = 0.0f;
					model = glm::rotate(model, glm::radians(angle), glm::vec3(0.5f, 1.0f, 0.0f));
					model = glm::scale(model, glm::vec3(0.2, 0.5, 1.0));
					modelLoc = glGetUniformLocation(shader.ID, "model");
					glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
					glDrawArrays(GL_TRIANGLES, 0, 36);

					std::string test = "vec3(40333.574219, 0.500000, 0.700000)";
					if (glfwGetTime() > 5)
					{
						startPosition = true;
						std::cout << "OBJECT REACHED DESTINATION" << std::endl;
					}
				}
				else if (i == 1)
				{
					glBindVertexArray(VAO[3]);
					model = glm::mat4(1.0f);
					model = glm::translate(model, CarPosition[i] + glm::vec3(glfwGetTime(), 0.0f, 0.0f));
					angle = 0.0f;
					model = glm::rotate(model, glm::radians(angle), glm::vec3(0.5f, 1.0f, 0.0f));
					model = glm::scale(model, glm::vec3(0.1, 0.5, 1.0));
					modelLoc = glGetUniformLocation(shader.ID, "model");
					glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
					glDrawArrays(GL_TRIANGLES, 0, 36);
				}
				else if (i == 2)
				{
					glBindVertexArray(VAO[3]);
					model = glm::mat4(1.0f);
					model = glm::translate(model, CarPosition[i] + glm::vec3(glfwGetTime(), 0.0f, 0.0f));
					angle = 60.0f;
					model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
					model = glm::scale(model, glm::vec3(0.05, 0.5, 1.0));
					modelLoc = glGetUniformLocation(shader.ID, "model");
					glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
					glDrawArrays(GL_TRIANGLES, 0, 36);
				}
			}
		}

		/*------------------------Cube-----------------------*/
		for (int i = 0; i < 3; i++)
		{
			if (i == 0)
			{
				glBindVertexArray(VAO[4]);
				model = glm::mat4(1.0f);
				model = glm::translate(model, CubePosition[i]);
				angle = 60.0f;
				model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
				model = glm::scale(model, glm::vec3(0.05, 0.5, 0.8));
				modelLoc = glGetUniformLocation(shader.ID, "model");
				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
			else if (i == 1)
			{
				glBindVertexArray(VAO[4]);
				model = glm::mat4(1.0f);
				model = glm::translate(model, CubePosition[i]);
				angle = 0.0f;
				model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
				model = glm::scale(model, glm::vec3(0.07, 0.5, 0.8));
				modelLoc = glGetUniformLocation(shader.ID, "model");
				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
			else if (i == 2)
			{
				glBindVertexArray(VAO[4]);
				model = glm::mat4(1.0f);
				model = glm::translate(model, CubePosition[i]);
				angle = 0.0f;
				model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
				model = glm::scale(model, glm::vec3(0.07, 0.5, 0.8));
				modelLoc = glGetUniformLocation(shader.ID, "model");
				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
		}

		/*------------------------StopCar-----------------------*/
		for (int i = 0; i < 2; i++)
		{
			if (i == 0)
			{
				glBindVertexArray(VAO[5]);
				model = glm::mat4(1.0f);
				model = glm::translate(model, stopPositions[i]);
				angle = 90.0f;
				model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
				model = glm::scale(model, glm::vec3(0.1, 0.15, 0.1));
				modelLoc = glGetUniformLocation(shader.ID, "model");
				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
			else if (i == 1)
			{
				glBindVertexArray(VAO[5]);
				model = glm::mat4(1.0f);
				model = glm::translate(model, stopPositions[i]);
				angle = 90.0f;
				model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
				model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
				model = glm::rotate(model, sin((float)glfwGetTime()), glm::vec3(0.0f, 0.0f, 1.0f));
				model = glm::scale(model, glm::vec3(0.1, 0.15, 0.1));
				modelLoc = glGetUniformLocation(shader.ID, "model");
				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}

		}
		

		/*------------Activate The Shader-----------------*/
		shader.use();
		/*----------Swap Buffers------------*/
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(2, VAO);
	glDeleteBuffers(2, VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}

/*------------------------User Input-----------------------*/
void processInput(GLFWwindow* window)
{
	const float cameraSpeed = 3.5f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

/*------------------------Viewport Refresh Rate-----------------------*/
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

/*------------------------Mouse Rotations-----------------------*/
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	
	lastX = xpos;
	lastY = ypos;

	const float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(direction);
}

/*------------------------Mouse Zooming-----------------------*/
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	fov -= (float)yoffset;
	if (fov < 1.0f)
		fov = 1.0f;
	if (fov > 45.0f)
		fov = 45.0f;
}
