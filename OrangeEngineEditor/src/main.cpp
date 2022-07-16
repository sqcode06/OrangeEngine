#include <iostream>
#include <memory>

#include <OrangeEngineCore/Application.h>
#include <OrangeEngineCore/Input.h>
#include <imgui/imgui.h>

class OrangeEngineEditor : public OrangeEngine::Application
{
	virtual void on_update() override
	{
		bool move_camera = false;
		glm::vec3 movement_offset{ 0, 0, 0 };
		glm::vec3 rotation_offset{ 0, 0, 0 };
        if (OrangeEngine::Input::is_key_pressed(OrangeEngine::KeyCode::W))
        {
            movement_offset.x += 0.05f;
            move_camera = true;
        }
        if (OrangeEngine::Input::is_key_pressed(OrangeEngine::KeyCode::S))
        {
            movement_offset.x -= 0.05f;
            move_camera = true;
        }
        if (OrangeEngine::Input::is_key_pressed(OrangeEngine::KeyCode::A))
        {
            movement_offset.y -= 0.05f;
            move_camera = true;
        }
        if (OrangeEngine::Input::is_key_pressed(OrangeEngine::KeyCode::D))
        {
            movement_offset.y += 0.05f;
            move_camera = true;
        }
        if (OrangeEngine::Input::is_key_pressed(OrangeEngine::KeyCode::Space))
        {
            movement_offset.z += 0.05f;
            move_camera = true;
        }
        if (OrangeEngine::Input::is_key_pressed(OrangeEngine::KeyCode::LeftShift))
        {
            movement_offset.z -= 0.05f;
            move_camera = true;
        }

        if (move_camera)
        {
            camera.move_and_rotate(movement_offset, rotation_offset);
        }
	}

	void on_ui_draw() override
	{
        camera_position[0] = camera.get_camera_position().x;
        camera_position[1] = camera.get_camera_position().y;
        camera_position[2] = camera.get_camera_position().z;
        camera_rotation[0] = camera.get_camera_rotation().x;
        camera_rotation[1] = camera.get_camera_rotation().y;
        camera_rotation[2] = camera.get_camera_rotation().z;

		ImGui::Begin("Editor");
		//ImGui::ColorEdit4("Background color picker", imgui_color_array);
		//ImGui::SliderFloat3("Object scale", object_scale, 0.f, 2.f);
		//ImGui::SliderFloat("Object rotation", &object_rotation, 0.f, 360.f);
		//ImGui::SliderFloat3("Object position", object_position, -10.f, 10.f);

        if (ImGui::SliderFloat3("Camera position", camera_position, -10.f, 10.f))
        {
            camera.set_position(glm::vec3(camera_position[0], camera_position[1], camera_position[2]));
        }
        if (ImGui::SliderFloat3("Camera rotation", camera_rotation, 0, 360.f))
        {
            camera.set_rotation(glm::vec3(camera_rotation[0], camera_rotation[1], camera_rotation[2]));
        }
		ImGui::Checkbox("Perspective camera", &perspective_camera);

		ImGui::End();
	}
};

int main(int argc, char** argv)
{
	auto pOrangeEngineEditor = std::make_unique<OrangeEngineEditor>();
	int returnCode = pOrangeEngineEditor->start(1600, 900, "The coolest game ever!", argv);
	std::cin.get();
	return returnCode;
}