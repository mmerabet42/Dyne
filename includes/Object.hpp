#ifndef OBJECT_HPP
# define OBJECT_HPP

# include <map>
# include <typeinfo>
# include <string>
# include "Component.hpp"

namespace dn
{
	// Forward declaration of the Component class, so no need to include the component header file

	// An object is a component container
	class Object
	{
	public:
		Object(const std::string &p_name = "");
		virtual ~Object();

		// Starting an object means starting each component attached to the object
		void start();
		// Updating an object means updating each component attached to the object
		void update();

		std::string name() const;
		void setName(const std::string &p_name);

		bool active() const;
		void setActive(const bool &p_active = true);

		// Template functions must be declared in the header file

		// Returns the component that is of the specified type `T'
		template <typename T>
		T *getComponent()
		{
			// Get the hash value of the given type
			size_t comp_hash = typeid(T).hash_code();
			// Checks if the hash value is in the map
			std::map<size_t, dn::Component *>::iterator it = this->_components.find(comp_hash);
			if (it != this->_components.end())
				// If it is return the component by casting it to the specified type
				return (dynamic_cast<T *>(it->second));
			// Otherwise return a null pointer
			return (nullptr);
		}

		// Attach a component
		template <typename T, typename ... _Args>
		T *addComponent(_Args ... p_args)
		{
			// Checks if the type is deriving the Component class
			static_assert(std::is_base_of<dn::Component, T>::value,
				"Only classes that inherits dn::Component can be attached to objects");
			// Get the hash value of `T'
			size_t comp_hash = typeid(T).hash_code();
			// If a component of the same type is already attached to the object, it is returned
			std::map<size_t, dn::Component *>::iterator it = this->_components.find(comp_hash);
			if (it != this->_components.end())
				return (dynamic_cast<T *>(it->second));
			// Create an instanciation of the component, with the given arguments
			T *comp = new T(p_args ...);
			// Attach the component to the object
			this->_components.insert(std::make_pair(comp_hash, comp));
			comp->setObject(this);
			// If the object has already started, the start function of the component is called
			if (this->_running)
				comp->start();
			// And finally, the component is returned
			return (comp);
		}

		// Detach a component
		template <typename T>
		void removeComponent()
		{
			size_t comp_hash = typeid(T).hash_code();
			std::map<size_t, dn::Component *>::iterator it = this->_components.find(comp_hash);
			if (it != this->_components.end())
			{
				delete it->second;
				this->_components.erase(it);
			}
		}

	private:
		// Is true if the object has started
		bool _running;
		// An object can be deactivated and activated
		bool _active;
		// The object name
		std::string _name;
		// The list of components attached to the object
		std::map<size_t, dn::Component *> _components;
	};
}

#endif // OBJECT_HPP
