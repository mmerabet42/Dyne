#ifndef AUDIOLISTENER_HPP
# define AUDIOLISTENER_HPP

# include "Component.hpp"

namespace dn
{
	class Transform;

	class AudioListener: public dn::UComponent
	{
	public:
		AudioListener();

		float volume() const;
		void setVolume(const float &p_volume, const bool &p_relative = false);

		void start();
		void update();
	private:
		dn::Transform *_transform;

		bool _started;
		float _volume;
	};
}

#endif // AUDIOLISTENER_HPP
