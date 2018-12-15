#ifndef WINDOW_H
# define WINDOW_H

# include <string>

# include "allgl.h"
# include "Color.h"
# include "Funcs.h"
# include "Codes.h"
# include "Event.h"

namespace dn
{
	// Forward declaration of the Application class to avoid cycles
	// as the application header file uses the Window class
	class Application;

	class Window
	{
	public:
		Window(const int &p_width, const int &p_height, const std::string &p_title = "Window");
		Window(const int &p_x, const int &p_y, const int &p_width, const int &p_height, const std::string &p_title = "Window");

		void	clear() const;
		void	clear(const float &p_r, const float &p_g, const float &p_b, const float &p_a = 1.0f) const;

		void	close();
		void	open();

		void	iconify();
		void	restore();
		bool	iconified() const;
	
		void	hide();
		void	show();
		bool	visible() const;

		void	focus();
		bool	focused() const;

		void	setContext(const bool &p_force = false);
		void	setViewport(const int &p_x, const int &p_y, const int &p_width, const int &p_height);
		void	updateViewport();

		int		getKey(const int &p_keycode) const;

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

			dn::Color	clearColor() const;
			void		setClearColor(const float &p_r, const float &p_g, const float &p_b);
			void		setClearColor(const int &p_r, const int &p_g, const int &p_b);

			int		flags() const;
			void	setFlag(const int &p_flag, const bool &p_set = true);
			bool	getFlag(const int &p_flag) const;

			float	opacity() const;
			void	setOpacity(const float &p_opacity);

			GLFWwindow	*glfw() const;

		void	setStartCb(const dn::startFunc &p_callback);
		void	setUpdateCb(const dn::updateFunc &p_callback);
		void	setCloseCb(const dn::closeFunc &p_callback);

		void	setKeyCb(const dn::keyFunc &p_callback);
		void	setSizeCb(const dn::sizeFunc &p_callback);
		void	setPosCb(const dn::posFunc &p_callback);
		void	setFocusCb(const dn::focusFunc &p_callback);
		void	setMaximizeCb(const dn::maximizeFunc &p_callback);
		void	setFramebufferSizeCb(const dn::framebufferSizeFunc &p_callback);
		void	setRefreshCb(const dn::refreshFunc &p_callback);
		void	setMouseButtonCb(const dn::mouseButtonFunc &p_callback);
		void	setMouseMoveCb(const dn::mouseMoveFunc &p_callback);
		void	setMouseEnterCb(const dn::mouseEnterFunc &p_callback);
		void	setScrollCb(const dn::scrollFunc &p_callback);
		void	setDropCb(const dn::dropFunc &p_callback);

		dn::PriorityEvent<dn::Window *>						startEvent;
		dn::PriorityEvent<dn::Window *>						updateEvent;
		dn::PriorityEvent<dn::Window *>						closeEvent;

		dn::PriorityEvent<dn::Window *, int, int, int>		keyEvent;
		dn::PriorityEvent<dn::Window *, int, int>			sizeEvent;
		dn::PriorityEvent<dn::Window *, int, int>			posEvent;
		dn::PriorityEvent<dn::Window *, bool>				focusEvent;
		dn::PriorityEvent<dn::Window *, bool>				maximizeEvent;
		dn::PriorityEvent<dn::Window *, int, int>			framebufferSizeEvent;
		dn::PriorityEvent<dn::Window *>						refreshEvent;
		dn::PriorityEvent<dn::Window *, int, int, int>		mouseButtonEvent;
		dn::PriorityEvent<dn::Window *, double, double>		mouseMoveEvent;
		dn::PriorityEvent<dn::Window *, bool>				mouseEnterEvent;
		dn::PriorityEvent<dn::Window *, double, double>		scrollEvent;
		dn::PriorityEvent<dn::Window *, int, const char **>	dropEvent;

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

		/* Initialized by dn::Application */
		GLFWwindow	*_glfw;
		int			_windowid;

		int			_flags;

		dn::Color	_clearColor;

		dn::startFunc			_startCb;
		dn::updateFunc			_updateCb;
		dn::closeFunc			_closeCb;
		dn::keyFunc				_keyCb;
		dn::sizeFunc			_sizeCb;
		dn::posFunc				_posCb;
		dn::focusFunc			_focusCb;
		dn::maximizeFunc		_maximizeCb;
		dn::framebufferSizeFunc	_framebufferSizeCb;
		dn::refreshFunc			_refreshCb;
		dn::mouseButtonFunc		_mouseButtonCb;
		dn::mouseMoveFunc		_mouseMoveCb;
		dn::mouseEnterFunc		_mouseEnterCb;
		dn::scrollFunc			_scrollCb;
		dn::dropFunc			_dropCb;

		/* The dn::Application class has access to all of the dn::Window attributes. */
		friend class dn::Application;
	};
}

#endif
