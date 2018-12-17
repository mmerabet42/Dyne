#include "Model.hpp"
#include "Math.hpp"

dn::Model::Model(const dn::VertexArray &p_vertices, const GLenum &p_method, const dn::IndiceArray &p_indices)
	: _vertices(p_vertices), _method(p_method), _indices(p_indices)
{

}

dn::Model::~Model()
{
	this->_vertices.clear();
	this->_indices.clear();
}

dn::VertexArray dn::Model::vertices() const { return (this->_vertices); }
dn::IndiceArray dn::Model::indices() const { return (this->_indices); }

void dn::Model::setIndices(const dn::IndiceArray &p_indices)
{
	this->_indices = p_indices;
}

GLenum dn::Model::method() const { return (this->_method); }
void dn::Model::setMethod(const GLenum &p_method)
{
	this->_method = p_method;
}


size_t dn::Model::verticesSize() const { return (sizeof(dn::Vertex) * this->_vertices.size()); }
size_t dn::Model::indicesSize() const { return (sizeof(GLuint) * this->_indices.size()); }

const void *dn::Model::verticesData() const { return ((const void *)this->_vertices.data()); }
const void *dn::Model::indicesData() const { return ((const void *)this->_indices.data()); }

dn::Model dn::Model::generatePoints(const int &p_n, const float &p_radius)
{
	dn::VertexArray vertices;
	dn::IndiceArray indices;

	for (int i = 0; i < p_n; ++i)
	{
		vertices.push_back(dn::Vertex
			{{
				dn::math::random(-p_radius, p_radius),
				dn::math::random(-p_radius, p_radius),
				dn::math::random(-p_radius, p_radius),
			}, {1.f, 1.f, 1.f, 1.f}});
		indices.push_back((GLuint)i);
	}
	return (dn::Model(vertices, DN_POINTS, indices));
}
