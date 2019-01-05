#ifndef COMPONENT_HPP
# define COMPONENT_HPP

# include <string>

namespace dn
{
	class Object;

	class Component
	{
	public:
		Component(const std::string &p_name = "", dn::Object *p_object = nullptr);
		Component(dn::Object *p_object, const std::string &p_name = "");
		virtual ~Component();

		dn::Object *object() const;
		void setObject(dn::Object *p_object);

		std::string name() const;
		void setName(const std::string &p_name);

		bool active() const;
		void setActive(const bool &p_active = true);

		// Pure virtual function which makes the class abstract and not instanciable
		// Indeed, the component class must be inherited in order to be used and
		// attached to objects

		// The start function is called when the object starts, or directly if
		// the object has already started
		virtual void start() = 0;
		// The update function is called everytimes the object, it is attached to, is updated
		virtual void update() = 0;
/*
		// Managing components on the attached object can be done directly from a component
		template <typename T>
		T *getComponent()
		{
			if (!this->_object)
				return (nullptr);
			return (this->_object->getComponent<T>());
		}

		template <typename T, typename ... _Args>
		T *addComponent(_Args ... p_args)
		{
			if (!this->_object)
				return (nullptr);
			return (this->_object->addComponent<T>(p_args ...));
		}

		template <typename T>
		void removeComponent()
		{
			if (!this->_object)
				return ;
			this->_object->removeComponent<T>();
		}*/
	private:
		// The object in which the component is attached to
		dn::Object *_object;
		// Maybe useless, but a component can have a name
		std::string _name;
		// A component can be deactivated and activated,
		// making the call of the update and start functions possible or not
		bool _active;
	};
}

#endif // COMPONENT_HPP
