#include "engine/scene/IScene.h"
#include "engine/graphics/Renderer.h"
#include "engine/managers/ShaderManager.h"
#include "engine/managers/ObjectManager.h"
#include "engine/managers/MaterialManager.h"
#include "engine/scene/GameObject.h"
#include "engine/utils/OBJReader.h"
#include "engine/components/MeshRenderer.h"

namespace LittleEngine
{
	class Scene1 : public IScene 
	{
	private:
		const char* PROGRAM_NAME			= "Program1";
		const char* VERTEX_SHADER_NAME		= "VertexShader";
		const char* FRAGMENT_SHADER_NAME	= "FragmentShader";
		const char* VERTEX_SHADER_PATH		= "../shaders/fwRendering.vert";
		const char* FRAGMENT_SHADER_PATH	= "../shaders/fwRendering.frag";
		const char* OBJ_PATH				= "../objs/cube.obj";
		const char* TEX01_PATH				= "../textures/color.png";

		const char* PROGRAM_NAME_PP			= "ProgramPP";
		const char* VERTEX_SHADER_NAME_PP	= "VertexShaderPP";
		const char* FRAGMENT_SHADER_NAME_PP	= "FragmentShaderPP";
		const char* VERTEX_SHADER_PATH_PP	= "../shaders/postProcessing.vert";
		const char* FRAGMENT_SHADER_PATH_PP	= "../shaders/postProcessing.frag";

		Renderer* renderer;
		std::vector<GameObject*> gameObjects;

		void createPrograms() 
		{
			//	TODO: Make object for programs config

			ShaderManager::instance()
				->createProgram	(PROGRAM_NAME)
				->createShader	(VERTEX_SHADER_NAME,   VERTEX_SHADER_PATH,   GL_VERTEX_SHADER)
				->assignShader	(VERTEX_SHADER_NAME,   PROGRAM_NAME)
				->createShader	(FRAGMENT_SHADER_NAME, FRAGMENT_SHADER_PATH, GL_FRAGMENT_SHADER)
				->assignShader	(FRAGMENT_SHADER_NAME, PROGRAM_NAME)
				->loadProgram	(PROGRAM_NAME)

				//	PostProcessing Program
				->createProgram(PROGRAM_NAME_PP)
				->createShader(VERTEX_SHADER_NAME_PP, VERTEX_SHADER_PATH_PP, GL_VERTEX_SHADER)
				->assignShader(VERTEX_SHADER_NAME_PP, PROGRAM_NAME_PP)
				->createShader(FRAGMENT_SHADER_NAME_PP, FRAGMENT_SHADER_PATH_PP, GL_FRAGMENT_SHADER)
				->assignShader(FRAGMENT_SHADER_NAME_PP, PROGRAM_NAME_PP)
				->loadProgram(PROGRAM_NAME_PP);
		}

		void createGameObjects()
		{
			//TODO: FUTURE IMPLEMENTATIONS - CREATE CONFIGURATION FILES CONTAINING OBJECTS.

			GameObject*		obj				= new GameObject	(0, "OBJ_TEST");
			MeshRenderer*	meshRendererOBJ	= new MeshRenderer	();				

			MaterialManager::instance()
				->createMaterial("MAT01")
				->loadTexture(
					"TEX01",
					TEX01_PATH, 
					ShaderManager::instance()
						->getProgram(PROGRAM_NAME)
						->getVariableId("colorTex", LittleEngine::VariableType::UNIFORM))
				->asignTextureToMaterial	("TEX01", "MAT01");

			meshRendererOBJ->setMesh(ObjectManager::instance()->loadMesh("Mesh", OBJ_PATH));
			meshRendererOBJ->initializeVAOData(ShaderManager::instance()->getProgram(PROGRAM_NAME));
			meshRendererOBJ->setMaterial(MaterialManager::instance()->getMaterial("MAT01"));

			obj->addComponent(meshRendererOBJ);

			gameObjects.push_back(obj);
		}

	public:

		~Scene1() {
			for (GameObject* gameObject : gameObjects)
			{
				delete gameObject;
			}
			gameObjects.clear();
			ObjectManager::instance()->destroy();
			MaterialManager::instance()->destroy();
			ShaderManager::instance()->destroy();
			delete renderer;
			delete[] this;
		}

		void resize(int width, int height)
		{
			renderer->resize(width, height);
		}

		void load()
		{
			createPrograms();
			createGameObjects();
			renderer = new Renderer();
			renderer
				->startRenderConfig()
				->createFBO();
		}

		void render()
		{
			renderer->clearBuffersFw();
			ShaderManager::instance()->useProgram(PROGRAM_NAME);
			for (GameObject* go : gameObjects)
			{
				go->onRender();
			}
			renderer->clearBuffersPP();
			ShaderManager::instance()->useProgram(PROGRAM_NAME_PP);
			renderer->renderFBO(ShaderManager::instance()->getProgram(PROGRAM_NAME_PP));
		}

		void update(double deltaTime)
		{
			for (GameObject* go : gameObjects)
			{
				go->onUpdate(deltaTime);
			}
		}
	};
}