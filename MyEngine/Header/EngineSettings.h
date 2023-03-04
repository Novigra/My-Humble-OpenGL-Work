#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class EngineSettings
{
public:
	EngineSettings();

	bool vsync;
	bool showHelp;

	int activeLin;
	int activeQuad;

	glm::vec3 lightDir;

	glm::vec3 lightDirAmb;
	glm::vec3 lightDirDiff;
	glm::vec3 lightDirSpec;

	glm::vec3 lightPoAmb;
	glm::vec3 lightPoDiff;
	glm::vec3 lightPoSpec;

	float lightConst;
	float lightLin;
	float lightQuad;

	glm::vec3 lightSpAmb;
	glm::vec3 lightSpDiff;
	glm::vec3 lightSpSpec;

	float cutOff;
	float outerCutOff;

	glm::vec3 objectSpec;
	float shininess;

	glm::vec3 ModelPosition;

	glm::vec3 pointLightPositions;
	
	/** Work In Progress */
	static std::string OpenFile(const char* filter);
	static std::string SaveFile(const char* filter);
	
	void WindowSettings();
};
