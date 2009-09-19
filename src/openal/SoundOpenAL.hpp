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

#ifndef _RAUMKLANG_SOUNDOPENAL_HPP_INCLUDED_
#define _RAUMKLANG_SOUNDOPENAL_HPP_INCLUDED_

#include <raumklang/Sound.hpp>

#include "Mutex.hpp"

namespace rk
{
	class SoundSourceOpenAL;
	class SoundEngineOpenAL;

	class SoundOpenAL: public Sound
	{
		public:
			SoundOpenAL(SoundEngineOpenAL *engine);
			virtual ~SoundOpenAL();

			bool init(SoundSourceOpenAL *source, bool is3d);

			virtual void setPaused(bool paused);
			virtual bool isPaused();

			virtual void stop();
			virtual bool isStopped();

			virtual void setPosition(const Vector3F &position);
			virtual Vector3F getPosition();

			virtual void setVelocity(const Vector3F &velocity);
			virtual Vector3F getVelocity();

			virtual bool is3D();

			virtual void setVolume(float volume);
			virtual float getVolume();

			virtual void setLooped(bool looped);
			virtual bool isLooped();

			virtual void setPan(float pan);
			virtual float getPan();

			virtual void setPitch(float pitch);
			virtual float getPitch();

			virtual unsigned int getLength();
			virtual void setPlayPosition(unsigned int msecs);
			virtual unsigned int getPlayPosition();

			virtual void setStopEventReceiver(SoundStopEventReceiver *receiver);

			virtual SoundSource *getSoundSource();

			virtual void grab() const;
			virtual void drop() const;

			void update();

			void doStopCallback();
		private:
			SoundEngineOpenAL *engine;
			unsigned int sound;
			SoundSourceOpenAL *source;
			unsigned int buffers[3];
			unsigned int position;
			bool loaded;
			bool is3d;
			mutable int refcount;

			SoundStopEventReceiver *receiver;

			Mutex mutex;
	};
}

#endif
