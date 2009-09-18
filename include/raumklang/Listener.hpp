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

#ifndef _RAUMKLANG_LISTENER_HPP_INCLUDED_
#define _RAUMKLANG_LISTENER_HPP_INCLUDED_

#include <raumklang/Vector3.hpp>

namespace rk
{
	/**
	 * Virtual ear of the sound engine.
	 */
	class Listener
	{
		public:
			virtual ~Listener()
			{
			}

			/**
			 * Sets the position of the listener. This only affects playback of
			 * 3D sounds.
			 */
			virtual void setPosition(const Vector3F &position) = 0;
			/**
			 * Returns the position of the listener.
			 */
			virtual Vector3F getPosition() = 0;

			/**
			 * Sets the orientation of the listener in euler angles.
			 */
			virtual void setOrientation(const Vector3F &orientation) = 0;
			/**
			 * Returns the orientation of the listener.
			 */
			virtual Vector3F getOrientation() = 0;

			/**
			 * Sets the velocity of the listener. This is used for effects like
			 * doppler effect.
			 */
			virtual void setVelocity(const Vector3F &velocity) = 0;
			/**
			 * Returns the velocity of the listener.
			 */
			virtual Vector3F getVelocity() = 0;
	};
}

#endif
