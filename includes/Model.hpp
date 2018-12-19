#ifndef MODEL_HPP
# define MODEL_HPP

# include <vector>
# include "Vertex.hpp"
# include "Codes.hpp"

namespace dn
{
	typedef std::vector<dn::Vertex> VertexArray;
	typedef std::vector<GLuint> IndiceArray;

	class Model
	{
	public:
		Model(const dn::VertexArray &p_vertices, const GLenum &p_method = DN_TRIANGLES, const dn::IndiceArray &p_indices = {});
		~Model();

		dn::VertexArray vertices() const;
		dn::IndiceArray indices() const;
		void setIndices(const dn::IndiceArray &p_indices);

		GLenum method() const;
		void setMethod(const GLenum &p_method);

		size_t verticesSize() const;
		size_t indicesSize() const;

		const void *verticesData() const;
		const void *indicesData() const;

		static dn::Model cube;
		static dn::Model cubeEdges;

		static dn::Model generatePoints(const int &p_n, const float &p_radius);
	private:

		dn::VertexArray _vertices;
		dn::IndiceArray _indices;
		GLenum _method;
	};
}

#endif //MODEL_HPP
