#ifndef DN_AUDIOSOURCE_HPP
# define DN_AUDIOSOURCE_HPP

# include "dn/allgl.hpp"
# include "dn/Component.hpp"
# include "dn/Codes.hpp"
# include "dn/Audio.hpp"

namespace dn
{
	class Transform;

	enum State {
		playing = DN_PLAYING,
		paused = DN_PAUSED,
		stopped = DN_STOPPED
	};

	class AudioSource: public dn::UComponent
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

#endif // DN_AUDIOSOURCE_HPP
