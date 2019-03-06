#ifndef DN_OBJECT_HPP
# define DN_OBJECT_HPP

# include <map>
# include <typeinfo>
# include <string>
# include <type_traits>
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

		bool mustBeUpdated() const;

		dn::Scene *scene() const;
		void setScene(dn::Scene *p_scene);

		void componentUpdated();
		void callUpdateScene();

		// Returns the component of type 'T'
		template <typename T>
		std::enable_if_t<std::is_base_of_v<dn::UComponent, T>, T *>
		/* T* */getComponent();
		template <typename T>
		std::enable_if_t<std::is_base_of_v<dn::Component, T>, T *>
		/* T* */getComponent();


		// Attach a component
		template <typename T, typename ... Args>
		std::enable_if_t<std::is_base_of_v<dn::UComponent, T>, T *>
		/* T* */addComponent(Args && ... p_args);
		template <typename T, typename ... Args>
		std::enable_if_t<std::is_base_of_v<dn::Component, T>, T *>
		/* T* */addComponent(Args && ... p_args);

		// Detach a component
		template <typename T>
		std::enable_if_t<std::is_base_of_v<dn::UComponent, T>, void>
		/* void */removeComponent();
		template <typename T>
		std::enable_if_t<std::is_base_of_v<dn::Component, T>, void>
		/* void */removeComponent();

		dn::UComponent *getHashUComponent(const size_t &p_hash_code);
		dn::Component *getHashDComponent(const size_t &p_hash_code);

	private:
		// Is true if the object has started
		bool _running;
		// An object can be deactivated and activated
		bool _active;
		// if there is at least one updatable component
		bool _mustBeUpdated;
		// The object name
		std::string _name;
		// The list of components attached to the object
		std::map<size_t, dn::UComponent *> _ucomponents;
		std::map<size_t, dn::Component *> _components;

		dn::Scene *_scene;
	};
} // namespace dn

# include "dn/Object.inl"

#endif // DN_OBJECT_HPP
