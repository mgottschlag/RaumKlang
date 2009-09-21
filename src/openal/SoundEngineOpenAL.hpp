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

#include "Mutex.hpp"

#include <vector>

namespace rk
{
	class SoundOpenAL;
	class SoundRecorderOpenAL;

	class SoundEngineOpenAL: public SoundEngine
	{
		public:
			static bool isSupported();
			static std::vector<SoundDevice> getDevices();
			static SoundEngine *create(std::string device = "");

			bool init(std::string device);
			virtual void destroy();

			virtual std::string getDriverName();

			virtual Listener *getListener();

			virtual SoundSource *getSource(std::string filename);
			virtual SoundSource *getSourcePCM(std::string filename,
				const SoundFormat &format);
			virtual SoundSource *getSource(std::string name, void *data,
				unsigned int size);
			virtual SoundSource *getSourcePCM(std::string name, void *data,
				unsigned int size, const SoundFormat &format);
			virtual SoundSource *getSource(std::string name, DataSource *source);
			virtual SoundSource *getSourcePCM(std::string name,
				DataSource *source, const SoundFormat &format);

			virtual Sound *play2D(SoundSource *source, bool looped = false,
				bool paused = false);
			virtual Sound *play2D(std::string file, bool looped = false,
				bool paused = false);
			virtual Sound *play3D(SoundSource *source, bool looped = false,
				bool paused = false);
			virtual Sound *play3D(std::string file, bool looped = false,
				bool paused = false);

			virtual void setVolume(float volume);
			virtual float getVolume();

			virtual void setAllPaused(bool paused);
			virtual void stopAll();

			virtual std::vector<SoundDevice> getRecorderDevices();
			virtual SoundRecorder *createSoundRecorder(std::string device = "");

			virtual bool update();

			void addSound(SoundOpenAL *sound);
			void removeSound(SoundOpenAL *sound);

			void removeSoundRecorder(SoundRecorderOpenAL *recorder);

			virtual ~SoundEngineOpenAL();
		private:
			SoundEngineOpenAL();

			bool supportsCapture();

			Listener *listener;
			std::vector<SoundOpenAL*> sounds;

			volatile bool running;
			volatile bool threadstopped;

			std::vector<SoundRecorderOpenAL*> recorders;

			Mutex mutex;
	};
}

#endif
