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

#ifndef _RAUMKLANG_SOUNDSOURCEOPENAL_HPP_INCLUDED_
#define _RAUMKLANG_SOUNDSOURCEOPENAL_HPP_INCLUDED_

#include <raumklang/SoundSource.hpp>

#include "Mutex.hpp"

namespace rk
{
	class SoundStream;

	class SoundSourceOpenAL : public SoundSource
	{
		public:
			SoundSourceOpenAL();
			virtual ~SoundSourceOpenAL();

			bool init(std::string name, SoundStream *stream);

			virtual void setStreamMode(StreamMode mode);
			virtual StreamMode getStreamMode();

			virtual bool isSeekable();

			virtual unsigned int getLength();

			virtual void grab() const;
			virtual void drop() const;

			bool isStreamed();

			unsigned int getSize();
			unsigned int fillBuffer(unsigned int buffer,
				unsigned int position);

			unsigned int getBuffer();
		private:
			mutable int refcount;
			SoundStream *stream;
			bool buffered;
			unsigned int buffer;

			Mutex mutex;
	};
}

#endif
