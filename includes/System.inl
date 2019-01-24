#include "System.hpp"
#include "Object.hpp"
#include <algorithm>

template <typename ... Filters>
dn::System<Filters ...>::System()
{
	static const size_t hashes[] = { typeid(Filters).hash_code() ... };

	for (size_t i = 0; i < sizeof...(Filters); ++i)
		this->_filters.insert(std::make_pair(hashes[i], std::vector<dn::SystemFilterBase *>()));
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
			return ;
		// otherwise a filter is created
		Filter *filter = Filter::loadFilter(p_object);

		// and added to the filter list
		filters.push_back((dn::SystemFilterBase *)filter);
		this->_allFilters.push_back((dn::SystemFilterBase *)filter);
		this->_mapFilters.insert(std::make_pair((dn::SystemFilterBase *)filter, hash_code));
		// and the onObjectAdded callback of the system is called
		this->onObjectAdded(*filter);
	}
	else
	{
		// if it doesn't pass the filter but the object was previously on the system
		// then it is removed
		if (it != filters.end())
		{
			// by first calling the onObjectRemoved callback
			this->onObjectRemoved(*(Filter *)*it);
			// deleting it
			delete (*it);
			// and erasing it from the filter list
			this->_allFilters.erase(std::find(this->_allFilters.begin(), this->_allFilters.end(),
				(dn::SystemFilterBase *)*it));
			this->_mapFilters.erase((dn::SystemFilterBase *)*it);
			filters.erase(it);
		}
	}
	// the object is tested on the other filters
	this->dn::SystemBase<Filters ...>::loadFilters(p_object);
}

template <typename ... Filters>
template <typename Filter>
void dn::System<Filters ...>::destroyObject(Filter &p_filter)
{
	static const size_t hash_code = typeid(Filter).hash_code();

	std::cout << "mdrr\n";
}

template <typename ... Filters>
void dn::System<Filters ...>::loadFilters(dn::Object &p_object)
{
	this->dn::SystemBase<Filters ...>::loadFilters(p_object);
}

template <typename ... Filters>
template <typename Entity_filter>
dn::Entities<Entity_filter> &dn::System<Filters ...>::getEntities()
{
	static const size_t hash_code = typeid(Entity_filter).hash_code();

	std::map<size_t, std::vector<dn::SystemFilterBase *>>::iterator it = this->_filters.find(hash_code);
	if (it == this->_filters.end())
		return (this->nullEntities<Entity_filter>());
	//std::vector<dn::SystemFilterBase *> *arr = &it->second;
	return (*(dn::Entities<Entity_filter> *)&it->second);
}

template <typename ... Filters>
dn::Entities<dn::SystemFilterBase> &dn::System<Filters ...>::getEntities()
{
	return (this->_allFilters);
}

template <typename ... Filters>
template <typename Entity_filter>
Entity_filter *dn::System<Filters ...>::getEntity(dn::SystemFilterBase *p_e)
{
	static const size_t hash_code = typeid(Entity_filter).hash_code();

	std::map<dn::SystemFilterBase *, size_t>::iterator it = this->_mapFilters.find(p_e);
	if (it != this->_mapFilters.end())
		return ((Entity_filter *)p_e);
	return (nullptr);
}

template <typename ... Filters>
template <typename Entity_filter>
dn::Entities<Entity_filter> &dn::System<Filters ...>::nullEntities()
{
	static dn::Entities<Entity_filter> &nullFilter
		= *(dn::Entities<Entity_filter> *)&dn::System<Filters...>::_nullFilter;
	return (nullFilter);
}

template <typename ... Filters>
template <typename Entity_filter>
bool dn::System<Filters ...>::isNull(const dn::Entities<Entity_filter> &p_entities)
{
	return (p_entities.empty());
}

template <typename ... Filters>
std::vector<dn::SystemFilterBase *> dn::System<Filters ...>::_nullFilter
	= std::vector<dn::SystemFilterBase *>();
