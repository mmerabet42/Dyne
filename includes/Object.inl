#ifndef OBJECT_INL
# define OBJECT_INL

#include "Object.hpp"

template <typename T>
T *dn::Object::getComponent()
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
T *dn::Object::getComponentData()
{
	// Get the hash value of the given type
	static const size_t comp_hash = typeid(T).hash_code();

	// Checks if the hash value is in the map
	std::map<size_t, dn::ComponentData *>::iterator it = this->_componentsData.find(comp_hash);
	if (it != this->_componentsData.end())
		// If it is return the component by casting it to the specified type
		return (dynamic_cast<T *>(it->second));
	// Otherwise return a null pointer
	return (nullptr);
}
/*
dn::Component *dn::Object::getHashComponent(const size_t &p_hash_code)
{
	std::map<size_t, dn::Component *>::iterator it = this->_components.find(p_hash_code);
	if (it != this->_components.end())
		return (it->second);
	return (nullptr);
}

dn::ComponentData *dn::Object::getHashComponentData(const size_t &p_hash_code)
{
	std::map<size_t, dn::ComponentData *>::iterator it = this->_componentsData.find(p_hash_code);
	if (it != this->_componentsData.end())
		return (it->second);
	return (nullptr);
}
*/
// Attach a component
template <typename T, typename ... _Args>
T *dn::Object::addComponent(_Args ... p_args)
{
	// Get the hash value of `T'
	static const size_t comp_hash = typeid(T).hash_code();

	// Checks if the type is deriving the Component class
	static_assert(std::is_base_of<dn::Component, T>::value,
		"Only classes that inherits dn::Component can be attached to objects");
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

template <typename T, typename ... _Args>
T *dn::Object::addComponentData(_Args ... p_args)
{
	// Get the hash value of `T'
	static const size_t comp_hash = typeid(T).hash_code();

	// Checks if the type is deriving the Component class
	static_assert(std::is_base_of<dn::ComponentData, T>::value,
		"Only classes that inherits dn::Component can be attached to objects");
	// If a component of the same type is already attached to the object, it is returned
	std::map<size_t, dn::ComponentData *>::iterator it = this->_componentsData.find(comp_hash);
	if (it != this->_componentsData.end())
		return (dynamic_cast<T *>(it->second));
	// Create an instanciation of the component, with the given arguments
	T *comp = new T(p_args ...);
	// Attach the component to the object
	this->_componentsData.insert(std::make_pair(comp_hash, comp));
	// And finally, the component is returned
	return (comp);
}

// Detach a component
template <typename T>
void dn::Object::removeComponent()
{
	static const size_t comp_hash = typeid(T).hash_code();

	std::map<size_t, dn::Component *>::iterator it = this->_components.find(comp_hash);
	if (it != this->_components.end())
	{
		delete it->second;
		this->_components.erase(it);
	}
}

template <typename T>
void dn::Object::removeComponentData()
{
	static const size_t comp_hash = typeid(T).hash_code();

	std::map<size_t, dn::ComponentData *>::iterator it = this->_componentsData.find(comp_hash);
	if (it != this->_componentsData.end())
	{
		delete it->second;
		this->_componentsData.erase(it);
	}
}

#endif // OBJECT_INL
