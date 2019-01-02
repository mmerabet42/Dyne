#ifndef AUDIO_HPP
# define AUDIO_HPP

# include <string>
# include "allgl.hpp"
# include "ApplicationDependent.hpp"

namespace dn
{
	class Audio: public dn::ApplicationDependent
	{
	public:
		Audio(const std::string &p_path, const bool &p_forceMono = false);
		~Audio();

		SF_INFO fileInfo() const;
		std::string path() const;

		ALuint buffer() const;

		ALshort *samples() const;
		ALsizei nbSamples() const;

		void create();
		void destroy();

	private:
		SF_INFO _fileInfo;
		std::string _path;

		ALuint _buffer;

		ALshort *_samples;
		ALsizei _nbSamples;

		bool _forceMono;
	};
}

#endif // AUDIO_HPP
