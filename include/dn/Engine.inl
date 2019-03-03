#ifndef DN_ENGINE_INL
# define DN_ENGINE_INL

#include "dn/Engine.hpp"
#include "dn/Object.hpp"
#include <algorithm>

template <typename ... Filters>
dn::Engine<Filters ...>::Engine()
{
	static const size_t hashes[] = { typeid(Filters).hash_code() ... };

	for (size_t i = 0; i < sizeof...(Filters); ++i)
		this->_filters.emplace(hashes[i], std::vector<dn::EngineFilterBase *>());
}

template <typename ... Filters>
dn::Engine<Filters ...>::~Engine()
{
	this->_filters.clear();
	this->_mapFilters.clear();
	for (size_t i = 0; i < this->_allFilters.size(); ++i)
		delete (this->_allFilters[i]);
}

template <typename Filter, typename ... Filters>
void dn::EngineBase<Filter, Filters ...>::loadFilters(dn::Object &p_object)
{
	// getting the hash code of the type 'Filter'
	static const size_t hash_code = typeid(Filter).hash_code();

	// testing if the object passes the filter
	bool passFilter = Filter::passFilter(p_object);

	// the 'loadFilters' function can be used to load a filter or update a filter
	// if the object is present in the filter list and if the object passes the filter
	// then nothing happens, otherwise if the object doesn't pass filter but
	// is present in the filter list, that means that a component has been removed
	// so the filter is unloaded from the filter list and from the engine completely
	std::vector<dn::EngineFilterBase *> &filters = this->_filters[hash_code];
	auto it = std::find_if(filters.begin(), filters.end(),
		[&p_object](dn::EngineFilterBase *p_f) {
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
		filters.emplace_back((dn::EngineFilterBase *)filter);
		this->_allFilters.emplace_back((dn::EngineFilterBase *)filter);
		this->_mapFilters.emplace((dn::EngineFilterBase *)filter, hash_code);
		// and the onObjectAdded callback of the engine is called
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
				(dn::EngineFilterBase *)*it));
			this->_mapFilters.erase((dn::EngineFilterBase *)*it);
			filters.erase(it);
		}
	}
	// the object is tested on the other filters
	this->dn::EngineBase<Filters ...>::loadFilters(p_object);
}

template <typename Filter, typename ... Filters>
void dn::EngineBase<Filter, Filters ...>::unloadFilter(dn::EngineFilterBase *p_filter)
{
	static const size_t hash_code1 = typeid(Filter).hash_code();

	std::vector<dn::EngineFilterBase *> filters = this->_filters[hash_code1];
	auto it = std::find(filters.begin(), filters.end(), (dn::EngineFilterBase *)&p_filter);
	if (it == filters.end())
	{
		this->dn::EngineBase<Filters ...>::unloadFilter(p_filter);
		return ;
	}
	this->onObjectRemoved(*(Filter *)p_filter);
	delete (*it);
	this->_allFilters.erase(std::find(this->_allFilters.begin(), this->_allFilters.end(),
		(dn::EngineFilterBase *)*it));
	this->_mapFilters.erase((dn::EngineFilterBase *)*it);
	filters.erase(it);
}

template <typename ... Filters>
template <typename Filter>
void dn::Engine<Filters ...>::destroyObject(Filter &p_filter)
{
//	std::cout << "unloading filter: " << p_filter.object()->name() << std::endl;
	this->dn::EngineBase<Filters ...>::unloadFilter((dn::EngineFilterBase *)&p_filter);
}

template <typename ... Filters>
void dn::Engine<Filters ...>::loadFilters(dn::Object &p_object)
{
	this->dn::EngineBase<Filters ...>::loadFilters(p_object);
}

template <typename ... Filters>
template <typename Entity_filter>
dn::Entities<Entity_filter> &dn::Engine<Filters ...>::getEntities()
{
	static const size_t hash_code = typeid(Entity_filter).hash_code();

	std::map<size_t, std::vector<dn::EngineFilterBase *>>::iterator it = this->_filters.find(hash_code);
	if (it == this->_filters.end())
		return (this->nullEntities<Entity_filter>());
	//std::vector<dn::SystemFilterBase *> *arr = &it->second;
	return (*(dn::Entities<Entity_filter> *)&it->second);
}

template <typename ... Filters>
dn::Entities<dn::EngineFilterBase> &dn::Engine<Filters ...>::getEntities()
{
	return (this->_allFilters);
}

template <typename ... Filters>
template <typename Entity_filter>
Entity_filter *dn::Engine<Filters ...>::getEntity(dn::EngineFilterBase *p_e)
{
	static const size_t hash_code = typeid(Entity_filter).hash_code();

	std::map<dn::EngineFilterBase *, size_t>::iterator it = this->_mapFilters.find(p_e);
	if (it != this->_mapFilters.end())
		return ((Entity_filter *)p_e);
	return (nullptr);
}

template <typename ... Filters>
template <typename Entity_filter>
dn::Entities<Entity_filter> &dn::Engine<Filters ...>::nullEntities()
{
	static dn::Entities<Entity_filter> &nullFilter
		= *(dn::Entities<Entity_filter> *)&dn::Engine<Filters...>::_nullFilter;
	return (nullFilter);
}

template <typename ... Filters>
template <typename Entity_filter>
bool dn::Engine<Filters ...>::isNull(const dn::Entities<Entity_filter> &p_entities)
{
	return (p_entities.empty());
}

template <typename ... Filters>
std::vector<dn::EngineFilterBase *> dn::Engine<Filters ...>::_nullFilter
	= std::vector<dn::EngineFilterBase *>();

#endif // DN_ENGINE_INL
