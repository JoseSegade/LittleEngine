#include "engine/scene/IScene.h"
#include "engine/graphics/Renderer.h"
#include "engine/managers/ShaderManager.h"
#include "engine/managers/ObjectManager.h"
#include "engine/managers/MaterialManager.h"
#include "engine/scene/GameObject.h"
#include "engine/scene/Camera.h"
#include "engine/scene/Light.h"
#include "engine/utils/OBJReader.h"
#include "engine/components/MeshRenderer.h"
#include "engine/components/examples/RotateComponent.hpp"

namespace LittleEngine
{
	class Scene4 : public IScene 
	{
	private:
		const char* OBJ_PATH				= "../objs/utah_teapot.obj";
		const char* TEX01_PATH				= "../textures/grey.png";

		const char* PROGRAM_NAME			= "Program1";
		const char* VERTEX_SHADER_NAME		= "VertexShader";
		const char* FRAGMENT_SHADER_NAME	= "FragmentShader";
		const char* VERTEX_SHADER_PATH		= "../shaders/fwRendering.vert";
		const char* FRAGMENT_SHADER_PATH	= "../shaders/fwRendering.frag";

		const char* PROGRAM_NAME_WF			= "ProgramWireframe";
		const char* VERTEX_SHADER_NAME_WF	= "VertexShaderWireframe";
		const char* GEOM_SHADER_NAME_WF		= "GeomShaderWireframe";
		const char* FRAGMENT_SHADER_NAME_WF = "FragmentShaderWireframe";
		const char* VERTEX_SHADER_PATH_WF	= "../shaders/geomWireframe.vert";
		const char* GEOM_SHADER_PATH_WF		= "../shaders/geomNormals.geom";
		const char* FRAGMENT_SHADER_PATH_WF	= "../shaders/geomWireframe.frag";

		const char* PROGRAM_NAME_PP			= "ProgramPP";
		const char* VERTEX_SHADER_NAME_PP	= "VertexShaderPP";
		const char* FRAGMENT_SHADER_NAME_PP	= "FragmentShaderPP";
		const char* VERTEX_SHADER_PATH_PP	= "../shaders/postProcessing.vert";
		const char* FRAGMENT_SHADER_PATH_PP	= "../shaders/postProcessing.frag";

		Renderer* renderer;
		std::vector<GameObject*> gameObjects;
		std::vector<Light*> lights;
		Camera* camera;

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

				->createProgram(PROGRAM_NAME_WF)
				->createShader(VERTEX_SHADER_NAME_WF, VERTEX_SHADER_PATH_WF, GL_VERTEX_SHADER)
				->assignShader(VERTEX_SHADER_NAME_WF, PROGRAM_NAME_WF)
				->createShader(GEOM_SHADER_NAME_WF, GEOM_SHADER_PATH_WF, GL_GEOMETRY_SHADER)
				->assignShader(GEOM_SHADER_NAME_WF, PROGRAM_NAME_WF)
				->createShader(FRAGMENT_SHADER_NAME_WF, FRAGMENT_SHADER_PATH_WF, GL_FRAGMENT_SHADER)
				->assignShader(FRAGMENT_SHADER_NAME_WF, PROGRAM_NAME_WF)
				->loadProgram(PROGRAM_NAME_WF)

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

			camera = new Camera(0, "CAMERA", CameraProjection::PERSPECTIVE);
			camera->transform->position.y = 2.f;
			camera->transform->position.z = 6.f;

			gameObjects.push_back(camera);

			GameObject*		obj				 = new GameObject	  (1, "OBJ_TEST");
			MeshRenderer*	meshRendererOBJ	 = new MeshRenderer	  ();				
			RotateComponent* rotateComponent = new RotateComponent();

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
			obj->addComponent(rotateComponent);

			gameObjects.push_back(obj);		

		}

	public:

		~Scene4() {
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
			camera->updateProportions(width, height);
		}

		void load()
		{
			createPrograms();
			createGameObjects();
			renderer = new Renderer();
			renderer
				->startRenderConfig()
				->createFBO(ShaderManager::instance()->getProgram(PROGRAM_NAME_PP));

			for (GameObject* go : gameObjects)
			{
				go->onStart();
			}
		}

		void render()
		{
			renderer->clearBuffersFw();
			ShaderManager::instance()->useProgram(PROGRAM_NAME);
			for (GameObject* go : gameObjects)
			{
				go->onRender(ShaderManager::instance()->getProgram(PROGRAM_NAME), camera->getViewProj());
			}
			ShaderManager::instance()->useProgram(PROGRAM_NAME_WF);
			renderer->setWireframeWidth(2.0);
			float normalSize = 0.3f;
			renderer->uploadUniformVariable(ShaderManager::instance()->getProgram(PROGRAM_NAME_WF), "normalSize", &normalSize);
			for (GameObject* go : gameObjects)
			{
				go->onRender(ShaderManager::instance()->getProgram(PROGRAM_NAME_WF), camera->getViewProj());
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