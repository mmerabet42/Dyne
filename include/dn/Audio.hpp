#ifndef DN_AUDIO_HPP
# define DN_AUDIO_HPP

# include <string>
# include "dn/allgl.hpp"
# include "dr_wav.h"
# include "dn/ApplicationDependent.hpp"

namespace dn
{
	class Audio: public dn::ApplicationDependent
	{
	public:
		Audio(const std::string &p_path, const bool &p_forceMono = false);
		~Audio();

		drwav fileInfo() const;
		std::string path() const;

		ALuint buffer() const;

		ALshort *samples() const;
		ALsizei nbSamples() const;

		void create();
		void destroy();

	private:
		drwav _fileInfo;
		std::string _path;

		ALuint _buffer;

		ALshort *_samples;
		ALsizei _nbSamples;

		bool _forceMono;
	};
}

#endif // DN_AUDIO_HPP
