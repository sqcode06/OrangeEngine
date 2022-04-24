#pragma once

#include "OrangeEngineCore/Graphics/OpenGL/VertexArray.h"
#include "OrangeEngineCore/Graphics/OpenGL/Shader.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <memory>

namespace OrangeEngine
{
	class Light
	{
	public:
		Light(glm::vec3 position, glm::vec3 color, bool visualize, bool imgui_impl);

		bool init_visualize();
		void visualize(glm::mat4 view_projection_matrix);
		void imgui_impl();

		void set_position(glm::vec3 position) { m_position = position; }
		glm::vec3 get_position() const { return m_position; }
		void set_color(glm::vec3 color) { m_color = color; }
		glm::vec3 get_color() const { return m_color; }

	private:
		glm::vec3 m_position;
		glm::vec3 m_color;

		std::unique_ptr<Shader> m_p_shader;
		std::unique_ptr<VertexArray> m_p_vao;
		std::unique_ptr<VertexBuffer> m_p_positions_vbo;
		std::unique_ptr<IndexBuffer> m_p_ibo;

		float m_imgui_positions[3] = { 0.0f, 1.0f, 3.0f };
	};
}