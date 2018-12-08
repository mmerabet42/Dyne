#ifndef WINDOW_H
# define WINDOW_H

# include <string>
# include "GLFW/glfw3.h"
# include "Color.h"

# define DN_CLOSED (1 << 0)
# define DN_POS_SPECIFIED (1 << 1)
# define DN_ICONIFIED (1 << 2)
# define DN_VISIBLE (1 << 3)

namespace dn
{
	/* Instead of including Application.h */
	class Application;

	class Window
	{
	public:
		Window(const int &p_width, const int &p_height, const std::string &p_title = "Window");
		Window(const int &p_x, const int &p_y, const int &p_width, const int &p_height, const std::string &p_title = "Window");

		void	close();

		void	iconify();
		void	restore();
		bool	iconified() const;
	
		void	hide();
		void	show();
		bool	visible() const;

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
		
		void	setStartCallback(void(*p_startCallback)(dn::Window *));
		void	setUpdateCallback(void(*p_updateCallback)(dn::Window *));
		
		void	setKeyCallback(void(*p_keyCallback)(dn::Window *, int, int));
		void	setSizeCallback(void(*p_sizeCallback)(dn::Window *, int, int));
		void	setPosCallback(void(*p_posCallback)(dn::Window *, int, int));

	private:
		int			_x;
		int			_y;

		int			_width;
		int			_height;

		std::string	_title;

		/* Initialized by dn::Application */
		GLFWwindow	*_glfw;
		int			_windowid;

		int			_flags;

		dn::Color	_clearColor;

		void(*_startCallback)(dn::Window *);
		void(*_updateCallback)(dn::Window *);
		void(*_keyCallback)(dn::Window *, int, int);
		void(*_sizeCallback)(dn::Window *, int, int);
		void(*_posCallback)(dn::Window *, int, int);

		/* The dn::Application class has access to all of the dn::Window attributes. */
		friend class dn::Application;
	};
}

#endif
