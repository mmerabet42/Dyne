#ifndef FUNCS_H
# define FUNCS_H

# include <functional>

namespace dn
{
	class Window;
	
	typedef std::function<void(dn::Window *)>						startFunc;
	typedef std::function<void(dn::Window *)>						updateFunc;
	typedef std::function<void(dn::Window *, int, int, int)>		keyFunc;
	typedef std::function<void(dn::Window *, int, int)>				sizeFunc;
	typedef std::function<void(dn::Window *, int, int)>				posFunc;
	typedef std::function<void(dn::Window *)>						closeFunc;
	typedef std::function<void(dn::Window *, bool)>					focusFunc;
	typedef std::function<void(dn::Window *, bool)>					maximizeFunc;
	typedef std::function<void(dn::Window *, int, int)>				framebufferSizeFunc;
	typedef std::function<void(dn::Window *)>						refreshFunc;
	typedef std::function<void(dn::Window *, int, int, int)>		mouseButtonFunc;
	typedef std::function<void(dn::Window *, double, double)>		mouseMoveFunc;
	typedef std::function<void(dn::Window *, bool)>					mouseEnterFunc;
	typedef std::function<void(dn::Window *, double, double)>		scrollFunc;
	typedef std::function<void(dn::Window *, int, const char **)>	dropFunc;
}

#endif
