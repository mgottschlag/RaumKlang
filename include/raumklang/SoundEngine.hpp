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

#ifndef _RAUMKLANG_SOUNDENGINE_HPP_INCLUDED_
#define _RAUMKLANG_SOUNDENGINE_HPP_INCLUDED_

#include <raumklang/SoundDriver.hpp>
#include <raumklang/SoundDevice.hpp>

#include <vector>

namespace rk
{
	class Listener;
	class Sound;
	class SoundSource;
	class StreamLoader;
	class SoundStream;

	class SoundEngine
	{
		public:
			static std::vector<SoundDriver> getSupportedDrivers();
			static std::vector<SoundDevice> getDevices(SoundDriver driver = ESD_AutoDetect);
			static SoundEngine *create(SoundDriver driver = ESD_AutoDetect,
				std::string device = "");

			virtual void destroy() = 0;

			virtual std::string getDriverName() = 0;

			virtual Listener *getListener() = 0;

			virtual SoundSource *getSource(std::string filename) = 0;

			virtual Sound *play2D(SoundSource *source, bool looped = false,
				bool paused = false) = 0;
			virtual Sound *play2D(std::string file, bool looped = false,
				bool paused = false) = 0;
			virtual Sound *play3D(SoundSource *source, bool looped = false,
				bool paused = false) = 0;
			virtual Sound *play3D(std::string file, bool looped = false,
				bool paused = false) = 0;

			void registerStreamLoader(StreamLoader *loader);

			virtual bool update() = 0;

			virtual ~SoundEngine()
			{
			}
		protected:
			void startUpdateThread();

			void initStreamLoaders();
			SoundStream *getStream(std::string filename);
		private:
			std::vector<StreamLoader*> loaders;
	};
}

#endif
