#include "ProgramObject.h"

#pragma region PUBLIC

LittleEngine::ProgramObject::ProgramObject(const char* name): name(name), id(0), attributes(), uniforms(), shaders(), state(ProgramState::UNLOADED)
{
	
}

LittleEngine::ProgramObject::~ProgramObject()
{
	attributes.clear();
	uniforms.clear();
	for (const auto& shader : shaders) {
		glDetachShader(id, shader.second->GetId());
	}
	shaders.clear();
	glDeleteProgram(id);
}

LittleEngine::ProgramObject* LittleEngine::ProgramObject::use()
{
	if (state == ProgramState::UNLOADED) 
	{
		Utils::printWarning(("Can't use an unloaded shader. Shader name " + name).c_str(), __FILE__, __LINE__);
	}
	else
	{
		glUseProgram(id);
	}
	return this;
}

LittleEngine::ProgramObject* LittleEngine::ProgramObject::setUniform1i(unsigned int variableLocation, unsigned int index)
{
	glUniform1i(variableLocation, index);
	return this;
}

int LittleEngine::ProgramObject::getVariableId(const std::string& name, const VariableType& type)
{
	return type == VariableType::ATTRIBUTE ? attributes[name] : uniforms[name];
}

LittleEngine::ProgramObject* LittleEngine::ProgramObject::addShader(Shader* shader)
{
	if (shaders.count(shader->GetType()) > 0) {
		Utils::printWarning("Can't insert a duplicate shader type inside a program. Shaders must be unique.", __FILE__, __LINE__);
		return this;
	}
	shaders[shader->GetType()] = shader;
	return this;
}

LittleEngine::ProgramObject* LittleEngine::ProgramObject::loadProgram()
{
	id = glCreateProgram();

	for (const auto& shader : shaders)
	{
		shader.second->SetProgram(&id);
		glAttachShader(id, shader.second->GetId());
	}
	glLinkProgram(id);

	int linked;
	glGetProgramiv(id, GL_LINK_STATUS, &linked);
	if (!linked)
	{
		GLint logLen;
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &logLen);

		char* logString = new char[logLen];
		glGetProgramInfoLog(id, logLen, NULL, logString);
		std::cout << "Error: " << logString << " At file " << __FILE__ << " line " << __LINE__ << std::endl;
		delete[] logString;

		glDeleteProgram(id);
		id = 0;
		exit(-1);
	}

	searchForAttributes();
	searchForUniforms();

	state = ProgramState::LOADED;
	return this;
}

#pragma endregion PUBLIC

#pragma region PRIVATE

void LittleEngine::ProgramObject::searchForAttributes()
{
	searchAndStoreVariables(VariableType::ATTRIBUTE);
}

void LittleEngine::ProgramObject::searchForUniforms()
{
	searchAndStoreVariables(VariableType::UNIFORM);
}

void LittleEngine::ProgramObject::searchAndStoreVariables(VariableType type)
{
	int count = 0;
	glGetProgramiv(id, type == VariableType::ATTRIBUTE ? GL_ACTIVE_ATTRIBUTES : GL_ACTIVE_UNIFORMS, &count);

	for (int i = 0; i < count; ++i)
	{
		ShaderVariable* var = new ShaderVariable();

		if (type == VariableType::ATTRIBUTE)
		{
			glGetActiveAttrib(id, i, NAME_LENGHT, &var->length, &var->size, &var->type, var->name);
			attributes[var->name] = glGetAttribLocation(id, var->name);
		}
		else
		{
			glGetActiveUniform(id, i, NAME_LENGHT, &var->length, &var->size, &var->type, var->name);
			uniforms[var->name] = glGetAttribLocation(id, var->name);
		}
	}
}

#pragma endregion PRIVATE
