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
#include "ScopedLock.hpp"
#include "SoundRecorderOpenAL.hpp"
#include "OpenAL.hpp"
#include "PCMStream.hpp"
#include <raumklang/MemorySource.hpp>
#include <raumklang/FileSource.hpp>
#include <raumklang/FileLogger.hpp>
#include <raumklang/ConsoleLogger.hpp>


#include <AL/alc.h>
#include <cstring>

namespace rk
{
	bool SoundEngineOpenAL::isSupported()
	{
		return true;
	}
	std::vector<SoundDevice> SoundEngineOpenAL::getDevices()
	{
		// Get device list
		const char *devicelist = alcGetString(NULL, ALC_DEVICE_SPECIFIER);
		// Split list
		std::vector<SoundDevice> devices;
		while (*devicelist)
		{
			devices.push_back(SoundDevice(devicelist, devicelist));
			devicelist += strlen(devicelist) + 1;
		}
		return devices;
	}
	SoundEngine *SoundEngineOpenAL::create(std::string device)
	{
		SoundEngineOpenAL *engine = new SoundEngineOpenAL();
		if (!engine->init(device))
		{
			delete engine;
			return 0;
		}
		return engine;
	}

	bool SoundEngineOpenAL::init(std::string device)
	{
		// Create logger
		FileLogger *logger = new FileLogger;
		if (logger->init("RaumKlang.htm"))
		{
			setLogger(logger);
		}
		else
		{
			delete logger;
			setLogger(new ConsoleLogger());
		}
		// Get default device
		if (device == "")
		{
			device = alcGetString(0, ALC_DEFAULT_DEVICE_SPECIFIER);
		}
		// Setup OpenAL context
		ALCdevice *dev = alcOpenDevice(device.c_str());
		if (!dev)
			return false;
		ALCcontext *context = alcCreateContext(dev, 0);
		alcMakeContextCurrent(context);
		if (alcGetError(dev) != ALC_NO_ERROR)
			return false;
		// Startup message
		getLogger()->writeLine(ELL_Information, "RaumKlang 0.0.1 (OpenAL)");
		getLogger()->writeLine(ELL_Information,
			std::string("Device: ") + device);
		// Create listener
		listener = new ListenerOpenAL();
		// Add stream loaders
		initStreamLoaders();
		// Start update thread
		running = true;
		threadstopped = false;
		startUpdateThread();
		return true;
	}
	void SoundEngineOpenAL::destroy()
	{
		// Stop thread
		running = false;
		while (!threadstopped)
			usleep(1000);
		// Delete listener
		if (listener)
			delete listener;
		// Delete recorders
		while (recorders.size() != 0)
			recorders[0]->destroy();
		// Delete sources
		std::map<std::string, SoundSource*>::iterator it = sources.begin();
		while (it != sources.end())
		{
			it->second->drop();
			it++;
		}
		// Delete sounds
		for (unsigned int i = 0; i < sounds.size(); i++)
		{
			sounds[i]->drop();
		}
		sounds.clear();
		// Destroy OpenAL context
		unsigned int error = alGetError();
		if (error != AL_NO_ERROR)
		{
			getLogger()->write(ELL_Error, "AL error on exit: %s!\n",
				getOpenALErrorString(error));
		}
		ALCcontext *context = alcGetCurrentContext();
		ALCdevice *dev = alcGetContextsDevice(context);
		error = alcGetError(dev);
		if (error != AL_NO_ERROR)
		{
			getLogger()->writeLine(ELL_Error, "ALC error on exit!\n");
		}
		alcMakeContextCurrent(0);
		alcDestroyContext(context);
		alcCloseDevice(dev);
		// Delete engine instance
		delete this;
	}

	const char *SoundEngineOpenAL::getDriverName()
	{
		return "OpenAL";
	}

	Listener *SoundEngineOpenAL::getListener()
	{
		return listener;
	}

	SoundSource *SoundEngineOpenAL::getSource(std::string filename, bool reuse)
	{
		if (reuse)
		{
			// Look for cached source
			SoundSource *source = getCachedSource(filename);
			if (source)
				return source;
		}
		FileSource *source = new FileSource();
		if (!source->open(filename))
		{
			delete source;
			return 0;
		}
		return getSource(filename, source);
	}
	SoundSource *SoundEngineOpenAL::getSourcePCM(std::string filename,
		const SoundFormat &format)
	{
		FileSource *source = new FileSource();
		if (!source->open(filename))
		{
			delete source;
			return 0;
		}
		return getSourcePCM(filename, source, format);
	}
	SoundSource *SoundEngineOpenAL::getSource(std::string name, void *data,
		unsigned int size, bool reuse)
	{
		if (reuse)
		{
			// Look for cached source
			SoundSource *source = getCachedSource(name);
			if (source)
				return source;
		}
		MemorySource *source = new MemorySource(data, size);
		return getSource(name, source);
	}
	SoundSource *SoundEngineOpenAL::getSourcePCM(std::string name, void *data,
		unsigned int size, const SoundFormat &format)
	{
		MemorySource *source = new MemorySource(data, size);
		return getSourcePCM(name, source, format);
	}
	SoundSource *SoundEngineOpenAL::getSource(std::string name,
		DataSource *source, bool reuse)
	{
		if (reuse)
		{
			// Look for cached source
			SoundSource *source = getCachedSource(name);
			if (source)
				return source;
		}
		// Get stream
		SoundStream *stream = getStream(name, source);
		if (!stream)
		{
			getLogger()->write(ELL_Error,
				"Could not load sound stream \"%s\".\n", name.c_str());
			return 0;
		}
		// Create sound source
		// TODO: Cache and reuse sources
		SoundSourceOpenAL *soundsource = new SoundSourceOpenAL();
		if (!soundsource->init(name, stream))
		{
			delete soundsource;
			return 0;
		}
		if (reuse)
		{
			ScopedLock lock(mutex);
			// Add source to source list
			// TODO: Memory limit?
			soundsource->grab();
			sources.insert(std::pair<std::string, SoundSource*>(name,
				soundsource));
		}
		return soundsource;
	}
	SoundSource *SoundEngineOpenAL::getSourcePCM(std::string name,
		DataSource *source, const SoundFormat &format)
	{
		if (format.getFrameSize())
			return 0;
		// Get stream
		PCMStream *stream = new PCMStream(name, source, format);
		// Create sound source
		// TODO: Cache and reuse sources
		SoundSourceOpenAL *soundsource = new SoundSourceOpenAL();
		if (!soundsource->init(name, stream))
		{
			delete soundsource;
			return 0;
		}
		return soundsource;
	}

	Sound *SoundEngineOpenAL::play2D(SoundSource *source, bool looped,
		bool paused)
	{
		// Create sound
		SoundOpenAL *sound = new SoundOpenAL(this);
		if (!sound->init((SoundSourceOpenAL*)source, false))
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
		if (!sound->init((SoundSourceOpenAL*)source, true))
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

	void SoundEngineOpenAL::setVolume(float volume)
	{
		alListenerf(AL_GAIN, volume);
	}
	float SoundEngineOpenAL::getVolume()
	{
		float volume;
		alGetListenerf(AL_GAIN, &volume);
		return volume;
	}

	void SoundEngineOpenAL::setAllPaused(bool paused)
	{
		ScopedLock lock(mutex);
		for (unsigned int i = 0; i < sounds.size(); i++)
		{
			sounds[i]->setPaused(paused);
		}
	}
	void SoundEngineOpenAL::stopAll()
	{
		mutex.lock();
		std::vector<SoundOpenAL*> sounds = this->sounds;
		mutex.unlock();
		for (unsigned int i = 0; i < sounds.size(); i++)
		{
			sounds[i]->stop();
		}
	}

	std::vector<SoundDevice> SoundEngineOpenAL::getRecorderDevices()
	{
		if (!supportsCapture())
			return std::vector<SoundDevice>();
		// Get device list
		const char *devicelist = alcGetString(NULL,
			ALC_CAPTURE_DEVICE_SPECIFIER);
		// Split list
		std::vector<SoundDevice> devices;
		while (*devicelist)
		{
			devices.push_back(SoundDevice(devicelist, devicelist));
			devicelist += strlen(devicelist) + 1;
		}
		return devices;
	}
	SoundRecorder *SoundEngineOpenAL::createSoundRecorder(std::string device)
	{
		if (!supportsCapture())
			return 0;
		// Create recorder
		SoundRecorderOpenAL *recorder = new SoundRecorderOpenAL(this);
		if (!recorder->create(device))
		{
			delete recorder;
			return 0;
		}
		// Add recorder to the recorder list for updates
		recorders.push_back(recorder);
		return recorder;
	}

	bool SoundEngineOpenAL::update()
	{
		ScopedLock lock(mutex);
		for (unsigned int i = 0; i < sounds.size(); i++)
		{
			if (sounds[i]->isStopped())
			{
				// Remove stopped sounds
				sounds[i]->doStopCallback();
				sounds[i]->drop();
				sounds.erase(sounds.begin() + i);
				i--;
			}
			else
			{
				sounds[i]->update();
			}
		}
		for (unsigned int i = 0; i < recorders.size(); i++)
		{
			recorders[i]->update();
		}
		if (!running)
			threadstopped = true;
		return running;
	}

	void SoundEngineOpenAL::addSound(SoundOpenAL *sound)
	{
		ScopedLock lock(mutex);
		sounds.push_back(sound);
		sound->grab();
	}
	void SoundEngineOpenAL::removeSound(SoundOpenAL *sound)
	{
		ScopedLock lock(mutex);
		// TODO: Different data structure for better performance
		for (unsigned int i = 0; i < sounds.size(); i++)
		{
			if (sounds[i] == sound)
			{
				sound->drop();
				sounds.erase(sounds.begin() + i);
				return;
			}
		}
	}

	void SoundEngineOpenAL::removeSoundRecorder(SoundRecorderOpenAL *recorder)
	{
		ScopedLock lock(mutex);
		for (unsigned int i = 0; i < recorders.size(); i++)
		{
			if (recorders[i] == recorder)
			{
				recorders.erase(recorders.begin() + i);
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

	bool SoundEngineOpenAL::supportsCapture()
	{
		ALCcontext *context = alcGetCurrentContext();
		ALCdevice *dev = alcGetContextsDevice(context);
		return alcIsExtensionPresent(dev, "ALC_EXT_CAPTURE") == AL_TRUE;
	}

	SoundSource *SoundEngineOpenAL::getCachedSource(std::string name)
	{
		ScopedLock lock(mutex);
		// Look for the name in the map and return the source conntected to it
		std::map<std::string, SoundSource*>::iterator it = sources.find(name);
		if (it == sources.end())
			return 0;
		return it->second;
	}
}
