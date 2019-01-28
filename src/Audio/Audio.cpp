#include "dn/Audio.hpp"
#define DR_WAV_IMPLEMENTATION
#include "dr_wav.h"
#include "dn/Application.hpp"

dn::Audio::Audio(const std::string &p_path, const bool &p_forceMono)
	: _path(p_path), _fileInfo(), _buffer(0), _samples(nullptr), _nbSamples(0),
	_forceMono(p_forceMono), ApplicationDependent()
{
	dn::Application::addDependent(this);
}
dn::Audio::~Audio()
{
	dn::Application::destroyDependent(this);
}

drwav dn::Audio::fileInfo() const
{
	return (this->_fileInfo);
}

std::string dn::Audio::path() const
{
	return (this->_path);
}

ALuint dn::Audio::buffer() const
{
	return (this->_buffer);
}

ALshort *dn::Audio::samples() const
{
	return (this->_samples);
}

ALsizei dn::Audio::nbSamples() const
{
	return (this->_nbSamples);
}

void dn::Audio::create()
{
	if (this->_buffer)
		return ;
	if (!drwav_init_file(&this->_fileInfo, this->_path.c_str()))
		return ;
	this->_nbSamples = (ALsizei)(this->_fileInfo.channels * this->_fileInfo.totalPCMFrameCount);
	this->_samples = new ALshort[this->_nbSamples];

	drwav_read_pcm_frames_s16(&this->_fileInfo, this->_fileInfo.totalPCMFrameCount, this->_samples);
	drwav_uninit(&this->_fileInfo);
	ALenum format;
	if (this->_fileInfo.channels == 1)
		format = AL_FORMAT_MONO16;
	else if (this->_forceMono)
	{
		format = AL_FORMAT_MONO16;
		this->_nbSamples /= 2;
	}
	else
		format = AL_FORMAT_STEREO16;

	alGenBuffers(1, &this->_buffer);
	alBufferData(this->_buffer,
		format,
		this->_samples,
		this->_nbSamples * sizeof(ALshort),
		(ALsizei)this->_fileInfo.sampleRate);
}

void dn::Audio::destroy()
{
	delete[] this->_samples;
	alDeleteBuffers(1, &this->_buffer);
}
