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

#include "SoundOpenAL.hpp"
#include "SoundSourceOpenAL.hpp"
#include "SoundEngineOpenAL.hpp"
#include "ScopedLock.hpp"
#include "OpenAL.hpp"

namespace rk
{
	SoundOpenAL::SoundOpenAL(SoundEngineOpenAL *engine) : engine(engine),
		source(0), loaded(false)
	{
	}
	SoundOpenAL::~SoundOpenAL()
	{
		// Remove updates
		if (source && source->isStreamed())
			engine->removeSoundUpdates(this);
		if (source)
			source->drop();
		// Remove sound from global sound list
		engine->removeSound(this);
		// Delete OpenAL data
		if (loaded)
		{
			alDeleteSources(1, &sound);
			if (source && source->isStreamed())
			{
				alDeleteBuffers(3, buffers);
			}
			else
			{
				alDeleteBuffers(1, buffers);
			}
		}
	}

	bool SoundOpenAL::init(SoundSourceOpenAL *source)
	{
		this->source = source;
		source->grab();
		position = 0;
		// Create OpenAL source
		alGenSources(1, &sound);
		alSourcef(sound, AL_PITCH, 1.0f);
		alSourcef(sound, AL_GAIN, 1.0f);
		alSource3f(sound, AL_POSITION, 0, 0, 0);
		alSource3f(sound, AL_VELOCITY, 0, 0, 0);
		// Fill initial buffers
		if (source->isStreamed())
		{
			alGenBuffers(3, buffers);
			position = source->fillBuffer(buffers[0], 0);
			position += source->fillBuffer(buffers[1], position);
			position += source->fillBuffer(buffers[2], position);
			alSourceQueueBuffers(sound, 3, buffers);
			// Updates?
			engine->registerSoundUpdates(this);
		}
		else
		{
			alGenBuffers(1, buffers);
			// TODO
		}
		loaded = true;
		// Add sound to global sound list
		engine->addSound(this);
		return true;
	}

	void SoundOpenAL::setPaused(bool paused)
	{
		if (!paused)
			alSourcePlay(sound);
		else
			alSourcePause(sound);
	}
	bool SoundOpenAL::isPaused()
	{
		ALint state;
		alGetSourcei(sound, AL_SOURCE_STATE, &state);
		return state == AL_PAUSED;
	}

	void SoundOpenAL::stop()
	{
		alSourceStop(sound);
	}
	bool SoundOpenAL::isStopped()
	{
		ALint state;
		alGetSourcei(sound, AL_SOURCE_STATE, &state);
		return state == AL_STOPPED;
	}

	void SoundOpenAL::setPosition(const Vector3F &position)
	{
		alSource3f(sound, AL_POSITION, position.x, position.y, position.z);
	}
	Vector3F SoundOpenAL::getPosition()
	{
		Vector3F vel;
		alGetSource3f(sound, AL_POSITION, &vel.x, &vel.y, &vel.z);
		return vel;
	}

	void SoundOpenAL::setVelocity(const Vector3F &velocity)
	{
		alSource3f(sound, AL_VELOCITY, velocity.x, velocity.y, velocity.z);
	}
	Vector3F SoundOpenAL::getVelocity()
	{
		Vector3F vel;
		alGetSource3f(sound, AL_VELOCITY, &vel.x, &vel.y, &vel.z);
		return vel;
	}

	bool SoundOpenAL::is3D()
	{
	}

	void SoundOpenAL::setVolume(float volume)
	{
		alSourcef(sound, AL_GAIN, volume);
	}
	float SoundOpenAL::getVolume()
	{
		float volume;
		alGetSourcef(sound, AL_GAIN, &volume);
		return volume;
	}

	void SoundOpenAL::setLooped(bool looped)
	{
		alSourcei(sound, AL_LOOPING, looped ? AL_TRUE : AL_FALSE);
	}
	bool SoundOpenAL::isLooped()
	{
		ALenum looped;
		alGetSourcei(sound, AL_LOOPING, &looped);
		return looped == AL_TRUE;
	}

	void SoundOpenAL::setPan(float pan)
	{
	}
	float SoundOpenAL::getPan()
	{
	}

	unsigned int SoundOpenAL::getLength()
	{
	}
	void SoundOpenAL::setPlayPosition(unsigned int msecs)
	{
	}
	unsigned int SoundOpenAL::getPlayPosition()
	{
	}

	SoundSource *SoundOpenAL::getSoundSource()
	{
		return source;
	}

	void SoundOpenAL::update()
	{
		ScopedLock lock(mutex);
		if (source->isStreamed())
		{
			// Refill processed buffers buffers
			int processed;
			alGetSourcei(sound, AL_BUFFERS_PROCESSED, &processed);
			for (int i = 0; i < processed; i++)
			{
				unsigned int buffer;
				alSourceUnqueueBuffers(sound, 1, &buffer);
				unsigned int framesread = source->fillBuffer(buffer, position);
				if (framesread != 0)
				{
					position += framesread;
					alSourceQueueBuffers(sound, 1, &buffer);
				}
			}
		}
	}
}
