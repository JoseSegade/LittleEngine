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
		const char* VERTEX_SHADER_PATH		= "../../";
		const char* FRAGMENT_SHADER_PATH	= "../../";
		const char* OBJ_PATH				= "../../";
		const char* TEX01_PATH				= "../../";

		Renderer* renderer;
		std::vector<GameObject*> gameObjects;

		void createProgram() 
		{
			ShaderManager::instance()
				->createProgram	(PROGRAM_NAME)
				->createShader	(VERTEX_SHADER_NAME,   VERTEX_SHADER_PATH,   GL_VERTEX_SHADER)
				->assignShader	(VERTEX_SHADER_NAME,   PROGRAM_NAME)
				->createShader	(FRAGMENT_SHADER_NAME, FRAGMENT_SHADER_PATH, GL_FRAGMENT_SHADER)
				->assignShader	(FRAGMENT_SHADER_NAME, PROGRAM_NAME)
				->loadProgram	(PROGRAM_NAME);
		}

		void createGameObjects()
		{
			//TODO: FUTURE IMPLEMENTATIONS - CREATE CONFIGURATION FILES CONTAINING OBJECTS.

			GameObject*		obj				= new GameObject	(0, "OBJ_TEST");
			MeshRenderer*	meshRendererOBJ	= new MeshRenderer	();				

			meshRendererOBJ->setMesh(ObjectManager::instance()->loadMesh("Mesh", OBJ_PATH));
			meshRendererOBJ->initializeVAOData(ShaderManager::instance()->getProgram(PROGRAM_NAME));

			obj->addComponent(meshRendererOBJ);

			MaterialManager::instance()
				->createMaterial			("MAT01")
				->loadTexture				("TEX01", TEX01_PATH)
				->asignTextureToMaterial	("TEX01", "MAT01");
		}

	public:

		~Scene1() {
			for (GameObject* gameObject : gameObjects)
			{
				delete gameObject;
			}
			gameObjects.clear();
			delete renderer;
		}

		void resize(int widht, int height)
		{

		}

		void load()
		{
			createProgram();
			createGameObjects();
			renderer = new Renderer();
			renderer->startRenderConfig();
		}

		void render()
		{

		}

		void update(double deltaTime)
		{

		}
	};
}