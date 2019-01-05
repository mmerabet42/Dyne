#ifndef FUNCS_HPP
# define FUNCS_HPP

# include <functional>
# include <vector>
# include "KeyCode.hpp"

namespace dn
{
	class Window;
	
	typedef std::function<void(dn::Window &)>						startFunc;
	typedef std::function<void(dn::Window &)>						updateFunc;
	typedef std::function<void(dn::Window &, dn::KeyCode, dn::Action, dn::Mod)>		keyFunc;
	typedef std::function<void(dn::Window &, int, int)>				sizeFunc;
	typedef std::function<void(dn::Window &, int, int)>				posFunc;
	typedef std::function<void(dn::Window &)>						closeFunc;
	typedef std::function<void(dn::Window &, bool)>					focusFunc;
	typedef std::function<void(dn::Window &, bool)>					maximizeFunc;
	typedef std::function<void(dn::Window &, int, int)>				framebufferSizeFunc;
	typedef std::function<void(dn::Window &)>						refreshFunc;
	typedef std::function<void(dn::Window &, dn::MouseButton, dn::Action, dn::Mod)>		mouseButtonFunc;
	typedef std::function<void(dn::Window &, double, double)>		mouseMoveFunc;
	typedef std::function<void(dn::Window &, bool)>					mouseEnterFunc;
	typedef std::function<void(dn::Window &, double, double)>		scrollFunc;
	typedef std::function<void(dn::Window &, const std::vector<std::string> &)>	dropFunc;
}

#endif
