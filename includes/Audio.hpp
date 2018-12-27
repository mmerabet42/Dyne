#ifndef AUDIO_HPP
# define AUDIO_HPP

# include <string>
# include "allgl.hpp"

namespace dn
{
	class Audio
	{
	public:
		Audio(const std::string &p_path);
		~Audio();

		void create();

		SF_INFO fileInfo() const;
		std::string path() const;

		ALuint buffer() const;

		ALshort *samples() const;
		ALsizei nbSamples() const;

	private:
		SF_INFO _fileInfo;
		std::string _path;

		ALuint _buffer;

		ALshort *_samples;
		ALsizei _nbSamples;
	};
}

#endif // AUDIO_HPP
