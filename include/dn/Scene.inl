#ifndef DN_SCENE_INL
# define DN_SCENE_INL

#include "dn/Scene.hpp"

template <typename E, typename ... Args>
std::enable_if_t<std::is_base_of_v<dn::EngineBase<>, E>>
/* void */dn::Scene::addEngine(Args && ... p_args)
{
	static const size_t hash_code = typeid(E).hash_code();

	std::map<size_t, dn::EngineBase<> *>::iterator it = this->_engines.find(hash_code);
	if (it != this->_engines.end())
		return ;
	E *engine = new E(std::forward<Args>(p_args) ...);
	engine->setScene(this);
	this->_engines.emplace(hash_code, engine);
	if constexpr (std::is_base_of_v<dn::CallbackReceiver, E>)
		this->_callbackReceivers.emplace_back(dynamic_cast<dn::CallbackReceiver *>(engine));
	if (this->_started)
		engine->onStart();
	// each object already added to the scene must loaded into the engine
	// to see if they pass the filters
	for (size_t i = 0; i < this->_objects.size(); ++i)
		engine->loadFilters(*this->_objects[i]);
}

#endif // DN_SCENE_INL
