#ifndef DN_OBJECT_INL
# define DN_OBJECT_INL

#include "Object.hpp"

template <typename T>
T *dn::Object::getUComponent()
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
T *dn::Object::getDComponent()
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

template <typename T>
T *dn::Object::getComponent()
{
	if constexpr (std::is_base_of<dn::Component, T>::value)
		return (this->getDComponent<T>());
	else if (std::is_base_of<dn::UComponent, T>::value)
		return (this->getUComponent<T>());
}

// Attach a component
template <typename T, typename ... Args>
T *dn::Object::addUComponent(Args && ... p_args)
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
T *dn::Object::addDComponent(Args && ... p_args)
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

template <typename T, typename ... Args>
T *dn::Object::addComponent(Args && ... p_args)
{
	if constexpr (std::is_base_of<dn::Component, T>::value)
		return (this->addDComponent<T>(std::forward<Args>(p_args)...));
	else if (std::is_base_of<dn::UComponent, T>::value)
		return (this->addUComponent<T>(std::forward<Args>(p_args)...));
}

// Detach a component
template <typename T>
void dn::Object::removeUComponent()
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
void dn::Object::removeDComponent()
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

template <typename T>
void dn::Object::removeComponent()
{
	if constexpr (std::is_base_of<dn::Component, T>::value)
		return (this->removeDComponent<T>());
	else if (std::is_base_of<dn::UComponent, T>::value)
		return (this->removeUComponent<T>());
}

#endif // DN_OBJECT_INL
