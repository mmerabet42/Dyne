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

	GLint viewProjectionUni = this->_shader->getUniform("viewProjection");
	glUniformMatrix4fv(viewProjectionUni, 1, GL_FALSE, &dn::Model::camViewProjection()[0][0]);

	glBindVertexArray(this->_vao);
	if (p_mode == -1)
		glDrawElements(this->_shape.method(), this->_shape.indices().size(), GL_UNSIGNED_INT, nullptr);
	else
		glDrawElements(p_mode, this->_shape.indices().size(), GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
	this->_shader->use(false);
}

bool dn::Model::change() const
{
	return (this->_positionMod || this->_rotationMod || this->_scaleMod || (this->_parent && this->_parent->_change));
}

const float &dn::Model::camFov() { return (dn::Model::_fov); }
void dn::Model::setCamFov(const float &p_fov)
{
	dn::Model::_projectionMod = true;
	dn::Model::_fov = p_fov;
}

const float &dn::Model::camFar() { return (dn::Model::_far); }
void dn::Model::setCamFar(const float &p_far)
{
	dn::Model::_projectionMod = true;
	dn::Model::_far = p_far;
}

const float &dn::Model::camNear() { return (dn::Model::_near); }
void dn::Model::setCamNear(const float &p_near)
{
	dn::Model::_projectionMod = true;
	dn::Model::_near = p_near;
}

const float &dn::Model::camAspectRatio() { return (dn::Model::_aspectRatio); }
void dn::Model::setCamAspectRatio(const float &p_aspectRatio)
{
	dn::Model::_projectionMod = true;
	dn::Model::_aspectRatio = p_aspectRatio;
}

const glm::vec3 &dn::Model::camPosition() { return (dn::Model::_camPosition); }
glm::vec3 &dn::Model::camPositionc()
{
	dn::Model::_viewMod = true;
	return (dn::Model::_camPosition);
}

const glm::vec3 &dn::Model::camRotation() { return (dn::Model::_camRotation); }
glm::vec3 &dn::Model::camRotationc()
{
	dn::Model::_viewMod = true;
	return (dn::Model::_camRotation);
}

glm::vec3 dn::Model::camForward()
{
	return (glm::toMat4(glm::quat(dn::Model::_camRotation)) * glm::vec4(0.f, 0.f, -1.f, 0.f));
}

glm::vec3 dn::Model::camUp()
{
	return (glm::toMat4(glm::quat(dn::Model::_camRotation)) * glm::vec4(0.f, 1.f, 0.f, 0.f));
}

const glm::mat4 &dn::Model::camViewProjection()
{
	dn::Model::_projectionMat = glm::perspective(
		dn::Model::_fov,
		dn::Model::_aspectRatio,
		dn::Model::_near,
		dn::Model::_far);

	dn::Model::_viewMat = glm::lookAt(
		dn::Model::_camPosition,
		dn::Model::_camPosition + dn::Model::camForward(),
		dn::Model::camUp()
	);

	return (dn::Model::_viewprojMat = dn::Model::_projectionMat * dn::Model::_viewMat);
}

glm::vec3	dn::Model::_camPosition(0.f, 0.f, 2.f);
glm::vec3	dn::Model::_camRotation(0.f, 0.f, 0.f);
glm::mat4	dn::Model::_viewMat;
glm::mat4	dn::Model::_projectionMat;
glm::mat4	dn::Model::_viewprojMat;

float		dn::Model::_fov(70.f);
float		dn::Model::_far(100.f);
float		dn::Model::_near(0.2f);
float		dn::Model::_aspectRatio(1.f);

bool		dn::Model::_viewMod(true);
bool		dn::Model::_projectionMod(true);

