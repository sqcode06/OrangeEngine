#include "OrangeEngineCore/Application.h"

#include "OrangeEngineCore/Window.h"
#include "OrangeEngineCore/Graphics/OpenGL/Shader.h"
#include "OrangeEngineCore/Graphics/OpenGL/VertexBuffer.h"
#include "OrangeEngineCore/Graphics/OpenGL/VertexArray.h"
#include "OrangeEngineCore/Graphics/OpenGL/Light/DirectionalLight.h"
#include "OrangeEngineCore/Graphics/OpenGL/Light/PointLight.h"
#include "OrangeEngineCore/Graphics/OpenGL/Light/SpotLight.h"
#include "OrangeEngineCore/Graphics/OpenGL/Material.h"
#include "OrangeEngineCore/Graphics/OpenGL/Texture.h"
#include "OrangeEngineCore/Graphics/OpenGL/Renderer_OpenGL.h"
#include "OrangeEngineCore/Modules/UIModule.h"
#include "OrangeEngineCore/ResourceLoader.h"
#include "OrangeEngineCore/Input.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>
#include <imgui/imgui.h>

namespace OrangeEngine
{
	GLfloat positions_and_normals[] = {
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f,

		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f
	};

	std::unique_ptr<Shader> p_object_shader;
	std::unique_ptr<VertexBuffer> p_positions_and_normals_vbo;
	std::unique_ptr<VertexArray> p_object_vao;
	
	std::unique_ptr<Texture> p_texture;

	float object_scale[3] = { 1.f, 1.f, 1.f };
	float object_rotation = 0.f;
	float object_position[3] = { 0.f, 0.f, 0.f };
	float imgui_color_array[4] = { 0.33f, 0.33f, 0.33f, 1.0f };

	std::unique_ptr<DirectionalLight> p_directional_light;
	std::unique_ptr<PointLight> p_point_light;
	std::unique_ptr<SpotLight> p_spot_light;

	Material material(glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(0.5f, 0.5f, 0.5f), 32.0f);
	 
	Application::Application()
	{
		spdlog::info("Application started. Logging session started.");
	}

	Application::~Application()
	{
		spdlog::info("Application closed. Logging session finished.");
	}

	void Application::show_cursor()
	{
		m_ptr_window->show_cursor();
	}

	void Application::hide_cursor()
	{
		m_ptr_window->hide_cursor();
	}

	int Application::start(unsigned int width, unsigned int height, const char* title, char** argv)
	{
		ResourceLoader::create_loader(argv[0]);
		m_ptr_window = std::make_unique<Window>(title, width, height);
		m_event_dispatcher.add_event_listener<EventWindowResize>(
			[&](EventWindowResize& event)
			{
				camera.set_aspect((float) event.width / (float) event.height);
			});
		m_event_dispatcher.add_event_listener<EventMouseMoved>(
			[&](EventMouseMoved& event)
			{
				if (!is_cursor_present)
				{
					glm::dvec3 rotation_offset = glm::vec3(0.f);

					rotation_offset.x += (m_ptr_window->get_width() / 2.f - event.x) / 10.f;
					rotation_offset.y += (m_ptr_window->get_height() / 2.f - event.y) * 16.f / 90.f;

					m_ptr_window->reset_cursor();

					camera.move_and_rotate(glm::vec3(0.f), rotation_offset);
				}
			});
		m_event_dispatcher.add_event_listener<EventWindowClose>(
			[&](EventWindowClose& event)
			{
				b_if_close_window = true;
			});
		m_event_dispatcher.add_event_listener<EventKeyPressed>(
			[&](EventKeyPressed& event)
			{
				Input::press_key(event.key_code);
			});
		m_event_dispatcher.add_event_listener<EventKeyReleased>(
			[&](EventKeyReleased& event)
			{
				Input::release_key(event.key_code);
			});
		m_ptr_window->set_event_callback(
			[&](BaseEvent& event)
			{
				m_event_dispatcher.dispatch(event);
			}
		);

		camera.set_aspect((float) m_ptr_window->get_width() / (float) m_ptr_window->get_height());

		ShaderData shaderData;
		if (!ResourceLoader::load_shader_data("object", true, false, shaderData))
		{
			spdlog::error("Failed to load shader data");
		}
		
		p_object_shader = std::make_unique<Shader>(shaderData.vertex_shader.c_str(), shaderData.fragment_shader.c_str());

		if (!p_object_shader->is_compiled())
		{
			return false;
		}

		BufferLayout buffer_layout
		{
			ShaderDataType::Float3,
			ShaderDataType::Float3,
			ShaderDataType::Float2
		};

		p_object_vao = std::make_unique<VertexArray>();
		p_positions_and_normals_vbo = std::make_unique<VertexBuffer>(positions_and_normals, sizeof(positions_and_normals), buffer_layout);

		p_object_vao->add_vbo(*p_positions_and_normals_vbo);
		//p_object_vao->set_ibo(*p_ibo);

		LightMaterial light_material;
		light_material.ambient = glm::vec3(0.2f);
		light_material.diffuse = glm::vec3(0.5f);
		light_material.specular = glm::vec3(1.0f);
		p_directional_light = std::make_unique<DirectionalLight>(glm::vec2(-90.0f, 60.0f), light_material);
		p_point_light = std::make_unique<PointLight>(glm::vec3(0.0f, 1.0f, 3.0f), glm::vec3(1.0f, 0.14f, 0.07f), light_material);
		p_spot_light = std::make_unique<SpotLight>(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0, 0, -1), glm::vec3(1.0f, 0.14f, 0.07f), 12.5f, 17.5f, light_material);

		p_texture = std::make_unique<Texture>("texture.jpg", TextureWrapType::MirroredRepeat, TextureFilterType::Linear, TextureFilterType::Linear, true, nullptr, false);

		while (!b_if_close_window)
		{
			Renderer_OpenGL::set_clear_color(imgui_color_array[0], imgui_color_array[1], imgui_color_array[2], imgui_color_array[3]);
			Renderer_OpenGL::clear();

			glm::mat4 model_matrix = glm::mat4(1.0f);
			model_matrix = glm::scale(model_matrix, glm::vec3(object_scale[0], object_scale[1], object_scale[2]));
			model_matrix = glm::rotate(model_matrix, glm::radians(object_rotation), glm::vec3(0, 0, 1));
			model_matrix = glm::translate(model_matrix, glm::vec3(object_position[0], object_position[1], object_position[2]));

			camera.set_projection_mode(perspective_camera ? Camera::ProjectionMode::Perspective : Camera::ProjectionMode::Orthographic);

			p_object_shader->bind();
			p_object_shader->set_vec3("view_pos", glm::vec3(camera_position[0], camera_position[1], camera_position[2]));
			p_object_shader->set_matrix4("model_matrix", model_matrix);
			p_object_shader->set_matrix4("view_projection_matrix", camera.get_projection_matrix() * camera.get_view_matrix());
			p_texture->bind();

			material.send_to_shader(p_object_shader, "material");
			p_directional_light->send_to_shader(p_object_shader, "directional_light");
			//p_point_light->send_to_shader(p_object_shader, "point_light");
			//p_spot_light->send_to_shader(p_object_shader, "spot_light");

			p_object_vao->bind();
			Renderer_OpenGL::draw(*p_object_vao, 36);
			//Renderer_OpenGL::draw_elements(*p_object_vao);

			UIModule::on_ui_draw_begin();

			ImGui::Begin("Options");

			ImGui::ColorEdit4("Background color picker", imgui_color_array);
			ImGui::SliderFloat3("Object scale", object_scale, 0.f, 2.f);
			ImGui::SliderFloat("Object rotation", &object_rotation, 0.f, 360.f);
			ImGui::SliderFloat3("Object position", object_position, -10.f, 10.f);

			ImGui::SliderFloat3("Camera position", camera_position, -10.f, 10.f);
			ImGui::SliderFloat3("Camera rotation", camera_rotation, 0.f, 360.f);
			ImGui::Checkbox("Perspective camera", &perspective_camera);

			ImGui::End();

			on_ui_draw();

			UIModule::on_ui_draw_end();

			m_ptr_window->on_update();
			on_update();
		}
		m_ptr_window = nullptr;
		return 0;
	}
}