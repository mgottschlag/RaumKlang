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
#include "ScopedLock.hpp"

#include <raumklang/SoundStream.hpp>

#include <AL/al.h>

namespace rk
{
	static ALenum getOpenALFormat(const SoundFormat &format)
	{
		switch (format.channels)
		{
			case 1:
				switch (format.format)
				{
					case ESF_UnsignedByte:
						return AL_FORMAT_MONO8;
					case ESF_SignedWord:
						return AL_FORMAT_MONO16;
				}
			case 2:
				switch (format.format)
				{
					case ESF_UnsignedByte:
						return AL_FORMAT_STEREO8;
					case ESF_SignedWord:
						return AL_FORMAT_STEREO16;
				}
			default:
				printf("openal: Invalid number of channels.");
				return 0;
		}
	}

	SoundSourceOpenAL::SoundSourceOpenAL() : refcount(0), stream(0)
	{
	}
	SoundSourceOpenAL::~SoundSourceOpenAL()
	{
		if (stream)
			stream->drop();
	}

	bool SoundSourceOpenAL::init(std::string name, SoundStream *stream)
	{
		this->name = name;
		this->stream = stream;
		stream->grab();

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
		SoundFormat format = stream->getFormat();
		return getSize() * 1000 / format.samplerate;
	}

	void SoundSourceOpenAL::grab() const
	{
		ScopedLock lock(mutex);
		refcount++;
	}
	void SoundSourceOpenAL::drop() const
	{
		mutex.lock();
		refcount--;
		if (refcount == 0)
			delete this;
		else
			mutex.unlock();
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
		ScopedLock lock(mutex);
		// Change stream position if necessary
		if (position != stream->getPosition())
			stream->setPosition(position);
		// Read data
		char data[16384];
		SoundFormat format = stream->getFormat();
		unsigned int framecount = 16384 / format.getFrameSize();
		unsigned int framesread = stream->read(data, framecount);
		alBufferData(buffer, getOpenALFormat(format), data,
			framesread * format.getFrameSize(), format.samplerate);
		return framesread;
	}

	unsigned int SoundSourceOpenAL::getBuffer()
	{
		return 0;
	}
}
