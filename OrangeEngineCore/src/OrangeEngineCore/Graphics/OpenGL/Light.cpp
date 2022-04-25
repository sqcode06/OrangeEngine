#include "OrangeEngineCore/Graphics/OpenGL/Light.h"

#include <imgui/imgui.h>
#include <spdlog/spdlog.h>

namespace OrangeEngine
{
	Light::Light(glm::vec3 position, LightMaterial light_material, bool visualize, bool imgui_impl)
		:m_position(position),
		 m_light_material(light_material)
	{
		if (!visualize)
		{
			delete& m_p_shader;
			delete& m_p_vao;
			delete& m_p_positions_vbo;
			delete& m_p_ibo;
		}

		if (!imgui_impl)
		{
			delete m_imgui_positions;
		}
	}

	bool Light::init_visualize()
	{
		const char* vertex_shader =
			R"(
				#version 460
				layout(location = 0) in vec3 vertex_position;
				uniform mat4 model_matrix;
				uniform mat4 view_projection_matrix;
				void main() {
					gl_Position = view_projection_matrix * model_matrix * vec4(vertex_position, 1.0);
				}
		)";

		const char* fragment_shader =
			R"(
				#version 460
				uniform vec3 light_color;
				out vec4 frag_color;
				void main() {
					frag_color = vec4(light_color, 1.0);
				}
		)";

		m_p_shader = std::make_unique<Shader>(vertex_shader, fragment_shader);

		if (!m_p_shader->isCompiled())
		{
			return false;
		}

		BufferLayout buffer_layout_vec3
		{
			ShaderDataType::Float3
		};

		GLfloat positions[] = {
			 0.1f,  0.1f,  0.1f,
			-0.1f,  0.1f,  0.1f,
			 0.1f,  0.1f, -0.1f,
			-0.1f,  0.1f, -0.1f,
			 0.1f, -0.1f,  0.1f,
			-0.1f, -0.1f,  0.1f,
			 0.1f, -0.1f, -0.1f,
			-0.1f, -0.1f, -0.1f
		};

		GLuint indices[] = {
			1, 0, 2,
			1, 3, 2,
			1, 3, 7,
			1, 5, 7,
			0, 2, 6,
			0, 4, 6,
			3, 2, 6,
			3, 7, 6,
			1, 0, 4,
			1, 5, 4,
			4, 5, 7,
			4, 6, 7
		};
		
		m_p_vao = std::make_unique<VertexArray>();
		m_p_positions_vbo = std::make_unique<VertexBuffer>(positions, sizeof(positions), buffer_layout_vec3);
		m_p_ibo = std::make_unique<IndexBuffer>(indices, sizeof(indices) / sizeof(GLuint));

		m_p_vao->add_vbo(*m_p_positions_vbo);
		m_p_vao->set_ibo(*m_p_ibo);

		return true;
	}

	void Light::visualize(glm::mat4 view_projection_matrix)
	{
		glm::mat4 model_matrix = glm::translate(glm::mat4(1.0f), m_position);
		m_p_shader->bind();
		m_p_shader->setVec3("light_color", m_light_material.specular);
		m_p_shader->setMatrix4("model_matrix", model_matrix);
		m_p_shader->setMatrix4("view_projection_matrix", view_projection_matrix);

		m_p_vao->bind();
		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_p_vao->get_indices_quantity()), GL_UNSIGNED_INT, nullptr);
	}

	void Light::imgui_impl()
	{
		ImGui::SliderFloat3("Light position", m_imgui_positions, -10.f, 10.f);
		m_position = glm::vec3(m_imgui_positions[0], m_imgui_positions[1], m_imgui_positions[2]);
	}

	void Light::send_to_shader(std::unique_ptr<Shader>& shader, const char* material_name, short name_length)
	{
		if (name_length > 32)
		{
			spdlog::error("Name of the light material is too long, it must be no larger than 32 symbols.");
			return;
		}
		char buf[42];
		strcpy(buf, material_name);
		strcat(buf, ".ambient");
		shader->setVec3(buf, m_light_material.ambient);
		strcpy(buf, material_name);
		strcat(buf, ".diffuse");
		shader->setVec3(buf, m_light_material.diffuse);
		strcpy(buf, material_name);
		strcat(buf, ".specular");
		shader->setVec3(buf, m_light_material.specular);
	}
}