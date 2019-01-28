#include "dn/Mesh.hpp"
#include "dn/Codes.hpp"

dn::Mesh::Mesh(dn::Model *p_model, dn::Shader *p_shader)
	: Component(), _model(p_model), _shader(p_shader),
	_texture(nullptr), _renderMode(DN_TEXTURE_COLOR | DN_MESH_COLOR), _color(1.f, 1.f, 1.f, 1.f)
{
}

dn::Model *dn::Mesh::model() const { return (this->_model); }
void dn::Mesh::setModel(dn::Model *p_model)
{
	this->_model = p_model;
}

dn::Shader *dn::Mesh::shader() const { return (this->_shader); }
void dn::Mesh::setShader(dn::Shader *p_shader)
{
	this->_shader = p_shader;
}

dn::Texture *dn::Mesh::texture() const { return (this->_texture); }
void dn::Mesh::setTexture(dn::Texture *p_texture)
{
	this->_renderMode = DN_TEXTURE_COLOR;
	this->_texture = p_texture;
}

glm::vec4 dn::Mesh::color() const { return (this->_color); }
glm::vec4 &dn::Mesh::color() { return (this->_color); }
void dn::Mesh::setColor(const glm::vec4 &p_color)
{
	this->_renderMode = DN_MESH_COLOR;
	this->_color = p_color;
}
void dn::Mesh::setColor(const float &p_r, const float &p_g, const float &p_b, const float &p_a)
{
	this->_renderMode = DN_MESH_COLOR;
	this->_color = glm::vec4(p_r, p_g, p_b, p_a);
}

int dn::Mesh::renderMode() const { return (this->_renderMode); }
void dn::Mesh::setRenderMode(const int &p_mode)
{
	this->_renderMode = p_mode;
}
