#pragma once

#include "OrangeEngineCore/Graphics/OpenGL/Light/LightMaterial.h"
#include "OrangeEngineCore/Graphics/OpenGL/Shader.h"

#include <glm/glm.hpp>

#include <memory>

namespace OrangeEngine
{
	class SpotLight
	{
	public:
		SpotLight(glm::vec3 position, glm::vec3 direction, glm::vec3 attenuation, GLfloat inner_cutoff, GLfloat outer_cutoff, LightMaterial light_material);

		void send_to_shader(std::unique_ptr<Shader>& shader, const char* name, short name_length);

		void set_position(glm::vec3 position) { m_position = position; }
		void set_direction(glm::vec3 direction) { m_direction = direction; }
		void set_attenuation(glm::vec3 attenuation) { m_attenuation = attenuation; }
		void set_inner_cutoff(GLfloat inner_cutoff) { m_inner_cutoff = glm::cos(glm::radians(inner_cutoff)); }
		void set_cutoff(GLfloat outer_cutoff) { m_outer_cutoff = glm::cos(glm::radians(outer_cutoff)); }

		glm::vec3 get_position() const { return m_position; }
		glm::vec3 get_direction() const { return m_direction; }
		glm::vec3 get_attenuation() const { return m_attenuation; }
		GLfloat get_inner_cutoff() const { return glm::degrees(glm::acos(m_inner_cutoff)); }
		GLfloat get_outer_cutoff() const { return glm::degrees(glm::acos(m_outer_cutoff)); }

	private:
		glm::vec3 m_position;
		glm::vec3 m_direction;
		glm::vec3 m_attenuation;
		GLfloat m_inner_cutoff;
		GLfloat m_outer_cutoff;
		LightMaterial m_light_material;
	};
}