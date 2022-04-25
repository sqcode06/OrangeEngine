#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>

namespace OrangeEngine
{
	class Shader
	{
	public:
		Shader(const char* vertex_shader_src, const char* fragment_shader_src);
		Shader(const char* vertex_shader_src, const char* geometry_shader_src, const char* fragment_shader_src);
		Shader(Shader&&) noexcept;
		Shader& operator=(Shader&&) noexcept;
		~Shader();

		Shader() = delete;
		Shader(const Shader&) = delete;
		Shader& operator=(const Shader&) = delete;

		void bind() const;
		static void unbind();
		bool isCompiled() const { return m_isCompiled; }

		void setFloat(const char* name, const GLfloat* var) const;
		void setVec3(const char* name, glm::vec3& vec) const;
		void setMatrix3(const char* name, glm::mat3& matrix) const;
		void setMatrix4(const char* name, glm::mat4& matrix) const;

	private:
		bool m_isCompiled = false;
		unsigned int m_id = 0;
	};
}