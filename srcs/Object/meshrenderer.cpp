#include "MeshRenderer.hpp"
#include "Prototype.hpp"
#include "Transform.hpp"
#include "Camera.hpp"
#include "Object.hpp"
#include "Texture.hpp"

dn::MeshRenderer::MeshRenderer(dn::Model *p_model, dn::Shader *p_shader)
	: Component("MeshRenderer"), _model(p_model), _shader(p_shader), _vao(0), _vbos{0, 0},
	_texture(nullptr), _modelAllocated(false)
{
	
}

dn::MeshRenderer::MeshRenderer(const dn::Model &p_model, dn::Shader *p_shader)
	: MeshRenderer(new dn::Model(p_model), p_shader)
{
	this->_modelAllocated = true;
}

dn::MeshRenderer::~MeshRenderer()
{
	if (this->_vao)
	{
		glDeleteVertexArrays(1, &this->_vao);
		glDeleteBuffers(2, this->_vbos);
	}
	if (this->_modelAllocated)
		delete this->_model;
}

dn::Model *dn::MeshRenderer::model() const { return (this->_model); }
void dn::MeshRenderer::setModel(dn::Model *p_model)
{
	if (this->_modelAllocated)
		delete this->_model;
	this->_modelAllocated = false;
	this->_model = p_model;
}
void dn::MeshRenderer::setModel(const dn::Model &p_model)
{
	if (this->_modelAllocated)
		delete this->_model;
	this->_modelAllocated = true;
	this->_model = new dn::Model(p_model);
}

dn::Shader *dn::MeshRenderer::shader() const { return (this->_shader); }
void dn::MeshRenderer::setShader(dn::Shader *p_shader)
{
	this->_shader = p_shader;
}

dn::Texture *dn::MeshRenderer::texture() const { return (this->_texture); }
void dn::MeshRenderer::setTexture(dn::Texture *p_texture)
{
	this->_texture = p_texture;
}

void dn::MeshRenderer::start()
{
	if (!this->_model || !this->_shader)
		return ;
	glGenVertexArrays(1, &this->_vao);
	glBindVertexArray(this->_vao);

	glGenBuffers(2, this->_vbos);

	glBindBuffer(GL_ARRAY_BUFFER, this->_vbos[0]);
	glBufferData(GL_ARRAY_BUFFER, this->_model->verticesSize(), this->_model->verticesData(), GL_STATIC_DRAW);

	GLuint positionAttrib = this->_shader->getAttrib("position");
	GLuint colorAttrib = this->_shader->getAttrib("color");
	GLuint texAttrib = this->_shader->getAttrib("tex");

	glEnableVertexAttribArray(positionAttrib);
	glVertexAttribPointer(positionAttrib, 3, GL_FLOAT, false,
		sizeof(dn::Vertex), nullptr);
	glEnableVertexAttribArray(colorAttrib);
	glVertexAttribPointer(colorAttrib, 4, GL_FLOAT, false,
		sizeof(dn::Vertex), (void *)sizeof(dn::Vertex::position));
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, false,
		sizeof(dn::Vertex), (void *)(sizeof(GLfloat) * 7));
		

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_vbos[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->_model->indicesSize(), this->_model->indicesData(), GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void dn::MeshRenderer::update()
{
	if (!this->_model || !this->_shader)
		return ;
	this->_shader->use();
	// The braces are definetely useless
	{
		// Getting the transform component at each update is really stupid
		dn::Transform *transform = this->object()->getComponent<dn::Transform>();
		if (transform)
		{
			GLuint transformUni = this->_shader->getUniform("transform");
			glUniformMatrix4fv(transformUni, 1, GL_FALSE, &transform->transformMat()[0][0]);
			if (dn::Camera::main)
			{
				GLuint viewProjectUni = this->_shader->getUniform("viewProjection");
				glUniformMatrix4fv(viewProjectUni, 1, GL_FALSE, &dn::Camera::main->viewProjectionMat()[0][0]);
			}
		}
		glBindVertexArray(this->_vao);

		if (this->_texture)
		{
			GLuint samplerUni = this->_shader->getUniform("unit");
			glUniform1i(samplerUni, GL_TEXTURE0);
			this->_texture->bind(0);
		}

		glDrawElements(this->_model->method(), this->_model->indices().size(), GL_UNSIGNED_INT, nullptr);

		if (this->_texture)
			this->_texture->unbind();

		glBindVertexArray(0);
	}
	this->_shader->use(false);
}
