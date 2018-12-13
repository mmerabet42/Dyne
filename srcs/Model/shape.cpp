#include "Shape.h"

dn::Shape::Shape(const dn::VertexArray &p_vertices, const dn::IndiceArray &p_indices)
	: _vertices(p_vertices), _indices(p_indices)
{

}

dn::Shape::~Shape()
{
	this->_vertices.clear();
	this->_indices.clear();
}

dn::VertexArray dn::Shape::vertices() const { return (this->_vertices); }
dn::IndiceArray dn::Shape::indices() const { return (this->_indices); }

void dn::Shape::setIndices(const dn::IndiceArray &p_indices)
{
	this->_indices = p_indices;
}

size_t dn::Shape::verticesSize() const { return (sizeof(dn::Vertex) * this->_vertices.size()); }
size_t dn::Shape::indicesSize() const { return (sizeof(GLuint) * this->_indices.size()); }

const void *dn::Shape::verticesData() const { return ((const void *)this->_vertices.data()); }
const void *dn::Shape::indicesData() const { return ((const void *)this->_indices.data()); }
