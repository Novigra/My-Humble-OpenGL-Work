/** Engine Settings will handel anything related to the user interface */

#include "Header/EngineSettings.h"
#include <Windows.h>
#include <commdlg.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"

EngineSettings::EngineSettings()
{
	// Limit the framerate
	vsync = false;

	// Show the demo window to help construct my custom window
	showHelp = false;

	activeLin = -1;
	activeQuad = -1;

	/** Light Properties */

	// Directional light
	lightDir = glm::vec3(-0.2f, -1.0f, -0.3f);

	lightDirAmb = glm::vec3(0.05f, 0.05f, 0.05f);
	lightDirDiff = glm::vec3(0.4f, 0.4f, 0.4f);
	lightDirSpec = glm::vec3(0.5f, 0.5f, 0.5f);

	// Pointlight
	lightPoAmb = glm::vec3(0.05f, 0.05f, 0.05f);
	lightPoDiff = glm::vec3(0.8f, 0.8f, 0.8f);
	lightPoSpec = glm::vec3(1.0f, 1.0f, 1.0f);

	lightConst = 1.0f;
	lightLin = 0.09;
	lightQuad = 0.032f;

	// Spotlight
	lightSpAmb = glm::vec3(0.0f, 0.0f, 0.0f);
	lightSpDiff = glm::vec3(1.0f, 1.0f, 1.0f);
	lightSpSpec = glm::vec3(1.0f, 1.0f, 1.0f);

	cutOff = 12.5f;
	outerCutOff = 15.5f;

	objectSpec = glm::vec3(0.5f, 0.5f, 0.5f);
	shininess = 32.0f;

	/** Model Properties */
	ModelPosition = glm::vec3(0.0f, 0.0f, 0.0f);

	pointLightPositions = glm::vec3(0.7f, 0.2f, 2.0f);
}

// Open files (Work In Progress)
std::string EngineSettings::OpenFile(const char* filter)
{
	OPENFILENAMEA ofn;
	CHAR szFile[260] = { 0 };

	// Initialization
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	//ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)window);
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = filter;
	ofn.nFilterIndex = 1;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

	if (GetOpenFileNameA(&ofn) == TRUE)
	{
		return ofn.lpstrFile;
	}
	return std::string();
}

// Save files (Work In Progress)
std::string EngineSettings::SaveFile(const char* filter)
{
	return std::string();
}

void EngineSettings::WindowSettings()
{
	ImGui::Begin("MAT Testing");

	ImGui::Text("Test how light affects the objects.");
	ImGui::Checkbox("Enable Vsync", &vsync); // Limit the framerate
	ImGui::Checkbox("Show Help Window", &showHelp);

	/** Light properties */
	ImGui::Text("Light Properties:");

	ImGui::Text("Directional Light:");

	ImGui::DragFloat3("Directional Light Location", &lightDir.x, 0.03f, -100.0f, 100.0f);
	ImGui::ColorEdit3("Directonal(Ambient)", &lightDirAmb.x);
	ImGui::ColorEdit3("Directonal(Diffuse)", &lightDirDiff.x);
	ImGui::ColorEdit3("Directonal(Specular)", &lightDirSpec.x);

	ImGui::Text("Pointlight:");

	ImGui::DragFloat3("Light Location", &pointLightPositions.x, 0.03f, -100.0f, 100.0f);
	ImGui::ColorEdit3("Point(Ambient)", &lightPoAmb.x);
	ImGui::ColorEdit3("Point(Diffuse)", &lightPoDiff.x);
	ImGui::ColorEdit3("Point(Specular)", &lightPoSpec.x);

	ImGui::Text("Light Linear:");
	ImGui::RadioButton("0.7", &activeLin, 0); ImGui::SameLine();
	ImGui::RadioButton("0.35", &activeLin, 1); ImGui::SameLine();
	ImGui::RadioButton("0.22", &activeLin, 2); ImGui::SameLine();
	ImGui::RadioButton("0.14", &activeLin, 3); ImGui::SameLine();
	ImGui::RadioButton("0.09", &activeLin, 4);

	ImGui::Text("Light Quadratic:");
	ImGui::RadioButton("1.8", &activeQuad, 0); ImGui::SameLine();
	ImGui::RadioButton("0.44", &activeQuad, 1); ImGui::SameLine();
	ImGui::RadioButton("0.20", &activeQuad, 2); ImGui::SameLine();
	ImGui::RadioButton("0.07", &activeQuad, 3); ImGui::SameLine();
	ImGui::RadioButton("0.032", &activeQuad, 4);

	ImGui::Text("Spotlight:");

	ImGui::ColorEdit3("Spot(Ambient)", &lightSpAmb.x);
	ImGui::ColorEdit3("Spot(Diffuse)", &lightSpDiff.x);
	ImGui::ColorEdit3("Spot(Specular)", &lightSpSpec.x);

	ImGui::DragFloat("CutOff Degree", &cutOff, 0.03f, -100.0f, 100.0f);
	ImGui::DragFloat("CutOff Degree", &outerCutOff, 0.03f, -100.0f, 100.0f);

	ImGui::Text("Model:");
	ImGui::DragFloat3("Model Location", &ModelPosition.x, 0.03f, -100.0f, 100.0f);

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	if (!vsync)
	{
		glfwSwapInterval(0);
	}
	else
	{
		glfwSwapInterval(1);
	}

	if (showHelp)
	{
		ImGui::ShowDemoWindow();
	}

	if (activeLin == 0)
	{
		lightLin = 0.7f;
	}
	else if (activeLin == 1)
	{
		lightLin = 0.35f;
	}
	else if (activeLin == 2)
	{
		lightLin = 0.22f;
	}
	else if (activeLin == 3)
	{
		lightLin = 0.14f;
	}
	else if (activeLin == 4)
	{
		lightLin = 0.09f;
	}

	if (activeQuad == 0)
	{
		lightQuad = 1.8f;
	}
	else if (activeQuad == 1)
	{
		lightQuad = 0.44f;
	}
	else if (activeQuad == 2)
	{
		lightQuad = 0.20f;
	}
	else if (activeQuad == 3)
	{
		lightQuad = 0.07f;
	}
	else if (activeQuad == 4)
	{
		lightQuad = 0.032f;
	}

	ImGui::End();
}
