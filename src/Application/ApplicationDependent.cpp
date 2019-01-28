#include "dn/ApplicationDependent.hpp"

dn::ApplicationDependent::ApplicationDependent()
	: _destroyed(false), _created(false) {}
dn::ApplicationDependent::~ApplicationDependent() {}

void dn::ApplicationDependent::create() {}
void dn::ApplicationDependent::destroy() {}

bool dn::ApplicationDependent::created() const
{
	return (this->_created);
}

bool dn::ApplicationDependent::destroyed() const
{
	return (this->_destroyed);
}
