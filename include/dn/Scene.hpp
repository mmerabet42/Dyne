#ifndef DN_SCENE_HPP
# define DN_SCENE_HPP

# include <vector>
# include <map>

# include "dn/Engine.hpp"

namespace dn
{
	class Window;
	class Object;

	class Scene
	{
	public:
		Scene();
		~Scene();

		template <typename E, typename ... Args>
		void addEngine(Args && ... p_args);

		void addObject(dn::Object &p_object);

		void start();
		void update();

		void updateEngines(dn::Object *p_object);
		void updateUObject(dn::Object *p_object);

		dn::Window *window() const;
		void setWindow(dn::Window *p_window);

	private:
		// All objects added to the scene
		std::vector<dn::Object *> _objects;
		// All Objects that have at least one 'UComponent', they need to be updated
		// like engines
		std::vector<dn::Object *> _uobjects;

		// All engines added to the scene
		std::map<size_t, dn::EngineBase<> *> _engines;
		// Engines that can receive callbacks (like mouse pressed, moved etc.)
//		std::vector<dn::CallbackReceiver *> _callbackReceivers;

		// The window to which the scene is connected to
		dn::Window *_window;

		bool _started;
	};
}

# include "dn/Scene.inl"

#endif // DN_SCENE_HPP
