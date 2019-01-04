#include "ModelInstance.hpp"

dn::ModelInstance::ModelInstance(dn::Shader *p_shader, dn::Model *p_model)
	: _shader(p_shader), _model(p_model)
{

}

void dn::ModelInstance::bind() {}

const dn::Shader *dn::ModelInstance::shader() const { return (this->_shader); }
const dn::Model *dn::ModelInstance::model() const { return (this->_model); }
