#include <iostream>

#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/transform.hpp"
#include "glm/gtx/quaternion.hpp"

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
		{{-0.1f, 0.1f, 0.f},	{1, 1, 1, 1}},
		{{0.1f, 0.1f, 0.f},		{1, 1, 1, 1}},
		{{0.1f, -0.1f, 0.f},	{1, 1, 1, 1}},
		{{-0.1f, -0.1f, 0.f},	{1, 1, 1, 1}},
	}, {
		0, 1, 2, 3, 0
	});

	dn::Model square(squareShape);
	dn::Model square1(squareShape);
	dn::Model square2(squareShape);
	dn::Model square3(squareShape);
	square1.setParent(&square);
	square1.position().x = 0.5f;
	square2.setParent(&square1);
	square2.position().y = 0.5f;
	square3.setParent(&square2);
	square3.position().x = 0.5f;

	win->startEvent([&](dn::Window *win) {
		win->updateViewport();
		square.create();
		square1.create();
		square2.create();
		square3.create();
	});
	win->framebufferSizeEvent([](dn::Window *win, int w, int h) {
		win->updateViewport();
	});

	win->updateEvent([&](dn::Window *win) {

		if (win->getKey(DN_KEY_LEFT))
			square.position().x -= 0.03f;
		if (win->getKey(DN_KEY_RIGHT))
			square.position().x += 0.03f;

		if (win->getKey(DN_KEY_UP))
			square.position().y += 0.03f;
		if (win->getKey(DN_KEY_DOWN))
			square.position().y -= 0.03f;

		if (win->getKey(DN_KEY_E))
			square.rotation().z += 0.02f;
		if (win->getKey(DN_KEY_R))
			square.rotation().z -= 0.02f;

		if (win->getKey(DN_KEY_D))
			square1.rotation().z += 0.02f;
		if (win->getKey(DN_KEY_F))
			square1.rotation().z -= 0.02f;
		if (win->getKey(DN_KEY_C))
			square2.rotation().z += 0.02f;
		if (win->getKey(DN_KEY_V))
			square2.rotation().z -= 0.02f;

		win->clear();
		square.draw(DN_LINE_STRIP);
		square1.draw(DN_LINE_STRIP);
		square2.draw(DN_LINE_STRIP);
		square3.draw(DN_LINE_STRIP);
	});

	dn::Application::setFlag(DN_FREEWINDOWS, true);
	return (dn::Application::run());
}
