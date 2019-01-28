#ifndef DN_SCENE_INL
# define DN_SCENE_INL

#include "dn/Scene.hpp"

template <typename E, typename ... Args>
void dn::Scene::addEngine(Args && ... p_args)
{
	static const size_t hash_code = typeid(E).hash_code();

	static_assert(std::is_base_of<dn::EngineBase<>, E>::value,
		"The engine must inherit from the dn::Engine class");
	std::map<size_t, dn::EngineBase<> *>::iterator it = this->_engines.find(hash_code);
	if (it != this->_engines.end())
		return ;
	E *engine = new E(std::forward<Args>(p_args) ...);
	engine->setScene(this);
	this->_engines.emplace(hash_code, engine);
	if (this->_started)
		engine->onStart();
	// each object must be sent to the system
	for (size_t i = 0; i < this->_objects.size(); ++i)
		engine->loadFilters(*this->_objects[i]);
}

#endif // DN_SCENE_INL
