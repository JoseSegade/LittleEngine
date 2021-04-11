#include "ShaderManager.h"

LittleEngine::ShaderManager* LittleEngine::ShaderManager::createProgram(const char* programName, RenderMode renderMode)
{
	if (programs.count(programName) > 0)
	{
		LittleEngine::Utils::printWarning("The program you are atempting to create is already created, or has the same name.", __FILE__, __LINE__);
		return this;
	}
	programs[programName] = new ProgramObject(programName, renderMode);
	return this;
}

LittleEngine::ShaderManager* LittleEngine::ShaderManager::createShader(const char* shaderName, const char* shaderPath, GLenum type)
{
	if (programs.count(shaderName) > 0)
	{
		LittleEngine::Utils::printWarning("The shader you are atempting to create is already created, or has the same name.", __FILE__, __LINE__);
		return this;
	}

	Shader* shaderToAdd = new Shader(shaderName, type);
	int id = shaderToAdd->LoadShader(shaderPath);

	if (id < 0) 
	{
		LittleEngine::Utils::printWarning("Shader not created.", __FILE__, __LINE__);
		return this;
	}

	shaders[shaderName] = shaderToAdd;
	return this;
}

LittleEngine::ShaderManager* LittleEngine::ShaderManager::assignShader(const char* shaderName, const char* programName)
{
	if(shaders.count(shaderName) < 1) 
	{
		LittleEngine::Utils::printWarning(("Shader not found. Shader name: " + std::string(shaderName)).c_str(), __FILE__, __LINE__);
		return this;
	}
	if (programs.count(programName) < 1)
	{
		LittleEngine::Utils::printWarning(("Program not found. Program name: " + std::string(programName)).c_str(), __FILE__, __LINE__);
		return this;
	}

	programs[programName]->addShader(shaders[shaderName]);
	return this;
}

LittleEngine::ShaderManager* LittleEngine::ShaderManager::loadAllPrograms()
{
	for (const auto& program : programs)
	{
		program.second->loadProgram();
	}
	return this;
}

LittleEngine::ShaderManager* LittleEngine::ShaderManager::loadProgram(const char* programName)
{
	if (programs.count(programName) < 1)
	{
		LittleEngine::Utils::printWarning(("Program not found. Program name: " + std::string(programName)).c_str(), __FILE__, __LINE__);
		return this;
	}
	programs[programName]->loadProgram();
	return this;
}

LittleEngine::ShaderManager* LittleEngine::ShaderManager::useProgram(const char* programName)
{
	if (programs.count(programName) < 1)
	{
		LittleEngine::Utils::printWarning(("Program not found. Program name: " + std::string(programName)).c_str(), __FILE__, __LINE__);
		return this;
	}
	programs[programName]->use();
	return this;
}

LittleEngine::ProgramObject* LittleEngine::ShaderManager::getProgram(const char* programName)
{
	if (programs.count(programName) < 1)
	{
		LittleEngine::Utils::printWarning(("Program not found. Program name: " + std::string(programName)).c_str(), __FILE__, __LINE__);
		return nullptr;
	}
	return programs[programName];
}

LittleEngine::Shader* LittleEngine::ShaderManager::getShader(const char* shaderName)
{
	if (shaders.count(shaderName) < 1)
	{
		LittleEngine::Utils::printWarning(("Shader not found. Program name: " + std::string(shaderName)).c_str(), __FILE__, __LINE__);
		return nullptr;
	}
	return shaders[shaderName];
}

void LittleEngine::ShaderManager::destroy()
{
	for (std::pair<std::string, ProgramObject*> program : programs)
	{
		delete program.second;
	}
	programs.clear();	
}
