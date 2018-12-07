#ifndef WINDOW_H
# define WINDOW_H

# include <string>
# include "GLFW/glfw3.h"

# define DN_CLOSED (1 << 0)
# define DN_POS_SPECIFIED (1 << 1)

namespace dn
{
	/* Instead of including Application.h */
	class Application;

	class Window
	{
	public:
		Window(const int &p_width, const int &p_height, const std::string &p_title = "Window");
		Window(const int &p_x, const int &p_y, const int &p_width, const int &p_height, const std::string &p_title = "Window");

		void	Close();

		/* Getters and setters */

			int		width() const;
			void	width(const int &p_width);

			int		height() const;
			void	height(const int &p_height);

			int		x() const;
			void	x(const int &p_x);

			int		y() const;
			void	y(const int &p_y);

			void	SetSize(const int &p_width, const int &p_height);
			void	SetPos(const int &p_x, const int &p_y);

			std::string	title() const;
			void		title(const std::string &p_title);

			int		GetKey(const int &p_keycode) const;

			int		flags() const;

		void	SetKeyCallback(void(*p_keyCallback)(dn::Window *, const int &, const int &));
		void	SetStartCallback(void(*p_startCallback)(dn::Window *));
		void	SetUpdateCallback(void(*p_updateCallback)(dn::Window *));

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
		
		void(*_startCallback)(dn::Window *);
		void(*_updateCallback)(dn::Window *);
		void(*_keyCallback)(dn::Window *, const int &, const int &);

		/* The dn::Application class has access to all of the dn::Window attributes. */
		friend class dn::Application;
	};
}

#endif
