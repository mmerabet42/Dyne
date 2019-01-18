#include "System.hpp"
#include "Object.hpp"

template <typename Filter, typename ... Args>
bool dn::SystemFilter<Filter, Args ...>
	::passFilter(dn::Object &p_object)
{
	static size_t hashes[] = { typeid(Args).hash_code()... };

	for (size_t i = 0; i < sizeof...(Args); ++i)
	{
		dn::Component *comp = p_object.getHashComponent(hashes[i]);
		if (!comp || !comp->active())
			return (false);
	}
	return (true);
}

template <typename Filter, typename ... Args>
Filter *dn::SystemFilter<Filter, Args ...>
	::loadFilter(dn::Object &p_object)
{
	// the array of the hash codes of each arguments
	static size_t hashes[] = { typeid(Args).hash_code()... };

	// before trying to load the filter, we must check if the object passes the filter
	if (!Filter::passFilter(p_object))
		return (nullptr);
	// creating a new instance of the filter
	Filter *newFilter = new Filter;

	// point the filter object pointer to the object received in parameter
	newFilter->_object = &p_object;
	dn::Component **components = (dn::Component **)newFilter;
	// jump the virtual function pointer
	++components;
	// jump the _object pointer
	++components;
	// filling out all the memory layouts
	for (size_t i = 0; i < sizeof...(Args); ++i)
		components[i] = p_object.getHashComponent(hashes[i]);
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

template <typename Filter, typename ... Filters>
void dn::System<Filter, Filters ...>::loadFilters(dn::Object &p_object)
{
	static const size_t hashes[] = { typeid(Filter).hash_code(), typeid(Filters).hash_code()... };
	dn::SystemFilterBase *filters[] = { Filter::loadFilter(p_object), Filters::loadFilter(p_object)... };

	for (size_t i = 0; i < sizeof...(Filters) + 1; ++i)
		if (filters[i])
			this->_filters[hashes[i]].push_back(filters[i]);
}

template <typename Filter, typename ... Filters>
template <typename Entity_filter>
dn::Entities<Entity_filter> &dn::System<Filter, Filters ...>::getEntities()
{
	static const size_t hash_code = typeid(Entity_filter).hash_code();

	std::map<size_t, std::vector<dn::SystemFilterBase *>>::iterator it = this->_filters.find(hash_code);
	if (it == this->_filters.end())
	{
	//	throw std::string("NO SUCH FILTERS");
		return (this->nullEntities<Entity_filter>());
	}

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
	return (p_entities.size() == 0);
}

template <typename Filter, typename ... Filters>
std::vector<dn::SystemFilterBase *> dn::System<Filter, Filters ...>::_nullFilter
	= std::vector<dn::SystemFilterBase *>();
/*
std::string dn::ComponentData::name() const
{
	return (this->_name);
}

void dn::ComponentData::setName(const std::string &p_name)
{
	this->_name = p_name;
}

bool dn::ComponentData::active() const
{
	return (this->_active);
}

void dn::ComponentData::setActive(const bool &p_active)
{
	this->_active = p_active;
}*/
