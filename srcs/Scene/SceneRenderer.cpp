#include "SceneRenderer.hpp"
#include "Object.hpp"
#include "ModelInstance.hpp"
#include "Model.hpp"
#include "MeshRenderer.hpp"
#include "Camera.hpp"
#include "Texture.hpp"
#include "Transform.hpp"
#include <algorithm>

dn::SceneRenderer::SceneRenderer()
	: _objects(), _instances(), _started(false), _camera(nullptr)
{

}


static dn::pair_MeshRenderer __make_pair_MeshRenderer(dn::MeshRenderer *p_mesh)
{
	dn::vector_MeshRenderer meshRenderer;
	dn::vector_InstanceData instanceData;

	meshRenderer.push_back(p_mesh);
	instanceData.push_back(dn::InstanceData());
	return (std::make_pair(meshRenderer, instanceData));
}

static dn::map_Texture __make_map_Texture(dn::MeshRenderer *p_mesh)
{
	dn::map_Texture texture;

	texture.insert(std::make_pair(p_mesh->texture(), __make_pair_MeshRenderer(p_mesh)));
	return (texture);
}

void dn::SceneRenderer::addObject(dn::Object *p_object)
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

	// we need to start the object if the scene has already started
	if (this->_started)
		p_object->start();

	// get the MeshRenderer of the object
	dn::MeshRenderer *mesh = p_object->getComponent<dn::MeshRenderer>();
	// if the object has no mesh then nothing special is done
	if (!mesh || !mesh->shader() || !mesh->model())
		return ;
	// but if it has one, it is implemented in the instances map

	// we first check if the shader that the mesh uses is known to the scene, 
	// if it is, we add it to the shader entry
	dn::map_Shader::iterator shader_it = this->_instances.find(mesh->shader());
	if (shader_it != this->_instances.end())
	{
		// the shader is known to the scene so no need to add the shader entry,
		// we then, do the same for the model, if it is known to the scene in this shader entry,
		// we add the mesh in the model entry.
		dn::map_Model::iterator model_it = shader_it->second.find(mesh->model());
		if (model_it != shader_it->second.end())
		{
			// the model entry is found, which means that a model instance has
			// already been created. So we finally check for the texture entry,
			// if the mesh texture is known to the scene in this model entry of
			// this shader entry, we add it to the entry
			dn::map_Texture::iterator texture_it = model_it->second.second.find(mesh->texture());
			if (texture_it != model_it->second.second.end())
			{
				// the texture entry is found, we add the mesh to the MeshRenderer list of
				// of this 'path' shader -> model -> texture
				texture_it->second.first.push_back(mesh);
				// the texture has also an instance data list, which is were all
				// the specific data of the mesh is stored, so all the list content
				// is send once to the gpu. Instead of creating the list every frame
				// in the render function it is better to add an instance data
				// everytime we add an object.
				texture_it->second.second.push_back(dn::InstanceData());
			}
			else
			{
				// the texture is unknown to the scene, so the texture entry
				// needs to be created, also the mesh list and instance data list
				// then the texture entry is created in the model entry
				model_it->second.second.insert(
					std::make_pair(mesh->texture(), __make_pair_MeshRenderer(mesh)));
			}
		}
		else
		{
			// the model of the mesh is unknown to the scene, so a model entry
			// must be created, by first generating the model instance.
		//	dn::ModelInstance *modelInstance = new dn::ModelInstance(mesh->shader(), mesh->model());

			// then we insert the model entry to this shader entry
			shader_it->second.insert(
				std::make_pair(mesh->model(),
					// we also need to create the texture entry, as the model entry
					// is a fresh new entry so it has no texture entry allocated to it
					std::make_pair(new dn::ModelInstance(mesh->shader(), mesh->model()),
						__make_map_Texture(mesh))));
		}
	}
	else
	{
		// if no shader entry is found, we need to add it.

		// first we generate the model instance
		dn::ModelInstance *modelInstance = new dn::ModelInstance(mesh->shader(), mesh->model());

		// as the shader entry is a fresh one, its model map needs to be created
		dn::map_Model model_map;
		// and we insert as a first element the model of the mesh
		model_map.insert(std::make_pair(mesh->model(),
			// same thing for the texture map, which needs to be created as the model
			// map is a new one
			std::make_pair(modelInstance, __make_map_Texture(mesh))));

		// finally the mesh shader entry is created
		this->_instances.insert(std::make_pair(mesh->shader(), model_map));
	}
}

void dn::SceneRenderer::start()
{
	if (this->_started)
		return ;
	this->_started = true;

	// the start method only starts its objects
	for (size_t i = 0; i < this->_objects.size(); ++i)
		this->_objects[i]->start();
}

void dn::SceneRenderer::update()
{
	if (!this->_started)
		return ;
	// the update method updates its objects
	for (size_t i = 0; i < this->_objects.size(); ++i)
			this->_objects[i]->update();
	// and renders the scene
	this->render();
}

void dn::SceneRenderer::render()
{
	// if there is no camera in the scene, nothing is rendered
	if (!this->_camera)
		return ;

	GLint viewprojectionU;
	GLint unitU;
	GLint lightColorU;
	GLint lightPositionU;

	// Iterating through each available shader entry
	this->_shader_it = this->_instances.begin();
	//  v he smiles lol
	for (; this->_shader_it != this->_instances.end(); ++this->_shader_it)
	{
		// using the actual shader
		this->_shader_it->first->use(true);

		// send the view projection matrix of the camera to the shader
		viewprojectionU = this->_shader_it->first->getUniform("viewprojection");
		if (viewprojectionU != -1)
			glUniformMatrix4fv(viewprojectionU, 1, GL_FALSE, &this->_camera->viewProjectionMat()[0][0]);
		// send the texture unit, for now it never changes, it is always GL_TEXTURE0
		unitU = this->_shader_it->first->getUniform("unit");
		if (unitU != -1)
			glUniform1i(unitU, GL_TEXTURE0);

		// also sending the lightPosition and the lightColor
		lightPositionU = this->_shader_it->first->getUniform("lightPosition");
		if (lightPositionU != -1)
			glUniform3fv(lightPositionU, 1, &dn::MeshRenderer::lightPosition[0]);
		lightColorU = this->_shader_it->first->getUniform("lightColor");
		if (lightColorU != -1)
			glUniform3fv(lightColorU, 1, &dn::MeshRenderer::lightColor[0]);

		// iterating through each model entry of this shader
		this->_model_it = this->_shader_it->second.begin();
		for (; this->_model_it != this->_shader_it->second.end(); ++this->_model_it)
		{
			// binding the ModelInstance
			this->_model_it->second.first->bind();
			this->_model_it->second.first->bindInstanceVb();
			// Iterating through each texture entry of this model
			this->_texture_it = this->_model_it->second.second.begin();
			for (; this->_texture_it != this->_model_it->second.second.end(); ++this->_texture_it)
			{
				// if the texture is not null (possible)
				if (this->_texture_it->first)
					// bind the texture
					this->_texture_it->first->bind(0);

				for (size_t i = 0; i != this->_texture_it->second.first.size(); ++i)
				{
					dn::MeshRenderer *mesh = this->_texture_it->second.first[i];
					dn::InstanceData *instance = &this->_texture_it->second.second[i];

					instance->transform = mesh->transform()->transformMat();
					instance->renderMode = mesh->renderMode();
					instance->meshColor = mesh->color();
				}
				glBufferData(GL_ARRAY_BUFFER,
					sizeof(dn::InstanceData) * this->_texture_it->second.second.size(),
					this->_texture_it->second.second.data(), GL_DYNAMIC_DRAW);

				glDrawElementsInstanced(this->_model_it->first->method(),
					this->_model_it->first->indices().size(), GL_UNSIGNED_INT, nullptr,
					this->_texture_it->second.second.size());
			}
		}
	}
}

dn::map_Shader dn::SceneRenderer::instances() const
{
	return (this->_instances);
}
