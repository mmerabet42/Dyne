#include "System.hpp"
#include "Object.hpp"

dn::Object *dn::SystemFilterBase::object() const
{
	return (this->_object);
}

void dn::SystemBase<>::loadFilters(dn::Object &p_object)
{
	(void)p_object;
}

void dn::SystemBase<>::unloadFilter(dn::SystemFilterBase *p_filter)
{
	(void)p_filter;
}

void dn::SystemBase<>::setScene(dn::Scene *p_scene)
{
	this->_scene = p_scene;
}

dn::Scene *dn::SystemBase<>::scene() const
{
	return (this->_scene);
}
