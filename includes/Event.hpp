#ifndef EVENT_HPP
# define EVENT_HPP

#include <vector>
#include <map>
#include <functional>

namespace dn
{
	// A simple event system
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
		virtual void addListener(const func &p_listener)
		{
			this->_listeners.push_back(p_listener);
		}
		virtual void clearListeners() { this->_listeners.clear(); }

		// Triggers the event, all added listeners are called with the same
		// argument that this function received
		virtual void trigger(_Args ... p_args)
		{
			if (this->_triggered)
				return ;
			this->_triggered = true;
			typename std::vector<func>::iterator it = this->_listeners.begin();
			for (; it != this->_listeners.end() && this->_triggered; ++it)
				(*it)(p_args ...);
			this->_triggered = false;
		}

		// Release the event
		virtual void release() { this->_triggered = false; }
	protected:
		bool _triggered;
		std::vector<func> _listeners;
	};

	template <typename ... _Args>
	dn::Event<_Args ...> &operator<<(
		dn::Event<_Args ...> &p_event,
		const typename dn::Event<_Args ...>::func &p_listener)
	{
		p_event.addListener(p_listener);
	}
	
	template <typename ... _Args>
	void connect(dn::Event<_Args ...> &p_event, const typename dn::Event<_Args ...>::func &p_listener)
	{
		p_event.addListener(p_listener);
	}

	template <typename ... _Args>
	class PriorityEvent : public Event<_Args ...>
	{
	public:
		typedef std::function<void(_Args ...)> func;
		typedef void(*ptrfunc)(_Args ...);
		
		PriorityEvent()
			: Event<_Args ...>() {}
		~PriorityEvent() { this->clearListeners(); }

		virtual void addListener(const func &p_listener)
		{
			this->addListener(0, p_listener);
		}

		virtual void addListener(const int &p_channel, const func &p_listener)
		{
			this->_chanListeners[p_channel].push_back(p_listener);
		}

		virtual void trigger(_Args ... p_args)
		{
			if (this->_triggered)
				return ;
			this->_triggered = true;
			typename std::map<int, std::vector<func>>::iterator it = this->_chanListeners.begin();
			for (; this->_triggered && it != this->_chanListeners.end(); ++it)
			{
				typename std::vector<func>::iterator it2 = it->second.begin();
				for (; this->_triggered && it2 != it->second.end(); ++it2)
					(*it2)(p_args ...);
			}
			this->_triggered = false;
		}

		virtual void release() { this->_triggered = false; }

		virtual void clearListeners()
		{
			typename std::map<int, std::vector<func>>::iterator it = this->_chanListeners.begin();
			for (; this->_triggered && it != this->_chanListeners.end(); ++it)
				it->second.clear();
			this->_chanListeners.clear();
		}

	private:
		std::map<int, std::vector<func>> _chanListeners;
	};

}

#endif
