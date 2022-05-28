#include <iostream>
#include <memory>

#include "OrangeEngineCore/Application.h"
#include <imgui/imgui.h>

class OrangeEngineEditor : public OrangeEngine::Application
{
	void onUpdate() override
	{

	}

	void onUIDraw() override
	{
		ImGui::Begin("Editor");
		//ImGui::ColorEdit4("Background color picker", imgui_color_array);
		//ImGui::SliderFloat3("Object scale", object_scale, 0.f, 2.f);
		//ImGui::SliderFloat("Object rotation", &object_rotation, 0.f, 360.f);
		//ImGui::SliderFloat3("Object position", object_position, -10.f, 10.f);

		ImGui::SliderFloat3("Camera position", camera_position, -10.f, 10.f);
		ImGui::SliderFloat3("Camera rotation", camera_rotation, 0.f, 360.f);
		ImGui::Checkbox("Perspective camera", &perspective_camera);

		ImGui::End();
	}
};

int main(int argc, char** argv)
{
	auto pOrangeEngineEditor = std::make_unique<OrangeEngineEditor>();
	int returnCode = pOrangeEngineEditor->start(1024, 1024, "The coolest game ever!", argv);
	std::cin.get();
	return returnCode;
}