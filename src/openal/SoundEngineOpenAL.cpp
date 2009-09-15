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

#include "SoundEngineOpenAL.hpp"
#include "ListenerOpenAL.hpp"
#include "SoundSourceOpenAL.hpp"
#include "SoundOpenAL.hpp"

#include <AL/alut.h>

namespace rk
{
	bool SoundEngineOpenAL::isSupported()
	{
		return true;
	}
	std::vector<SoundDevice> SoundEngineOpenAL::getDevices()
	{
		std::vector<SoundDevice> devices;
		devices.push_back(SoundDevice("default", "Default device."));
		return devices;
	}
	SoundEngine *SoundEngineOpenAL::create(std::string device)
	{
		SoundEngineOpenAL *engine = new SoundEngineOpenAL();
		if (!engine->init())
		{
			delete engine;
			return 0;
		}
		return engine;
	}

	bool SoundEngineOpenAL::init()
	{
		// Setup OpenAL
		// TODO: Properly select the device
		if (!alutInit(0, 0))
		{
			return false;
		}
		// Create listener
		listener = new ListenerOpenAL();
		// Add stream loaders
		initStreamLoaders();
		// Start update thread
		startUpdateThread();
		return true;
	}
	void SoundEngineOpenAL::destroy()
	{
		// Delete listener
		if (listener)
			delete listener;
		// TODO: Delete sounds and sources
		// Destroy OpenAL context
		alutExit();
		// Delete engine instance
		delete this;
	}

	std::string SoundEngineOpenAL::getDriverName()
	{
		return "OpenAL";
	}

	Listener *SoundEngineOpenAL::getListener()
	{
		return listener;
	}

	SoundSource *SoundEngineOpenAL::getSource(std::string filename)
	{
		// Get stream
		SoundStream *stream = getStream(filename);
		if (!stream)
		{
			printf("Could not load sound stream \"%s\".\n", filename.c_str());
			return 0;
		}
		// Create sound source
		// TODO: Cache and reuse sources
		SoundSourceOpenAL *source = new SoundSourceOpenAL();
		if (!source->init(filename, stream))
		{
			delete source;
			return 0;
		}
		return source;
	}

	Sound *SoundEngineOpenAL::play2D(SoundSource *source, bool looped, bool paused)
	{
		// Create sound
		SoundOpenAL *sound = new SoundOpenAL(this);
		if (!sound->init((SoundSourceOpenAL*)source))
		{
			delete sound;
			return 0;
		}
		// Start sound
		sound->setLooped(looped);
		sound->setPaused(paused);
		return sound;
	}
	Sound *SoundEngineOpenAL::play2D(std::string file, bool looped, bool paused)
	{
		// Get source
		SoundSource *source = getSource(file);
		if (!source)
			return 0;
		// Play sound
		return play2D(source, looped, paused);
	}
	Sound *SoundEngineOpenAL::play3D(SoundSource *source, bool looped, bool paused)
	{
		// Create sound
		SoundOpenAL *sound = new SoundOpenAL(this);
		if (!sound->init((SoundSourceOpenAL*)source))
		{
			delete sound;
			return 0;
		}
		// Start sound
		sound->setLooped(looped);
		sound->setPaused(paused);
		return sound;
	}
	Sound *SoundEngineOpenAL::play3D(std::string file, bool looped, bool paused)
	{
		// Get source
		SoundSource *source = getSource(file);
		if (!source)
			return 0;
		// Play sound
		return play3D(source, looped, paused);
	}

	bool SoundEngineOpenAL::update()
	{
		for (unsigned int i = 0; i < sounds.size(); i++)
		{
			sounds[i]->update();
		}
		return true;
	}


	void SoundEngineOpenAL::registerSoundUpdates(SoundOpenAL *sound)
	{
		sounds.push_back(sound);
	}
	void SoundEngineOpenAL::removeSoundUpdates(SoundOpenAL *sound)
	{
		// TODO: Different data structure for better performance
		for (unsigned int i = 0; i < sounds.size(); i++)
		{
			if (sounds[i] == sound)
			{
				sounds.erase(sounds.begin() + i);
				return;
			}
		}
	}

	SoundEngineOpenAL::~SoundEngineOpenAL()
	{
	}
	SoundEngineOpenAL::SoundEngineOpenAL()
	{
		listener = 0;
	}
}
