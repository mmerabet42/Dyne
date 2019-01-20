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
			std::cout << "Mesh filter added !!!" << p_filter.object()->name() << std::endl;
		}

		void onObjectRemoved(dn::MeshFilter &p_filter)
		{
			std::cout << "Mesh filter removed !!!" << p_filter.object()->name() << std::endl;
		}

		void onStart()
		{
			std::cout << "Render system started !!\n";
		}

		void onUpdate()
		{
			std::cout << "Render system updated !!\n";
		}
	};
}

#endif
