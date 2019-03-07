#ifndef DN_WINDOW_HPP
# define DN_WINDOW_HPP

# include <string>
# include <vector>
# include <map>

# include "dn/allgl.hpp"
# include "dn/Funcs.hpp"
# include "dn/Codes.hpp"
# include "dn/Event.hpp"
# include "dn/KeyCode.hpp"
# include "dn/Vector4.hpp"

namespace dn
{
	// Forward declaration of the Application class to avoid cycles
	// as the application header file uses the Window class
	class Application;

	class Scene;

	class Window
	{
	public:
		Window(const int &p_width,
			   const int &p_height,
			   const std::string &p_title,
			   dn::Window *p_share = nullptr);

		Window(const int &p_x,
			   const int &p_y,
			   const int &p_width,
			   const int &p_height,
			   const std::string &p_title,
			   dn::Window *p_share = nullptr);

		/* Clear the window */
		void clear() const;
		void clear(const float &p_r,
				   const float &p_g,
				   const float &p_b,
				   const float &p_a = 1.0f) const;

		/* Close the window */
		void close();
		/* Open the window */
		void open();

		/* Iconifies the window */
		void iconify();
		/* Restores the window if it is iconified */
		void restore();
		/* Returns if the window is currently iconified */
		bool isIconified() const;

		/* Hides the window */
		void hide();
		/* Shows the window if it has been hidden */
		void show();
		/* Returns if the window is visible */
		bool isVisible() const;

		/* Puts the focus on the window */
		void focus();
		/* Returns if the window has the focus */
		bool isFocused() const;

		/* If `p_lock` is true then the mouse is locked in the center of the
		 * window and becomes invisible (usefull for infinite motion in games),
		 * if `p_lock` is false then sticky mouse is disabled */
		void setMouseLock(const bool &p_lock);

		void setContext();
		void updateViewport();
		void setViewport(const int &p_x, const int &p_y, const int &p_width, const int &p_height);

		/* Returns true if the key represented by `p_keycode`
		 * is currently held down, false otherwise.
		 * It will always return true until the key is released */
		bool getKey(const int &p_keycode);
		/* Same as above but returns true only once and false if the key
		 * isn't down */
		bool getKeyDown(const int &p_keycode);
		/* Returns true if the key has been released or false otherwise */
		bool getKeyUp(const int &p_keycode);
		/* They are basically the same as the functions above except that the
		 * key code is represented by the enum class `dn::KeyCode` */
		bool getKey(const dn::KeyCode &p_keycode);
		bool getKeyDown(const dn::KeyCode &p_keycode);
		bool getKeyUp(const dn::KeyCode &p_keycode);

		/* Returns true if the mouse button represented by `p_button`
		 * is currently held down, false otherwise.
		 * It will always return true until the button is released */
		bool getButton(const int &p_button);
		/* Same as above but returns true only once and false if the key
		 * is not down */
		bool getButtonDown(const int &p_button);
		/* Returns true if the button has been released or false otherwise  */
		bool getButtonUp(const int &p_button);
		/* They are basically the same as the functions above except that the 
		 * button code is represented by the enum class `dn::MouseButton` */
		bool getButton(const dn::MouseButton &p_button);
		bool getButtonDown(const dn::MouseButton &p_button);
		bool getButtonUp(const dn::MouseButton &p_button);

		/* Getters and setters */

			/* Returns the current width of the window */
			int		width() const;
			/* Sets the width of the window */
			void	setWidth(const int &p_width);

			/* Returns the current height if the window */
			int		height() const;
			/* Sets the height of the window */
			void	setHeight(const int &p_height);

			/* Returns the current frame buffer width of the window */
			int		framebufferWidth() const;
			/* Returns the current frame buffer height of the window */
			int		framebufferHeight() const;

			/* Returns the aspect ratio of the window (width/height) */
			float	aspectRatio() const;

			/* Sets the size limits */
			void	setMinLimits(const int &p_width, const int &p_height);
			void	setMaxLimits(const int &p_width, const int &p_height);
			void	setSizeLimits(const int &p_minwidth, const int &p_minheight, const int &p_maxwidth, const int &p_maxheight);

			/* Returns the position of the window in the X axis */
			int		x() const;
			/* Sets the position of the window in the X axis */
			void	setX(const int &p_x);

			/* Returns the position of the window in the Y axis */
			int		y() const;
			/* Sets the position of the window in the Y axis */
			void	setY(const int &p_y);

			/* Sets the width and the height of the window */
			void	setSize(const int &p_width, const int &p_height);
			/* Sets the position of the window in the X and Y axis */
			void	setPos(const int &p_x, const int &p_y);

			/* Returns the current title of the window */
			std::string	title() const;
			/* Sets the current title of the window */
			void		setTitle(const std::string &p_title);

			/* Returns the X position of the mouse in the window */
			double mouseX() const;
			/* Returns the Y position of the mouse in the window */
			double mouseY() const;
			/* Returns the X delta of the mouse */
			double mouseDeltaX();
			/* Returns the Y delta of the mouse */
			double mouseDeltaY();

			/* Returns the RGBA color of the clear control attribute in the universal
			 * exposition in both, the ground and the stigmatisation */
			dn::Vector4f clearColor() const;
			/* Sets the clear color, the RGB and A attribute must be between
			 * 0 and 1*/
			void setClearColor(const float &p_r, const float &p_g, const float &p_b);
			/* Sets the clear color, the RGB and A attributes must be between
			 * 0 and 255 */
			void setClearColor(const int &p_r, const int &p_g, const int &p_b);

			/* Returns the flags state */
			int		flags() const;
			void	setFlag(const int &p_flag, const bool &p_set = true);
			bool	getFlag(const int &p_flag) const;

			/* Current opacity of the window */
			float	opacity() const;
			void	setOpacity(const float &p_opacity);

			GLFWwindow	*glfw() const;

			dn::Scene *scene() const;
			void setScene(dn::Scene *p_scene);

		/* Callbacks are managable with events by adding listeners etc.
		 * So it is possible to have multiple listeners on one event */

		dn::Event<dn::Window &>					startEvent;
		dn::Event<dn::Window &>					updateEvent;
		dn::Event<dn::Window &>					closeEvent;

		dn::Event<dn::Window &, int, int>		sizeEvent;
		dn::Event<dn::Window &, int, int>		posEvent;
		dn::Event<dn::Window &, bool>			focusEvent;
		dn::Event<dn::Window &, bool>			maximizeEvent;
		dn::Event<dn::Window &, int, int>		framebufferSizeEvent;
		dn::Event<dn::Window &>					refreshEvent;
		dn::Event<dn::Window &, double, double>	mouseMoveEvent;
		dn::Event<dn::Window &, bool>			mouseEnterEvent;
		dn::Event<dn::Window &, double, double>	scrollEvent;

		dn::Event<dn::Window &, dn::KeyCode, dn::Action, dn::Mod>		keyEvent;
		dn::Event<dn::Window &, dn::KeyCode, dn::Mod>					keyPressEvent;
		dn::Event<dn::Window &, dn::KeyCode, dn::Mod>					keyReleaseEvent;
		dn::Event<dn::Window &, dn::KeyCode, dn::Mod>					keyRepeatEvent;
		dn::Event<dn::Window &, dn::MouseButton, dn::Action, dn::Mod>	mouseButtonEvent;
		dn::Event<dn::Window &, dn::MouseButton, dn::Mod>				mousePressEvent;
		dn::Event<dn::Window &, dn::MouseButton, dn::Mod>				mouseRepeatEvent;
		dn::Event<dn::Window &, dn::MouseButton, dn::Mod>				mouseReleaseEvent;
		dn::Event<dn::Window &, const std::vector<std::string> &>		dropEvent;

		/* Deprecated function, when only one listener was possible */

		void	setStartCb(const dn::startFunc &p_callback);
		void	setUpdateCb(const dn::updateFunc &p_callback);
		void	setCloseCb(const dn::closeFunc &p_callback);

		void	setKeyCb(const dn::keyFunc &p_callback);
		void	setKeyPressCb(const dn::keyPressFunc &p_callback);
		void	setKeyRepeatCb(const dn::keyRepeatFunc &p_callback);
		void	setKeyReleaseCb(const dn::keyReleaseFunc &p_callback);
		void	setSizeCb(const dn::sizeFunc &p_callback);
		void	setPosCb(const dn::posFunc &p_callback);
		void	setFocusCb(const dn::focusFunc &p_callback);
		void	setMaximizeCb(const dn::maximizeFunc &p_callback);
		void	setFramebufferSizeCb(const dn::framebufferSizeFunc &p_callback);
		void	setRefreshCb(const dn::refreshFunc &p_callback);
		void	setMouseButtonCb(const dn::mouseButtonFunc &p_callback);
		void	setMousePressCb(const dn::mousePressFunc &p_callback);
		void	setMouseRepeatCb(const dn::mouseRepeatFunc &p_callback);
		void	setMouseReleaseCb(const dn::mouseReleaseFunc &p_callback);
		void	setMouseMoveCb(const dn::mouseMoveFunc &p_callback);
		void	setMouseEnterCb(const dn::mouseEnterFunc &p_callback);
		void	setScrollCb(const dn::scrollFunc &p_callback);
		void	setDropCb(const dn::dropFunc &p_callback);

	private:
		int			_x;
		int			_y;

		int			_width;
		int			_height;

		int			_framebufferWidth;
		int			_framebufferHeight;

		int			_minwidth;
		int			_maxwidth;
		int			_minheight;
		int			_maxheight;

		std::string	_title;

		float		_opacity;

		dn::Window *_share;

		dn::Scene *_scene;

		// Stores the state of keys and mouses buttons (pressed, held, released)
		std::map<int, int> _keyLogger;
		std::map<int, int> _mouseLogger;
		// Mouse position and delta
		double _mousePos[4];

		/* Initialized by dn::Application */
		GLFWwindow	*_glfw;
		int			_windowid;

		int			_flags;

		dn::Vector4f _clearColor;

		dn::startFunc			_startCb;
		dn::updateFunc			_updateCb;
		dn::closeFunc			_closeCb;
		dn::keyFunc				_keyCb;
		dn::keyPressFunc		_keyPressCb;
		dn::keyReleaseFunc		_keyReleaseCb;
		dn::keyRepeatFunc		_keyRepeatCb;
		dn::sizeFunc			_sizeCb;
		dn::posFunc				_posCb;
		dn::focusFunc			_focusCb;
		dn::maximizeFunc		_maximizeCb;
		dn::framebufferSizeFunc	_framebufferSizeCb;
		dn::refreshFunc			_refreshCb;
		dn::mouseButtonFunc		_mouseButtonCb;
		dn::mousePressFunc		_mousePressCb;
		dn::mouseRepeatFunc		_mouseRepeatCb;
		dn::mouseReleaseFunc	_mouseReleaseCb;
		dn::mouseMoveFunc		_mouseMoveCb;
		dn::mouseEnterFunc		_mouseEnterCb;
		dn::scrollFunc			_scrollCb;
		dn::dropFunc			_dropCb;

		/* The dn::Application class needs access to all of the dn::Window's
		 * private members */
		friend class dn::Application;
	}; // class Window

} // namespace dn

#endif // DN_WINDOW_HPP
