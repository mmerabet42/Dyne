#include <iostream>

#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"
extern "C" {
#include "ft_lexiq.h"
#include "ft_printf.h"
}
#include "Window.h"
#include "Application.h"

int main()
{
	dn::Window	*win = new dn::Window(600, 400, "My App");
	dn::Window	*win2 = new dn::Window(600, 400, "zpovion");
	dn::Window	*win3 = new dn::Window(500, 20, "pzoouibhvjcs");

	win2->setPos(300, 500);
	win3->setPos(500, 10);
	win3->setClearColor(1.f, 0.f, 0.f);
	win2->setClearColor(0.f, 1.f, 0.f);
	win->setClearColor(0.1f, 0.1f, 0.1f);

	win2->setSizeCallback([](dn::Window *win, int w, int h) {
		std::cout << "win '" << win->title() << "' size change " << w << h << std::endl;
	});

	win->setPosCallback([](dn::Window *win, int x, int y) {
		std::cout << "win '" << win->title() << "' pos change " << x << y << std::endl;
	});

	win3->setUpdateCallback([](dn::Window *win) {
		(void)win;
		if (win->getKey(GLFW_KEY_ESCAPE))
			win->close();
	});

	win2->setUpdateCallback([](dn::Window *win) {
		if (win->getKey(GLFW_KEY_ESCAPE))
			win->close();
	});

	win->setStartCallback([](dn::Window *win) {
		std::cout << win->x() << ", " << win->y() << std::endl;
	});

	win->setUpdateCallback([](dn::Window *win) {
		static int	scl = 3;

		if (win->getKey(GLFW_KEY_ESCAPE))
			win->close();

		if (win->getKey(GLFW_KEY_LEFT_SHIFT))
		{
			if (win->getKey(GLFW_KEY_LEFT_CONTROL) && win->getKey(GLFW_KEY_UP))
				win->height(win->height() - 1);
			else if (win->getKey(GLFW_KEY_UP))
				win->y(win->y() - scl);

			if (win->getKey(GLFW_KEY_LEFT_CONTROL) && win->getKey(GLFW_KEY_DOWN))
				win->height(win->height() + 1);
			else if (win->getKey(GLFW_KEY_DOWN))
				win->y(win->y() + scl);

			if (win->getKey(GLFW_KEY_LEFT_CONTROL) && win->getKey(GLFW_KEY_LEFT))
				win->width(win->width() - 1);
			else if (win->getKey(GLFW_KEY_LEFT))
				win->x(win->x() - scl);

			if (win->getKey(GLFW_KEY_LEFT_CONTROL) && win->getKey(GLFW_KEY_RIGHT))
				win->width(win->width() + 1);
			else if (win->getKey(GLFW_KEY_RIGHT))
				win->x(win->x() + scl);
		}

	});

	dn::Application::run();
}
