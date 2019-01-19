#ifndef RENDERSYSTEM_HPP
# define RENDERSYSTEM_HPP

# include "System.hpp"

namespace dn
{
	struct MeshFilter: public dn::SystemFilter<dn::MeshFilter, dn::TransformData>
	{
		dn::TransformData *transform;
	};

	class RenderSystem: public dn::System<dn::MeshFilter>
	{
	public:

		void onObjectAdded(dn::MeshFilter &p_filter)
		{

		}
	};
}

#endif
