#ifndef COMPONENT_H
# define COMPONENT_H

# include <string>

namespace dn
{
	// Forward declaration of the Object class
	class Object;

	class Component
	{
	public:
		Component(dn::Object *p_object = nullptr, const std::string &p_name = "");

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
}
#include <iostream>
class SimpleComp: public dn::Component
{
public:
	void start()
	{
		std::cout << "Starting component" << std::endl;
	}

	void update()
	{
		std::cout << "Updating component" << std::endl;
	}
};

#endif // COMPONENT_H
