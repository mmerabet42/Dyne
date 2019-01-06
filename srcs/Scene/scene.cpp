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

	// if the scene has already started, the object is started
	if (this->_started)
		p_object->start();

	// get the MeshRenderer of the object
	dn::MeshRenderer *mesh = p_object->getComponent<dn::MeshRenderer>();
	// if it has no MeshRenderer, the function stops and do nothing
	if (!mesh || !mesh->shader() || !mesh->model())
		return ;
	// but if it has one, it is implemented in the instances map
	// check for shader entry first
	dn::map_Shader::iterator shader_it = this->_instances.find(mesh->shader());
	if (shader_it != this->_instances.end())
	{
		// a shader entry entry has been found, we then check for a model entry
		dn::map_Model::iterator model_it = shader_it->second.find(mesh->model());
		if (model_it != shader_it->second.end())
		{
			// a model entry has been found, we then check for a texture entry
			dn::map_Texture::iterator texture_it = model_it->second.second.find(mesh->texture());
			if (texture_it != model_it->second.second.end())
				// there is a texture entry, so we insert the MeshRenderer
				// to this path: (shader -> model -> modelInstance -> texture ...)
				texture_it->second.push_back(mesh);
			else
			{
				// no texture entry, so we create a new texture entry with 
				// the texture of the mesh
				// But the a texture entry has a list of MeshRenderer as a value,
				// so we need to create that value
				dn::vector_MeshRenderer meshRenderer_vector;
				// and add the object mesh as a first element in this list
				meshRenderer_vector.push_back(mesh);
				// then the texture entry is created in the model entry
				model_it->second.second.insert(std::make_pair(mesh->texture(), meshRenderer_vector));
			}
		}
		else
		{
			// no model entry, so the model of the mesh is 'unknown' to the scene
			// we make the scene aware of the model by creating a model entry.
			// But first, a texture entry, and mesh list must be created,
			// because we are creating a fresh model entry, the entries are created
			// in the reverse order so it make sense when reading the code.
			// So, first, the mesh list is created
			dn::vector_MeshRenderer meshRenderer_vector;
			// with the object mesh as a first element
			meshRenderer_vector.push_back(mesh);

			// then the texture entry is created
			dn::map_Texture texture_map;
			// by inserting the texture of the mesh as a first element, and the mesh
			// list created above as the mesh list of the texture entry
			texture_map.insert(std::make_pair(mesh->texture(), meshRenderer_vector));

			// then the model instance is created, which just links the shader and the model
			dn::ModelInstance *mdl = new dn::ModelInstance(mesh->shader(), mesh->model());
			// a ModelInstance has texture entry connected to it
			dn::pair_ModelInstance modelInstance_it = std::make_pair(mdl, texture_map);

			// and finally the newly created mesh entry is inserted into the shader entry
			shader_it->second.insert(std::make_pair(mesh->model(), modelInstance_it));
		}
	}
	else
	{
		// no shader entry found, unknown to the scene, so it needs to be created
		// First, we create the mesh list
		dn::vector_MeshRenderer meshRenderer_vector;
		// and the mesh object as a first element to the list
		meshRenderer_vector.push_back(mesh);

		// then the texture entry is created
		dn::map_Texture texture_map;
		// we 'link' the mesh texture and list of meshes created above
		texture_map.insert(std::make_pair(mesh->texture(), meshRenderer_vector));

		// the ModelInstance is also created, which links the shader and the model
		dn::ModelInstance *mdl = new dn::ModelInstance(mesh->shader(), mesh->model());
		// and we 'pair' the ModelInstance to the texture entry
		dn::pair_ModelInstance modelInstance_it = std::make_pair(mdl, texture_map);

		// and a model entry is also created
		dn::map_Model model_map;
		model_map.insert(std::make_pair(mesh->model(), modelInstance_it));

		// finally the mesh shader is addded to the global instances
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

	// Iterating through each available shader entry
	dn::map_Shader::iterator shader_it = this->_instances.begin();
	//  v he smiles lol
	for (; shader_it != this->_instances.end(); ++shader_it)
	{
		// using the actual shader
		shader_it->first->use(true);

		// send the view projection matrix of the camera to the shader
		viewprojectionU = shader_it->first->getUniform("viewprojection");
		if (viewprojectionU != -1)
			glUniformMatrix4fv(viewprojectionU, 1, GL_FALSE, &this->_camera->viewProjectionMat()[0][0]);
		// send the texture unit, for now it never changes, it is always GL_TEXTURE0
		unitU = shader_it->first->getUniform("unit");
		if (unitU != -1)
			glUniform1i(unitU, GL_TEXTURE0);

		// also sending the lightPosition and the lightColor
		lightPositionU = shader_it->first->getUniform("lightPosition");
		if (lightPositionU != -1)
			glUniform3fv(lightPositionU, 1, &dn::MeshRenderer::lightPosition[0]);
		lightColorU = shader_it->first->getUniform("lightColor");
		if (lightColorU != -1)
			glUniform3fv(lightColorU, 1, &dn::MeshRenderer::lightColor[0]);

		// iterating through each model entry of this shader
		dn::map_Model::iterator model_it = shader_it->second.begin();
		for (; model_it != shader_it->second.end(); ++model_it)
		{
			// binding the ModelInstance
			model_it->second.first->bind();
			// Iterating through each texture entry of this model
			dn::map_Texture::iterator texture_it = model_it->second.second.begin();
			for (; texture_it != model_it->second.second.end(); ++texture_it)
			{
				// if the texture is not null (possible)
				if (texture_it->first)
				{
					// bind the texture
					texture_it->first->bind(0);
				}

				// iterating through each mesh of this texture entry
				dn::vector_MeshRenderer::iterator mesh_it = texture_it->second.begin();
				for (; mesh_it != texture_it->second.end(); ++mesh_it)
				{
					// send the render mode of the mesh to the shader
					// checking first is better
					renderModeU = shader_it->first->getUniform("renderMode");
					if (renderModeU != -1)
						glUniform1i(renderModeU, (*mesh_it)->renderMode());

					glBindBuffer(GL_ARRAY_BUFFER, model_it->second.first->instanceVb());
					glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4),
						&(*mesh_it)->transform()->transformMat()[0][0], GL_DYNAMIC_DRAW);

				/*	transformU = shader_it->first->getUniform("transform");
					if (transformU != -1)
					{
						// send the transform matrix to the shader
						glUniformMatrix4fv(
							transformU,
							1, GL_FALSE,
							&(*mesh_it)->transform()->transformMat()[0][0]);
					}
*/
					meshColorU = shader_it->first->getUniform("meshColor");
					if (((*mesh_it)->renderMode() & DN_MESH_COLOR) && meshColorU != -1)
						glUniform4fv(meshColorU, 1, &(*mesh_it)->color()[0]);

					// Later i will implement glDrawElementsInstanced
					glDrawElementsInstanced(model_it->first->method(), model_it->first->indices().size(),
						GL_UNSIGNED_INT, nullptr, 1);
				}
			}
		}
	}
}

dn::map_Shader dn::Scene::instances() const
{
	return (this->_instances);
}
