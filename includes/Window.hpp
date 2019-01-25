#ifndef WINDOW_HPP
# define WINDOW_HPP

# include <string>
# include <vector>
# include <map>

# include "allgl.hpp"
# include "Funcs.hpp"
# include "Codes.hpp"
# include "Event.hpp"
# include "KeyCode.hpp"
# include "Vector4.hpp"

namespace dn
{
	// Forward declaration of the Application class to avoid cycles
	// as the application header file uses the Window class
	class Application;

	class Scene;

	class Window
	{
	public:
		Window(const int &p_width, const int &p_height, const std::string &p_title, dn::Window *p_share = nullptr);
		Window(const int &p_x, const int &p_y, const int &p_width, const int &p_height, const std::string &p_title, dn::Window *p_share = nullptr);

		void clear() const;
		void clear(const float &p_r, const float &p_g, const float &p_b, const float &p_a = 1.0f) const;

		void close();
		void open();

		void iconify();
		void restore();
		bool iconified() const;
	
		void hide();
		void show();
		bool visible() const;

		void focus();
		bool focused() const;

		void setMouseLock(const bool &p_lock);

		void setContext(const bool &p_force = false);
		void setViewport(const int &p_x, const int &p_y, const int &p_width, const int &p_height);
		void updateViewport();

		bool getKey(const int &p_keycode);
		bool getKeyDown(const int &p_keycode);
		bool getKeyUp(const int &p_keycode);
		bool getKey(const dn::KeyCode &p_keycode);
		bool getKeyDown(const dn::KeyCode &p_keycode);
		bool getKeyUp(const dn::KeyCode &p_keycode);

		bool getButton(const int &p_button);
		bool getButtonDown(const int &p_button);
		bool getButtonUp(const int &p_button);
		bool getButton(const dn::MouseButton &p_button);
		bool getButtonDown(const dn::MouseButton &p_button);
		bool getButtonUp(const dn::MouseButton &p_button);

		/* Getters and setters */

			int		width() const;
			void	width(const int &p_width);

			int		height() const;
			void	height(const int &p_height);

			int		framebufferWidth() const;
			int		framebufferHeight() const;

			float	aspectRatio() const;

			void	setMinLimits(const int &p_width, const int &p_height);
			void	setMaxLimits(const int &p_width, const int &p_height);
			void	setSizeLimits(const int &p_minwidth, const int &p_minheight, const int &p_maxwidth, const int &p_maxheight);

			int		x() const;
			void	x(const int &p_x);

			int		y() const;
			void	y(const int &p_y);

			void	setSize(const int &p_width, const int &p_height);
			void	setPos(const int &p_x, const int &p_y);

			std::string	title() const;
			void		title(const std::string &p_title);

			double mouseX() const;
			double mouseY() const;
			double mouseDeltaX();
			double mouseDeltaY();

			dn::Vector4f clearColor() const;
			void setClearColor(const float &p_r, const float &p_g, const float &p_b);
			void setClearColor(const int &p_r, const int &p_g, const int &p_b);

			int		flags() const;
			void	setFlag(const int &p_flag, const bool &p_set = true);
			bool	getFlag(const int &p_flag) const;

			float	opacity() const;
			void	setOpacity(const float &p_opacity);

			GLFWwindow	*glfw() const;

			dn::Scene *scene() const;
			void setScene(dn::Scene *p_scene);

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

		/* The dn::Application class has access to all of the dn::Window attributes. */
		friend class dn::Application;
	};
}

#endif
