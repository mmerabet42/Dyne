#ifndef SYSTEM_HPP
# define SYSTEM_HPP

# include <map>
# include <vector>
# include <string>

namespace dn
{
	struct SystemFilterBase
	{
		virtual ~SystemFilterBase() {}

		dn::Object *object() const;

	protected:
		dn::Object *_object;
	};

	template <typename Filter, typename ... Components>
	struct SystemFilter: public dn::SystemFilterBase
	{
		static bool passFilter(dn::Object &p_object);
		static Filter *loadFilter(dn::Object &p_object);
	};

	template <typename Entity_filter>
	using Entities = std::vector<Entity_filter *>;

	template <typename ...>
	class SystemOverloader;

	template <>
	class SystemOverloader<>
	{
	public:
		virtual void loadFilters(dn::Object &p_object);
	protected:
		std::map<size_t, std::vector<dn::SystemFilterBase *>> _filters;
	};

	template <typename Filter, typename ... Filters>
	class SystemOverloader<Filter, Filters ...>: public dn::SystemOverloader<Filters ...>
	{
	public:
		virtual void loadFilters(dn::Object &p_object);
		virtual void onObjectAdded(Filter &p_filter) {}
	};

	template <typename Filter, typename ... Filters>
	class System: public dn::SystemOverloader<Filter, Filters ...>
	{
	public:
		System();

		bool passFilters(dn::Object &p_object);

		template <typename Entity_filter>
		dn::Entities<Entity_filter> &getEntities();

		template <typename Entity_filter>
		dn::Entities<Entity_filter> &nullEntities();

		template <typename Entity_filter>
		bool isNull(const dn::Entities<Entity_filter> &p_entities);

		virtual void onStart() {}
		virtual void onUpdate() {}

	private:
		static std::vector<dn::SystemFilterBase *> _nullFilter;
	};
}

# include "System.inl"

#endif // SYSTEM_HPP
