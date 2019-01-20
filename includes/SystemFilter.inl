#include "System.hpp"
#include "Object.hpp"

template <typename Filter, typename ... Components>
bool dn::SystemFilter<Filter, Components ...>
	::passFilter(dn::Object &p_object)
{
	static const size_t hashes[] = { typeid(Components).hash_code()... };

	for (size_t i = 0; i < sizeof...(Components); ++i)
	{
		dn::ComponentData *comp = p_object.getHashComponentData(hashes[i]);
		if (!comp || !comp->active())
			return (false);
	}
	return (true);
}

template <typename Filter, typename ... Components>
Filter *dn::SystemFilter<Filter, Components ...>
	::loadFilter(dn::Object &p_object)
{
	// the array of the hash codes of each arguments
	static const size_t hashes[] = { typeid(Components).hash_code()... };

	// before trying to load the filter, we must check if the object passes the filter
	if (!Filter::passFilter(p_object))
		return (nullptr);
	// creating a new instance of the filter
	Filter *newFilter = new Filter;

	// point the filter object pointer to the object received in parameter
	newFilter->_object = &p_object;
	dn::ComponentData **components = (dn::ComponentData **)newFilter;
	// jump vtbl (virtual function pointers)
	++components;
	// jump the _object pointer
	++components;
	// filling out all the memory layouts
	for (size_t i = 0; i < sizeof...(Components); ++i)
		components[i] = p_object.getHashComponentData(hashes[i]);
	return (newFilter);
}
/*
dn::Object *dn::SystemFilterBase::object() const
{
	return (this->_object);
}*/
