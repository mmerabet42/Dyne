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

dn::Object *dn::SystemFilterBase::object() const
{
	return (this->_object);
}

template <typename Filter, typename ... Filters>
dn::System<Filter, Filters ...>::System()
{
	static const size_t hashes[] = { typeid(Filter).hash_code(), typeid(Filters).hash_code() ... };

	for (size_t i = 0; i < sizeof...(Filters) + 1; ++i)
		this->_filters.insert(std::make_pair(hashes[i], std::vector<dn::SystemFilterBase *>()));
}

template <typename Filter, typename ... Filters>
bool dn::System<Filter, Filters ...>::passFilters(dn::Object &p_object)
{
	bool passes[] = { Filter::passFilter(p_object), Filters::passFilter(p_object)... };
	for (size_t i = 0; i < sizeof...(Filters) + 1; ++i)
		if (passes[i])
			return (true);
	return (false);
}

void dn::SystemOverloader<>::loadFilters(dn::Object &p_object)
{
	(void)p_object;
}

template <typename Filter, typename ... Filters>
void dn::SystemOverloader<Filter, Filters ...>::loadFilters(dn::Object &p_object)
{
	static const size_t hash_code = typeid(Filter).hash_code();

	Filter *filter = Filter::loadFilter(p_object);
	if (filter)
	{
		this->_filters[hash_code].push_back((dn::SystemFilterBase *)filter);
		this->onObjectAdded(*filter);
	}
	this->dn::SystemOverloader<Filters ...>::loadFilters(p_object);
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
