#ifndef DN_CALLBACKRECEIVER_HPP
# define DN_CALLBACKRECEIVER_HPP

# include "dn/KeyCode.hpp"
# include "dn/Window.hpp"

namespace dn
{
	class CallbackReceiver
	{
	public:
		virtual void onKey				(dn::Window &, dn::KeyCode, dn::Action, dn::Mod) {}
		virtual void onKeyPress			(dn::Window &, dn::KeyCode, dn::Mod) {}
		virtual void onKeyRelease		(dn::Window &, dn::KeyCode, dn::Mod) {}
		virtual void onKeyRepeat		(dn::Window &, dn::KeyCode, dn::Mod) {}
		virtual void onMouseButton		(dn::Window &, dn::MouseButton, dn::Action, dn::Mod) {}
		virtual void onMousePress		(dn::Window &, dn::MouseButton, dn::Mod) {}
		virtual void onMouseRelease		(dn::Window &, dn::MouseButton, dn::Mod) {}
		virtual void onMouseRepeat		(dn::Window &, dn::MouseButton, dn::Mod) {}

		virtual void onSize				(dn::Window &, int, int) {}
		virtual void onPos				(dn::Window &, int, int) {}
		virtual void onFocus			(dn::Window &, bool) {}
		virtual void onMaximize			(dn::Window &, bool) {}
		virtual void onFrameBufferSize	(dn::Window &, int, int) {}
		virtual void onRefresh			(dn::Window &) {}
		virtual void onMouseMove		(dn::Window &, double double) {}
		virtual void onMouseEnter		(dn::Window &, bool) {}
		virtual void onScroll			(dn::Window &, double, double) {}

	private:
		
	};
}

#endif // DN_CALLBACKRECEIVER_HPP
