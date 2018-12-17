#include "Prototype.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/transform.hpp"
#include "glm/gtx/quaternion.hpp"

dn::Prototype::Prototype(const dn::Model &p_model, dn::Shader *p_shader)
	: _model(p_model), _shader(p_shader), _vao(0), _vbos{0,0}, _parent(nullptr),
	_position(0.f, 0.f, 0.f), _rotation(0.f, 0.f, 0.f), _scale(1.f, 1.f, 1.f),

	_positionMod(true), _rotationMod(true), _scaleMod(true)
{
	
}

dn::Prototype::~Prototype()
{
	glDeleteVertexArrays(1, &this->_vao);
	glDeleteBuffers(2, this->_vbos);
}

const dn::Model &dn::Prototype::model() const { return (this->_model); }
const dn::Shader *dn::Prototype::shader() const { return (this->_shader); }

void dn::Prototype::setModel(const dn::Model &p_model) { this->_model = p_model; }
void dn::Prototype::setShader(dn::Shader *p_shader) { this->_shader = p_shader; }

glm::vec3 dn::Prototype::position() const { return (this->_position); }
glm::vec3 dn::Prototype::rotation() const { return (this->_rotation); }
glm::vec3 dn::Prototype::scale() const { return (this->_scale); }

glm::vec3 &dn::Prototype::position()
{
	this->_positionMod = true;
	return (this->_position);
}
glm::vec3 &dn::Prototype::rotation()
{
	this->_rotationMod = true;
	return (this->_rotation);
}
glm::vec3 &dn::Prototype::scale()
{
	this->_scaleMod = true;
	return (this->_scale);
}

dn::Prototype *dn::Prototype::parent() const { return (this->_parent); }
void dn::Prototype::setParent(dn::Prototype *p_parent)
{
	this->_parent = (p_parent == this ? nullptr : p_parent);
}
const glm::mat4 &dn::Prototype::transform()
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

void dn::Prototype::create()
{
	if (!this->_shader)
		return ;
	this->_shader->compile();

	glGenVertexArrays(1, &this->_vao);
	glBindVertexArray(this->_vao);
	
	glGenBuffers(2, this->_vbos);

	glBindBuffer(GL_ARRAY_BUFFER, this->_vbos[0]);
	glBufferData(GL_ARRAY_BUFFER, this->_model.verticesSize(), this->_model.verticesData(), GL_STATIC_DRAW);

	GLuint positionAttrib = this->_shader->getAttrib("position");
	GLuint colorAttrib = this->_shader->getAttrib("color");

	glEnableVertexAttribArray(positionAttrib);
	glVertexAttribPointer(positionAttrib, 3, GL_FLOAT, false, sizeof(dn::Vertex), nullptr);
	glEnableVertexAttribArray(colorAttrib);
	glVertexAttribPointer(colorAttrib, 4, GL_FLOAT, false, sizeof(dn::Vertex), (void *)sizeof(dn::Vertex::position));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_vbos[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->_model.indicesSize(), this->_model.indicesData(), GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void dn::Prototype::draw(const GLenum &p_mode)
{
	this->_change = false;
	if (!this->_vao)
		return ;
	this->_shader->use();
	
	GLint transformUni = this->_shader->getUniform("transform");
	glUniformMatrix4fv(transformUni, 1, GL_FALSE, &this->transform()[0][0]);

	GLint viewProjectionUni = this->_shader->getUniform("viewProjection");
	glUniformMatrix4fv(viewProjectionUni, 1, GL_FALSE, &dn::Prototype::camViewProjection()[0][0]);

	std::cout << transformUni << ", " << viewProjectionUni << std::endl;

	glBindVertexArray(this->_vao);
	if (p_mode == -1)
		glDrawElements(this->_model.method(), this->_model.indices().size(), GL_UNSIGNED_INT, nullptr);
	else
		glDrawElements(p_mode, this->_model.indices().size(), GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
	this->_shader->use(false);
}

bool dn::Prototype::change() const
{
	return (this->_positionMod || this->_rotationMod || this->_scaleMod || (this->_parent && this->_parent->_change));
}

const float &dn::Prototype::camFov() { return (dn::Prototype::_fov); }
void dn::Prototype::setCamFov(const float &p_fov)
{
	dn::Prototype::_projectionMod = true;
	dn::Prototype::_fov = p_fov;
}

const float &dn::Prototype::camFar() { return (dn::Prototype::_far); }
void dn::Prototype::setCamFar(const float &p_far)
{
	dn::Prototype::_projectionMod = true;
	dn::Prototype::_far = p_far;
}

const float &dn::Prototype::camNear() { return (dn::Prototype::_near); }
void dn::Prototype::setCamNear(const float &p_near)
{
	dn::Prototype::_projectionMod = true;
	dn::Prototype::_near = p_near;
}

const float &dn::Prototype::camAspectRatio() { return (dn::Prototype::_aspectRatio); }
void dn::Prototype::setCamAspectRatio(const float &p_aspectRatio)
{
	dn::Prototype::_projectionMod = true;
	dn::Prototype::_aspectRatio = p_aspectRatio;
}

const glm::vec3 &dn::Prototype::camPosition() { return (dn::Prototype::_camPosition); }
glm::vec3 &dn::Prototype::camPositionc()
{
	dn::Prototype::_viewMod = true;
	return (dn::Prototype::_camPosition);
}

const glm::vec3 &dn::Prototype::camRotation() { return (dn::Prototype::_camRotation); }
glm::vec3 &dn::Prototype::camRotationc()
{
	dn::Prototype::_viewMod = true;
	return (dn::Prototype::_camRotation);
}

glm::vec3 dn::Prototype::camForward()
{
	return (glm::toMat4(glm::quat(dn::Prototype::_camRotation)) * glm::vec4(0.f, 0.f, -1.f, 0.f));
}

glm::vec3 dn::Prototype::camUp()
{
	return (glm::toMat4(glm::quat(dn::Prototype::_camRotation)) * glm::vec4(0.f, 1.f, 0.f, 0.f));
}

const glm::mat4 &dn::Prototype::camViewProjection()
{
	dn::Prototype::_projectionMat = glm::perspective(
		dn::Prototype::_fov,
		dn::Prototype::_aspectRatio,
		dn::Prototype::_near,
		dn::Prototype::_far);

	dn::Prototype::_viewMat = glm::lookAt(
		dn::Prototype::_camPosition,
		dn::Prototype::_camPosition + dn::Prototype::camForward(),
		dn::Prototype::camUp()
	);

	return (dn::Prototype::_viewprojMat = dn::Prototype::_projectionMat * dn::Prototype::_viewMat);
}

glm::vec3	dn::Prototype::_camPosition(0.f, 0.f, 2.f);
glm::vec3	dn::Prototype::_camRotation(0.f, 0.f, 0.f);
glm::mat4	dn::Prototype::_viewMat;
glm::mat4	dn::Prototype::_projectionMat;
glm::mat4	dn::Prototype::_viewprojMat;

float		dn::Prototype::_fov(70.f);
float		dn::Prototype::_far(100.f);
float		dn::Prototype::_near(0.01f);
float		dn::Prototype::_aspectRatio(1.f);

bool		dn::Prototype::_viewMod(true);
bool		dn::Prototype::_projectionMod(true);

