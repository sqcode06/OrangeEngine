#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

#include <string>

namespace OrangeEngine
{
	class Shader
	{
	public:
		Shader(const char* vertexShaderSource, const char* fragmentShaderSource);
		Shader(const char* vertexShaderSource, const char* geometryShaderSource, const char* fragmentShaderSource);
		Shader(Shader&&) noexcept;
		Shader& operator=(Shader&&) noexcept;
		~Shader();

		Shader() = delete;
		Shader(const Shader&) = delete;
		Shader& operator=(const Shader&) = delete;

		void bind() const;
		static void unbind();
		bool is_compiled() const { return b_is_compiled; }

		void set_float(std::string name, const GLfloat* variable) const;
		void set_vec3(std::string name, glm::vec3& vec3) const;
		void set_matrix3(std::string name, glm::mat3& matrix3) const;
		void set_matrix4(std::string name, glm::mat4& matrix4) const;

	private:
		bool b_is_compiled = false;
		unsigned int m_id = 0;
	};
}