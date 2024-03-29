#ifndef DN_COMPONENT_HPP
# define DN_COMPONENT_HPP

# include <string>

namespace dn
{
	class Object;

	class UComponent
	{
	public:
		UComponent(const std::string &p_name = "");
		virtual ~UComponent();

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
	private:
		// The object in which the component is attached to
		dn::Object *_object;
		// Maybe useless, but a component can have a name
		std::string _name;
		// A component can be deactivated and activated,
		// making the call of the update and start functions possible or not
		bool _active;
	};

	class Component
	{
	public:
		Component();
		virtual ~Component();

		bool active() const;
		void setActive(const bool &p_active = true);

		dn::Object *object() const;
		void setObject(dn::Object *p_object);

	private:
		// A component can be deactivated and activated
		bool _active;
		// The object it is attached to
		dn::Object *_object;
	};
}

#endif // DN_COMPONENT_HPP
