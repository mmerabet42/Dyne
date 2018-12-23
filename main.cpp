#include <iostream>
#include <sndfile.h>
#include <AL/al.h>
#include <AL/alc.h>

#include "Window.hpp"
#include "Application.hpp"
#include "Prototype.hpp"
#include "Math.hpp"
#include "Object.hpp"
#include "Component.hpp"
#include "Model.hpp"

#include "Transform.hpp"
#include "MeshRenderer.hpp"
#include "Camera.hpp"
#include "Texture.hpp"

void closeWinEscape(dn::Window *w, int k, int, int) { if (k == DN_KEY_ESCAPE) w->close(); }

int main()
{
	dn::Window *win = new dn::Window(600, 400, "Window 1");

	win->keyEvent.addListener(closeWinEscape);
	win->setClearColor(37, 44, 56);
	
	dn::Object *camera = new dn::Object;
	dn::Object *cube = new dn::Object;
	dn::Object *surroundCube = new dn::Object;
	dn::Object *gridPlane = new dn::Object;
	dn::Object *preCube = new dn::Object;
	std::vector<dn::Object *> minecraftObjects;

	cube->addComponent<dn::Transform>();
	cube->addComponent<dn::MeshRenderer>(&dn::Model::cube);
	cube->getComponent<dn::MeshRenderer>()->setTexture(new dn::Texture("res/minecraft_grass.png"));
	
	surroundCube->addComponent<dn::Transform>(cube->getComponent<dn::Transform>());
	surroundCube->addComponent<dn::MeshRenderer>(&dn::Model::cubeEdges);

	preCube->addComponent<dn::Transform>();
	preCube->addComponent<dn::MeshRenderer>(&dn::Model::cubeEdges);

	dn::Transform *cameraTransform = camera->addComponent<dn::Transform>(0.f, 0.f, 5.f);
	camera->addComponent<dn::Camera>(70.f, 0.02f, 100000000.f);

	gridPlane->addComponent<dn::Transform>();
	gridPlane->addComponent<dn::MeshRenderer>(dn::Model::generateGridPlane(101, 2.f));

	win->startEvent([&](dn::Window *win) {
		win->setMouseLock(true);
		cube->start();
		surroundCube->start();
		gridPlane->start();
		preCube->start();
	});

	float speedMove = 0.1f;

	ALCdevice *device = alcOpenDevice(nullptr);
	ALCcontext *context = alcCreateContext(device, nullptr);

	alcMakeContextCurrent(context);

	SF_INFO fileInfos;
	SNDFILE *file = sf_open("res/bounce.wav", SFM_READ, &fileInfos);

	ALsizei nbSamples = (ALsizei)(fileInfos.channels * fileInfos.frames);
	ALsizei samplerate = (ALsizei)fileInfos.samplerate;

	ALshort *samples = new ALshort[nbSamples];
	sf_read_short(file, samples, nbSamples);
	sf_close(file);

	ALenum format = (fileInfos.channels == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16);

	ALuint buffer;
	alGenBuffers(1, &buffer);
	alBufferData(buffer, format, samples, nbSamples * sizeof(ALsizei), samplerate);

	ALuint source;
	alGenSources(1, &source);
	alSourcei(source, AL_BUFFER, buffer);
	alSourcei(source, AL_LOOPING, AL_TRUE);

	alSource3f(source, AL_POSITION, 0.f, 0.f, 0.f);

	alSourcePlay(source);

	win->updateEvent([&](dn::Window *win) {

		if (win->getKey(DN_KEY_W))
			cameraTransform->position() += cameraTransform->forward() * speedMove;
		if (win->getKey(DN_KEY_S))
			cameraTransform->position() -= cameraTransform->forward() * speedMove;

		if (win->getKey(DN_KEY_A))
			cameraTransform->position() -= cameraTransform->right() * speedMove;
		if (win->getKey(DN_KEY_D))
			cameraTransform->position() += cameraTransform->right() * speedMove;

		if (win->getKey(DN_KEY_LEFT_SHIFT))
			cameraTransform->position() -= cameraTransform->up() * speedMove;
		if (win->getKey(DN_KEY_SPACE))
			cameraTransform->position() += cameraTransform->up() * speedMove;

		if (win->getKey(DN_KEY_KP_ADD))
			camera->getComponent<dn::Camera>()->fov() += 0.005f;
		if (win->getKey(DN_KEY_KP_SUBTRACT))
			camera->getComponent<dn::Camera>()->fov() -= 0.005f;

		if (win->getKey(DN_KEY_LEFT_CONTROL))
			speedMove = (win->getKeyDown(DN_KEY_RIGHT_CONTROL) ? 100.f : 2.f);
		else
			speedMove = 0.1f;

		if (win->getKey(DN_KEY_O))
			cube->getComponent<dn::Transform>()->position() += cube->getComponent<dn::Transform>()->right();
		if (win->getKey(DN_KEY_P))
			cube->getComponent<dn::Transform>()->position() -= cube->getComponent<dn::Transform>()->right();

		if (win->getButton(DN_MOUSE_LEFT))
		{
			dn::Object *obj = new dn::Object;
			dn::Object *obj2 = new dn::Object;
			glm::vec3 frwrd = cameraTransform->position() + cameraTransform->forward() * 5.f;
			obj->addComponent<dn::Transform>()->position() = frwrd;
			obj->addComponent<dn::MeshRenderer>(&dn::Model::cube)->setTexture(new dn::Texture("res/minecraft_grass.png"));
			obj2->addComponent<dn::Transform>()->position() = frwrd;
			obj2->addComponent<dn::MeshRenderer>(&dn::Model::cubeEdges);

			obj->start();
			obj2->start();
			minecraftObjects.push_back(obj);
			minecraftObjects.push_back(obj2);
		}

		if (win->getKeyDown(DN_KEY_C))
			win->setMouseLock(!win->getFlag(DN_MOUSELOCKED));

		cameraTransform->rotation().x += win->mouseDeltaY() * 0.1f;
		cameraTransform->rotation().y += win->mouseDeltaX() * 0.1f;

		alListener3f(AL_POSITION, cameraTransform->position().x, cameraTransform->position().y, cameraTransform->position().z);

		preCube->getComponent<dn::Transform>()->position() = cameraTransform->position() + cameraTransform->forward() * 5.f;

		win->updateViewport();
		camera->getComponent<dn::Camera>()->setAspectRatio(win->aspectRatio());

		win->clear();
		cube->update();
		surroundCube->update();
		gridPlane->update();
		preCube->update();
		for (size_t i = 0; i < minecraftObjects.size(); ++i)
			minecraftObjects[i]->update();
	});

	dn::Application::setFlag(DN_FREEWINDOWS, true);
	dn::Application::run();

	delete[] samples;

	alDeleteBuffers(1, &buffer);
	alSourcei(source, AL_BUFFER, 0);
	alDeleteSources(1, &source);

	alcMakeContextCurrent(nullptr);
	alcDestroyContext(context);
	alcCloseDevice(device);
	
	return (0);
}
