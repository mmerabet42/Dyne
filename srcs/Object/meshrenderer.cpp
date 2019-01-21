#include "MeshRenderer.hpp"
#include "Transform.hpp"
#include "Texture.hpp"
#include "Object.hpp"

dn::MeshRenderer::MeshRenderer(dn::Model *p_model, dn::Shader *p_shader)
	: Component("MeshRenderer"), _model(p_model), _shader(p_shader),
	_texture(nullptr), _renderMode(DN_TEXTURE_COLOR | DN_MESH_COLOR), _color(1.f, 1.f, 1.f, 1.f)
{
	
}

dn::Model *dn::MeshRenderer::model() const { return (this->_model); }
void dn::MeshRenderer::setModel(dn::Model *p_model)
{
	this->_model = p_model;
}

dn::Shader *dn::MeshRenderer::shader() const { return (this->_shader); }
void dn::MeshRenderer::setShader(dn::Shader *p_shader)
{
	this->_shader = p_shader;
}

dn::Texture *dn::MeshRenderer::texture() const { return (this->_texture); }
void dn::MeshRenderer::setTexture(dn::Texture *p_texture)
{
	this->_renderMode = DN_TEXTURE_COLOR;
	this->_texture = p_texture;
}

glm::vec4 dn::MeshRenderer::color() const { return (this->_color); }
glm::vec4 &dn::MeshRenderer::color() { return (this->_color); }
void dn::MeshRenderer::setColor(const glm::vec4 &p_color)
{
	this->_renderMode = DN_MESH_COLOR;
	this->_color = p_color;
}
void dn::MeshRenderer::setColor(const float &p_r, const float &p_g, const float &p_b, const float &p_a)
{
	this->_renderMode = DN_MESH_COLOR;
	this->_color = glm::vec4(p_r, p_g, p_b, p_a);
}

int dn::MeshRenderer::renderMode() const { return (this->_renderMode); }
void dn::MeshRenderer::setRenderMode(const int &p_mode)
{
	this->_renderMode = p_mode;
}
dn::Transform *dn::MeshRenderer::transform() const { return (this->_transform); }

void dn::MeshRenderer::start()
{
	this->_transform = this->object()->getComponent<dn::Transform>();
}

void dn::MeshRenderer::update()
{
}
