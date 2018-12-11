#ifndef APPLICATION_H
# define APPLICATION_H

# include <vector>
# include <map>
# include <functional>
# include "GLFW/glfw3.h"
# include "Codes.h"

namespace dn
{
	/* Instead of including Window.h */
	class Window;

	class Application
	{
	public:

		/* Start the application */
		static int run();
		static int terminate();
		static void stop();
		static bool running();

		/* Private function reserved for dn::Window */

			static int addWindow(dn::Window *p_window);

			static dn::Window *focusedWindow();

	static void setStartCb(const std::function<void()> &p_callback);
	static void setUpdateCb(const std::function<void()> &p_callback);

	static dn::Window *getWindow(const size_t &p_index);
	static dn::Window *getWindow(dn::Window *p_window);

	static void setFlag(const int &p_flag, const bool &p_set);
	static bool getFlag(const int &p_flag);

	private:
		/* The list of added window, inserted once the dn::Window constructor is called1 */
		static std::vector<dn::Window *> _windows;
		/*
		 * A map of windows indexed by their GLFWwindow identifiers.
		 * Created after the run() function.
		*/
		static std::map<GLFWwindow *, dn::Window *> _glfwWindows;

		/* Becomes true once the run() function is called */
		static bool	_running;
		static bool	_stopped;
		static int	_flags;

		/* The window that has the current context */
		static dn::Window *_context;
		static dn::Window *_focused;

		/* Creates the GLFW window */
		static int	createGLFWwindow(dn::Window *p_window);

		/* Returns the dn::Window from the GLFWwindow */
		static dn::Window	*getWindow(GLFWwindow *p_window);

		static void	destroyWindow(std::vector<dn::Window *>::iterator &p_it);
		static void	destroyWindows();

		/* Application callbacks */
		static std::function<void()>	_startCallback;
		static std::function<void()>	_updateCallback;

		/*
		 * Global callbacks called directly by the GLFW library.
		 * The Application will make sure of sending it to the proper window.
		*/

		static void windowStartCallback(dn::Window *p_window);
		static void windowUpdateCallback(dn::Window *p_window);
		static void windowCloseCallback(GLFWwindow *p_window);

		static void windowKeyCallback(GLFWwindow *p_window, int p_keycode, int p_scancode, int p_action, int p_mods);
		static void windowSizeCallback(GLFWwindow *p_window, int p_width, int p_height);
		static void windowPosCallback(GLFWwindow *p_window, int p_x, int p_y);
		static void windowFocusCallback(GLFWwindow *p_window, int p_focused);
		static void windowMaximizeCallback(GLFWwindow *p_window, int p_maximized);
		static void windowFramebufferSizeCallback(GLFWwindow *p_window, int p_width, int p_height);
		static void windowRefreshCallback(GLFWwindow *p_window);
		static void windowMouseButtonCallback(GLFWwindow *p_window, int p_button, int p_action, int p_mods);
		static void windowMouseMoveCallback(GLFWwindow *p_window, double p_x, double p_y);
		static void windowMouseEnterCallback(GLFWwindow *p_window, int p_entered);
		static void windowScrollCallback(GLFWwindow *p_window, double p_x, double p_y);
		static void windowDropCallback(GLFWwindow *p_window, int p_count, const char **p_paths);

		friend class dn::Window;
	};

	typedef Application app;
}


#endif
