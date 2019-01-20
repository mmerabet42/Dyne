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

#include "Matrix.hpp"

#include "Scene.hpp"
#include "RenderSystem.hpp"

int main()
{
	dn::Object obj;

	obj.setName("Object 1");
	obj.addComponentData<dn::TransformData>();
	obj.addComponent<dn::MeshRenderer>(&dn::Model::cube);
	obj.addComponent<dn::AudioSource>();

	dn::Object obj2;

	obj2.setName("Object 2");
	obj2.addComponent<dn::Camera>();

	dn::Scene scn;
	scn.addSystem<dn::RenderSystem>();

	scn.addObject(obj);
	scn.addObject(obj2);

/*	dn::RenderSystem renderSystem;
	renderSystem.loadFilters(obj);
	renderSystem.loadFilters(obj);
	renderSystem.loadFilters(obj2);
	dn::Entities<dn::MeshFilter> renderer = renderSystem.getEntities<dn::MeshFilter>();
	for (auto i : renderer)
	{
		std::cout << i->object()->name() << std::endl;
		if (i->transform == obj.getComponentData<dn::TransformData>())
			std::cout << "TRANSFORM OKKK!!\n";
	}
*/
	return (0);
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
	dn::Model chaletModel = dn::Model::loadObj("res/chalet.obj");
	dn::Model gridPlaneModel = dn::Model::generateGridPlane(101, 2.f);
//	dn::Model dragonModel = dn::Model::parse("res/dragon.obj");

	dn::Object chalet;
		chalet.addComponent<dn::Transform>(0.f, 0.f, 20.f);
		chalet.getComponent<dn::Transform>()->scale() *= 10.f;
		chalet.getComponent<dn::Transform>()->rotation().x = glm::radians(-90.f);
		chalet.addComponent<dn::MeshRenderer>(&chaletModel);
		chalet.getComponent<dn::MeshRenderer>()->setTexture(&chaletTexture);

	dn::Object cube;
		cube.setName("prout");
		cube.addComponent<dn::Transform>();
		cube.addComponent<dn::MeshRenderer>(&dn::Model::cube);
		cube.getComponent<dn::MeshRenderer>()->setTexture(&minecraftTexture);
		cube.addComponent<dn::AudioSource>(&rainClip);
		cube.getComponent<dn::AudioSource>()->setLooping(true);
		cube.getComponent<dn::MeshRenderer>()->setRenderMode(DN_TEXTURE_COLOR | DN_LIGHT_COLOR);

	dn::Object surroundCube;
		surroundCube.addComponent<dn::Transform>(cube.getComponent<dn::Transform>());
		surroundCube.addComponent<dn::MeshRenderer>(&dn::Model::cubeEdges);
		surroundCube.getComponent<dn::MeshRenderer>()->setColor(0.f, 0.f, 0.f);

	dn::Object preCube;
		preCube.addComponent<dn::Transform>();
		preCube.addComponent<dn::MeshRenderer>(&dn::Model::cubeEdges);

	dn::Object camera;
		dn::Transform *cameraTransform = camera.addComponent<dn::Transform>(0.f, 0.f, 5.f);
		camera.addComponent<dn::Camera>(70.f, 0.02f, 100000000.f);
		camera.addComponent<dn::AudioListener>();

	dn::Object gridPlane;
		gridPlane.addComponent<dn::Transform>();
		gridPlane.addComponent<dn::MeshRenderer>(&gridPlaneModel);
		gridPlane.getComponent<dn::MeshRenderer>()->setColor(1.f, 1.f, 1.f, 0.1f);

	dn::Object planet;
		planet.addComponent<dn::Transform>()->position() = glm::vec3(1000.f, 500.f, 1000.f);
		planet.getComponent<dn::Transform>()->scale() = glm::vec3(100.f, 100.f, 100.f);
		planet.getComponent<dn::Transform>()->rotation() = glm::vec3(2.f, 1.f, 1.f);
		planet.addComponent<dn::MeshRenderer>(&planetModel)->setTexture(&planetTexture);

	dn::Object earth;
		earth.addComponent<dn::Transform>()->position() = glm::vec3(-1000.f, 500.f, -1000.f);
		earth.getComponent<dn::Transform>()->scale() = glm::vec3(100.f, 100.f, 100.f);
		earth.getComponent<dn::Transform>()->rotation() = glm::vec3(0.f, 4.f, 0.f);
		earth.addComponent<dn::MeshRenderer>(&planetModel)->setTexture(&earthTexture);

	dn::SceneRenderer scene;

	scene.addObject(&camera);
	scene.addObject(&gridPlane);
	scene.addObject(&cube);
	scene.addObject(&surroundCube);
	scene.addObject(&preCube);
	scene.addObject(&planet);
	scene.addObject(&earth);
	scene.addObject(&chalet);

	win.startEvent.addListener([&](dn::Window &win) {
		win.focus();
		win.setMouseLock(true);

		cube.getComponent<dn::AudioSource>()->play();

		scene.start();

	});

	float speedMove = 0.1f;
	dn::MeshRenderer::lightPosition = glm::vec3(0.f, 0.f, 100.f);

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
			cube.getComponent<dn::Transform>()->position() += cube.getComponent<dn::Transform>()->right();
		if (win.getKey(dn::KeyCode::P))
			cube.getComponent<dn::Transform>()->position() -= cube.getComponent<dn::Transform>()->right();

		if (win.getButton(dn::MouseButton::left))
		{
			dn::Object *obj = new dn::Object;
			dn::Object *obj2 = new dn::Object;
			glm::vec3 frwrd = cameraTransform->position() + cameraTransform->forward() * 5.f;
			obj->addComponent<dn::Transform>()->position() = frwrd;
			dn::MeshRenderer *m = obj->addComponent<dn::MeshRenderer>(&dn::Model::cube);
			if (win.getKey(dn::KeyCode::K))
				m->setTexture(&minecraftTexture);
			else
				m->setTexture(&bricksTexture);
		//	obj->addComponent<dn::AudioSource>(&rainClip)->setLooping(true);

			obj2->addComponent<dn::Transform>()->position() = frwrd;
			obj2->addComponent<dn::MeshRenderer>(&dn::Model::cubeEdges)->setColor(0.f, 0.f, 0.f);

			scene.addObject(obj);
		//	obj->getComponent<dn::AudioSource>()->play();
			scene.addObject(obj2);
			minecraftObjects.push_back(obj);
			minecraftObjects.push_back(obj2);
		}

		if (win.getKeyDown(dn::KeyCode::C))
			win.setMouseLock(!win.getFlag(DN_MOUSELOCKED));

		if (win.getKeyDown(dn::KeyCode::N))
			std::cout << "Cubes: " << minecraftObjects.size() << std::endl;

		cameraTransform->rotation().x += win.mouseDeltaY() * dn::Application::deltaTime();
		cameraTransform->rotation().y += win.mouseDeltaX() * dn::Application::deltaTime();

		preCube.getComponent<dn::Transform>()->position() = cameraTransform->position() + cameraTransform->forward() * 5.f;

		win.updateViewport();
		camera.getComponent<dn::Camera>()->setAspectRatio(win.aspectRatio());

		win.clear();

		scene.update();
	});

	dn::Application::run();

	for (size_t i = 0; i < minecraftObjects.size(); ++i)
		delete minecraftObjects[i];

	return (0);
}
