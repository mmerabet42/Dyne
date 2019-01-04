#ifndef APPLICATIONDEPENDENT_HPP
# define APPLICATIONDEPENDENT_HPP

namespace dn
{
	// Forward declaration of the Application class to avoid including its header file
	class Application;

	// Every thing that depends on the application state inherits this class.
	// When i say it depends on the application i mean that it must be created only once
	// the application has run and destroyed once the application has done or if
	// destroyed manually. They are commonly known as ressources.

	class ApplicationDependent
	{
	public:
		ApplicationDependent();
		virtual ~ApplicationDependent();

		// called once the application has run
		virtual void create();
		// called once the application has done 'running' or if the instance is destroyed
		virtual void destroy();

		bool destroyed() const;
		bool created() const;

	private:
		bool _destroyed;
		bool _created;

		// the Application class is the only one to have access to the private members
		// of this class
		friend class dn::Application;
	};
}

#endif // APPLICATIONDEPENDENT_HPP
