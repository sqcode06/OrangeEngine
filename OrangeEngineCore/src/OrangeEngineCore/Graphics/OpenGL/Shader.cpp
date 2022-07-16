#include "Shader.h"

#include <glad/glad.h>
#include <spdlog/spdlog.h>

namespace OrangeEngine
{
	bool create_shader(const char* source, const GLenum shaderType, GLuint& shaderID)
	{
		shaderID = glCreateShader(shaderType);
		glShaderSource(shaderID, 1, &source, nullptr);
		glCompileShader(shaderID);

		GLint success;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE)
		{
			char info_log[1024];
			glGetShaderInfoLog(shaderID, 1024, nullptr, info_log);

			spdlog::critical("Shader compilation error:\n{}", info_log);
			return false;
		}
		return true;
	}

	Shader::Shader(const char* vertexShaderSource, const char* fragmentShaderSource)
	{
		GLuint vertex_shader_id = 0;
		if (!create_shader(vertexShaderSource, GL_VERTEX_SHADER, vertex_shader_id))
		{
			spdlog::critical("Vertex shader: compile error!");
			glDeleteShader(vertex_shader_id);
			return;
		}

		GLuint fragment_shader_id = 0;
		if (!create_shader(fragmentShaderSource, GL_FRAGMENT_SHADER, fragment_shader_id))
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
			spdlog::critical("Shader program: link-time error:\n{0}", info_log);
			glDeleteProgram(m_id);
			m_id = 0;
			glDeleteShader(vertex_shader_id);
			glDeleteShader(fragment_shader_id);
			return;
		}
		else
		{
			b_is_compiled = true;
		}

		glDetachShader(m_id, vertex_shader_id);
		glDetachShader(m_id, fragment_shader_id);
		glDeleteShader(vertex_shader_id);
		glDeleteShader(fragment_shader_id);
	}

	Shader::Shader(const char* vertexShaderSource, const char* geometryShaderSource, const char* fragmentShaderSource)
	{
		GLuint vertex_shader_id = 0;
		if (!create_shader(vertexShaderSource, GL_VERTEX_SHADER, vertex_shader_id))
		{
			spdlog::critical("Vertex shader: compile error!");
			glDeleteShader(vertex_shader_id);
			return;
		}

		GLuint geometry_shader_id = 0;
		if (!create_shader(geometryShaderSource, GL_GEOMETRY_SHADER, geometry_shader_id))
		{
			spdlog::critical("Geometry shader: compile error!");
			glDeleteShader(vertex_shader_id);
			glDeleteShader(geometry_shader_id);
			return;
		}

		GLuint fragment_shader_id = 0;
		if (!create_shader(fragmentShaderSource, GL_FRAGMENT_SHADER, fragment_shader_id))
		{
			spdlog::critical("Fragment shader: compile error!");
			glDeleteShader(vertex_shader_id);
			glDeleteShader(geometry_shader_id);
			glDeleteShader(fragment_shader_id);
			return;
		}

		m_id = glCreateProgram();
		glAttachShader(m_id, vertex_shader_id);
		glAttachShader(m_id, geometry_shader_id);
		glAttachShader(m_id, fragment_shader_id);
		glLinkProgram(m_id);

		GLint success;
		glGetProgramiv(m_id, GL_LINK_STATUS, &success);
		if (success == GL_FALSE)
		{
			GLchar info_log[1024];
			glGetProgramInfoLog(m_id, 1024, nullptr, info_log);
			spdlog::critical("Shader program: link-time error:\n{0}", info_log);
			glDeleteProgram(m_id);
			m_id = 0;
			glDeleteShader(vertex_shader_id);
			glDeleteShader(geometry_shader_id);
			glDeleteShader(fragment_shader_id);
			return;
		}
		else
		{
			b_is_compiled = true;
		}

		glDetachShader(m_id, vertex_shader_id);
		glDetachShader(m_id, geometry_shader_id);
		glDetachShader(m_id, fragment_shader_id);
		glDeleteShader(vertex_shader_id);
		glDeleteShader(geometry_shader_id);
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
		b_is_compiled = shader.b_is_compiled;

		shader.m_id = 0;
		shader.b_is_compiled = false;
		return *this;
	}

	Shader::Shader(Shader&& shader) noexcept
	{
		m_id = shader.m_id;
		b_is_compiled = shader.b_is_compiled;

		shader.m_id = 0;
		shader.b_is_compiled = false;
	}

	void Shader::set_float(std::string name, const GLfloat* variable) const
	{
		glUniform1fv(glGetUniformLocation(m_id, name.c_str()), 1, variable);
	}

	void Shader::set_vec3(std::string name, glm::vec3& vec3) const
	{
		glUniform3fv(glGetUniformLocation(m_id, name.c_str()), 1, glm::value_ptr(vec3));
	}

	void Shader::set_matrix3(std::string name, glm::mat3& matrix3) const
	{
		glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix3));
	}

	void Shader::set_matrix4(std::string name, glm::mat4& matrix4) const
	{
		glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix4));
	}
}