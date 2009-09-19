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

#include <raumklang/SoundEngine.hpp>

#include "openal/SoundEngineOpenAL.hpp"
#include "OggVorbisLoader.hpp"
#include "WavLoader.hpp"

#include <pthread.h>

namespace rk
{
	static void *startThread(void *engine)
	{
		while (1)
		{
			// Exiting from the loop
			if (!((SoundEngine*)engine)->update())
				break;
			usleep(5000);
		}
		return 0;
	}
	std::vector<SoundDriver> SoundEngine::getSupportedDrivers()
	{
		std::vector<SoundDriver> drivers;
		drivers.push_back(ESD_OpenAL);
		return drivers;
	}
	std::vector<SoundDevice> SoundEngine::getDevices(SoundDriver driver)
	{
		switch (driver)
		{
			case ESD_OpenAL:
				return SoundEngineOpenAL::getDevices();
			default:
				return std::vector<SoundDevice>();
		}
	}
	SoundEngine *SoundEngine::create(SoundDriver driver, std::string device)
	{
		switch (driver)
		{
			case ESD_OpenAL:
				return SoundEngineOpenAL::create(device);
			case ESD_AutoDetect:
				// TODO
				return SoundEngineOpenAL::create(device);
			default:
				return 0;
		}
	}

	void SoundEngine::registerStreamLoader(StreamLoader *loader)
	{
		loaders.push_back(loader);
	}

	void SoundEngine::startUpdateThread()
	{
		pthread_t thread;
		pthread_create(&thread, NULL, startThread, (void*)this);
	}

	void SoundEngine::initStreamLoaders()
	{
		registerStreamLoader(&OggVorbisLoader::get());
		registerStreamLoader(&WavLoader::get());
	}
	SoundStream *SoundEngine::getStream(std::string name, DataSource *source)
	{
		// Get the extension
		if (name.rfind(".") == std::string::npos)
			return 0;
		std::string extension = name.substr(name.rfind(".") + 1);
		// Try all stream loaders
		for (unsigned int i = 0; i < loaders.size(); i++)
		{
			if (loaders[i]->isExtensionSupported(extension))
			{
				SoundStream *stream = loaders[i]->open(name, source);
				// If the stream could not be loaded, try other loaders
				if (stream)
					return stream;
			}
		}
		return 0;
	}
}
