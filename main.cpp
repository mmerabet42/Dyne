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

	win2->setFlag(DN_AUTOCLEAR, true);
	win3->setFlag(DN_AUTOCLEAR, true);

	win->setOpacity(0.5f);

	win->setKeyCb([](dn::Window *win, int key, int ac) {
		std::cout << "Key event " << key << " " << ac << std::endl;
	});

	win->setCloseCb([](dn::Window *win) {
		if (!win->getFlag(DN_CUSTOM_FLAG0))
		{
			std::cout << "Cannot be closed click on 'L' to enable closing" << std::endl;
			win->open();
		}
	});

	win->setStartCb([](dn::Window *win) {
		std::cout << "Window '" << win->title() << "' oppened" << std::endl;
	});

	win->setUpdateCb([](dn::Window *win) {
		static int	scl = 3;

		win->clear();

		if (win->getKey(GLFW_KEY_ESCAPE))
			win->close();
		if (win->getKey(GLFW_KEY_L))
		{
			std::cout << "Closing the window is now possible !" << std::endl;
			win->setClearColor(0.f, 0.f, 1.f);
			win->setFlag(DN_CUSTOM_FLAG0, true);
		}

		if (win->getKey(GLFW_KEY_E))
			std::cout << "E pressed" << std::endl;

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