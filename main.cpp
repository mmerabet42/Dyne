#include <iostream>
#include <memory>
#include <cstring>

#include "dn/Window.hpp"
#include "dn/Application.hpp"
#include "dn/Math.hpp"
#include "dn/Component.hpp"
#include "dn/Model.hpp"

#include "dn/Transform.hpp"
#include "dn/Mesh.hpp"
#include "dn/Camera.hpp"
#include "dn/Texture.hpp"
#include "dn/Object.hpp"
#include "dn/AudioListener.hpp"
#include "dn/AudioSource.hpp"
#include "dn/Audio.hpp"
#include "dn/Light.hpp"
#include "glm/glm.hpp"

#include "dn/Scene.hpp"
#include "dn/RenderEngine.hpp"

class RotatorData: public dn::Component
{
public:
	float rotateSpeed;
};

struct RotatorFilter: public dn::EngineFilter<RotatorFilter, RotatorData, dn::Transform>
{
	RotatorData *rotator;
	dn::Transform *transform;
};

class RotatorEngine: public dn::Engine<RotatorFilter>
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

struct PlayerFilter: public dn::EngineFilter<PlayerFilter, dn::Camera, dn::Transform>
{
	dn::Camera *camera;
	dn::Transform *transform;
};

struct PrecubeFilter: public dn::EngineFilter<PrecubeFilter, dn::Transform>
{
	dn::Transform *transform;
};

class MoveEngine: public dn::Engine<PlayerFilter, PrecubeFilter>
{
	PlayerFilter *player;
	PrecubeFilter *precube;

	float speedMove = 0.1f;
public:

	void onObjectAdded(PlayerFilter &p_player)
	{
		player = &p_player;
	}

	void onObjectAdded(PrecubeFilter &p_other)
	{
		if (p_other.object()->name() == "precube")
			precube = &p_other;
		else
		{
			destroyObject(p_other);
		}
	}

	void onUpdate()
	{
		if (player)
		{
			if (scene()->window()->getKey(dn::KeyCode::W))
				player->transform->position() += player->transform->forward() * speedMove;
			if (scene()->window()->getKey(dn::KeyCode::S))
				player->transform->position() -= player->transform->forward() * speedMove;

			if (scene()->window()->getKey(dn::KeyCode::A))
				player->transform->position() -= player->transform->right() * speedMove;
			if (scene()->window()->getKey(dn::KeyCode::D))
				player->transform->position() += player->transform->right() * speedMove;

			if (scene()->window()->getKey(dn::KeyCode::leftShift))
				player->transform->position() -= player->transform->up() * speedMove;
			if (scene()->window()->getKey(dn::KeyCode::space))
				player->transform->position() += player->transform->up() * speedMove;

			if (scene()->window()->getKey(dn::KeyCode::leftControl))
				speedMove = 2.f;
			else
				speedMove = 0.1f;

			player->transform->rotation().x
				+= scene()->window()->mouseDeltaY() * dn::Application::deltaTime();
			player->transform->rotation().y
				+= scene()->window()->mouseDeltaX() * dn::Application::deltaTime();

			precube->transform->position()
				= player->transform->position() + player->transform->forward() * 5.f;
		}
	}
};

class RotateLol: public dn::UComponent
{
public:
	dn::Transform *transform;

	void start()
	{
		transform = object()->getComponent<dn::Transform>();
	}

	void update()
	{
		transform->rotation().x += 0.05f;
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
		chalet.addComponent<dn::Transform>(0.f, 0.f, 20.f);
		chalet.getComponent<dn::Transform>()->scale() *= 10.f;
		chalet.getComponent<dn::Transform>()->rotation().x = glm::radians(-90.f);
	//	chalet.addComponent<dn::Mesh>(&chaletModel);
	//	chalet.getComponent<dn::Mesh>()->setTexture(&chaletTexture);

	dn::Object cube;
		cube.setName("prout");
		cube.addComponent<dn::Transform>();
		cube.addComponent<dn::Mesh>(&dn::Model::cube);
		cube.getComponent<dn::Mesh>()->setTexture(&minecraftTexture);
		cube.getComponent<dn::Mesh>()->setRenderMode(DN_TEXTURE_COLOR | DN_LIGHT_COLOR);
		cube.addComponent<RotateLol>();
		cube.addComponent<dn::AudioSource>(&rainClip);

	dn::Object surroundCube;
		surroundCube.addComponent<dn::Transform>(cube.getComponent<dn::Transform>());
		surroundCube.addComponent<dn::Mesh>(&dn::Model::cubeEdges);
		surroundCube.getComponent<dn::Mesh>()->setColor(0.f, 0.f, 0.f);

	dn::Object preCube;
		preCube.setName("precube");
		preCube.addComponent<dn::Transform>();
		preCube.addComponent<dn::Mesh>(&dn::Model::cubeEdges);

	dn::Object camera;
		camera.setName("eourihvb");
		dn::Transform *cameraTransform = camera.addComponent<dn::Transform>(0.f, 0.f, 5.f);
		camera.addComponent<dn::Camera>(70.f, 0.02f, 100000000.f);
		camera.addComponent<dn::AudioListener>();

	dn::Object gridPlane;
		gridPlane.setName("gridPlane");
		gridPlane.addComponent<dn::Transform>();
		gridPlane.addComponent<dn::Mesh>(&gridPlaneModel);
		gridPlane.getComponent<dn::Mesh>()->setColor(1.f, 1.f, 1.f, 0.1f);

	dn::Object planet;
		planet.addComponent<dn::Transform>()->position() = glm::vec3(1000.f, 500.f, 1000.f);
		planet.getComponent<dn::Transform>()->scale() = glm::vec3(100.f, 100.f, 100.f);
		planet.getComponent<dn::Transform>()->rotation() = glm::vec3(2.f, 1.f, 1.f);
		planet.addComponent<dn::Mesh>(&planetModel)->setTexture(&planetTexture);

	dn::Object earth;
		earth.addComponent<dn::Transform>()->position() = glm::vec3(-1000.f, 500.f, -1000.f);
		earth.getComponent<dn::Transform>()->scale() = glm::vec3(100.f, 100.f, 100.f);
		earth.getComponent<dn::Transform>()->rotation() = glm::vec3(0.f, 4.f, 0.f);
		earth.addComponent<dn::Mesh>(&planetModel)->setTexture(&earthTexture);

	dn::Scene scene;
	scene.addEngine<dn::RenderEngine>();
	scene.addEngine<RotatorEngine>();
	scene.addEngine<MoveEngine>();

	scene.addObject(camera);
	scene.addObject(gridPlane);
	scene.addObject(cube);
	scene.addObject(surroundCube);
	scene.addObject(preCube);
	scene.addObject(planet);
	scene.addObject(earth);

	win.setScene(&scene);
	//scene.addObject(chalet);
/*
	for (size_t i = 0; i < 5000; ++i)
	{
		dn::Object *o = new dn::Object;
		o->addComponent<dn::Transform>(
			dn::math::randomVector(-200.f, 200.f));
		o->addComponent<dn::Mesh>(&dn::Model::cube)->setTexture(&minecraftTexture);
	//	o->addComponent<RotatorData>()->rotateSpeed = dn::math::random(0.f, 1.f);

		scene.addObject(*o);
		minecraftObjects.push_back(o);
	}
*/
	win.startEvent.addListener([&](dn::Window &win) {
		win.focus();
		win.setMouseLock(true);

		cube.getComponent<dn::AudioSource>()->play();
		cube.getComponent<dn::AudioSource>()->setLooping(true);
	});

	float speedMove = 0.1f;
	dn::Light::lightPosition = glm::vec3(0.f, 0.f, 100.f);

	win.updateEvent.addListener([&](dn::Window &win) {

		if (win.getKey(dn::KeyCode::O))
			cube.getComponent<dn::Transform>()->position()
				+= cube.getComponent<dn::Transform>()->right();
		if (win.getKey(dn::KeyCode::P))
			cube.getComponent<dn::Transform>()->position()
				-= cube.getComponent<dn::Transform>()->right();

		if (win.getButton(dn::MouseButton::left))
		{
			dn::Object *obj = new dn::Object;
			dn::Object *obj2 = new dn::Object;
			glm::vec3 frwrd = cameraTransform->position() + cameraTransform->forward() * 5.f;
			obj->addComponent<dn::Transform>()->position() = frwrd;
			obj->addComponent<RotatorData>()->rotateSpeed = dn::math::random(0.01f, 0.5f);
			dn::Mesh *m = obj->addComponent<dn::Mesh>(&dn::Model::cube);
			if (win.getKey(dn::KeyCode::K))
				m->setTexture(&minecraftTexture);
			else
				m->setTexture(&bricksTexture);
			m->setRenderMode(DN_TEXTURE_COLOR | DN_LIGHT_COLOR);
		//	obj->addComponent<dn::AudioSource>(&rainClip)->setLooping(true);

			obj2->addComponent<dn::Transform>()->position() = frwrd;
			obj2->addComponent<dn::Mesh>(&dn::Model::cubeEdges)->setColor(1.f, 1.f, 1.f);

			scene.addObject(*obj);
			scene.addObject(*obj2);
			minecraftObjects.push_back(obj);
			minecraftObjects.push_back(obj2);
		}

		if (win.getKeyDown(dn::KeyCode::Y))
		{
			for (int i = 0; i < minecraftObjects.size(); i += 1)
				minecraftObjects[i]->getComponent<dn::Mesh>()->setActive(false);
		}
		if (win.getKeyUp(dn::KeyCode::Y))
		{
			for (int i = 0; i < minecraftObjects.size(); i += 1)
				minecraftObjects[i]->getComponent<dn::Mesh>()->setActive(true);
		}

		if (win.getKeyDown(dn::KeyCode::C))
			win.setMouseLock(!win.getFlag(DN_MOUSELOCKED));

		if (win.getKeyDown(dn::KeyCode::N))
			std::cout << "Cubes: " << minecraftObjects.size() << std::endl;

		win.updateViewport();
		camera.getComponent<dn::Camera>()->setAspectRatio(win.aspectRatio());

		win.clear();
	});

	dn::Application::run();

	for (size_t i = 0; i < minecraftObjects.size(); ++i)
		delete minecraftObjects[i];

	return (0);
}
