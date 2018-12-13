#ifndef SHAPE_H
# define SHAPE_H

# include <vector>
# include "Vertex.h"

namespace dn
{
	typedef std::vector<dn::Vertex> VertexArray;
	typedef std::vector<GLuint> IndiceArray;

	class Shape
	{
	public:
		Shape(const dn::VertexArray &p_vertices, const dn::IndiceArray &p_indices = {});
		~Shape();

		dn::VertexArray vertices() const;
		dn::IndiceArray indices() const;
		void setIndices(const dn::IndiceArray &p_indices);

		size_t verticesSize() const;
		size_t indicesSize() const;

		const void *verticesData() const;
		const void *indicesData() const;
	private:

		dn::VertexArray _vertices;
		dn::IndiceArray _indices;
	};
}

#endif //SHAPE_H
