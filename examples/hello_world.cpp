#include "dn/Application.hpp"
#include "dn/Window.hpp"

#include "dn/Object.hpp"
#include "dn/Scene.hpp"
#include "dn/RenderEngine.hpp"
#include "dn/Light.hpp"

#include "dn/Model.hpp"
#include "dn/Engine.hpp"

struct MeshedObject: public dn::EngineFilter<MeshedObject, dn::Mesh, dn::Transform>
{
	dn::Mesh *mesh;
	dn::Transform *transform;
};

class TestEngine: public dn::Engine<MeshedObject, dn::CameraFilter>
{
public:

	dn::CameraFilter *camera = nullptr;
	MeshedObject *cube = nullptr;

	void onObjectAdded(MeshedObject &o)
	{
		o.mesh->setRenderMode(DN_MESH_COLOR | DN_LIGHT_COLOR);
		cube = &o;
	}

	void onObjectAdded(dn::CameraFilter &o)
	{
		camera = &o;
	}

	void onStart()
	{
		scene()->window()->setMouseLock(true);
		if (camera)
			camera->transform->rotation() = glm::vec3(0.f, 0.f, 0.f);
	}

	void onUpdate()
	{
		if (scene()->window()->getKey(dn::KeyCode::escape))
			scene()->window()->close();

		if (scene()->window()->getKey(dn::KeyCode::W))
			camera->transform->position()
				+= camera->transform->forward() * dn::Application::deltaTimef() * 5.f;
		if (scene()->window()->getKey(dn::KeyCode::S))
			camera->transform->position()
				-= camera->transform->forward() * dn::Application::deltaTimef() * 5.f;
		if (scene()->window()->getKey(dn::KeyCode::A))
			camera->transform->position()
				-= camera->transform->right() * dn::Application::deltaTimef() * 5.f;
		if (scene()->window()->getKey(dn::KeyCode::D))
			camera->transform->position()
				+= camera->transform->right() * dn::Application::deltaTimef() * 5.f;
		if (scene()->window()->getKey(dn::KeyCode::space))
			camera->transform->position()
				+= camera->transform->up() * dn::Application::deltaTimef() * 5.f;
		if (scene()->window()->getKey(dn::KeyCode::leftShift))
			camera->transform->position()
				-= camera->transform->up() * dn::Application::deltaTimef() * 5.f;

		dn::Transform *current = camera->transform;
		if (scene()->window()->getButton(dn::MouseButton::left))
			current = cube->transform;
		current->rotation().x
			+= scene()->window()->mouseDeltaY() * dn::Application::deltaTimef() * 1.f;
		current->rotation().y
			+= scene()->window()->mouseDeltaX() * dn::Application::deltaTimef() * 1.f;

		dn::Light::lightPosition = camera->transform->position();
	}

};

int main()
{
	dn::Window win(600, 400, "Hello world !");

	dn::Object cube("Cube");
	cube.addComponent<dn::Transform>();
	cube.addComponent<dn::Mesh>(&dn::Model::cube)->setColor(1.f, 1.f, 1.f);

	dn::Object camera("Main Camera");
	camera.addComponent<dn::Transform>(0.f, 0.f, 5.f);
	camera.addComponent<dn::Camera>();

	dn::Scene scene;
	scene.addEngine<dn::RenderEngine>();
	scene.addEngine<TestEngine>();

	scene.addObject(cube);
	scene.addObject(camera);

	win.setScene(&scene);

	dn::Application::run();
	return 0;
}
