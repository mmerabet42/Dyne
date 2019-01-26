#ifndef DN_ENGINE_HPP
# define DN_ENGINE_HPP

# include <map>
# include <vector>
# include <string>

# include "Logger.hpp"

namespace dn
{
	class Scene;
	class Object;

	struct EngineFilterBase
	{
		virtual ~EngineFilterBase() {}

		dn::Object *object() const;

	protected:
		dn::Object *_object;
	};

	template <typename Filter, typename ... Components>
	struct EngineFilter: public dn::EngineFilterBase
	{
		static bool passFilter(dn::Object &p_object);
		static Filter *loadFilter(dn::Object &p_object);
	};

	template <typename Entity_filter>
	using Entities = std::vector<Entity_filter *>;

	template <typename ...>
	class EngineBase;

	template <>
	class EngineBase<>
	{
	public:
		virtual ~EngineBase() = default;

		virtual void loadFilters(dn::Object &p_object);
		virtual void unloadFilter(dn::EngineFilterBase *p_filter);

		virtual void onStart() {}
		virtual void onUpdate() {}

		void setScene(dn::Scene *p_scene);
		dn::Scene *scene() const;

	protected:
		dn::Scene *_scene;
		std::vector<dn::EngineFilterBase *> _allFilters;
		std::map<dn::EngineFilterBase *, size_t> _mapFilters;
		std::map<size_t, std::vector<dn::EngineFilterBase *>> _filters;
	};

	template <typename Filter, typename ... Filters>
	class EngineBase<Filter, Filters ...>: public dn::EngineBase<Filters ...>
	{
	public:
		virtual void loadFilters(dn::Object &p_object);
		virtual void unloadFilter(dn::EngineFilterBase *p_filter);

		virtual void onObjectAdded(Filter &p_filter) {}
		virtual void onObjectRemoved(Filter &p_filter) {}

	};

	template <typename ... Filters>
	class Engine: public dn::EngineBase<Filters ...>
	{
	public:
		Engine();
		virtual ~Engine();

		void loadFilters(dn::Object &p_object) final;

		template <typename Filter>
		void destroyObject(Filter &p_filter);

		template <typename Entity_filter>
		dn::Entities<Entity_filter> &getEntities();

		dn::Entities<dn::EngineFilterBase> &getEntities();

		template <typename Entity_filter>
		Entity_filter *getEntity(dn::EngineFilterBase *p_e);

		template <typename Entity_filter>
		dn::Entities<Entity_filter> &nullEntities();

		template <typename Entity_filter>
		bool isNull(const dn::Entities<Entity_filter> &p_entities);

	private:
		static std::vector<dn::EngineFilterBase *> _nullFilter;
	};
}

# include "EngineFilter.inl"
# include "Engine.inl"

#endif // DN_SYSTEM_HPP
