#ifndef SYSTEM_HPP
# define SYSTEM_HPP

# include <map>
# include <vector>
# include <string>

# include "Logger.hpp"

namespace dn
{
	class Scene;
	class Object;

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
	class SystemBase;

	template <>
	class SystemBase<>
	{
	public:

		virtual void loadFilters(dn::Object &p_object);

		virtual void onStart() {}
		virtual void onUpdate() {}

		void setScene(dn::Scene *p_scene);
		dn::Scene *scene() const;

	protected:
		dn::Scene *_scene;
		std::vector<dn::SystemFilterBase *> _allFilters;
		std::map<dn::SystemFilterBase *, size_t> _mapFilters;
		std::map<size_t, std::vector<dn::SystemFilterBase *>> _filters;
	};

	template <typename Filter, typename ... Filters>
	class SystemBase<Filter, Filters ...>: public dn::SystemBase<Filters ...>
	{
	public:
		virtual void loadFilters(dn::Object &p_object);

		virtual void onObjectAdded(Filter &p_filter) {}
		virtual void onObjectRemoved(Filter &p_filter) {}
	};

	template <typename Filter, typename ... Filters>
	class System: public dn::SystemBase<Filter, Filters ...>
	{
	public:
		System();

		bool passFilters(dn::Object &p_object);
		void loadFilters(dn::Object &p_object) final;

		template <typename Entity_filter>
		dn::Entities<Entity_filter> &getEntities();

		dn::Entities<dn::SystemFilterBase> &getEntities();

		template <typename Entity_filter>
		Entity_filter *getEntity(dn::SystemFilterBase *p_e);

		template <typename Entity_filter>
		dn::Entities<Entity_filter> &nullEntities();

		template <typename Entity_filter>
		bool isNull(const dn::Entities<Entity_filter> &p_entities);

	private:
		static std::vector<dn::SystemFilterBase *> _nullFilter;
	};
}

# include "SystemFilter.inl"
# include "System.inl"

#endif // SYSTEM_HPP
