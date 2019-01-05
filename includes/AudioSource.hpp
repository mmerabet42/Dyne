#ifndef AUDIOSOURCE_HPP
# define AUDIOSOURCE_HPP

# include "allgl.hpp"
# include "Component.hpp"
# include "Codes.hpp"

namespace dn
{
	class Transform;
	class Audio;

	enum State {
		playing = DN_PLAYING,
		paused = DN_PAUSED,
		stopped = DN_STOPPED
	};

	class AudioSource: public dn::Component
	{
	public:
		AudioSource(dn::Audio *p_audioClip = nullptr);
		~AudioSource();

		dn::Audio *audioClip() const;
		void setAudioClip(dn::Audio *p_audioClip);

		float volume() const;
		void setVolume(const float &p_volume, const bool &p_relative = false);

		bool looping() const;
		void setLooping(const bool &p_looping);

		float pitch() const;
		void setPitch(const float &p_pitch, const bool &p_relative = false);

		void start();
		void update();

		void play();
		void pause();
		void stop();

		dn::State state() const;

	private:
		dn::Transform *_transform;
		dn::Audio *_audioClip;

		ALuint _sourceId;

		bool _looping;
		float _volume;
		float _pitch;
		bool _played;
	};
}

#endif // AUDIOSOURCE_HPP
