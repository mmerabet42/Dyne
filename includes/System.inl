#include "System.hpp"
#include "Object.hpp"

template <typename Filter, typename ... Args>
bool dn::loadFilter(dn::SystemFilter<Filter, Args ...> &p_filter, const dn::Object &p_object)
{
	static size_t hashes[] = { typeid(Args).hash_code()... };
	static dn::Component *ptrs[sizeof...(Args)] = { nullptr };

	for (size_t i = 0; i < sizeof...(Args); ++i)
	{
		ptrs[i] = p_object.getHashComponent(hashes[i]);
		if (!ptrs[i])
			return (false);
	}

	dn::Component **components = (dn::Component **)&p_filter;
	for (size_t i = 0; i < sizeof...(Args); ++i)
		components[i] = ptrs[i];
	return (true);
}
