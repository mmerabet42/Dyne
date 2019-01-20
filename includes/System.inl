#include "System.hpp"
#include "Object.hpp"
#include <algorithm>

template <typename Filter, typename ... Filters>
dn::System<Filter, Filters ...>::System()
{
	static const size_t hashes[] = { typeid(Filter).hash_code(), typeid(Filters).hash_code() ... };

	for (size_t i = 0; i < sizeof...(Filters) + 1; ++i)
		this->_filters.insert(std::make_pair(hashes[i], std::vector<dn::SystemFilterBase *>()));
}
/*
void dn::SystemBase<>::setScene(dn::Scene *p_scene)
{
	this->_scene = p_scene;
}

dn::Scene *dn::SystemBase<>::scene() const
{
	return (this->_scene);
}
*/
template <typename Filter, typename ... Filters>
bool dn::System<Filter, Filters ...>::passFilters(dn::Object &p_object)
{
	bool passes[] = { Filter::passFilter(p_object), Filters::passFilter(p_object)... };
	for (size_t i = 0; i < sizeof...(Filters) + 1; ++i)
		if (passes[i])
			return (true);
	return (false);
}

template <typename Filter, typename ... Filters>
void dn::SystemBase<Filter, Filters ...>::loadFilters(dn::Object &p_object)
{
	// getting the hash code of the type 'Filter'
	static const size_t hash_code = typeid(Filter).hash_code();

	// testing if the object passes the filter
	bool passFilter = Filter::passFilter(p_object);

	// the 'loadFilters' function can be used to load a filter or update a filter
	// if the object is present in the filter list and if the object passes the filter
	// then nothing happens, otherwise if the object doesn't pass filter but
	// is present in the filter list, that mean that a component has been removed
	// so the filter is unloaded from the filter list and from the system completely
	std::vector<dn::SystemFilterBase *> &filters = this->_filters[hash_code];
	auto it = std::find_if(filters.begin(), filters.end(),
		[&p_object](dn::SystemFilterBase *p_f) {
			return (p_f->object() == &p_object);
	});
	// if the object passes the filter
	if (passFilter)
	{
		// if the object is present in the filter list, then nothing happens
		if (it != filters.end())
		{
			dn::log(p_object.name(), " passes the filter", dn::endl);
			return ;
		}
		// otherwise a filter is created
		Filter *filter = Filter::loadFilter(p_object);

		// and added to the filter list
		filters.push_back((dn::SystemFilterBase *)filter);
		// and the onObjectAdded callback of the system is called
		this->onObjectAdded(*filter);
	}
	else
	{
		dn::log(p_object.name(), " doesn't pass the filter !!", dn::endl);
		// if it doesn't pass the filter but the object was previously on the system
		// then it is removed
		if (it != filters.end())
		{
			// by first call the onObjectRemoved callback
			this->onObjectRemoved(*(Filter *)*it);
			// deleting it
			delete (*it);
			// and erasing it from the filter list
			filters.erase(it);
		}
	}
	// the object is tested on the other filters
	this->dn::SystemBase<Filters ...>::loadFilters(p_object);
}

template <typename Filter, typename ... Filters>
void dn::System<Filter, Filters ...>::loadFilters(dn::Object &p_object)
{
	this->dn::SystemBase<Filter, Filters ...>::loadFilters(p_object);
}

template <typename Filter, typename ... Filters>
template <typename Entity_filter>
dn::Entities<Entity_filter> &dn::System<Filter, Filters ...>::getEntities()
{
	static const size_t hash_code = typeid(Entity_filter).hash_code();

	std::map<size_t, std::vector<dn::SystemFilterBase *>>::iterator it = this->_filters.find(hash_code);
	if (it == this->_filters.end())
		return (this->nullEntities<Entity_filter>());
	std::vector<dn::SystemFilterBase *> *arr = &it->second;
	return (*(dn::Entities<Entity_filter> *)arr);
}

template <typename Filter, typename ... Filters>
template <typename Entity_filter>
dn::Entities<Entity_filter> &dn::System<Filter, Filters ...>::nullEntities()
{
	static dn::Entities<Entity_filter> &nullFilter
		= *(dn::Entities<Entity_filter> *)&dn::System<Filter, Filters...>::_nullFilter;
	return (nullFilter);
}

template <typename Filter, typename ... Filters>
template <typename Entity_filter>
bool dn::System<Filter, Filters ...>::isNull(const dn::Entities<Entity_filter> &p_entities)
{
	return (p_entities.empty());
}

template <typename Filter, typename ... Filters>
std::vector<dn::SystemFilterBase *> dn::System<Filter, Filters ...>::_nullFilter
	= std::vector<dn::SystemFilterBase *>();
