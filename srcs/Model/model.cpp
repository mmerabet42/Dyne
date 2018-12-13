#include "Model.h"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/transform.hpp"
#include "glm/gtx/quaternion.hpp"

dn::Model::Model(const dn::Shape &p_shape, dn::Shader *p_shader)
	: _shape(p_shape), _shader(p_shader), _vao(0), _vbos{0,0}, _parent(nullptr),
	_position(0.f, 0.f, 0.f), _rotation(0.f, 0.f, 0.f), _scale(1.f, 1.f, 1.f),

	_positionMod(true), _rotationMod(true), _scaleMod(true)
{
	
}

dn::Model::~Model()
{
	glDeleteVertexArrays(1, &this->_vao);
	glDeleteBuffers(2, this->_vbos);
}

const dn::Shape &dn::Model::shape() const { return (this->_shape); }
const dn::Shader *dn::Model::shader() const { return (this->_shader); }

void dn::Model::setShape(const dn::Shape &p_shape) { this->_shape = p_shape; }
void dn::Model::setShader(dn::Shader *p_shader) { this->_shader = p_shader; }

glm::vec3 dn::Model::position() const { return (this->_position); }
glm::vec3 dn::Model::rotation() const { return (this->_rotation); }
glm::vec3 dn::Model::scale() const { return (this->_scale); }

glm::vec3 &dn::Model::position()
{
	this->_positionMod = true;
	return (this->_position);
}
glm::vec3 &dn::Model::rotation()
{
	this->_rotationMod = true;
	return (this->_rotation);
}
glm::vec3 &dn::Model::scale()
{
	this->_scaleMod = true;
	return (this->_scale);
}

dn::Model *dn::Model::parent() const { return (this->_parent); }
void dn::Model::setParent(dn::Model *p_parent)
{
	this->_parent = (p_parent == this ? nullptr : p_parent);
}
const glm::mat4 &dn::Model::transform()
{
	if (!this->change())
		return (this->_transform);
	this->_change = true;
	if (this->_positionMod)
	{
		this->_positionMod = false;
		this->_positionMat = glm::translate(this->_position);
	}
	if (this->_rotationMod)
	{
		this->_rotationMod = false;
		this->_rotationMat = glm::toMat4(glm::quat(this->_rotation));
	}
	if (this->_scaleMod)
	{
		this->_scaleMod = false;
		this->_scaleMat = glm::scale(this->_scale);
	}
	if (!this->_parent)
		return (this->_transform = this->_positionMat * this->_rotationMat * this->_scaleMat);
	return (this->_transform = this->_parent->transform() * this->_positionMat * this->_rotationMat * this->_scaleMat);
}

void dn::Model::create()
{
	if (!this->_shader)
		return ;
	this->_shader->compile();

	glGenVertexArrays(1, &this->_vao);
	glBindVertexArray(this->_vao);
	
	glGenBuffers(2, this->_vbos);

	glBindBuffer(GL_ARRAY_BUFFER, this->_vbos[0]);
	glBufferData(GL_ARRAY_BUFFER, this->_shape.verticesSize(), this->_shape.verticesData(), GL_STATIC_DRAW);

	GLuint positionAttrib = this->_shader->getAttrib("position");
	GLuint colorAttrib = this->_shader->getAttrib("color");

	glEnableVertexAttribArray(positionAttrib);
	glVertexAttribPointer(positionAttrib, 3, GL_FLOAT, false, sizeof(dn::Vertex), nullptr);
	glEnableVertexAttribArray(colorAttrib);
	glVertexAttribPointer(colorAttrib, 4, GL_FLOAT, false, sizeof(dn::Vertex), (void *)sizeof(dn::Vertex::position));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_vbos[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->_shape.indicesSize(), this->_shape.indicesData(), GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void dn::Model::draw(const GLenum &p_mode)
{
	this->_change = false;
	if (!this->_vao)
		return ;
	this->_shader->use();
	
	GLint transformUni = this->_shader->getUniform("transform");
	glUniformMatrix4fv(transformUni, 1, GL_FALSE, &this->transform()[0][0]);
	
	glBindVertexArray(this->_vao);
	glDrawElements(p_mode, this->_shape.indices().size(), GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
	this->_shader->use(false);
}

bool dn::Model::change() const
{
	return (this->_positionMod || this->_rotationMod || this->_scaleMod || (this->_parent && this->_parent->_change));
}
