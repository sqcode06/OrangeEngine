#include "OrangeEngineCore/Graphics/OpenGL/Light/DirectionalLight.h"

#include <spdlog/spdlog.h>

namespace OrangeEngine
{
	DirectionalLight::DirectionalLight(glm::vec2 angle, LightMaterial lightMaterial)
	{
		glm::vec4 direction(1, 0, 0, 1);
		glm::mat4 matrix_xz;
		glm::mat4 matrix_vy;
		matrix_xz = glm::rotate(glm::mat4(1.0f), glm::radians(angle.x), glm::vec3(0, 1, 0));
		matrix_vy = glm::rotate(glm::mat4(1.0f), glm::radians(angle.y), glm::cross(glm::vec3(direction * matrix_xz), glm::vec3(0, 1, 0)));

		m_direction = glm::vec3(direction * matrix_xz * matrix_vy);
		m_light_material = lightMaterial;
	}

	void DirectionalLight::set_angle(glm::vec2 angle)
	{
		glm::vec4 direction(1, 0, 0, 1);
		glm::mat4 matrix_xz;
		glm::mat4 matrix_vy;
		matrix_xz = glm::rotate(glm::mat4(1.0f), glm::radians(angle.x), glm::vec3(0, 1, 0));
		matrix_vy = glm::rotate(glm::mat4(1.0f), glm::radians(angle.y), glm::cross(glm::vec3(direction * matrix_xz), glm::vec3(0, 1, 0)));

		m_direction = glm::vec3(direction * matrix_xz * matrix_vy);
	}

	void DirectionalLight::send_to_shader(std::unique_ptr<Shader>& shader, std::string name)
	{
		shader->set_vec3(name + ".ambient", m_light_material.ambient);
		shader->set_vec3(name + ".diffuse", m_light_material.diffuse);
		shader->set_vec3(name + ".specular", m_light_material.specular);
		shader->set_vec3(name + ".direction", m_direction);
	}
}