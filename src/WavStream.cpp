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

#include "WavStream.hpp"
#include <raumklang/DataSource.hpp>

#include <iostream>
#include <cstdio>

namespace rk
{
	#ifdef MSC_VER
	#pragma pack(push, 1)
	#endif
	struct WavHeader
	{
		// Wave header
		uint32_t rifftag;
		uint32_t filesize;
		uint32_t wavetag;
		// Format chunk
		uint32_t fmttag;
		uint32_t fmtsize;
		uint16_t format;
		uint16_t channels;
		uint32_t samplerate;
		uint32_t bytespersecond;
		uint16_t blockalign;
		uint16_t bitspersample;
		// Data chunk
		uint32_t datatag;
		uint32_t datasize;
	#ifdef MSC_VER
	};
	#pragma pack(pop)
	#else
	} __attribute((packed));
	#endif

	WavStream::WavStream() : SoundStream(), source(0)
	{
	}
	WavStream::~WavStream()
	{
		if (source)
			source->drop();
	}

	bool WavStream::load(std::string name, DataSource *source)
	{
		this->source = source;
		source->grab();
		// Read header
		WavHeader header;
		if (source->read(&header, sizeof(WavHeader)) != sizeof(WavHeader))
		{
			printf("Could not read WAV header.\n");
			return false;
		}
		// TODO: Validate header
		// Get format information
		if (header.bitspersample == 8)
			format.format = ESF_UnsignedByte;
		else if (header.bitspersample == 16)
			format.format = ESF_SignedWord;
		else
			return false;
		format.channels = header.channels;
		format.samplerate = header.samplerate;
		framesize = format.channels * header.bitspersample / 8;
		// Stream state
		size = header.datasize / framesize;
		position = 0;
		return true;
	}

	unsigned int WavStream::read(void *target, unsigned int count)
	{
		// Read data
		unsigned int samplesread = source->read(target, count * framesize);
		samplesread /= framesize;
		position += samplesread;
		// Return number of samples read
		return samplesread;
	}
	bool WavStream::isSeekable()
	{
		return source->isSeekable();
	}
	void WavStream::setPosition(unsigned int position)
	{
		source->seek(((int)this->position - position) * framesize, true);
		this->position = position;
	}
	unsigned int WavStream::getPosition()
	{
		return position;
	}
	SoundFormat WavStream::getFormat()
	{
		return format;
	}

	unsigned int WavStream::getSize()
	{
		return size;
	}
}
