#ifndef WINDOW_H
# define WINDOW_H

# include <string>
# include "GLFW/glfw3.h"
# include "Color.h"
# include "Funcs.h"

# define DN_CLOSED (1 << 0)
# define DN_POS_SPECIFIED (1 << 1)
# define DN_ICONIFIED (1 << 2)
# define DN_VISIBLE (1 << 3)
# define DN_AUTOCLEAR (1 << 4)
# define DN_FLAG_NUM 5

# define DN_CUSTOM_FLAG0 (1 << (DN_FLAG_NUM + 0))
# define DN_CUSTOM_FLAG1 (1 << (DN_FLAG_NUM + 1))
# define DN_CUSTOM_FLAG2 (1 << (DN_FLAG_NUM + 2))
# define DN_CUSTOM_FLAG4 (1 << (DN_FLAG_NUM + 3))
# define DN_CUSTOM_FLAG5 (1 << (DN_FLAG_NUM + 4))

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

		void	setStartCb(dn::startCbFunc p_callback);
		void	setUpdateCb(dn::updateCbFunc p_callback);
		void	setCloseCb(dn::closeCbFunc p_callback);

		void	setKeyCb(dn::keyCbFunc p_callback);
		void	setSizeCb(dn::sizeCbFunc p_callback);
		void	setPosCb(dn::posCbFunc p_callback);
		void	setFocusCb(dn::focusCbFunc p_callback);

	private:
		int			_x;
		int			_y;

		int			_width;
		int			_height;

		std::string	_title;

		float		_opacity;

		/* Initialized by dn::Application */
		GLFWwindow	*_glfw;
		int			_windowid;

		int			_flags;

		dn::Color	_clearColor;

		dn::startCbFunc		_startCb;
		dn::updateCbFunc	_updateCb;
		dn::closeCbFunc		_closeCb;
		
		dn::keyCbFunc		_keyCb;
		dn::sizeCbFunc		_sizeCb;
		dn::posCbFunc		_posCb;
		dn::focusCbFunc		_focusCb;

		/* The dn::Application class has access to all of the dn::Window attributes. */
		friend class dn::Application;
	};
}

#endif
