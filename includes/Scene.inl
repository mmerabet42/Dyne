#include "Scene.hpp"

template <typename S>
void dn::Scene::addSystem()
{
	static const size_t hash_code = typeid(S).hash_code();

	std::map<size_t, dn::SystemBase<> *>::iterator it = this->_systems.find(hash_code);
	if (it != this->_systems.end())
		return ;
	static_assert(std::is_base_of<dn::SystemBase<>, S>::value,
		"S must be a system deriving the dn::System<...> class");
	S *system = new S();
	system->setScene(this);
	this->_systems.insert(std::make_pair(hash_code, system));
	if (this->_started)
		system->onStart();
	// each object must be sent to the system
	for (size_t i = 0; i < this->_objects.size(); ++i)
		system->loadFilters(*this->_objects[i]);
}
