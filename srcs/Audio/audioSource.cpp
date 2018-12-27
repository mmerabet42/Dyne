#include "AudioSource.hpp"
#include "Audio.hpp"
#include "Transform.hpp"
#include "Object.hpp"

dn::AudioSource::AudioSource(dn::Audio *p_audioClip)
	: Component("AudioSource"),
	_audioClip(p_audioClip), _transform(nullptr), _sourceId(0),
	_looping(false), _volume(1.f), _pitch(1.f)
{

}
dn::AudioSource::~AudioSource()
{
	alDeleteSources(1, &this->_sourceId);
}

dn::Audio *dn::AudioSource::audioClip() const
{
	return (this->_audioClip);
}

void dn::AudioSource::setAudioClip(dn::Audio *p_audioClip)
{
	this->_audioClip = p_audioClip;
	if (this->_sourceId)
		alSourcei(this->_sourceId, AL_BUFFER, p_audioClip->buffer());
}

float dn::AudioSource::volume() const { return (this->_volume); }
void dn::AudioSource::setVolume(const float &p_volume, const bool &p_relative)
{
	if (p_relative)
		this->_volume += p_volume;
	else
		this->_volume = p_volume;
	if (this->_volume < 0.0f)
		this->_volume = 0.0f;

	if (this->_sourceId)
		alSourcef(this->_sourceId, AL_GAIN, this->_volume);
}

bool dn::AudioSource::looping() const { return (this->_looping); }
void dn::AudioSource::setLooping(const bool &p_looping)
{
	this->_looping = p_looping;
	if (this->_sourceId)
		alSourcei(this->_sourceId, AL_LOOPING, p_looping);
}

float dn::AudioSource::pitch() const { return (this->_pitch); }
void dn::AudioSource::setPitch(const float &p_pitch, const bool &p_relative)
{
	if (p_relative)
		this->_pitch += p_pitch;
	else
		this->_pitch = p_pitch;
	if (this->_pitch < 0.0f)
		this->_pitch = 0.0f;

	if (this->_sourceId)
		alSourcei(this->_sourceId, AL_PITCH, this->_pitch);
}

void dn::AudioSource::start()
{
	this->_transform = this->object()->getComponent<dn::Transform>();
	alGenSources(1, &this->_sourceId);
	if (this->_audioClip)
		alSourcei(this->_sourceId, AL_BUFFER, this->_audioClip->buffer());
	alSourcei(this->_sourceId, AL_LOOPING, this->_looping);
	alSourcef(this->_sourceId, AL_GAIN, this->_volume);
	alSourcef(this->_sourceId, AL_PITCH, this->_pitch);
	this->update();
}

void dn::AudioSource::update()
{
	float position[] = { 0.0f, 0.0f, 0.0f };
	if (this->_transform)
	{
		position[0] = this->_transform->position().x;
		position[1] = this->_transform->position().y;
		position[2] = this->_transform->position().z;
	}
	alSourcefv(this->_sourceId, AL_POSITION, position);
}

void dn::AudioSource::play()
{
	if (this->_sourceId)
		alSourcePlay(this->_sourceId);
}
