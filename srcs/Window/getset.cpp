#include "Window.hpp"
#include "Application.hpp"
#include "Scene.hpp"

/* Getters and setters */

int		dn::Window::width() const { return (this->_width); }
void	dn::Window::width(const int &p_width)
{
	if (p_width < 0)
		return ;
	this->_width = p_width;
	if (this->_glfw)
		glfwSetWindowSize(this->_glfw, this->_width, this->_height);
}

int		dn::Window::height() const { return (this->_height); }
void	dn::Window::height(const int &p_height)
{
	if (p_height < 0)
		return ;
	this->_height = p_height;
	if (this->_glfw)
		glfwSetWindowSize(this->_glfw, this->_width, this->_height);
}

int		dn::Window::framebufferWidth() const { return (this->_framebufferWidth); }
int		dn::Window::framebufferHeight() const { return (this->_framebufferHeight); }

float	dn::Window::aspectRatio() const
{
	return ((float)this->_framebufferWidth / (float)this->_framebufferHeight);
}

void	dn::Window::setSize(const int &p_width, const int &p_height)
{
	if (p_width < 0 || p_height < 0)
		return ;
	this->_width = p_width;
	this->_height = p_height;
	if (this->_glfw)
		glfwSetWindowSize(this->_glfw, this->_width, this->_height);
}

int		dn::Window::x() const { return (this->_x); }
void	dn::Window::x(const int &p_x)
{
	if (p_x < 0)
		return ;
	this->_x = p_x;
	if (this->_glfw)
		glfwSetWindowPos(this->_glfw, this->_x, this->_y);
	else
		this->_flags |= DN_POS_SPECIFIED;
}

int		dn::Window::y() const { return (this->_y); }
void	dn::Window::y(const int &p_y)
{
	if (p_y < 0)
		return ;
	this->_y = p_y;
	if (this->_glfw)
		glfwSetWindowPos(this->_glfw, this->_x, this->_y);
	else
		this->_flags |= DN_POS_SPECIFIED;
}

void	dn::Window::setPos(const int &p_x, const int &p_y)
{
	if (p_x < 0 || p_y < 0)
		return ;
	this->_x = p_x;
	this->_y = p_y;
	if (this->_glfw)
		glfwSetWindowPos(this->_glfw, this->_x, this->_y);
	else
		this->_flags |= DN_POS_SPECIFIED;
}

double dn::Window::mouseX() const
{
	return (this->_mousePos[0]);
}

double dn::Window::mouseY() const
{
	return (this->_mousePos[1]);
}

double dn::Window::mouseDeltaX()
{
	return (this->_mousePos[2] *= 0.1);
}

double dn::Window::mouseDeltaY()
{
	return (this->_mousePos[3] *= 0.1);
}

std::string	dn::Window::title() const { return (this->_title); }
void		dn::Window::title(const std::string &p_title)
{
	this->_title = p_title;
	if (this->_glfw)
		glfwSetWindowTitle(this->_glfw, this->_title.c_str());
}

dn::Vector4f dn::Window::clearColor() const { return (this->_clearColor); }
void dn::Window::setClearColor(const float &p_r, const float &p_g, const float &p_b)
{
	this->_clearColor.set(p_r, p_g, p_b, 1.f);
}
void		dn::Window::setClearColor(const int &p_r, const int &p_g, const int &p_b)
{
	this->_clearColor.set((float)p_r / 255.f, (float)p_g / 255.f, (float)p_b / 255.f, 1.f);
}

float		dn::Window::opacity() const { return (this->_opacity); }
void		dn::Window::setOpacity(const float &p_opacity)
{
	this->_opacity = p_opacity;
	if (this->_glfw)
		glfwSetWindowOpacity(this->_glfw, this->_opacity);
}

void		dn::Window::setMinLimits(const int &p_width, const int &p_height)
{
	this->_minwidth = p_width;
	this->_minheight = p_height;
	if (this->_glfw)
		glfwSetWindowSizeLimits(this->_glfw, p_width, p_height, this->_maxwidth, this->_maxheight);
}

void		dn::Window::setMaxLimits(const int &p_width, const int &p_height)
{
	this->_maxwidth = p_width;
	this->_maxheight = p_height;
	if (this->_glfw)
		glfwSetWindowSizeLimits(this->_glfw, this->_minwidth, this->_minwidth, p_width, p_height);
}

void		dn::Window::setSizeLimits(const int &p_minwidth, const int &p_maxwidth, const int &p_minheight, const int &p_maxheight)
{
	this->_minwidth = p_minwidth;
	this->_maxwidth = p_maxwidth;
	this->_minheight = p_minheight;
	this->_maxheight = p_maxheight;
	if (this->_glfw)
		glfwSetWindowSizeLimits(this->_glfw, p_minwidth, p_minheight, p_maxwidth, p_maxheight);
}

GLFWwindow	*dn::Window::glfw() const { return (this->_glfw); }

dn::Scene *dn::Window::scene() const
{
	return (this->_scene);
}

void dn::Window::setScene(dn::Scene *p_scene)
{
	if ((this->_scene = p_scene))
		this->_scene->setWindow(this);
}
