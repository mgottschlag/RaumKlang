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
	class Listener
	{
		public:
			virtual ~Listener()
			{
			}

			virtual void setPosition(const Vector3F &position) = 0;
			virtual Vector3F getPosition() = 0;

			virtual void setOrientation(const Vector3F &orientation) = 0;
			virtual Vector3F getOrientation() = 0;

			virtual void setVelocity(const Vector3F &velocity) = 0;
			virtual Vector3F getVelocity() = 0;
	};
}

#endif
