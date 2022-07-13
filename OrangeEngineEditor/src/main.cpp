#include <iostream>
#include <memory>

#include <OrangeEngineCore/Application.h>
#include <OrangeEngineCore/Input.h>
#include <imgui/imgui.h>

class OrangeEngineEditor : public OrangeEngine::Application
{
	virtual void on_update() override
	{
		if (OrangeEngine::Input::is_key_pressed(OrangeEngine::KeyCode::LeftShift))
		{
			camera_position[1] -= 0.01f;
		}

		if (OrangeEngine::Input::is_key_pressed(OrangeEngine::KeyCode::Space))
		{
			camera_position[1] += 0.01f;
		}
	}

	void on_ui_draw() override
	{
		ImGui::Begin("Editor");
		//ImGui::ColorEdit4("Background color picker", imgui_color_array);
		//ImGui::SliderFloat3("Object scale", object_scale, 0.f, 2.f);
		//ImGui::SliderFloat("Object rotation", &object_rotation, 0.f, 360.f);
		//ImGui::SliderFloat3("Object position", object_position, -10.f, 10.f);

		ImGui::SliderFloat3("Camera position", camera_position, -10.f, 10.f);
		ImGui::SliderFloat3("Camera rotation", camera_rotation, -90.f, 90.f);
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