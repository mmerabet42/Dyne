#include "dn/Engine.hpp"
#include "dn/Object.hpp"

dn::Object *dn::EngineFilterBase::object() const
{
	return (this->_object);
}

void dn::EngineBase<>::loadFilters(dn::Object &p_object)
{
	(void)p_object;
}

void dn::EngineBase<>::unloadFilter(dn::EngineFilterBase *p_filter)
{
	(void)p_filter;
}

void dn::EngineBase<>::setScene(dn::Scene *p_scene)
{
	this->_scene = p_scene;
}

dn::Scene *dn::EngineBase<>::scene() const
{
	return (this->_scene);
}
