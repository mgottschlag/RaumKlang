/*
Copyright (c) 2009, Mathias Gottschlag

Permission to use, copy, modify, and/or distribute this software for any
purpose with or without fee is hereby granted, provided that the above
copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#ifndef _RAUMKLANG_SOUNDENGINEOPENAL_HPP_INCLUDED_
#define _RAUMKLANG_SOUNDENGINEOPENAL_HPP_INCLUDED_

#include <raumklang/SoundEngine.hpp>

namespace rk
{
	class SoundEngineOpenAL: public SoundEngine
	{
		public:
			static bool isSupported();
			static std::vector<SoundDevice> getDevices();
			static SoundEngine *create(std::string device = "");

			bool init();
			virtual void destroy();

			virtual std::string getDriverName();

			virtual Listener *getListener();

			virtual SoundSource *getSource(std::string filename);

			virtual Sound *play2D(SoundSource *source, bool looped = false,
				bool paused = false);
			virtual Sound *play2D(std::string file, bool looped = false,
				bool paused = false);
			virtual Sound *play3D(SoundSource *source, bool looped = false,
				bool paused = false);
			virtual Sound *play3D(std::string file, bool looped = false,
				bool paused = false);

			virtual bool update();

			virtual ~SoundEngineOpenAL();
		private:
			SoundEngineOpenAL();

			Listener *listener;
	};
}

#endif
