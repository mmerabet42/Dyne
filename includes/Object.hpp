#ifndef OBJECT_HPP
# define OBJECT_HPP

# include <map>
# include <typeinfo>
# include <string>
# include "Component.hpp"

namespace dn
{
	class Scene;

	// An object is a component container
	class Object
	{
	public:
		Object(const std::string &p_name = "");
		virtual ~Object();

		// Starting an object means starting each component attached to the object
		void start();
		// Updating an object means updating each component attached to the object
		void update();

		std::string name() const;
		void setName(const std::string &p_name);

		bool active() const;
		void setActive(const bool &p_active = true);

		dn::Scene *scene() const;
		void setScene(dn::Scene *p_scene);

		void componentUpdated();

		// Returns the component that is of the specified type `T'
		template <typename T>
		T *getComponent();
		template <typename T>
		T *getComponentData();

		// Attach a component
		template <typename T, typename ... _Args>
		T *addComponent(_Args ... p_args);
		template <typename T, typename ... _Args>
		T *addComponentData(_Args ... p_args);

		// Detach a component
		template <typename T>
		void removeComponent();
		template <typename T>
		void removeComponentData();

		dn::Component *getHashComponent(const size_t &p_hash_code);
		dn::ComponentData *getHashComponentData(const size_t &p_hash_code);

	private:
		// Is true if the object has started
		bool _running;
		// An object can be deactivated and activated
		bool _active;
		// The object name
		std::string _name;
		// The list of components attached to the object
		std::map<size_t, dn::Component *> _components;
		std::map<size_t, dn::ComponentData *> _componentsData;

		dn::Scene *_scene;
	};
}

# include "Object.inl"

#endif // OBJECT_HPP
