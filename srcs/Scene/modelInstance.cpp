#include "ModelInstance.hpp"
#include "Application.hpp"
#include "Shader.hpp"
#include "Model.hpp"
#include "Vertex.hpp"
#include "glm/matrix.hpp"

dn::ModelInstance::ModelInstance(dn::Shader *p_shader, dn::Model *p_model)
	: _shader(p_shader), _model(p_model)
{
	dn::Application::addDependent(this);
}
dn::ModelInstance::~ModelInstance()
{
	dn::Application::destroyDependent(this);
}

void dn::ModelInstance::bind()
{
	// binding a model instance means binding its vertex array
	glBindVertexArray(this->_vao);
}

const dn::Shader *dn::ModelInstance::shader() const { return (this->_shader); }
const dn::Model *dn::ModelInstance::model() const { return (this->_model); }

void dn::ModelInstance::create()
{
	glGenVertexArrays(1, &this->_vao);
	glBindVertexArray(this->_vao);

	glGenBuffers(VB_SIZE, this->_vbos);

	glBindBuffer(GL_ARRAY_BUFFER, this->_vbos[VERTEX_VB]);
	glBufferData(GL_ARRAY_BUFFER,this->_model->verticesSize(), this->_model->verticesData(),
		GL_STATIC_DRAW);

	GLint positionAttrib = this->_shader->getAttrib("position");
	GLint colorAttrib = this->_shader->getAttrib("color");
	GLint texAttrib = this->_shader->getAttrib("tex");
	GLint normalAttrib = this->_shader->getAttrib("normal");

	glEnableVertexAttribArray(positionAttrib);
	glVertexAttribPointer(positionAttrib, 3, GL_FLOAT, false,
		sizeof(dn::Vertex), (void *)offsetof(dn::Vertex, position));
	glEnableVertexAttribArray(colorAttrib);
	glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, false,
		sizeof(dn::Vertex), (void *)offsetof(dn::Vertex, color));
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, false,
		sizeof(dn::Vertex), (void *)offsetof(dn::Vertex, tex));
	glEnableVertexAttribArray(normalAttrib);
	glVertexAttribPointer(normalAttrib, 3, GL_FLOAT, false,
		sizeof(dn::Vertex), (void *)offsetof(dn::Vertex, normal));
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_vbos[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->_model->indicesSize(), this->_model->indicesData(),
		GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, this->_vbos[INSTANCE_VB]);

	GLint transformAttrib = this->_shader->getAttrib("transform");

	glEnableVertexAttribArray(transformAttrib + 0);
	glVertexAttribPointer(transformAttrib + 0, 4, GL_FLOAT, false,
		sizeof(dn::InstanceData), (void *)(sizeof(GLfloat) * 4 * 0));
	glVertexAttribDivisor(transformAttrib + 0, 1);
	glEnableVertexAttribArray(transformAttrib + 1);
	glVertexAttribPointer(transformAttrib + 1, 4, GL_FLOAT, false,
		sizeof(dn::InstanceData), (void *)(sizeof(GLfloat) * 4 * 1));
	glVertexAttribDivisor(transformAttrib + 1, 1);
	glEnableVertexAttribArray(transformAttrib + 2);
	glVertexAttribPointer(transformAttrib + 2, 4, GL_FLOAT, false,
		sizeof(dn::InstanceData), (void *)(sizeof(GLfloat) * 4 * 2));
	glVertexAttribDivisor(transformAttrib + 2, 1);
	glEnableVertexAttribArray(transformAttrib + 3);
	glVertexAttribPointer(transformAttrib + 3, 4, GL_FLOAT, false,
		sizeof(dn::InstanceData), (void *)(sizeof(GLfloat) * 4 * 3));
	glVertexAttribDivisor(transformAttrib + 3, 1);

	GLint renderModeAttrib = this->_shader->getAttrib("renderMode");

	glEnableVertexAttribArray(renderModeAttrib);
	glVertexAttribIPointer(renderModeAttrib, 1, GL_INT,
		sizeof(dn::InstanceData), (void *)offsetof(dn::InstanceData, renderMode));
	glVertexAttribDivisor(renderModeAttrib, 1);

	GLint meshColorAttrib = this->_shader->getAttrib("lmeshColor");

	glEnableVertexAttribArray(meshColorAttrib);
	glVertexAttribPointer(meshColorAttrib, 4, GL_FLOAT, false,
		sizeof(dn::InstanceData), (void *)offsetof(dn::InstanceData, meshColor));
	glVertexAttribDivisor(meshColorAttrib, 1);

	glBindVertexArray(0);
}

void dn::ModelInstance::destroy()
{
	glDeleteVertexArrays(1, &this->_vao);
	glDeleteBuffers(2, this->_vbos);
}

void dn::ModelInstance::bindInstanceVb()
{
	glBindBuffer(GL_ARRAY_BUFFER, this->_vbos[INSTANCE_VB]);
}
