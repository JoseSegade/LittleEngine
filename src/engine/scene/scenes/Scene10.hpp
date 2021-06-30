#include <glm/glm.hpp>
#include <functional>
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
#include "engine/graphics/ParticleSystem.h"
#include "engine/components/ParticleAttractor.h"

namespace LittleEngine
{
	class Scene10 : public IScene
	{
	private:
		const char* OBJ_PATH = "../objs/utah_teapot.obj";
		const char* TEX01_PATH = "../textures/earth.png";

		const char* PROGRAM_NAME_COMPUTE   = "ComputeProgram";
		const char* COMPUTE_SHADER_01_NAME = "ComputeShader01";
		const char* COMPUTE_SHADER_01_PATH = "../shaders/particleSystemSimple.comp";

		const char* PROGRAM_NAME     = "Program1";
		const char* VERT_SHADER_NAME = "VertexShaderParticleSystem";
		const char* GEOM_SHADER_NAME = "GeometryShaderParticleSystem";
		const char* FRAG_SHADER_NAME = "FragmentShaderParticleSystem";
		const char* VERT_SHADER_PATH = "../shaders/particleSystemSimple.vert";
		const char* GEOM_SHADER_PATH = "../shaders/particleSystemSimple.geom";
		const char* FRAG_SHADER_PATH = "../shaders/particleSystemSimple.frag";

		const char* PROGRAM_NAME_PP = "ProgramPP";
		const char* VERTEX_SHADER_NAME_PP = "VertexShaderPP";
		const char* FRAGMENT_SHADER_NAME_PP = "FragmentShaderPP";
		const char* VERTEX_SHADER_PATH_PP = "../shaders/postProcessing.vert";
		const char* FRAGMENT_SHADER_PATH_PP = "../shaders/postProcessing.frag";

		Renderer* renderer;
		std::vector<GameObject*> gameObjects;
		std::unordered_map<std::string, std::vector<GameObject*>> gameObjectsRendering;
		std::vector<Light*> lights;
		Camera* camera;

		void createPrograms()
		{
			//	TODO: Make object for programs config

			ShaderManager::instance()
				->createProgram(PROGRAM_NAME_COMPUTE)
				->createShader(COMPUTE_SHADER_01_NAME, COMPUTE_SHADER_01_PATH, GL_COMPUTE_SHADER)
				->assignShader(COMPUTE_SHADER_01_NAME, PROGRAM_NAME_COMPUTE)
				->loadProgram(PROGRAM_NAME_COMPUTE)

				->createProgram(PROGRAM_NAME, RenderMode::POINTS)
				->createShader(VERT_SHADER_NAME, VERT_SHADER_PATH, GL_VERTEX_SHADER)
				->createShader(FRAG_SHADER_NAME, FRAG_SHADER_PATH, GL_FRAGMENT_SHADER)
				->assignShader(VERT_SHADER_NAME, PROGRAM_NAME)
				->assignShader(FRAG_SHADER_NAME, PROGRAM_NAME)
				->loadProgram(PROGRAM_NAME)

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
			camera->transform->position.z = 18.f;

			gameObjects.push_back(camera);
			GameObject* obj = new GameObject(1, "PARTICLE_EMITTER");
			ParticleSystem* particleSystem = new ParticleSystem();
			ParticleAttractor* particleAtractor = new ParticleAttractor();

			obj->addComponent(particleSystem);
			obj->addComponent(particleAtractor);

			particleSystem->setNumParticles(1024*1024);
			particleSystem->initializeVAOData(ShaderManager::instance()->getProgram(PROGRAM_NAME));

			particleAtractor->addAttractor(glm::vec3(10., 28., 2.6), .2f, .5f)->createBufferToCompute(1);


			gameObjectsRendering[PROGRAM_NAME_COMPUTE].push_back(obj);
			gameObjectsRendering[PROGRAM_NAME].push_back(obj);

			gameObjects.push_back(obj);

		}

		void uploadUniformsToProgram(ProgramObject* program)
		{
			int count = 10;
			float timeStep = 0.1;
			glm::vec4 gravity = glm::vec4(0.f, -.5f, 0.f, 0.f);
			// Center position and radius
			glm::vec4 sphere = glm::vec4(0, -3.f, 0.f, 2.f);
			renderer->uploadUniformVariable(program, "particlesCount", &count);
			renderer->uploadUniformVariable(program, "timeStep", &timeStep);
			renderer->uploadUniformVariable(program, "gravity", &gravity);
			renderer->uploadUniformVariable(program, "spherePos", &sphere);
		}

	public:

		~Scene10() {			
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

			InputManager::instance()->subscribe("SCENE10", f);
			for (GameObject* go : gameObjects)
			{
				go->onStart();
			}
		}

		void render()
		{
			renderer->clearBuffersFw();
			ShaderManager::instance()->useProgram(PROGRAM_NAME_COMPUTE);
			uploadUniformsToProgram(ShaderManager::instance()->getProgram(PROGRAM_NAME_COMPUTE));
			for (GameObject* go : gameObjectsRendering[PROGRAM_NAME_COMPUTE])
			{
				go->onCompute(ShaderManager::instance()->getProgram(PROGRAM_NAME_COMPUTE));
			}
			ShaderManager::instance()->useProgram(PROGRAM_NAME);
			renderer->setWireframeWidth(1, WireframeType::POINT);
			for (GameObject* go : gameObjectsRendering[PROGRAM_NAME])
			{
				go->onRender(ShaderManager::instance()->getProgram(PROGRAM_NAME), camera->getViewProj());
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
				camera->transform->position.z = std::min(15.f, camera->transform->position.z += 0.5);
			}
			else if (a == 334)
			{
				camera->transform->position.z = std::max(2.0f, camera->transform->position.z -= 0.5);
			}
		}
	};
}