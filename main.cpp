#include <iostream>

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

void closeWinEscape(dn::Window *w, int k, int, int) { if (k == DN_KEY_ESCAPE) w->close(); }

int main()
{
	dn::Window *win = new dn::Window(600, 400, "Window 1");

	win->keyEvent.addListener(closeWinEscape);
	win->setClearColor(37, 44, 56);

	dn::Model cubeModel({
		{{0.5f, -0.5f, 0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.f, 0.f}},
		{{0.5f, 0.5f, 0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.f, 0.f}},
		{{-0.5f, -0.5f, 0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.f, 0.f}},
		{{-0.5f, 0.5f, 0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.f, 0.f}},

		{{0.5f, -0.5f, -0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.f, 0.f}},
		{{0.5f, 0.5f, -0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.f, 0.f}},
		{{-0.5f, -0.5f, -0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.f, 0.f}},
		{{-0.5f, 0.5f, -0.5f}, {1.f, 1.f, 1.f, 1.f}, {0.f, 0.f}},
	}, GL_LINE_STRIP, {
		0, 1, 3, 2, 0, 4, 6, 2, 3, 7, 6, 4, 5, 1, 5, 7
	});
	dn::Model pointsModel = dn::Model::generatePoints(5000, 1000.f);

	dn::Object *cube = new dn::Object;
	dn::Object *cube1 = new dn::Object;
	dn::Object *points = new dn::Object;
	dn::Object *camera = new dn::Object;

	std::vector<dn::Object *> cubes;
	int nCubes = 100;
	float area = 100.f;
	for (int i = 0; i < nCubes; ++i)
	{
		dn::Object *newCube = new dn::Object;
		newCube->addComponent<dn::Transform>(
			dn::math::random(-area, area),
			dn::math::random(-area, area),
			dn::math::random(-area, area));
		newCube->addComponent<dn::MeshRenderer>(&cubeModel);
		cubes.push_back(newCube);
	}

	dn::Transform *cubeTransform = cube->addComponent<dn::Transform>();
	cube->addComponent<dn::MeshRenderer>(&cubeModel);

	dn::Transform *cube1Transform = cube1->addComponent<dn::Transform>(0.f, -5.f, 0.f);
	cube1->addComponent<dn::MeshRenderer>(&cubeModel);

	dn::Transform *pointsTransform = points->addComponent<dn::Transform>();
	points->addComponent<dn::MeshRenderer>(&pointsModel);

	dn::Transform *cameraTransform = camera->addComponent<dn::Transform>(0.f, 0.f, 5.f);
	camera->addComponent<dn::Camera>(70.f, 0.02f, 100000000.f);

	win->startEvent([&](dn::Window *win) {
		cube->start();
		cube1->start();
		points->start();
		for (int i = 0; i < nCubes; ++i)
			cubes[i]->start();
	});

	float vel = 0.f;
	float target = 100.f;
	float smooth = 0.1f;
	float speedMove = 0.1f;
	float cubesMove = 0.1f;

	win->keyEvent.addListener([&](dn::Window *win, int k, int a, int) {
		if (k == DN_KEY_G && a == DN_PRESS)
			target = (target == 100.f ? -100.f : 100.f);
	});

	win->updateEvent([&](dn::Window *win) {

		if (win->getKey(DN_KEY_LEFT))
			cameraTransform->rotation().y += 0.5f * dn::Application::deltaTime();
		if (win->getKey(DN_KEY_RIGHT))
			cameraTransform->rotation().y -= 0.5f * dn::Application::deltaTime();

		if (win->getKey(DN_KEY_UP))
			cameraTransform->rotation().x += 0.5f * dn::Application::deltaTime();
		if (win->getKey(DN_KEY_DOWN))
			cameraTransform->rotation().x -= 0.5f * dn::Application::deltaTime();

		if (win->getKey(DN_KEY_W))
			cameraTransform->position() += cameraTransform->forward() * speedMove;
		if (win->getKey(DN_KEY_S))
			cameraTransform->position() -= cameraTransform->forward() * speedMove;

		if (win->getKey(DN_KEY_A))
			cameraTransform->position() -= cameraTransform->right() * speedMove;
		if (win->getKey(DN_KEY_D))
			cameraTransform->position() += cameraTransform->right() * speedMove;

		if (win->getKey(DN_KEY_LEFT_SHIFT))
			cameraTransform->position() -= cameraTransform->up() * speedMove;
		if (win->getKey(DN_KEY_SPACE))
			cameraTransform->position() += cameraTransform->up() * speedMove;

		if (win->getKey(DN_KEY_KP_ADD))
			camera->getComponent<dn::Camera>()->fov() += 0.005f;
		else if (win->getKey(DN_KEY_KP_SUBTRACT))
			camera->getComponent<dn::Camera>()->fov() -= 0.005f;

		pointsTransform->scale() += 0.001f;

		if (win->getKey(DN_KEY_LEFT_CONTROL))
			speedMove = (win->getKey(DN_KEY_RIGHT_CONTROL) ? 100.f : 2.f);
		else
			speedMove = 0.1f;

		if (win->getKey(DN_KEY_H))
			cubesMove += 0.01f;
		if (win->getKey(DN_KEY_J))
			cubesMove -= 0.01f;

		cubeTransform->position().x = dn::math::smoothDamp(cubeTransform->position().x, target, vel, smooth);
		cube1Transform->lookAt(cubeTransform->position());

		win->updateViewport();
		camera->getComponent<dn::Camera>()->setAspectRatio(win->aspectRatio());

		win->clear();
		for (int i = 0; i < nCubes; ++i)
		{
			dn::Transform *transform = cubes[i]->getComponent<dn::Transform>();
			transform->position() += transform->forward() * cubesMove;
			transform->lookAt(cubeTransform->position());
			cubes[i]->update();
		}
		cube->update();
		cube1->update();
		points->update();
	});

	dn::Application::setFlag(DN_FREEWINDOWS, true);
	return (dn::Application::run());
}
