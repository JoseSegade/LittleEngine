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
#include "engine/components/examples/CameraRotateAroundScene.hpp"

namespace LittleEngine
{
	class Scene10 : public IScene
	{
	private:
		const char* SPHERE_PATH = "../objs/sphere.obj";
		const char* TEX01_PATH = "../textures/grey.png";

		const char* PROGRAM_NAME_COMPUTE   = "ComputeProgram";
		const char* COMPUTE_SHADER_01_NAME = "ComputeShader01";
		const char* COMPUTE_SHADER_01_PATH = "../shaders/particleSystemSimple.comp";

		const char* PROGRAM_NAME     = "Program1";
		const char* VERT_SHADER_NAME = "VertexShaderParticleSystem";
		const char* FRAG_SHADER_NAME = "FragmentShaderParticleSystem";
		const char* VERT_SHADER_PATH = "../shaders/particleSystemSimple.vert";
		const char* FRAG_SHADER_PATH = "../shaders/particleSystemSimple.frag";

		const char* PROGRAM_NAME_WF     = "ProgramWF";
		const char* VERT_SHADER_NAME_WF = "VertexShaderWF";
		const char* GEOM_SHADER_NAME_WF = "GeometryShaderWF";
		const char* FRAG_SHADER_NAME_WF = "FragmentShaderWF";
		const char* VERT_SHADER_PATH_WF = "../shaders/geomWireframe.vert";
		const char* GEOM_SHADER_PATH_WF = "../shaders/geomWireframe.geom";
		const char* FRAG_SHADER_PATH_WF = "../shaders/geomWireframe.frag";

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

				->createProgram(PROGRAM_NAME_WF, RenderMode::TRIANGLES)
				->createShader(VERT_SHADER_NAME_WF, VERT_SHADER_PATH_WF, GL_VERTEX_SHADER)
				->createShader(GEOM_SHADER_NAME_WF, GEOM_SHADER_PATH_WF, GL_GEOMETRY_SHADER)
				->createShader(FRAG_SHADER_NAME_WF, FRAG_SHADER_PATH_WF, GL_FRAGMENT_SHADER)
				->assignShader(VERT_SHADER_NAME_WF, PROGRAM_NAME_WF)
				->assignShader(GEOM_SHADER_NAME_WF, PROGRAM_NAME_WF)
				->assignShader(FRAG_SHADER_NAME_WF, PROGRAM_NAME_WF)
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
			camera->transform->position.z = 18.f;

			CameraRotateAroundScene* camComp = new CameraRotateAroundScene();
			camera->addComponent(camComp);

			gameObjects.push_back(camera);

			GameObject* obj = new GameObject(1, "PARTICLE_EMITTER");

			obj->transform->position = glm::vec3(7.f, 1.f, 0.f);
			obj->transform->rotation = glm::rotate(obj->transform->rotation, glm::radians(90.f), glm::vec3(0.f, 0.f, 1.f));

			ParticleSystem* particleSystem = new ParticleSystem();
			ParticleAttractor* particleAtractor = new ParticleAttractor();

			obj->addComponent(particleSystem);
			obj->addComponent(particleAtractor);

			particleSystem->setNumParticles(8192);
			particleSystem->initializeVAOData(ShaderManager::instance()->getProgram(PROGRAM_NAME));

			//particleAtractor->addAttractor(glm::vec3(0., 5., 0), 50.f, .5f)->createBufferToCompute(1);

			gameObjectsRendering[PROGRAM_NAME_COMPUTE].push_back(obj);
			gameObjectsRendering[PROGRAM_NAME].push_back(obj);

			gameObjects.push_back(obj);

			GameObject* obj1 = new GameObject(3, "PARTICLE_EMITTER_2");
			obj1->transform->position = glm::vec3(-7.f, 3.f, 0.f);
			obj1->transform->rotation = glm::rotate(obj1->transform->rotation, glm::radians(-90.f), glm::vec3(0.f, 0.f, 1.f));
			ParticleSystem* particleSystem1 = new ParticleSystem();
			obj1->addComponent(particleSystem1);
			particleSystem1->setNumParticles(8192);
			particleSystem1->initializeVAOData(ShaderManager::instance()->getProgram(PROGRAM_NAME));
			gameObjectsRendering[PROGRAM_NAME_COMPUTE].push_back(obj1);
			gameObjectsRendering[PROGRAM_NAME].push_back(obj1);
			gameObjects.push_back(obj1);

			GameObject* obj2 = new GameObject(4, "PARTICLE_EMITTER_3");
			obj2->transform->position = glm::vec3(0.f, 10.f, 0.f);
			obj2->transform->rotation = glm::rotate(obj2->transform->rotation, glm::radians(180.f), glm::vec3(0.f, 0.f, 1.f));
			ParticleSystem* particleSystem2 = new ParticleSystem();
			obj2->addComponent(particleSystem2);
			particleSystem2->setNumParticles(32768);
			particleSystem2->setRadius(2.f);
			particleSystem2->setColorIni(0.145f, 0.812f, 0.8f);
			particleSystem2->setColorEnd(0.176f, 0.345f, 0.419f);
			particleSystem2->initializeVAOData(ShaderManager::instance()->getProgram(PROGRAM_NAME));
			gameObjectsRendering[PROGRAM_NAME_COMPUTE].push_back(obj2);
			gameObjectsRendering[PROGRAM_NAME].push_back(obj2);
			gameObjects.push_back(obj2);

			GameObject* sphere = new GameObject(2, "SPHERE");
			sphere->transform->position = glm::vec3(0.f, -15.f, 0.f);
			sphere->transform->scale    = glm::vec3(8.f);
			MeshRenderer* sphereMesh = new MeshRenderer();

			MaterialManager::instance()
				->createMaterial("GREY_MAT")
				->loadTexture(
					"GREY_TEX",
					TEX01_PATH,
					ShaderManager::instance()
					->getProgram(PROGRAM_NAME)
					->getVariableId("colorTex", LittleEngine::VariableType::UNIFORM))
				->asignTextureToMaterial("GREY_TEX", "GREY_MAT");

			sphereMesh->setMesh(ObjectManager::instance()->loadMesh("SphereMesh", SPHERE_PATH));
			sphereMesh->initializeVAOData(ShaderManager::instance()->getProgram(PROGRAM_NAME));
			sphereMesh->setMaterial(MaterialManager::instance()->getMaterial("GREY_MAT"));

			sphere->addComponent(sphereMesh);

			gameObjectsRendering[PROGRAM_NAME_WF].push_back(sphere);

			gameObjects.push_back(sphere);
		}

		void uploadUniformsToCompute(ProgramObject* program, float timeStep)
		{
			int count = 10;
			glm::vec4 gravity = glm::vec4(0.f, -.5f, 0.f, 0.f);
			// Center position and radius
			glm::vec4 sphere = glm::vec4(0, -15.f, 0.f, 8.f);
			renderer->uploadUniformVariable(program, "particlesCount", &count);
			renderer->uploadUniformVariable(program, "timeStep", &timeStep);
			renderer->uploadUniformVariable(program, "gravity", &gravity);
			renderer->uploadUniformVariable(program, "spherePos", &sphere);
		}

		void uploadUniformsToProgram_WF(ProgramObject* program)
		{
			renderer->setWireframeWidth(1.f);
			float zOffset = 0.005f;
			glm::vec3 wireColor = glm::vec3(0.f, 1.f, 1.f);
			renderer->uploadUniformVariable(program, "zOffset", &zOffset);
			renderer->uploadUniformVariable(program, "wireColor", &wireColor);
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
				->changeBackgroungColor(glm::vec4(0,0,0,1))
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
			renderer->setWireframeWidth(1, WireframeType::POINT);
			for (GameObject* go : gameObjectsRendering[PROGRAM_NAME])
			{
				go->onRender(ShaderManager::instance()->getProgram(PROGRAM_NAME), camera->getViewProj());
			}
			ShaderManager::instance()->useProgram(PROGRAM_NAME_WF);
			uploadUniformsToProgram_WF(ShaderManager::instance()->getProgram(PROGRAM_NAME_WF));
			for (GameObject* go : gameObjectsRendering[PROGRAM_NAME_WF])
			{
				go->onRender(ShaderManager::instance()->getProgram(PROGRAM_NAME_WF), camera->getViewProj());
			}
			renderer->clearBuffersPP();
			ShaderManager::instance()->useProgram(PROGRAM_NAME_PP);
			renderer->renderFBO(ShaderManager::instance()->getProgram(PROGRAM_NAME_PP));
		}

		void updateCamera(double deltaTime)
		{
			camera->onUpdate(deltaTime);
		}

		void update(double deltaTime)
		{
			ShaderManager::instance()->useProgram(PROGRAM_NAME_COMPUTE);
			uploadUniformsToCompute(ShaderManager::instance()->getProgram(PROGRAM_NAME_COMPUTE), deltaTime);
			for (GameObject* go : gameObjectsRendering[PROGRAM_NAME_COMPUTE])
			{
				go->onCompute(ShaderManager::instance()->getProgram(PROGRAM_NAME_COMPUTE));
			}

			for (GameObject* go : gameObjects)
			{
				go->onUpdate(deltaTime);
			}
		}

		void inputHandle(const void* data, const int classId)
		{

		}
	};
}