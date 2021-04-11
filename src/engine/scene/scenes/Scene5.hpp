#include <glm/glm.hpp>
#include "engine/scene/IScene.h"
#include "engine/graphics/Renderer.h"
#include "engine/managers/ShaderManager.h"
#include "engine/managers/ObjectManager.h"
#include "engine/managers/MaterialManager.h"
#include "engine/managers/InputManager.h"
#include "engine/scene/GameObject.h"
#include "engine/scene/Camera.h"
#include "engine/scene/Light.h"
#include "engine/utils/OBJReader.h"
#include "engine/components/MeshRenderer.h"
#include "engine/components/examples/RotateComponent.hpp"

namespace LittleEngine
{
	class Scene5 : public IScene 
	{
	private:
		const char* OBJ_PATH				= "../objs/quad.obj";
		const char* TEX01_PATH				= "../textures/grey.png";

		const char* PROGRAM_NAME			= "Program1";
		const char* VERTEX_SHADER_NAME		= "VertexShader";
		const char* FRAGMENT_SHADER_NAME	= "FragmentShader";
		const char* VERTEX_SHADER_PATH		= "../shaders/fwRendering.vert";
		const char* FRAGMENT_SHADER_PATH	= "../shaders/fwRendering.frag";

		const char* PROGRAM_NAME_WF			= "ProgramWireframe";
		const char* VERTEX_SHADER_NAME_WF	= "VertexShaderWireframe";
		const char* TESC_SHADER_NAME_WF     = "TescShaderWireFrame";
		const char* TESE_SHADER_NAME_WF     = "TeseShaderWireFrame";
		const char* GEOM_SHADER_NAME_WF		= "GeomShaderWireframe";
		const char* FRAGMENT_SHADER_NAME_WF = "FragmentShaderWireframe";
		const char* VERTEX_SHADER_PATH_WF	= "../shaders/quadSubDiv.vert";
		const char* TESC_SHADER_PATH_WF     = "../shaders/quadSubDiv.tesc";
		const char* TESE_SHADER_PATH_WF     = "../shaders/quadSubDiv.tese";
		const char* GEOM_SHADER_PATH_WF		= "../shaders/quadSubDiv.geom";
		const char* FRAGMENT_SHADER_PATH_WF	= "../shaders/quadSubDiv.frag";

		const char* PROGRAM_NAME_PP			= "ProgramPP";
		const char* VERTEX_SHADER_NAME_PP	= "VertexShaderPP";
		const char* FRAGMENT_SHADER_NAME_PP	= "FragmentShaderPP";
		const char* VERTEX_SHADER_PATH_PP	= "../shaders/postProcessing.vert";
		const char* FRAGMENT_SHADER_PATH_PP	= "../shaders/postProcessing.frag";

		Renderer* renderer;
		std::vector<GameObject*> gameObjects;
		std::vector<Light*> lights;
		Camera* camera;
		float divs = 5.0f;

		void createPrograms() 
		{
			//	TODO: Make object for programs config

			ShaderManager::instance()
				->createProgram(PROGRAM_NAME_WF, RenderMode::QUADS)
				->createShader(VERTEX_SHADER_NAME_WF, VERTEX_SHADER_PATH_WF, GL_VERTEX_SHADER)
				->assignShader(VERTEX_SHADER_NAME_WF, PROGRAM_NAME_WF)
				->createShader(TESC_SHADER_NAME_WF, TESC_SHADER_PATH_WF, GL_TESS_CONTROL_SHADER)
				->assignShader(TESC_SHADER_NAME_WF, PROGRAM_NAME_WF)
				->createShader(TESE_SHADER_NAME_WF, TESE_SHADER_PATH_WF, GL_TESS_EVALUATION_SHADER)
				->assignShader(TESE_SHADER_NAME_WF, PROGRAM_NAME_WF)
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

			camera = new Camera(0, "CAMERA", CameraProjection::ORTOGRAPHIC);
			camera->transform->position.z = 6.f;

			gameObjects.push_back(camera);

			GameObject*		obj				 = new GameObject	  (1, "OBJ_TEST");
			MeshRenderer*	meshRendererOBJ	 = new MeshRenderer	  ();				
			RotateComponent* rotateComponent = new RotateComponent();

			obj->transform->rotation = glm::rotate(obj->transform->rotation, 90.f, glm::vec3(1.0, 0.0, 0.0));

			MaterialManager::instance()
				->createMaterial("MAT01")
				->loadTexture(
					"TEX01",
					TEX01_PATH, 
					ShaderManager::instance()
						->getProgram(PROGRAM_NAME_WF)
						->getVariableId("colorTex", LittleEngine::VariableType::UNIFORM))
				->asignTextureToMaterial	("TEX01", "MAT01");

			meshRendererOBJ->setMesh(ObjectManager::instance()->loadMesh("Mesh", OBJ_PATH));
			meshRendererOBJ->initializeVAOData(ShaderManager::instance()->getProgram(PROGRAM_NAME_WF));
			meshRendererOBJ->setMaterial(MaterialManager::instance()->getMaterial("MAT01"));

			obj->addComponent(meshRendererOBJ);
			obj->addComponent(rotateComponent);

			gameObjects.push_back(obj);		

		}

		void uploadUniformsToProgram(ProgramObject* program)
		{
			renderer->setWireframeWidth(2.0);
			float zOffset = 0.03f;
			
			glm::vec3 wireColor = glm::vec3(1.0, 1.0, 0.0);
			renderer->uploadUniformVariable(program, "zOffset"  , &zOffset);
			renderer->uploadUniformVariable(program, "wireColor", &wireColor);
			renderer->uploadUniformVariable(program, "divs", &divs);
		}

	public:

		~Scene5() {
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

			std::function<void(int, int)> f = [=](int a, int b) {
				this->inputHandle(a, b);
			};

			InputManager::instance()->subscribe("SCENE05", f);
			for (GameObject* go : gameObjects)
			{
				go->onStart();
			}
		}

		void render()
		{
			renderer->clearBuffersFw();
			ShaderManager::instance()->useProgram(PROGRAM_NAME_WF);
			uploadUniformsToProgram(ShaderManager::instance()->getProgram(PROGRAM_NAME_WF));
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

		void inputHandle(int a, int b)
		{
			if (a == 333)
			{
				divs = std::max(1.f, --divs);
			}
			else if (a == 334)
			{
				divs = std::min(12.f, ++divs);

			}
		}
	};
}