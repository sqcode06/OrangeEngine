#pragma once

#include "OrangeEngineCore/Graphics/OpenGL/Shader.h"

#include <glm/glm.hpp>

#include <memory>

namespace OrangeEngine
{
	class Material
	{
	public:
		Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, GLfloat shininess);

		void send_to_shader(std::unique_ptr<Shader>& shader, const char* material_name, short name_length);

	private:
		glm::vec3 m_ambient;
		glm::vec3 m_diffuse;
		glm::vec3 m_specular;
		GLfloat m_shininess;
	};
}