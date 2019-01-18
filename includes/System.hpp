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

	struct SystemFilterBase
	{
		virtual ~SystemFilterBase() {}

		dn::Object *object() const;

	protected:
		dn::Object *_object;
	};

	template <typename Filter, typename ... Args>
	struct SystemFilter: public dn::SystemFilterBase
	{
		virtual ~SystemFilter() {}

		static bool passFilter(dn::Object &p_object);
		static Filter *loadFilter(dn::Object &p_object);
	};

	template <typename Entity_filter>
	using Entities = std::vector<Entity_filter *>;

	template <typename Filter, typename ... Filters>
	class System
	{
	public:
		System();

		bool passFilters(dn::Object &p_object);
		void loadFilters(dn::Object &p_object);

		template <typename Entity_filter>
		dn::Entities<Entity_filter> &getEntities();

		template <typename Entity_filter>
		dn::Entities<Entity_filter> &nullEntities();

		template <typename Entity_filter>
		bool isNull(const dn::Entities<Entity_filter> &p_entities);

	protected:
		std::map<size_t, std::vector<dn::SystemFilterBase *>> _filters;
		static std::vector<dn::SystemFilterBase *> _nullFilter;
	};
}

# include "System.inl"

#endif // SYSTEM_HPP
