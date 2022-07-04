#include "OrangeEngineCore/Graphics/OpenGL/Material.h"

#include <spdlog/spdlog.h>

namespace OrangeEngine
{
	Material::Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, GLfloat shininess)
		:m_ambient(ambient),
		 m_diffuse(diffuse),
		 m_specular(specular),
		 m_shininess(shininess)
	{}

	void Material::send_to_shader(std::unique_ptr<Shader>& shader, std::string name)
	{
		shader->set_vec3(name + ".ambient", m_ambient);
		shader->set_vec3(name + ".diffuse", m_diffuse);
		shader->set_vec3(name + ".specular", m_specular);
		shader->set_float(name + ".shininess", &m_shininess);
	}
}