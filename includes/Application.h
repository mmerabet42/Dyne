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
		static int	run();
		static bool	running();

		/* Private function reserved for dn::Window */

			static int	addWindow(dn::Window *p_window);

			static void	closeWindow(dn::Window *p_window);
			static void	destroyWindows();

			static dn::Window	*focusedWindow();

	static void	onStart(void(*p_callback)());
	static void	onUpdate(void(*p_callback)());

	private:
		/* The list of added window, inserted once the dn::Window constructor is called1 */
		static std::vector<dn::Window *> _windows;
		/*
		 * A map of windows indexed by their GLFWwindow identifiers.
		 * Created after the run() function.
		*/
		static std::map<GLFWwindow *, dn::Window *> _glfwWindows;

		/* Becomes true once the run() function is called */
		static bool _running;

		/* The window that has the current context */
		static dn::Window *_context;
		static dn::Window *_focused;

		/* Creates the GLFW window */
		static int	createGLFWwindow(dn::Window *p_window);

		/* Returns the dn::Window from the GLFWwindow */
		static dn::Window *getWindow(GLFWwindow *p_window);

		/* Application callbacks */
		static void(*_startCallback)();
		static void(*_updateCallback)();

		/*
		 * Global callbacks called directly by the GLFW library.
		 * The Application will make sure of sending it to the proper window.
		*/

		static void	windowStartCallback(dn::Window *p_window);
		static void	windowUpdateCallback(dn::Window *p_window);
		static void	windowCloseCallback(GLFWwindow *p_window);

		static void	windowKeyCallback(GLFWwindow *p_window, int p_keycode, int p_scancode, int p_action, int p_mods);
		static void	windowSizeCallback(GLFWwindow *p_window, int p_width, int p_height);
		static void	windowPosCallback(GLFWwindow *p_window, int p_x, int p_y);
		static void	windowFocusCallback(GLFWwindow *p_window, int focused);
	
		friend class dn::Window;
	};
}

#endif
