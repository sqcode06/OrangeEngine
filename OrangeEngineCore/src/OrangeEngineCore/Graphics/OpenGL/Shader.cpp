#include "Shader.h"

#include <glad/glad.h>
#include <spdlog/spdlog.h>

namespace OrangeEngine
{
	bool create_shader(const char* source, const GLenum shader_type, GLuint& shader_id)
	{
		shader_id = glCreateShader(shader_type);
		glShaderSource(shader_id, 1, &source, nullptr);
		glCompileShader(shader_id);

		GLint success;
		glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE)
		{
			char info_log[1024];
			glGetShaderInfoLog(shader_id, 1024, nullptr, info_log);

			spdlog::critical("Shader compilation error:\n{}", info_log);
			return false;
		}
		return true;
	}

	Shader::Shader(const char* vertex_shader_src, const char* fragment_shader_src)
	{
		GLuint vertex_shader_id = 0;
		if (!create_shader(vertex_shader_src, GL_VERTEX_SHADER, vertex_shader_id))
		{
			spdlog::critical("Vertex shader: compile error!");
			glDeleteShader(vertex_shader_id);
			return;
		}

		GLuint fragment_shader_id = 0;
		if (!create_shader(fragment_shader_src, GL_FRAGMENT_SHADER, fragment_shader_id))
		{
			spdlog::critical("Fragment shader: compile error!");
			glDeleteShader(vertex_shader_id);
			glDeleteShader(fragment_shader_id);
			return;
		}

		m_id = glCreateProgram();
		glAttachShader(m_id, vertex_shader_id);
		glAttachShader(m_id, fragment_shader_id);
		glLinkProgram(m_id);

		GLint success;
		glGetProgramiv(m_id, GL_LINK_STATUS, &success);
		if (success == GL_FALSE)
		{
			GLchar info_log[1024];
			glGetProgramInfoLog(m_id, 1024, nullptr, info_log);
			spdlog::critical("SHADER PROGRAM: Link-time error:\n{0}", info_log);
			glDeleteProgram(m_id);
			m_id = 0;
			glDeleteShader(vertex_shader_id);
			glDeleteShader(fragment_shader_id);
			return;
		}
		else
		{
			m_isCompiled = true;
		}

		glDetachShader(m_id, vertex_shader_id);
		glDetachShader(m_id, fragment_shader_id);
		glDeleteShader(vertex_shader_id);
		glDeleteShader(fragment_shader_id);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_id);
	}

	void Shader::bind() const
	{
		glUseProgram(m_id);
	}

	void Shader::unbind()
	{
		glUseProgram(0);
	}

	Shader& Shader::operator=(Shader&& shader) noexcept
	{
		glDeleteProgram(m_id);
		m_id = shader.m_id;
		m_isCompiled = shader.m_isCompiled;

		shader.m_id = 0;
		shader.m_isCompiled = false;
		return *this;
	}

	Shader::Shader(Shader&& shader) noexcept
	{
		m_id = shader.m_id;
		m_isCompiled = shader.m_isCompiled;

		shader.m_id = 0;
		shader.m_isCompiled = false;
	}

	void Shader::setMatrix4(const char* name, glm::mat4& matrix) const
	{
		glUniformMatrix4fv(glGetUniformLocation(m_id, name), 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void Shader::setVec3(const char* name, glm::vec3& vec) const
	{
		glUniform3fv(glGetUniformLocation(m_id, name), 1, glm::value_ptr(vec));
	}
}