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

	void Material::send_to_shader(std::unique_ptr<Shader>& shader, const char* material_name, short name_length)
	{
		if (name_length > 32)
		{
			spdlog::error("Name of the material is too long, it must be no larger than 32 symbols.");
			return;
		}
		char buf[42];
		strcpy(buf, material_name);
		strcat(buf, ".ambient");
		shader->setVec3(buf, m_ambient);
		strcpy(buf, material_name);
		strcat(buf, ".diffuse");
		shader->setVec3(buf, m_diffuse);
		strcpy(buf, material_name);
		strcat(buf, ".specular");
		shader->setVec3(buf, m_specular);
		strcpy(buf, material_name);
		strcat(buf, ".shininess");
		shader->setFloat(buf, &m_shininess);
	}
}