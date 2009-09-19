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

#ifndef _RAUMKLANG_SOUND_HPP_INCLUDED_
#define _RAUMKLANG_SOUND_HPP_INCLUDED_

#include <raumklang/Vector3.hpp>
#include <raumklang/ReferenceCounted.hpp>

namespace rk
{
	class SoundSource;
	class SoundStopEventReceiver;

	/**
	 * Main class for every 2D or 3D sound. This class uses reference counting.
	 * Additionally to the references the user creates and registers (via
	 * grab()), the engine registers one reference as long as the sound is
	 * played. As soon as it is stopped, this reference is dropped and if there
	 * are no user references, the sound is deleted.
	 */
	class Sound : public ReferenceCountedBase
	{
		public:
			virtual ~Sound()
			{
			}

			/**
			 * Function to pause/resume a sound.
			 */
			virtual void setPaused(bool paused) = 0;
			/**
			 * Returns true, if the sound is currently paused.
			 */
			virtual bool isPaused() = 0;

			/**
			 * Stops playback. If no references to this sound are left, the
			 * class instance is deleted.
			 */
			virtual void stop() = 0;
			/**
			 * Returns true, if the sound was stopped (either by stop() or
			 * because the end of the sound stream was reached) but there are
			 * references to the class left.
			 */
			virtual bool isStopped() = 0;

			/**
			 * Sets the position of the sound emitter. This only works with
			 * 3D sounds.
			 *
			 * @todo Currently, this only works with mono sounds!
			 */
			virtual void setPosition(const Vector3F &position) = 0;
			/**
			 * Returns the position of the sound emitter. This only works with
			 * 3D sounds.
			 */
			virtual Vector3F getPosition() = 0;

			/**
			 * Sets the velocity of the sound emitter. This only works with
			 * 3D sounds. The velocity is used for effects like doppler effect.
			 */
			virtual void setVelocity(const Vector3F &velocity) = 0;
			/**
			 * Returns the velocity of the sound emitter. This only works with
			 * 3D sounds.
			 */
			virtual Vector3F getVelocity() = 0;

			/**
			 * Returns true if the sound was loaded as a 3D sound.
			 */
			virtual bool is3D() = 0;

			/**
			 * Sets the volume of a sound.
			 * @param volume Number between 0.0 and 1.0 specifying how loud the
			 * sound is played.
			 */
			virtual void setVolume(float volume) = 0;
			/**
			 * Returns the current volume of the sound.
			 */
			virtual float getVolume() = 0;

			/**
			 * Sets whether the sound starts again at the beginning when the
			 * end of the stream is reched. Does only work with streams which
			 * support seeking.
			 */
			virtual void setLooped(bool looped) = 0;
			/**
			 * Returns whether the sound is looped.
			 */
			virtual bool isLooped() = 0;

			/**
			 * Sets the panning of the sound. 1.0 means right, -1.0 means left.
			 */
			virtual void setPan(float pan) = 0;
			/**
			 * Returns the panning of the sound.
			 */
			virtual float getPan() = 0;

			/**
			 * Returns the length of the sound stream.
			 */
			virtual unsigned int getLength() = 0;
			/**
			 * Sets the current position in the stream in milliseconds. Does not
			 * work with streams which do not support seeking.
			 */
			virtual void setPlayPosition(unsigned int msecs) = 0;
			/**
			 * Returns the current position in the stream in milliseconds.
			 */
			virtual unsigned int getPlayPosition() = 0;

			/**
			 * Sets the stop event receiver for this sound. Sound stop events
			 * are triggered every time a sound stops playing.
			 */
			virtual void setStopEventReceiver(SoundStopEventReceiver *receiver) = 0;

			/**
			 * Returns the sound source connected to this sound.
			 */
			virtual SoundSource *getSoundSource() = 0;
	};
}

#endif
