#include "Component.hpp"
#include "Object.hpp"

dn::ComponentData::ComponentData()
	: _active(true)
{

}

dn::ComponentData::~ComponentData()
{

}

bool dn::ComponentData::active() const
{
	return (this->_active);
}

void dn::ComponentData::setActive(const bool &p_active)
{
	this->_active = p_active;
}
