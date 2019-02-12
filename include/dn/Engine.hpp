#ifndef DN_ENGINE_HPP
# define DN_ENGINE_HPP

# include <map>
# include <vector>
# include <string>

# include "dn/Logger.hpp"

namespace dn
{
	// Forward declaring the Scene class, because Engines needs a pointer to the
	// scene they are connected to
	class Scene;
	// Engine filters needs a pointer to the object they are connected to
	class Object;

	// Needed to represent all filters
	struct EngineFilterBase
	{
		virtual ~EngineFilterBase() {}

		dn::Object *object() const;

	protected:
		dn::Object *_object;
	};

	// Custom filters must inherit this class.
	// The first template argument is the inheriting class, it might seem unusual
	// but it is necessary for it to work (to fill the datas)
	// The following template arguments are the components that should have the object
	// in order to pass the filter
	template <typename Filter, typename ... Components>
	struct EngineFilter: public dn::EngineFilterBase
	{
		static bool passFilter(dn::Object &p_object);
		static Filter *loadFilter(dn::Object &p_object);
	};

	// A default filter which accepts any objects
	struct BasicFilter: public dn::EngineFilter<dn::BasicFilter> {};

	// A more usual way to get the entities: dn::Entities<Filter> e
	// instead of: std::vector<Filter *> e
	template <typename EntityFilter>
	using Entities = std::vector<EntityFilter *>;

	class Window;

	// Complicated to explain
	template <typename ...>
	class EngineBase;

	// But necessary for having generic engines
	template <>
	class EngineBase<>
	{
	public:
		virtual ~EngineBase() = default;

		virtual void loadFilters(dn::Object &p_object);
		virtual void unloadFilter(dn::EngineFilterBase *p_filter);

		virtual void onStart() {}
		virtual void onUpdate() {}

		virtual void onWindowLink(dn::Window &p_window) {}
		virtual void onWindowUnlink(dn::Window &p_window) {}

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

	// Custom classes must inherit this class in order to be added to scenes
	// and apply behaviour
	template <typename ... Filters>
	class Engine: public dn::EngineBase<Filters ...>
	{
	public:
		Engine();
		virtual ~Engine();

		template <typename Entity_filter>
		dn::Entities<Entity_filter> &getEntities();

		dn::Entities<dn::EngineFilterBase> &getEntities();

		template <typename Entity_filter>
		Entity_filter *getEntity(dn::EngineFilterBase *p_e);

		template <typename Entity_filter>
		dn::Entities<Entity_filter> &nullEntities();

		void loadFilters(dn::Object &p_object) final;

		template <typename Filter>
		void destroyObject(Filter &p_filter);

		template <typename Entity_filter>
		bool isNull(const dn::Entities<Entity_filter> &p_entities);

	private:
		static std::vector<dn::EngineFilterBase *> _nullFilter;
	};
}

# include "dn/EngineFilter.inl"
# include "dn/Engine.inl"

#endif // DN_SYSTEM_HPP
