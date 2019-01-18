#ifndef SYSTEM_HPP
# define SYSTEM_HPP

# include <map>
# include <vector>
# include <string>

namespace dn
{
	/*struct ComponentData
	{
		std::string name() const;
		void setName(const std::string &p_name);

		bool active() const;
		void setActive(const bool &p_active);

	private:
		std::string _name;
		bool _active;
	};*/

	struct SystemFilterBase {};

	template <typename Filter, typename ... Args>
	struct SystemFilter: public dn::SystemFilterBase
	{
		dn::Object *object() const;

	private:
		dn::Object *_object;
	
		template <typename Filter_fr, typename ... Args_fr>
		friend bool loadFilter(dn::SystemFilter<Filter_fr, Args_fr ...> &p_filter, dn::Object &p_object);
	};

	template <typename Filter, typename ... Args>
	bool loadFilter(dn::SystemFilter<Filter, Args ...> &p_filter, dn::Object &p_object);

	template <typename ... Filters>
	class System
	{
	public:
		System();

		

	protected:
		std::map<size_t, std::vector<dn::SystemFilterBase *>> _filters;
	};
}

# include "System.inl"

#endif // SYSTEM_HPP
