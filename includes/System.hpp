#ifndef SYSTEM_HPP
# define SYSTEM_HPP

namespace dn
{
	template <typename Filter, typename ... Args>
	struct SystemFilter {};

	template <typename Filter, typename ... Args>
	bool loadFilter(dn::SystemFilter<Filter, Args ...> &p_filter, const dn::Object &p_object);

	template <typename ... Filters>
	class System
	{
	public:

	protected:
		
	};
}

# include "System.inl"

#endif // SYSTEM_HPP
