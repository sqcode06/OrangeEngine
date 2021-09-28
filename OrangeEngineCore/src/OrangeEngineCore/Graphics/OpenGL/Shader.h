#pragma once

namespace OrangeEngine
{
	class Shader
	{
	public:
		Shader(const char* vertex_shader_src, const char* fragment_shader_src);
		Shader(Shader&&) noexcept;
		Shader& operator=(Shader&&) noexcept;
		~Shader();

		Shader() = delete;
		Shader(const Shader&) = delete;
		Shader& operator=(const Shader&) = delete;

		void bind() const;
		static void unbind();
		bool isCompiled() const { return m_isCompiled; }

	private:
		bool m_isCompiled = false;
		unsigned int m_id = 0;
	};
}