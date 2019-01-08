#include <iostream>
#include <iomanip>
#include <cstring>
#include <AL/al.h>
#include <AL/alc.h>
#include <sndfile.h>

int printError(const std::string &p_msg);

int main(int argc, char **argv)
{
	ALCdevice *device = alcOpenDevice(nullptr);
	if (!device)
		return (printError("Device failed to opened"));
	
	ALCcontext *context = alcCreateContext(device, nullptr);
	if (!context)
	{
		alcCloseDevice(device);
		return (printError("Failed to create context"));
	}

	if (!alcMakeContextCurrent(context))
	{
		alcMakeContextCurrent(nullptr);
		alcDestroyContext(context);
		alcCloseDevice(device);
		return (printError("Failed to make context current"));
	}

	SF_INFO fileInfos;
	SNDFILE *file = sf_open(argv[1], SFM_READ, &fileInfos);
	if (!file)
	{
		alcMakeContextCurrent(nullptr);
		alcDestroyContext(context);
		alcCloseDevice(device);
		return (printError("Failed to open wav file"));
	}

	ALsizei nbSamples = (ALsizei)(fileInfos.channels * fileInfos.frames);
	ALsizei samplerate = (ALsizei)fileInfos.samplerate;

	ALshort *samples = new ALshort[nbSamples];

	if (sf_read_short(file, samples, nbSamples) < nbSamples)
	{
		sf_close(file);
		delete[] samples;
		alcMakeContextCurrent(nullptr);
		alcDestroyContext(context);
		alcCloseDevice(device);
		return (printError("Failed to read samples from file"));
	}
	sf_close(file);

	ALenum format = (fileInfos.channels == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16);

	ALuint buffer;
	alGenBuffers(1, &buffer);
	alBufferData(buffer, format, samples, nbSamples * sizeof(ALshort), samplerate);

	ALuint source;
	alGenSources(1, &source);
	alSourcei(source, AL_BUFFER, buffer);
	alSourcei(source, AL_LOOPING, AL_TRUE);

	alSourcePlay(source);

	float xPos = 8.f;
	alSource3f(source, AL_POSITION, xPos, 0.f, 2.f);

	ALint status;
	do
	{
		ALfloat seconds = 0;
		alGetSourcef(source, AL_SEC_OFFSET, &seconds);
		std::cout << "\rListening ... " << std::fixed << std::setprecision(2) << seconds;

		xPos -= 0.00003f;
		alSource3f(source, AL_POSITION, xPos, 0.f, 2.f);

		alGetSourcei(source, AL_SOURCE_STATE, &status);
	} while (status == AL_PLAYING);

	alDeleteBuffers(1, &buffer);
	alSourcei(source, AL_BUFFER, 0);
	alDeleteSources(1, &source);

	delete[] samples;
	alcMakeContextCurrent(nullptr);
	alcDestroyContext(context);
	alcCloseDevice(device);
	return (0);
}

int printError(const std::string &p_msg)
{
	std::cout << p_msg << std::endl;
	return (0);
}
