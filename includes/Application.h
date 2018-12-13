#ifndef APPLICATION_H
# define APPLICATION_H

# include <vector>
# include <map>
# include <functional>

# include "allgl.h"
# include "Codes.h"

namespace dn
{
	// Forward declaration of the Window class to avoid cycles
	// as the window header file uses the Application class
	class Window;

	// The Application class is just a set of static functions that abstracts
	// window additions, event callbacks etc.
	class Application
	{
	public:

		// The run() function must be called to run the Application, all added
		// windows are created and shown after this call.
		// The function returns once no more window is open.
		static int run();
		// The terminate() function destroys all windows and terminate glfw,
		// then it sets the _running attribute to false
		static int terminate();
		// The stop() function closes all windows and stop the application by setting the
		// _running attribute to false
		static void stop();
		// Returns if the application is currently running
		static bool running();

		// Static function that might be called by the Window class

			static int addWindow(dn::Window *p_window);
			static dn::Window *focusedWindow();

			static dn::Window *getWindow(const size_t &p_index);
			static dn::Window *getWindow(dn::Window *p_window);
			// Set and get the current context, all opengl draws are done
			// on the window that has the current context
			static void setContext(dn::Window *p_window, const bool &p_force = false);
			static dn::Window *context();

		// The start callback is called once the run() function is called,
		// glew and glfw were initiated and all windows were created
		static void setStartCb(const std::function<void()> &p_callback);
		// The update callback is called at every cycles of the main loop in the run() function
		static void setUpdateCb(const std::function<void()> &p_callback);
		// The exit callback is called at the end of the main loop in the run() function
		static void setExitCb(const std::function<void()> &p_callback);

		// Flag getter, enabler and disabler
		static void setFlag(const int &p_flag, const bool &p_set);
		static bool getFlag(const int &p_flag);

	private:
		// All the windows added to the Application are stored here
		// A window is added once the dn::Window constructor is called
		static std::vector<dn::Window *> _windows;
		// Maps the windows according to their GLFWwindow pointer which is initiated
		// once the run() function is called
		static std::map<GLFWwindow *, dn::Window *> _glfwWindows;

		// Attributes for memorizing the current state of the Application
		static bool	_running;
		static bool	_stopped;
		static int	_flags;

		static dn::Window *_context;
		static dn::Window *_focused;

		// Creates the GLFWwindow and connects the callbacks
		static int	createGLFWwindow(dn::Window *p_window);

		// Returns the mapped dn::Window from the GLFWwindow
		static dn::Window	*getWindow(GLFWwindow *p_window);

		// Destroy all windows
		static void	destroyWindow(std::vector<dn::Window *>::iterator &p_it);
		static void	destroyWindows();

		// Callback pointers, the reason why std::function is used instead of
		// a function pointer is that std::function can capture variables when
		// using lambdas
		static std::function<void()>	_startCallback;
		static std::function<void()>	_updateCallback;
		static std::function<void()>	_exitCallback;

		// Callback functions called directly by the GLFW api, each window has
		// his callbacks connected to these functions, then the application sends
		// the callback to the proper dn::Window

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

		// The window call needs access to some private members of the Application
		friend class dn::Window;
	};

	typedef Application app;
}


#endif
