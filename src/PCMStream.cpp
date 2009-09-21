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

#include "PCMStream.hpp"
#include <raumklang/DataSource.hpp>

#include <iostream>
#include <cstdio>

namespace rk
{
	PCMStream::PCMStream(std::string name, DataSource *source,
		const SoundFormat &format) : SoundStream(), source(source),
		format(format), position(0)
	{
		source->grab();
	}
	PCMStream::~PCMStream()
	{
		source->drop();
	}

	unsigned int PCMStream::read(void *target, unsigned int count)
	{
		// Read data
		unsigned int framesize = format.getFrameSize();
		unsigned int samplesread = source->read(target, count * framesize);
		samplesread /= framesize;
		position += samplesread;
		// Return number of samples read
		return samplesread;
	}
	bool PCMStream::isSeekable()
	{
		return source->isSeekable();
	}
	void PCMStream::setPosition(unsigned int position)
	{
		unsigned int framesize = format.getFrameSize();
		source->seek(((int)this->position - position) * framesize, true);
		this->position = position;
	}
	unsigned int PCMStream::getPosition()
	{
		return position;
	}
	SoundFormat PCMStream::getFormat()
	{
		return format;
	}

	unsigned int PCMStream::getSize()
	{
		unsigned int framesize = format.getFrameSize();
		return source->getSize() / framesize;
	}
}
