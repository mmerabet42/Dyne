#ifndef EVENT_H
# define EVENT_H

#include <vector>
#include <functional>

namespace dn
{
	// A simple event system for the window class to handle the callbacks differently
	template <typename ... _Args>
	class Event
	{
	public:
		typedef std::function<void(_Args ...)> func;
		typedef void(*ptrfunc)(_Args ...);

		Event()
			: _triggered(false) {}
		~Event() { this->clearListeners(); }

		// Listeners are called in the same order they were added
		void addListener(const func &p_listener)
		{
			this->_listeners.push_back(p_listener);
		}
		void clearListeners() { this->_listeners.clear(); }

		// Triggers the event, all added listeners are called with the same
		// argument that this function received
		void trigger(_Args ... p_args)
		{
			this->_triggered = true;
			for (typename std::vector<func>::iterator it = this->_listeners.begin(); it != this->_listeners.end() && this->_triggered; ++it)
				(*it)(p_args ...);
		}
		// Untrigger the event
		void release() { this->_triggered = false; }
	protected:
		bool _triggered;
		std::vector<func> _listeners;
	};

	template <typename ... _Args>
	void connect(dn::Event<_Args ...> &p_event, const typename dn::Event<_Args ...>::func &p_listener)
	{
		p_event.addListener(p_listener);
	}
}

#endif
