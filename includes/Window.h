#ifndef WINDOW_H
# define WINDOW_H

# include <string>
# include "GLFW/glfw3.h"
# include "Color.h"
# include "Funcs.h"
# include "Codes.h"

namespace dn
{
	/* Instead of including Application.h */
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

		int		getKey(const int &p_keycode) const;

		/* Getters and setters */

			int		width() const;
			void	width(const int &p_width);

			int		height() const;
			void	height(const int &p_height);

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

			int		flags() const;
			void	setFlag(const int &p_flag, const bool &p_set = true);
			bool	getFlag(const int &p_flag) const;

			float	opacity() const;
			void	setOpacity(const float &p_opacity);

		void	setStartCb(const dn::startFunc &p_callback);
		void	setUpdateCb(const dn::updateFunc &p_callback);
		void	setCloseCb(const dn::closeFunc &p_callback);

		void	setKeyCb(const dn::keyFunc &p_callback);
		void	setSizeCb(const dn::sizeFunc &p_callback);
		void	setPosCb(const dn::posFunc &p_callback);
		void	setFocusCb(const dn::focusFunc &p_callback);
		void	setMaximizeCb(const dn::maximizeFunc &p_callback);
		void	setFramebufferSizeCb(const dn::framebufferSizeFunc &p_callback);

	private:
		int			_x;
		int			_y;

		int			_width;
		int			_height;
		int			_framebufferWidth;
		int			_framebufferHeight;

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

		/* The dn::Application class has access to all of the dn::Window attributes. */
		friend class dn::Application;
	};
}

#endif
