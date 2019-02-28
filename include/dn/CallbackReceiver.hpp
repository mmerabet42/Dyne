#ifndef DN_CALLBACKRECEIVER_HPP
# define DN_CALLBACKRECEIVER_HPP

# include "KeyCode.hpp"

namespace dn
{
	class CallbackReceiver
	{
		virtual void onKeyPress(dn::KeyCode p_key, dn::Mod p_mod) {}
	};
}

#endif // DN_CALLBACKRECEIVER_HPP
