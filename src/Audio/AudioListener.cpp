#include "AudioListener.hpp"
#include "Transform.hpp"
#include "Object.hpp"
#include "allgl.hpp"

dn::AudioListener::AudioListener()
	: UComponent("AudioListener"), _transform(nullptr),
	_started(false), _volume(1.f)
{

}

float dn::AudioListener::volume() const { return (this->_volume); }
void dn::AudioListener::setVolume(const float &p_volume, const bool &p_relative)
{
	if (p_relative)
		this->_volume += p_volume;
	else
		this->_volume = p_volume;
	if (this->_volume < 0.0f)
		this->_volume = 0.0f;

	if (this->_started)
		alListenerf(AL_GAIN, this->_volume);
}

void dn::AudioListener::start()
{
	this->_started = true;
	this->_transform = this->object()->getComponent<dn::Transform>();
	alListenerf(AL_GAIN, this->_volume);
}

void dn::AudioListener::update()
{
	float position[] = { 0.0f, 0.0f, 0.0f };
	float orientation[] = { 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f };
	if (this->_transform)
	{
		glm::vec3 forward = this->_transform->forward();
		glm::vec3 up = this->_transform->up();

		position[0] = this->_transform->position().x;
		position[1] = this->_transform->position().y;
		position[2] = this->_transform->position().z;

		orientation[0] = forward.x;
		orientation[1] = forward.y;
		orientation[2] = forward.z;
		orientation[3] = up.x;
		orientation[4] = up.y;
		orientation[5] = up.z;
	}
	alListenerfv(AL_POSITION, position);
	alListenerfv(AL_ORIENTATION, orientation);
}
