#pragma once

#include <string>
#include <vector>
#include <glad/glad.h>
#include <unordered_map>


namespace LittleEngine {
	enum class VariableType {
		UNIFORM,
		ATTRIBUTE
	};

	class Shader
	{
	private:
		std::string								name;
		int										id;
		int										program;
		GLenum									type;
		std::unordered_map<std::string, int>	attributes;
		std::unordered_map<std::string, int>	uniforms;

		void SearchForAttributes();
		void SearchForUniforms();
		void SearchAndStoreVariables(VariableType type);

	public:
		Shader(const std::string& name, GLenum type);
		~Shader();

		std::string		GetName();
		int				GetProgram();
		GLenum			GetType();

		void			Bind();
		void			Unbind();

		GLuint			LoadShader		(const char* fileName);
		int				GetVariableId	(const std::string& name, const VariableType& type);


	};
}

