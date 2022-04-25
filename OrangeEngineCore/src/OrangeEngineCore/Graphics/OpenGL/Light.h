#pragma once

#include "OrangeEngineCore/Graphics/OpenGL/VertexArray.h"
#include "OrangeEngineCore/Graphics/OpenGL/Shader.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <memory>

namespace OrangeEngine
{
	struct LightMaterial
	{
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};

	class Light
	{
	public:
		Light(glm::vec3 position, LightMaterial light_material, bool visualize, bool imgui_impl);

		bool init_visualize();
		void visualize(glm::mat4 view_projection_matrix);
		void imgui_impl();

		void set_position(glm::vec3 position) { m_position = position; }
		glm::vec3 get_position() const { return m_position; }
		void set_light_material(LightMaterial light_material) { m_light_material = light_material; }
		LightMaterial get_light_material() const { return m_light_material; }
		
		void send_to_shader(std::unique_ptr<Shader>& shader, const char* material_name, short name_length);

	private:
		glm::vec3 m_position;
		LightMaterial m_light_material;

		std::unique_ptr<Shader> m_p_shader;
		std::unique_ptr<VertexArray> m_p_vao;
		std::unique_ptr<VertexBuffer> m_p_positions_vbo;
		std::unique_ptr<IndexBuffer> m_p_ibo;

		float m_imgui_positions[3] = { 0.0f, 1.0f, 3.0f };
	};
}