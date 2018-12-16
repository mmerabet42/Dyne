#include <iostream>

#include "Window.h"
#include "Application.h"
#include "Model.h"
#include "Math.h"
#include "Object.h"
#include "Component.h"

void closeWinEscape(dn::Window *w, int k, int, int) { if (k == DN_KEY_ESCAPE) w->close(); }

int main()
{
	dn::Window *win = new dn::Window(600, 400, "Window 1");

	win->keyEvent.addListener(closeWinEscape);
	win->setClearColor(37, 44, 56);

	dn::Shape cubeShape({
		{{0.5f, -0.5f, 0.5f}, {1.f, 1.f, 1.f, 1.f}},
		{{0.5f, 0.5f, 0.5f}, {1.f, 1.f, 1.f, 1.f}},
		{{-0.5f, -0.5f, 0.5f}, {1.f, 1.f, 1.f, 1.f}},
		{{-0.5f, 0.5f, 0.5f}, {1.f, 1.f, 1.f, 1.f}},

		{{0.5f, -0.5f, -0.5f}, {1.f, 1.f, 1.f, 1.f}},
		{{0.5f, 0.5f, -0.5f}, {1.f, 1.f, 1.f, 1.f}},
		{{-0.5f, -0.5f, -0.5f}, {1.f, 1.f, 1.f, 1.f}},
		{{-0.5f, 0.5f, -0.5f}, {1.f, 1.f, 1.f, 1.f}},
	}, GL_LINE_STRIP, {
		0, 1, 3, 2, 0, 4, 6, 2, 3, 7, 6, 4, 5, 1, 5, 7
	});

	dn::Model cube(cubeShape);

	dn::Model::camPositionc().z = 5.f;

	dn::Object *obj = new dn::Object;

	obj->addComponent<SimpleComp>();
	obj->removeComponent<SimpleComp>();

	win->startEvent([&](dn::Window *win) {
		win->setContext();
		cube.create();
		obj->start();
	});

	float vel = 0.f;

	win->updateEvent([&](dn::Window *win) {

		if (win->getKey(DN_KEY_LEFT))
			cube.rotation().y -= 1.5f * dn::Application::deltaTime();
		if (win->getKey(DN_KEY_RIGHT))
			cube.rotation().y += 1.5f * dn::Application::deltaTime();

		if (win->getKey(DN_KEY_UP))
			cube.rotation().x += 1.5f * dn::Application::deltaTime();
		if (win->getKey(DN_KEY_DOWN))
			cube.rotation().x -= 1.5f * dn::Application::deltaTime();

		if (win->getKey(DN_KEY_W))
			dn::Model::camPositionc().z -= 2.5f * dn::Application::deltaTime();
		if (win->getKey(DN_KEY_S))
			dn::Model::camPositionc().z += 2.5f * dn::Application::deltaTime();

		if (win->getKey(DN_KEY_A))
			dn::Model::camPositionc().x -= 2.5f * dn::Application::deltaTime();
		if (win->getKey(DN_KEY_D))
			dn::Model::camPositionc().x += 2.5f * dn::Application::deltaTime();

		if (win->getKey(DN_KEY_KP_ADD))
			dn::Model::setCamFov(dn::Model::camFov() + 0.005f);
		else if (win->getKey(DN_KEY_KP_SUBTRACT))
			dn::Model::setCamFov(dn::Model::camFov() - 0.005f);

		cube.position().x = dn::math::smoothDamp(cube.position().x, 5.f, vel, 0.05f);

		win->updateViewport();
		dn::Model::setCamAspectRatio(win->aspectRatio());

		win->clear();
		cube.draw();
	});

	dn::Application::setFlag(DN_FREEWINDOWS, true);
	return (dn::Application::run());
}
