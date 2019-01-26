#include "Window.hpp"
#include "Application.hpp"

/* Constructors */

dn::Window::Window(const int &p_width, const int &p_height, const std::string &p_title, dn::Window *p_share)
	// Initializing the window attributes to default
	: _x(0), _y(0), _width(p_width), _height(p_height), _title(p_title), _glfw(nullptr), _share(p_share),
	_flags(DN_VISIBLE), _clearColor(0.f, 0.f, 0.f, 1.f), _opacity(1.f),
	_framebufferWidth(0), _framebufferHeight(0),
	_minwidth(DN_NONE), _minheight(DN_NONE), _maxwidth(DN_NONE), _maxheight(DN_NONE),
	_mousePos{0.0, 0.0, 0.0, 0.0}, _scene(nullptr),

	// Initializing all function pointer to null
	_keyCb(nullptr), _startCb(nullptr), _updateCb(nullptr), _sizeCb(nullptr),
	_posCb(nullptr), _closeCb(nullptr), _focusCb(nullptr), _maximizeCb(nullptr),
	_refreshCb(nullptr), _mouseButtonCb(nullptr), _mouseMoveCb(nullptr), _mouseEnterCb(nullptr),
	_scrollCb(nullptr), _dropCb(nullptr), _keyPressCb(nullptr), _keyReleaseCb(nullptr),
	_keyRepeatCb(nullptr), _mousePressCb(nullptr), _mouseRepeatCb(nullptr), _mouseReleaseCb(nullptr),

	// Calling the constructor of each event
	startEvent(), updateEvent(), closeEvent(), keyEvent(), sizeEvent(), posEvent(), focusEvent(),
	maximizeEvent(), refreshEvent(), mouseButtonEvent(), mouseMoveEvent(), mouseEnterEvent(),
	scrollEvent(), dropEvent(), keyPressEvent(), keyReleaseEvent(), keyRepeatEvent(),
	mousePressEvent(), mouseReleaseEvent(), mouseRepeatEvent()
{
	// Adding the window to the application.
	this->_windowid = dn::Application::addWindow(this);
}

dn::Window::Window(const int &p_x, const int &p_y, const int &p_width, const int &p_height, const std::string &p_title, dn::Window *p_share)
	: Window(p_width, p_height, p_title, p_share)
{
	this->_x = p_x;
	this->_y = p_y;
	this->_flags |= DN_POS_SPECIFIED;
}

void	dn::Window::clear() const
{
	this->clear(this->_clearColor.r(), this->_clearColor.g(), this->_clearColor.b(), this->_clearColor.a());
}

void	dn::Window::clear(const float &p_r, const float &p_g, const float &p_b, const float &p_a) const
{
	if (this->_glfw)
	{
		glClearColor(p_r, p_g, p_b, p_a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}

void	dn::Window::close()
{
	// Releasing all the events before closing
	this->startEvent.release();
	this->updateEvent.release();
	this->keyEvent.release();
	this->keyPressEvent.release();
	this->keyReleaseEvent.release();
	this->keyRepeatEvent.release();
	this->sizeEvent.release();
	this->posEvent.release();
	this->focusEvent.release();
	this->maximizeEvent.release();
	this->refreshEvent.release();
	this->mouseButtonEvent.release();
	this->mousePressEvent.release();
	this->mouseRepeatEvent.release();
	this->mouseReleaseEvent.release();
	this->mouseMoveEvent.release();
	this->mouseEnterEvent.release();
	this->scrollEvent.release();
	this->dropEvent.release();

	// Enabling the DN_CLOSED flag
	this->_flags |= DN_CLOSED;
	if (this->_glfw)
		glfwSetWindowShouldClose(this->_glfw, true);
	dn::Application::windowCloseCallback(this->_glfw);
}

void	dn::Window::open()
{
	this->_flags &= ~DN_CLOSED;
	if (this->_glfw)
		glfwSetWindowShouldClose(this->_glfw, false);
}

void		dn::Window::iconify()
{
	this->_flags |= DN_ICONIFIED;
	if (this->_glfw)
		glfwIconifyWindow(this->_glfw);
}

void		dn::Window::restore()
{
	this->_flags &= ~DN_ICONIFIED;
	if (this->_glfw)
		glfwRestoreWindow(this->_glfw);
}

bool		dn::Window::isIconified() const { return (this->_flags & DN_ICONIFIED); }
bool		dn::Window::isVisible() const { return (this->_flags & DN_VISIBLE); }

void		dn::Window::hide()
{
	this->_flags &= ~DN_VISIBLE;
	if (this->_glfw)
		glfwHideWindow(this->_glfw);
}

void		dn::Window::show()
{
	this->_flags |= DN_VISIBLE;
	if (this->_glfw)
		glfwShowWindow(this->_glfw);
}

bool		dn::Window::isFocused() const
{
	return (dn::Application::focusedWindow() == this);
}

void		dn::Window::focus()
{
	dn::Application::_focused = this;
	if (this->_glfw)
		glfwFocusWindow(this->_glfw);
}

void dn::Window::setMouseLock(const bool &p_lock)
{
	this->setFlag(DN_MOUSELOCKED, p_lock);
	if (this->_glfw)
	{
		if (p_lock)
			glfwSetInputMode(this->_glfw, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		else
			glfwSetInputMode(this->_glfw, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

bool dn::Window::getKey(const int &p_keycode)
{
	if (this->_keyLogger[p_keycode] == DN_PRESS)
	{
		this->_keyLogger[p_keycode] = DN_REPEAT;
		return (true);
	}
	else if (this->_keyLogger[p_keycode] == DN_REPEAT)
		return (true);
	return (false);
}
bool dn::Window::getKey(const dn::KeyCode &p_keycode)
{
	return (this->getKey((int)p_keycode));
}

bool dn::Window::getKeyDown(const int &p_keycode)
{
	if (this->_keyLogger[p_keycode] == DN_PRESS)
	{
		this->_keyLogger[p_keycode] = DN_REPEAT;
		return (true);
	}
	return (false);
}
bool dn::Window::getKeyDown(const dn::KeyCode &p_keycode)
{
	return (this->getKeyDown((int)p_keycode));
}

bool dn::Window::getKeyUp(const int &p_keycode)
{
	if (this->_keyLogger[p_keycode] == DN_RELEASE)
	{
		this->_keyLogger[p_keycode] = 0;
		return (true);
	}
	return (false);
}
bool dn::Window::getKeyUp(const dn::KeyCode &p_keycode)
{
	return (this->getKeyUp((int)p_keycode));
}

bool dn::Window::getButton(const int &p_button)
{
	if (this->_mouseLogger[p_button] == DN_PRESS)
	{
		this->_mouseLogger[p_button] = DN_REPEAT;
		return (true);
	}
	else if (this->_mouseLogger[p_button] == DN_REPEAT)
		return (true);
	return (false);
}
bool dn::Window::getButton(const dn::MouseButton &p_button)
{
	return (this->getButton((int)p_button));
}

bool dn::Window::getButtonDown(const int &p_button)
{
	if (this->_mouseLogger[p_button] == DN_PRESS)
	{
		this->_mouseLogger[p_button] = DN_REPEAT;
		return (true);
	}
	return (false);
}
bool dn::Window::getButtonDown(const dn::MouseButton &p_button)
{
	return (this->getButtonDown((int)p_button));
}

bool dn::Window::getButtonUp(const int &p_button)
{
	if (this->_mouseLogger[p_button] == DN_RELEASE)
	{
		this->_mouseLogger[p_button] = 0;
		return (true);
	}
	return (false);
}
bool dn::Window::getButtonUp(const dn::MouseButton &p_button)
{
	return (this->getButtonUp((int)p_button));
}

int			dn::Window::flags() const { return (this->_flags); }

void		dn::Window::setFlag(const int &p_flag, const bool &p_set)
{
	if (p_set)
		this->_flags |= p_flag;
	else
		this->_flags &= ~p_flag;
}

bool		dn::Window::getFlag(const int &p_flag) const
{
	return (this->_flags & p_flag);
}

void		dn::Window::setContext()
{
	dn::Application::setContext(this);
}

void		dn::Window::setViewport(const int &p_x, const int &p_y, const int &p_width, const int &p_height)
{
	if (dn::Application::_context != this)
		glfwMakeContextCurrent(this->_glfw);
	glViewport(p_x, p_y, p_width, p_height);
}

void		dn::Window::updateViewport()
{
	if (dn::Application::_context != this)
		glfwMakeContextCurrent(this->_glfw);
	glViewport(0, 0, this->_framebufferWidth, this->_framebufferHeight);
}
