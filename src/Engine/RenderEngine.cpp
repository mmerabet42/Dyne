#include "dn/RenderEngine.hpp"
#include "dn/Model.hpp"
#include "dn/Shader.hpp"
#include "dn/Texture.hpp"
#include "dn/Light.hpp"
#include "dn/Scene.hpp"
#include "dn/Window.hpp"

glm::vec3 dn::Light::lightPosition(0.f, 0.f, 0.f);
glm::vec3 dn::Light::lightColor(1.f, 1.f, 1.f);

static dn::layerMeshFilterInstanceData _layerMeshFilterInstanceData(dn::MeshFilter &p_filter);
static dn::layerModelInstance _layerModelInstance(dn::MeshFilter &p_filter);
static dn::layerModel _layerModel(dn::MeshFilter &p_filter);

void dn::RenderEngine::onObjectAdded(dn::MeshFilter &p_filter)
{
	dn::layerShader::iterator shader_it = this->_instances.find(p_filter.mesh->shader());
	if (shader_it != this->_instances.end())
	{
		dn::layerModel::iterator model_it = shader_it->second.find(p_filter.mesh->model());
		if (model_it != shader_it->second.end())
		{
			dn::layerTexture::iterator texture_it = model_it->second.second.find(p_filter.mesh->texture());
			if (texture_it != model_it->second.second.end())
			{
				texture_it->second.first.push_back(&p_filter);
				texture_it->second.second.push_back(dn::InstanceData());
			}
			else
				model_it->second.second.emplace(
					p_filter.mesh->texture(), _layerMeshFilterInstanceData(p_filter));
		}
		else
			shader_it->second.emplace(p_filter.mesh->model(), _layerModelInstance(p_filter));
	}
	else
		this->_instances.emplace(p_filter.mesh->shader(), _layerModel(p_filter));
}

void dn::RenderEngine::onObjectRemoved(dn::MeshFilter &p_filter)
{
	dn::layerShader::iterator shader_it = this->_instances.find(p_filter.mesh->shader());
	dn::layerModel::iterator model_it = shader_it->second.find(p_filter.mesh->model());
	dn::layerTexture::iterator texture_it = model_it->second.second.find(p_filter.mesh->texture());
	if (texture_it->second.first.size() == 1)
	{
		texture_it->second.first.clear();
		texture_it->second.second.clear();
	}
	else
	{
		dn::layerMeshFilter::iterator mesh_it = std::find(
			texture_it->second.first.begin(), texture_it->second.first.end(), &p_filter);
		texture_it->second.first.erase(mesh_it);
		texture_it->second.second.pop_back();
	}
}

void dn::RenderEngine::onObjectAdded(dn::CameraFilter &p_filter)
{
	this->_camera = p_filter.camera;
	this->_camera->setTransform(p_filter.transform);
	if (this->scene()->window())
		this->_camera->setAspectRatio(this->scene()->window()->aspectRatio());
}

void dn::RenderEngine::onFramebufferSize(dn::Window &p_window, int, int)
{
	if (this->_camera)
		this->_camera->setAspectRatio(p_window.aspectRatio());
}

void dn::RenderEngine::onObjectRemoved(dn::CameraFilter &p_filter)
{
	this->_camera = nullptr;
}

void dn::RenderEngine::onUpdate()
{
	if (!this->_camera)
		return ;

	dn::layerShader::iterator shader_it = this->_instances.begin();
	for (; shader_it != this->_instances.end(); ++shader_it)
	{
		shader_it->first->use(true);

		GLint viewProjectionU = shader_it->first->getUniform("viewprojection");
		GLint unitU = shader_it->first->getUniform("unit");
		GLint lightPositionU = shader_it->first->getUniform("lightPosition");
		GLint lightColorU = shader_it->first->getUniform("lightColor");

		if (viewProjectionU != -1)
			glUniformMatrix4fv(viewProjectionU, 1, GL_FALSE, &this->_camera->viewProjectionMat()[0][0]);
		if (unitU != -1)
			glUniform1i(unitU, GL_TEXTURE0);
		if (lightPositionU != -1)
			glUniform3fv(lightPositionU, 1, &dn::Light::lightPosition[0]);
		if (lightColorU != -1)
			glUniform3fv(lightColorU, 1, &dn::Light::lightColor[0]);

		dn::layerModel::iterator model_it = shader_it->second.begin();
		for (; model_it != shader_it->second.end(); ++model_it)
		{
			model_it->second.first->bind();
			model_it->second.first->bindInstanceVb();

			dn::layerTexture::iterator texture_it = model_it->second.second.begin();
			for (; texture_it != model_it->second.second.end(); ++texture_it)
			{
				if (texture_it->first)
					texture_it->first->bind(0);

				for (size_t i = 0; i < texture_it->second.first.size(); ++i)
				{
					dn::MeshFilter *f = texture_it->second.first[i];
					dn::InstanceData *instance = &texture_it->second.second[i];

					instance->transform = f->transform->transformMat();
					instance->renderMode = f->mesh->renderMode();
					instance->meshColor = f->mesh->color();
				}
				glBufferData(GL_ARRAY_BUFFER,
					sizeof(dn::InstanceData) * texture_it->second.second.size(),
					texture_it->second.second.data(), GL_DYNAMIC_DRAW);

				glDrawElementsInstanced(model_it->first->method(),
					model_it->first->indices().size(), GL_UNSIGNED_INT, nullptr,
					texture_it->second.second.size());
			}
		}
	}
}

dn::layerMeshFilterInstanceData _layerMeshFilterInstanceData(dn::MeshFilter &p_filter)
{
	dn::layerMeshFilter meshFilter_layer;
	dn::layerInstanceData instanceData_layer;

	meshFilter_layer.push_back(&p_filter);
	instanceData_layer.push_back(dn::InstanceData());
	return (dn::layerMeshFilterInstanceData(meshFilter_layer, instanceData_layer));
}

dn::layerModelInstance _layerModelInstance(dn::MeshFilter &p_filter)
{
	dn::ModelInstance *mdl = new dn::ModelInstance(p_filter.mesh->shader(), p_filter.mesh->model());
	dn::layerTexture texture_layer;

	texture_layer.emplace(p_filter.mesh->texture(), _layerMeshFilterInstanceData(p_filter));
	return (dn::layerModelInstance(mdl, texture_layer));
}

dn::layerModel _layerModel(dn::MeshFilter &p_filter)
{
	dn::layerModel model_layer;

	model_layer.emplace(p_filter.mesh->model(), _layerModelInstance(p_filter));
	return (model_layer);
}
