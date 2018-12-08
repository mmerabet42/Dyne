#ifndef FUNCS_H
# define FUNCS_H

namespace dn
{
	class Window;
	
	typedef void(*startCallbackFunc)(dn::Window *);
	typedef void(*updateCallbackFunc)(dn::Window *);
	typedef void(*keyCallbackFunc)(dn::Window *, int, int);
	typedef void(*sizeCallbackFunc)(dn::Window *, int, int);
	typedef void(*posCallbackFunc)(dn::Window *, int, int);
	typedef void(*closeCallbackFunc)(dn::Window *);
	typedef void(*focusCallbackFunc)(dn::Window *, int);
}

#endif
