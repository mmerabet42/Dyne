#ifndef APPLICATION_H
# define APPLICATION_H

#include <vector>
#include <map>
#include "GLFW/glfw3.h"

namespace dn
{
	enum {
		DN_OK,
		DN_GLFW_FAIL,
		DN_GLEW_FAIL,
		DN_ALRDY_RUNNING,
		DN_WINDOW_FAIL,
	};

	/* Instead of including Window.h */
	class Window;

	class Application
	{
	public:

		/* Start the application */
		static int	Run();

		/* Private function reserved for dn::Window */

			static int	AddWindow(dn::Window *p_window);
			static int	CreateGLFWwindow(dn::Window *p_window);

			static void	CloseWindow(dn::Window *p_window);
			static void	DestroyWindows();

	private:
		static std::vector<dn::Window *>			_windows;
		static std::map<GLFWwindow *, dn::Window *>	_glfwWindows;

		static bool	_running;

		/* Global callbacks called directly by the GLFW library */

		static void	WindowStartCallback(dn::Window *p_window);
		static void	WindowUpdateCallback(dn::Window *p_window);
		static void	WindowKeyCallback(GLFWwindow *p_window, int p_keycode, int p_scancode, int p_action, int p_mods);
	};
}

#endif
