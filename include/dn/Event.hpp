#ifndef DN_EVENT_HPP
# define DN_EVENT_HPP

#include <vector>
#include <map>
#include <functional>

namespace dn
{
	// A simple event system
	template <typename ... Args>
	class Event
	{
	public:
		typedef std::function<void(Args ...)> func;
		typedef void(*ptrfunc)(Args ...);

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
		virtual void trigger(Args ... p_args)
		{
			if (this->_triggered)
				return ;
			this->_triggered = true;
			for (auto &&i_listener : this->_listeners)
				i_listener(std::forward<Args>(p_args) ...);
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
		return (p_event);
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
			for (auto &&i_channel : this->_chanListeners)
			{
				for (auto &&i_listener : i_channel.second)
				{
					if (!this->_triggered)
						return ;
					i_listener(p_args ...);
				}
			}
			this->_triggered = false;
		}

		virtual void release() { this->_triggered = false; }

		virtual void clearListeners()
		{
			for (auto &&i_channel : this->_chanListeners)
				i_channel.second.clear();
			this->_chanListeners.clear();
		}

	private:
		std::map<int, std::vector<func>> _chanListeners;
	};

}

#endif // DN_EVENT_HPP
