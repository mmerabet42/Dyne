#include "Audio.hpp"
#include "Application.hpp"

dn::Audio::Audio(const std::string &p_path)
	: _path(p_path), _fileInfo(), _buffer(0), _samples(nullptr), _nbSamples(0)
{
	dn::Application::addAudio(this);
}
dn::Audio::~Audio()
{
	delete this->_samples;
	alDeleteBuffers(1, &this->_buffer);
}

SF_INFO dn::Audio::fileInfo() const
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
	SNDFILE *file = sf_open(this->_path.c_str(), SFM_READ, &this->_fileInfo);
	this->_nbSamples = (ALsizei)(this->_fileInfo.channels * this->_fileInfo.frames);
	this->_samples = new ALshort[this->_nbSamples];

	sf_read_short(file, this->_samples, this->_nbSamples);
	sf_close(file);

	if (this->_fileInfo.channels == 2)
		this->_nbSamples /= 2;

	alGenBuffers(1, &this->_buffer);
	alBufferData(this->_buffer,
		AL_FORMAT_MONO16,
		this->_samples,
		this->_nbSamples * sizeof(ALshort),
		(ALsizei)this->_fileInfo.samplerate);
}
