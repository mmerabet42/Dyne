#include <iostream>
#include <memory>
#include <cstring>

#include "Window.hpp"
#include "Application.hpp"
#include "Prototype.hpp"
#include "Math.hpp"
#include "Object.hpp"
#include "Component.hpp"
#include "Model.hpp"

#include "Transform.hpp"
#include "MeshRenderer.hpp"
#include "Camera.hpp"
#include "Texture.hpp"
#include "Audio.hpp"
#include "AudioListener.hpp"
#include "AudioSource.hpp"
#include "SceneRenderer.hpp"
#include "Light.hpp"

#include "Matrix.hpp"

#include "Scene.hpp"
#include "RenderSystem.hpp"

class RotatorData: public dn::ComponentData
{
public:
	float rotateSpeed;
};

struct RotatorFilter: public dn::SystemFilter<RotatorFilter, RotatorData, dn::TransformData>
{
	RotatorData *rotator;
	dn::TransformData *transform;
};

class RotatorSystem: public dn::System<RotatorFilter>
{
public:

	void onUpdate()
	{
		dn::Entities<RotatorFilter> rotators = getEntities<RotatorFilter>();
		for (auto &e : rotators)
		{
			e->transform->rotation().y += e->rotator->rotateSpeed;
		}
	}

};

int main()
{
	dn::Window win(600, 400, "Window 1");

	win.keyPressEvent.addListener([](dn::Window &w, dn::KeyCode k, dn::Mod) {
		if (k == dn::KeyCode::escape)
			w.close();
	});
	win.setClearColor(37, 44, 56);

	std::vector<dn::Object *> minecraftObjects;

	dn::Audio rainClip("res/rain3.wav", true);
	dn::Texture minecraftTexture("res/minecraft_grass.png");
	dn::Texture bricksTexture("res/bricks.jpg");
	dn::Texture planetTexture("res/planet_texture.png");
	dn::Texture earthTexture("res/Earth_Diffuse.jpg");
	dn::Texture chaletTexture("res/chalet.jpg");
	dn::Model planetModel = dn::Model::loadObj("res/planet.obj");
	//dn::Model chaletModel = dn::Model::loadObj("res/chalet.obj");
	dn::Model gridPlaneModel = dn::Model::generateGridPlane(101, 2.f);
//	dn::Model dragonModel = dn::Model::parse("res/dragon.obj");

	dn::Object chalet;
		chalet.addComponentData<dn::TransformData>(0.f, 0.f, 20.f);
		chalet.getComponentData<dn::TransformData>()->scale() *= 10.f;
		chalet.getComponentData<dn::TransformData>()->rotation().x = glm::radians(-90.f);
	//	chalet.addComponentData<dn::MeshData>(&chaletModel);
	//	chalet.getComponentData<dn::MeshData>()->setTexture(&chaletTexture);

	dn::Object cube;
		cube.setName("prout");
		cube.addComponentData<dn::TransformData>();
		cube.addComponentData<dn::MeshData>(&dn::Model::cube);
		cube.getComponentData<dn::MeshData>()->setTexture(&minecraftTexture);
		cube.getComponentData<dn::MeshData>()->setRenderMode(DN_TEXTURE_COLOR | DN_LIGHT_COLOR);
		//cube.addComponent<dn::AudioSource>(&rainClip);
		//cube.getComponent<dn::AudioSource>()->setLooping(true);

	dn::Object surroundCube;
		surroundCube.addComponentData<dn::TransformData>(cube.getComponentData<dn::TransformData>());
		surroundCube.addComponentData<dn::MeshData>(&dn::Model::cubeEdges);
		surroundCube.getComponentData<dn::MeshData>()->setColor(0.f, 0.f, 0.f);

	dn::Object preCube;
		preCube.addComponentData<dn::TransformData>();
		preCube.addComponentData<dn::MeshData>(&dn::Model::cubeEdges);

	dn::Object camera;
		dn::TransformData *cameraTransform = camera.addComponentData<dn::TransformData>(0.f, 0.f, 5.f);
		camera.addComponentData<dn::CameraData>(70.f, 0.02f, 100000000.f);
		//camera.addComponent<dn::AudioListener>();

	dn::Object gridPlane;
		gridPlane.addComponentData<dn::TransformData>();
		gridPlane.addComponentData<dn::MeshData>(&gridPlaneModel);
		gridPlane.getComponentData<dn::MeshData>()->setColor(1.f, 1.f, 1.f, 0.1f);

	dn::Object planet;
		planet.addComponentData<dn::TransformData>()->position() = glm::vec3(1000.f, 500.f, 1000.f);
		planet.getComponentData<dn::TransformData>()->scale() = glm::vec3(100.f, 100.f, 100.f);
		planet.getComponentData<dn::TransformData>()->rotation() = glm::vec3(2.f, 1.f, 1.f);
		planet.addComponentData<dn::MeshData>(&planetModel)->setTexture(&planetTexture);

	dn::Object earth;
		earth.addComponentData<dn::TransformData>()->position() = glm::vec3(-1000.f, 500.f, -1000.f);
		earth.getComponentData<dn::TransformData>()->scale() = glm::vec3(100.f, 100.f, 100.f);
		earth.getComponentData<dn::TransformData>()->rotation() = glm::vec3(0.f, 4.f, 0.f);
		earth.addComponentData<dn::MeshData>(&planetModel)->setTexture(&earthTexture);

	dn::Scene scene;
	scene.addSystem<dn::RenderSystem>();
	scene.addSystem<RotatorSystem>();

	scene.addObject(camera);
	scene.addObject(gridPlane);
	scene.addObject(cube);
	scene.addObject(surroundCube);
	scene.addObject(preCube);
	scene.addObject(planet);
	scene.addObject(earth);
	//scene.addObject(chalet);
/*
	for (size_t i = 0; i < 5000; ++i)
	{
		dn::Object *o = new dn::Object;
		o->addComponentData<dn::TransformData>(
			dn::math::randomVector(-200.f, 200.f));
		o->addComponentData<dn::MeshData>(&dn::Model::cube)->setTexture(&minecraftTexture);
	//	o->addComponentData<RotatorData>()->rotateSpeed = dn::math::random(0.f, 1.f);

		scene.addObject(*o);
		minecraftObjects.push_back(o);
	}
*/
	win.startEvent.addListener([&](dn::Window &win) {
		win.focus();
		win.setMouseLock(true);

		//cube.getComponent<dn::AudioSource>()->play();

		scene.start();

	});

	float speedMove = 0.1f;
	dn::Light::lightPosition = glm::vec3(0.f, 0.f, 100.f);

	win.updateEvent.addListener([&](dn::Window &win) {

		if (win.getKey(dn::KeyCode::W))
			cameraTransform->position() += cameraTransform->forward() * speedMove;
		if (win.getKey(dn::KeyCode::S))
			cameraTransform->position() -= cameraTransform->forward() * speedMove;

		if (win.getKey(dn::KeyCode::A))
			cameraTransform->position() -= cameraTransform->right() * speedMove;
		if (win.getKey(dn::KeyCode::D))
			cameraTransform->position() += cameraTransform->right() * speedMove;

		if (win.getKey(dn::KeyCode::leftShift))
			cameraTransform->position() -= cameraTransform->up() * speedMove;
		if (win.getKey(dn::KeyCode::space))
			cameraTransform->position() += cameraTransform->up() * speedMove;

		if (win.getKey(dn::KeyCode::keypadPlus))
			camera.getComponent<dn::AudioListener>()->setVolume(0.1f, true);
		if (win.getKey(dn::KeyCode::keypadMinus))
			camera.getComponent<dn::AudioListener>()->setVolume(-0.1f, true);

		if (win.getKey(dn::KeyCode::leftControl))
			speedMove = (win.getKeyDown(dn::KeyCode::rightControl) ? 100.f : 2.f);
		else
			speedMove = 0.1f;

		if (win.getKey(dn::KeyCode::O))
			cube.getComponentData<dn::TransformData>()->position()
				+= cube.getComponent<dn::Transform>()->right();
		if (win.getKey(dn::KeyCode::P))
			cube.getComponentData<dn::TransformData>()->position()
				-= cube.getComponentData<dn::TransformData>()->right();

		if (win.getButton(dn::MouseButton::left))
		{
			dn::Object *obj = new dn::Object;
			dn::Object *obj2 = new dn::Object;
			glm::vec3 frwrd = cameraTransform->position() + cameraTransform->forward() * 5.f;
			obj->addComponentData<dn::TransformData>()->position() = frwrd;
			obj->addComponentData<RotatorData>()->rotateSpeed = dn::math::random(0.01f, 0.5f);
			dn::MeshData *m = obj->addComponentData<dn::MeshData>(&dn::Model::cube);
			if (win.getKey(dn::KeyCode::K))
				m->setTexture(&minecraftTexture);
			else
				m->setTexture(&bricksTexture);
		//	obj->addComponent<dn::AudioSource>(&rainClip)->setLooping(true);

			obj2->addComponentData<dn::TransformData>()->position() = frwrd;
			obj2->addComponentData<dn::MeshData>(&dn::Model::cubeEdges)->setColor(0.f, 0.f, 0.f);

			scene.addObject(*obj);
		//	obj->getComponent<dn::AudioSource>()->play();
			scene.addObject(*obj2);
			minecraftObjects.push_back(obj);
			minecraftObjects.push_back(obj2);
		}

		if (win.getKeyDown(dn::KeyCode::Y))
		{
			for (int i = 0; i < minecraftObjects.size(); i += 1)
				minecraftObjects[i]->getComponentData<dn::MeshData>()->setActive(false);
		}
		if (win.getKeyUp(dn::KeyCode::Y))
		{
			for (int i = 0; i < minecraftObjects.size(); i += 1)
				minecraftObjects[i]->getComponentData<dn::MeshData>()->setActive(true);
		}

		if (win.getKeyDown(dn::KeyCode::C))
			win.setMouseLock(!win.getFlag(DN_MOUSELOCKED));

		if (win.getKeyDown(dn::KeyCode::N))
			std::cout << "Cubes: " << minecraftObjects.size() << std::endl;

		cameraTransform->rotation().x += win.mouseDeltaY() * dn::Application::deltaTime();
		cameraTransform->rotation().y += win.mouseDeltaX() * dn::Application::deltaTime();

		preCube.getComponentData<dn::TransformData>()->position()
			= cameraTransform->position() + cameraTransform->forward() * 5.f;

		win.updateViewport();
		camera.getComponentData<dn::CameraData>()->setAspectRatio(win.aspectRatio());

		win.clear();

		scene.update();
	});

	dn::Application::run();

	for (size_t i = 0; i < minecraftObjects.size(); ++i)
		delete minecraftObjects[i];

	return (0);
}
