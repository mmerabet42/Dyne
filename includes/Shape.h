#ifndef SHAPE_H
# define SHAPE_H

# include <vector>
# include "Vertex.h"
# include "Codes.h"

namespace dn
{
	typedef std::vector<dn::Vertex> VertexArray;
	typedef std::vector<GLuint> IndiceArray;

	class Shape
	{
	public:
		Shape(const dn::VertexArray &p_vertices, const GLenum &p_method = DN_TRIANGLES, const dn::IndiceArray &p_indices = {});
		~Shape();

		dn::VertexArray vertices() const;
		dn::IndiceArray indices() const;
		void setIndices(const dn::IndiceArray &p_indices);

		GLenum method() const;
		void setMethod(const GLenum &p_method);

		size_t verticesSize() const;
		size_t indicesSize() const;

		const void *verticesData() const;
		const void *indicesData() const;
	private:

		dn::VertexArray _vertices;
		dn::IndiceArray _indices;
		GLenum _method;
	};
}

#endif //SHAPE_H
