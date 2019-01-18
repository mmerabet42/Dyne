#include "System.hpp"
#include "Object.hpp"

template <typename Filter, typename ... Args>
bool dn::loadFilter(dn::SystemFilter<Filter, Args ...> &p_filter, dn::Object &p_object)
{
	static size_t hashes[] = { typeid(Args).hash_code()... };
	static dn::Component *ptrs[sizeof...(Args)] = { nullptr };

	for (size_t i = 0; i < sizeof...(Args); ++i)
	{
		ptrs[i] = p_object.getHashComponent(hashes[i]);
		if (!ptrs[i])
			return (false);
	}

	dn::Component **components = (dn::Component **)&p_filter;
	++components;
	p_filter._object = &p_object;
	for (size_t i = 0; i < sizeof...(Args); ++i)
		components[i] = ptrs[i];
	return (true);
}

template <typename Filter, typename ... Args>
dn::Object *dn::SystemFilter<Filter, Args ...>::object() const
{
	return (this->_object);
}

template <typename ... Filters>
dn::System<Filters ...>::System()
{
	static const size_t hashes[] = { typeid(Filters).hash_code() ... };

	for (size_t i = 0; i < sizeof...(Filters); ++i)
		this->_filters.insert(std::make_pair(hashes[i], std::vector<dn::SystemFilterBase *>()));
}

template <typename ... Filters>
bool dn::System<Filters ...>::passFilters(dn::Object &p_object)
{
	
}

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
