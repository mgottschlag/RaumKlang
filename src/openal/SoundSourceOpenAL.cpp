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

#include "SoundSourceOpenAL.hpp"

#include <raumklang/SoundStream.hpp>

#include <AL/al.h>

namespace rk
{
	SoundSourceOpenAL::SoundSourceOpenAL()
	{
	}

	bool SoundSourceOpenAL::init(std::string name, SoundStream *stream)
	{
		this->name = name;
		this->stream = stream;

		return true;
	}

	void SoundSourceOpenAL::setStreamMode(StreamMode mode)
	{
	}
	StreamMode SoundSourceOpenAL::getStreamMode()
	{
		return ESM_Streamed;
	}

	bool SoundSourceOpenAL::isSeekable()
	{
		return stream->isSeekable();
	}

	unsigned int SoundSourceOpenAL::getLength()
	{
		return 0;
	}

	bool SoundSourceOpenAL::isStreamed()
	{
		return true;
	}

	unsigned int SoundSourceOpenAL::getSize()
	{
		return stream->getSize();
	}
	unsigned int SoundSourceOpenAL::fillBuffer(unsigned int buffer,
		unsigned int position)
	{
		char data[16384];
		// TODO: Format
		unsigned int size = stream->read(data, 4096) * 4;
		alBufferData(buffer, AL_FORMAT_STEREO16, data, size, 44100);
		return size;
	}

	unsigned int SoundSourceOpenAL::getBuffer()
	{
		return 0;
	}
}
