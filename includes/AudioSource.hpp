#ifndef AUDIOSOURCE_HPP
# define AUDIOSOURCE_HPP

# include "allgl.hpp"
# include "Component.hpp"

namespace dn
{
	class Transform;
	class Audio;

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

		void play();

		void start();
		void update();

	private:
		dn::Transform *_transform;
		dn::Audio *_audioClip;

		ALuint _sourceId;

		bool _looping;
		float _volume;
		float _pitch;
	};
}

#endif // AUDIOSOURCE_HPP
