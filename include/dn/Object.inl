#ifndef DN_OBJECT_INL
# define DN_OBJECT_INL

#include "dn/Object.hpp"

template <typename T>
std::enable_if_t<std::is_base_of_v<dn::UComponent, T>, T *>
/* T* */dn::Object::getComponent()
{
	// Get the hash value of the given type
	static const size_t comp_hash = typeid(T).hash_code();

	// Checks if the hash value is in the map
	std::map<size_t, dn::UComponent *>::iterator it = this->_ucomponents.find(comp_hash);
	if (it != this->_ucomponents.end())
		// If it is return the component by casting it to the specified type
		return (dynamic_cast<T *>(it->second));
	// Otherwise return a null pointer
	return (nullptr);
}

template <typename T>
std::enable_if_t<std::is_base_of_v<dn::Component, T>, T *>
/* T* */dn::Object::getComponent()
{
	// Get the hash value of the given type
	static const size_t comp_hash = typeid(T).hash_code();

	// Checks if the hash value is in the map
	std::map<size_t, dn::Component *>::iterator it = this->_components.find(comp_hash);
	if (it != this->_components.end())
		// If it is return the component by casting it to the specified type
		return (dynamic_cast<T *>(it->second));
	// Otherwise return a null pointer
	return (nullptr);
}

// Attach a component
template <typename T, typename ... Args>
std::enable_if_t<std::is_base_of_v<dn::UComponent, T>, T *>
/* T* */dn::Object::addComponent(Args && ... p_args)
{
	// Get the hash value of `T'
	static const size_t comp_hash = typeid(T).hash_code();

	// If a component of the same type is already attached to the object, it is returned
	std::map<size_t, dn::UComponent *>::iterator it = this->_ucomponents.find(comp_hash);
	if (it != this->_ucomponents.end())
		return (dynamic_cast<T *>(it->second));
	// Create an instanciation of the component, with the given arguments
	T *comp = new T(std::forward<Args>(p_args) ...);
	// Attach the component to the object
	this->_ucomponents.emplace(comp_hash, comp);
	comp->setObject(this);
	if (!this->_mustBeUpdated && this->_scene)
		this->callUpdateScene();
	this->_mustBeUpdated = true;
	// If the object has already started, the start function of the component is called
	if (this->_running)
		comp->start();
	// And finally, the component is returned
	return (comp);
}

template <typename T, typename ... Args>
std::enable_if_t<std::is_base_of_v<dn::Component, T>, T *>
/* T* */dn::Object::addComponent(Args && ... p_args)
{
	// Get the hash value of `T'
	static const size_t comp_hash = typeid(T).hash_code();

	// If a component of the same type is already attached to the object, it is returned
	std::map<size_t, dn::Component *>::iterator it = this->_components.find(comp_hash);
	if (it != this->_components.end())
		return (dynamic_cast<T *>(it->second));
	// Create an instanciation of the component, with the given arguments
	T *comp = new T(std::forward<Args>(p_args) ...);
	// Attach the component to the object
	this->_components.emplace(comp_hash, comp);
	comp->setObject(this);
	this->componentUpdated();
	// And finally, the component is returned
	return (comp);
}

// Detach a component
template <typename T>
std::enable_if_t<std::is_base_of_v<dn::UComponent, T>, void>
/* void */dn::Object::removeComponent()
{
	static const size_t comp_hash = typeid(T).hash_code();

	std::map<size_t, dn::UComponent *>::iterator it = this->_ucomponents.find(comp_hash);
	if (it != this->_ucomponents.end())
	{
		delete it->second;
		this->_ucomponents.erase(it);
		if (this->_ucomponents.size() == 0)
		{
			this->_mustBeUpdated = false;
			if (this->_scene)
				this->callUpdateScene();
		}
	}
}

template <typename T>
std::enable_if_t<std::is_base_of_v<dn::Component, T>, void>
/* void */dn::Object::removeComponent()
{
	static const size_t comp_hash = typeid(T).hash_code();

	std::map<size_t, dn::Component *>::iterator it = this->_components.find(comp_hash);
	if (it != this->_components.end())
	{
		delete it->second;
		this->_components.erase(it);
		this->componentUpdated();
	}
}

#endif // DN_OBJECT_INL
