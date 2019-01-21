#include "MeshRenderer.hpp"
#include "Transform.hpp"
#include "Texture.hpp"

dn::MeshData::MeshData(dn::Model *p_model, dn::Shader *p_shader)
	: ComponentData(), _model(p_model), _shader(p_shader),
	_texture(nullptr), _renderMode(DN_TEXTURE_COLOR | DN_MESH_COLOR), _color(1.f, 1.f, 1.f, 1.f)
{
}

dn::Model *dn::MeshData::model() const { return (this->_model); }
void dn::MeshData::setModel(dn::Model *p_model)
{
	this->_model = p_model;
}

dn::Shader *dn::MeshData::shader() const { return (this->_shader); }
void dn::MeshData::setShader(dn::Shader *p_shader)
{
	this->_shader = p_shader;
}

dn::Texture *dn::MeshData::texture() const { return (this->_texture); }
void dn::MeshData::setTexture(dn::Texture *p_texture)
{
	this->_renderMode = DN_TEXTURE_COLOR;
	this->_texture = p_texture;
}

glm::vec4 dn::MeshData::color() const { return (this->_color); }
glm::vec4 &dn::MeshData::color() { return (this->_color); }
void dn::MeshData::setColor(const glm::vec4 &p_color)
{
	this->_renderMode = DN_MESH_COLOR;
	this->_color = p_color;
}
void dn::MeshData::setColor(const float &p_r, const float &p_g, const float &p_b, const float &p_a)
{
	this->_renderMode = DN_MESH_COLOR;
	this->_color = glm::vec4(p_r, p_g, p_b, p_a);
}

int dn::MeshData::renderMode() const { return (this->_renderMode); }
void dn::MeshData::setRenderMode(const int &p_mode)
{
	this->_renderMode = p_mode;
}
