#ifndef FUNCS_H
# define FUNCS_H

namespace dn
{
	class Window;
	
	typedef void(*startCbFunc)(dn::Window *);
	typedef void(*updateCbFunc)(dn::Window *);
	typedef void(*keyCbFunc)(dn::Window *, int, int);
	typedef void(*sizeCbFunc)(dn::Window *, int, int);
	typedef void(*posCbFunc)(dn::Window *, int, int);
	typedef void(*closeCbFunc)(dn::Window *);
	typedef void(*focusCbFunc)(dn::Window *, int);
}

#endif
