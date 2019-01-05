#include "Scene.hpp"
#include "Object.hpp"
#include "ModelInstance.hpp"
#include "Model.hpp"
#include "MeshRenderer.hpp"
#include "Camera.hpp"
#include "Texture.hpp"
#include "Transform.hpp"
#include <algorithm>

dn::Scene::Scene()
	: _objects(), _instances(), _started(false), _camera(nullptr)
{

}

void dn::Scene::addObject(dn::Object *p_object)
{
	// checks if the object is already in the scene
	std::vector<dn::Object *>::iterator it = std::find(
			this->_objects.begin(),
			this->_objects.end(),
			p_object);
	if (it != this->_objects.end())
		return ;
	this->_objects.push_back(p_object);

	// if the added object has a camera component attached to it, then it is
	// used as the scene camera
	dn::Camera *camera = p_object->getComponent<dn::Camera>();
	if (camera)
		this->_camera = camera;

	if (this->_started)
		p_object->start();

	// get the MeshRenderer of the object
	dn::MeshRenderer *mesh = p_object->getComponent<dn::MeshRenderer>();
	// if it has no MeshRenderer, the function stops and do nothing
	if (!mesh || !mesh->shader() || !mesh->model())
		return ;
	// but if it has one, it is implemented in the instances map
	// check for shader entry firstly
	dn::map_Shader::iterator shader_it = this->_instances.find(mesh->shader());
	if (shader_it != this->_instances.end())
	{
		// check for model entry secondly
		dn::map_Model::iterator model_it = shader_it->second.find(mesh->model());
		if (model_it != shader_it->second.end())
		{
			// check for texture entry finally
			dn::map_Texture::iterator texture_it = model_it->second.second.find(mesh->texture());
			if (texture_it != model_it->second.second.end())
				texture_it->second.push_back(mesh);
			else
			{
				dn::vector_MeshRenderer meshRenderer_vector;
				meshRenderer_vector.push_back(mesh);

				model_it->second.second.insert(std::make_pair(mesh->texture(), meshRenderer_vector));
			}
		}
		else
		{
			dn::vector_MeshRenderer meshRenderer_vector;
			meshRenderer_vector.push_back(mesh);

			dn::map_Texture texture_map;
			texture_map.insert(std::make_pair(mesh->texture(), meshRenderer_vector));

			dn::ModelInstance *mdl = new dn::ModelInstance(mesh->shader(), mesh->model());
			dn::pair_ModelInstance modelInstance_it = std::make_pair(mdl, texture_map);

			shader_it->second.insert(std::make_pair(mesh->model(), modelInstance_it));
		}
	}
	else
	{
		dn::vector_MeshRenderer meshRenderer_vector;
		meshRenderer_vector.push_back(mesh);

		dn::map_Texture texture_map;
		texture_map.insert(std::make_pair(mesh->texture(), meshRenderer_vector));

		dn::ModelInstance *mdl = new dn::ModelInstance(mesh->shader(), mesh->model());
		dn::pair_ModelInstance modelInstance_it = std::make_pair(mdl, texture_map);

		dn::map_Model model_map;
		model_map.insert(std::make_pair(mesh->model(), modelInstance_it));

		this->_instances.insert(std::make_pair(mesh->shader(), model_map));
	}
}

void dn::Scene::start()
{
	if (this->_started)
		return ;
	this->_started = true;

	for (size_t i = 0; i < this->_objects.size(); ++i)
		this->_objects[i]->start();
}

void dn::Scene::update()
{
	if (!this->_started)
		return ;
	for (size_t i = 0; i < this->_objects.size(); ++i)
			this->_objects[i]->update();
	this->render();
}

void dn::Scene::render()
{
	// if there is no camera in the scene, nothing is rendered
	if (!this->_camera)
		return ;

	GLint renderModeU;
	GLint transformU;
	GLint viewprojectionU;
	GLint meshColorU;
	GLint unitU;
	GLint lightColorU;
	GLint lightPositionU;

	dn::map_Shader::iterator shader_it = this->_instances.begin();
	//  v he smiles lol
	for (; shader_it != this->_instances.end(); ++shader_it)
	{
		// use the shader for every model that uses this shader
		shader_it->first->use(true);

		// send the view projection matrix of the camera to the shader
		viewprojectionU = shader_it->first->getUniform("viewprojection");
		if (viewprojectionU != -1)
			glUniformMatrix4fv(viewprojectionU, 1, GL_FALSE, &this->_camera->viewProjectionMat()[0][0]);
		// send the texture unit, for now it never changes, it is always GL_TEXTURE0
		unitU = shader_it->first->getUniform("unit");
		if (unitU != -1)
			glUniform1i(unitU, GL_TEXTURE0);

		lightPositionU = shader_it->first->getUniform("lightPosition");
		if (lightPositionU != -1)
			glUniform3fv(lightPositionU, 1, &dn::MeshRenderer::lightPosition[0]);
		lightColorU = shader_it->first->getUniform("lightColor");
		if (lightColorU != -1)
			glUniform3fv(lightColorU, 1, &dn::MeshRenderer::lightColor[0]);

		dn::map_Model::iterator model_it = shader_it->second.begin();
		for (; model_it != shader_it->second.end(); ++model_it)
		{
			// bind the model instance for every mesh that uses this model
			model_it->second.first->bind();

			dn::map_Texture::iterator texture_it = model_it->second.second.begin();
			for (; texture_it != model_it->second.second.end(); ++texture_it)
			{
				// there can be no texture at all
				if (texture_it->first)
				{
					// bind the texture
					texture_it->first->bind(0);
				}

				dn::vector_MeshRenderer::iterator mesh_it = texture_it->second.begin();
				for (; mesh_it != texture_it->second.end(); ++mesh_it)
				{
					// send the used render mode to the shader
					// checking first is better
					renderModeU = shader_it->first->getUniform("renderMode");
					if (renderModeU != -1)
						glUniform1i(renderModeU, (*mesh_it)->renderMode());

					transformU = shader_it->first->getUniform("transform");
					if (transformU != -1)
					{
						// send the transform matrix to the shader
						glUniformMatrix4fv(
							transformU,
							1, GL_FALSE,
							&(*mesh_it)->transform()->transformMat()[0][0]);
					}

					meshColorU = shader_it->first->getUniform("meshColor");
					if (((*mesh_it)->renderMode() & DN_MESH_COLOR) && meshColorU != -1)
						glUniform4fv(meshColorU, 1, &(*mesh_it)->color()[0]);

					// Later i will implement glDrawElementsInstanced
					glDrawElements(model_it->first->method(), model_it->first->indices().size(),
						GL_UNSIGNED_INT, nullptr);
				}
			}
		}
	}
}

dn::map_Shader dn::Scene::instances() const
{
	return (this->_instances);
}
