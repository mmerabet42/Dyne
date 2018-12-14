#include <iostream>

#include "Window.h"
#include "Application.h"
#include "Model.h"

void closeWinEscape(dn::Window *w, int k, int, int) { if (k == DN_KEY_ESCAPE) w->close(); }

int main()
{
	dn::Window *win = new dn::Window(600, 400, "loader");

	win->keyEvent.addListener(closeWinEscape);
	win->setClearColor(37, 44, 56);

	dn::Shape squareShape({
		{{-0.5f, 0.5f, 0.f},	{1, 1, 1, 1}},
		{{0.5f, 0.5f, 0.f},		{1, 1, 1, 1}},
		{{-0.5f, -0.5f, 0.f},	{1, 1, 1, 1}},
		{{0.5f, -0.5f, 0.f},	{1, 1, 1, 1}},
	}, DN_TRIANGLE_STRIP, {
		0, 1, 2, 3,
	});
/*
	dn::Shape cubeShape({
		{{0.5f, -0.5f, 0.5f}, {1.f, 1.f, 1.f, 1.f}},
		{{0.5f, 0.5f, 0.5f}, {1.f, 1.f, 1.f, 1.f}},
		{{-0.5f, -0.5f, 0.5f}, {1.f, 1.f, 1.f, 1.f}},
		{{-0.5f, 0.5f, 0.5f}, {1.f, 1.f, 1.f, 1.f}},

		{{0.5f, -0.5f, -0.5f}, {1.f, 1.f, 1.f, 1.f}},
		{{0.5f, 0.5f, -0.5f}, {1.f, 1.f, 1.f, 1.f}},
		{{-0.5f, -0.5f, -0.5f}, {1.f, 1.f, 1.f, 1.f}},
		{{-0.5f, 0.5f, -0.5f}, {1.f, 1.f, 1.f, 1.f}},
	}, {
		0, 1, 3, 2,
		6, 7, 3, 1,
		5, 7, 6, 4,
		5, 4, 0, 2, 6
	});
*/
	dn::Model square(squareShape);
	dn::Model square1(squareShape);
	dn::Model square2(squareShape);
	dn::Model square3(squareShape);
	square1.setParent(&square);
	square1.position().x = 1.5f;
	square2.setParent(&square1);
	square2.position().y = 1.5f;
	square3.setParent(&square2);
	square3.position().x = 1.5f;

	win->startEvent([&](dn::Window *win) {
		win->updateViewport();
		dn::Model::setCamAspectRatio((float)win->framebufferWidth() / (float)win->framebufferHeight());
		square.create();
		square1.create();
		square2.create();
		square3.create();
	});
	win->framebufferSizeEvent([](dn::Window *win, int w, int h) {
		win->updateViewport();
		dn::Model::setCamAspectRatio((float)w / (float)h);
	});

	win->updateEvent([&](dn::Window *win) {

		if (win->getKey(DN_KEY_LEFT))
			square.position().x -= 2.f * dn::Application::deltaTime();
		if (win->getKey(DN_KEY_RIGHT))
			square.position().x += 2.f * dn::Application::deltaTime();

		if (win->getKey(DN_KEY_UP))
			square.position().y += 2.f * dn::Application::deltaTime();
		if (win->getKey(DN_KEY_DOWN))
			square.position().y -= 2.f * dn::Application::deltaTime();

		if (win->getKey(DN_KEY_E))
			square.rotation().z += 2.f * dn::Application::deltaTime();
		if (win->getKey(DN_KEY_R))
			square.rotation().z -= 2.f * dn::Application::deltaTime();

		if (win->getKey(DN_KEY_D))
			square1.rotation().z += 2.f * dn::Application::deltaTime();
		if (win->getKey(DN_KEY_F))
			square1.rotation().z -= 2.f * dn::Application::deltaTime();
		if (win->getKey(DN_KEY_C))
			square2.rotation().z += 2.f * dn::Application::deltaTime();
		if (win->getKey(DN_KEY_V))
			square2.rotation().z -= 2.f * dn::Application::deltaTime();

		if (win->getKey(DN_KEY_O))
			square.rotation().x += 2.f * dn::Application::deltaTime();
		else if (win->getKey(DN_KEY_P))
			square.rotation().x -= 2.f * dn::Application::deltaTime();

		if (win->getKey(DN_KEY_W))
			dn::Model::camPositionc().z -= 0.05f;
		if (win->getKey(DN_KEY_S))
			dn::Model::camPositionc().z += 0.05f;

		win->clear();
		square.draw();
		square1.draw();
		square2.draw();
		square3.draw();
	});

	dn::Application::setFlag(DN_FREEWINDOWS, true);
	return (dn::Application::run());
}
