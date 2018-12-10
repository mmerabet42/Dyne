#ifndef FUNCS_H
# define FUNCS_H

# include <functional>

namespace dn
{
	class Window;
	
	typedef std::function<void(dn::Window *)>				startFunc;
	typedef std::function<void(dn::Window *)>				updateFunc;
	typedef std::function<void(dn::Window *, int, int)>		keyFunc;
	typedef std::function<void(dn::Window *, int, int)>		sizeFunc;
	typedef std::function<void(dn::Window *, int, int)>		posFunc;
	typedef std::function<void(dn::Window *)>				closeFunc;
	typedef std::function<void(dn::Window *, int)>			focusFunc;
	typedef std::function<void(dn::Window *, int)>			maximizeFunc;
	typedef std::function<void(dn::Window *, int, int)>		framebufferSizeFunc;
}

#endif
