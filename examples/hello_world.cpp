#include "Application.hpp"
#include "Window.hpp"

#include "Object.hpp"
#include "Scene.hpp"
#include "RenderEngine.hpp"

#include "Model.hpp"

int main()
{
	dn::Window win(600, 400, "Hello world !");

	dn::Object cube;
	cube.addComponent<dn::Transform>();
	cube.addComponent<dn::Mesh>(&dn::Model::cubeEdges)->setColor(1.f, 1.f, 1.f);

	dn::Object camera;
	camera.addComponent<dn::Transform>(0.f, 0.f, 5.f);
	camera.addComponent<dn::Camera>();

	dn::Scene scene;
	scene.addEngine<dn::RenderEngine>();

	scene.addObject(cube);
	scene.addObject(camera);

	win.setScene(&scene);

	dn::Application::run();
	return 0;
}
