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

	WavStream::WavStream() : SoundStream(), file(0)
	{
	}
	WavStream::~WavStream()
	{
		if (file)
			fclose((FILE*)file);
	}

	bool WavStream::load(std::string filename)
	{
		// Open file
		FILE *file = fopen(filename.c_str(), "rb");
		this->file = file;
		if (!file)
		{
			printf("Could not open wav file \"%s\".\n", filename.c_str());
			return false;
		}
		// Read header
		WavHeader header;
		if (fread((char*)&header, sizeof(WavHeader), 1, file) != 1)
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
		unsigned int bytesread = fread(target, framesize, count, (FILE*)file);
		position += bytesread / framesize;
		// Return number of samples read
		return bytesread / framesize;
	}
	bool WavStream::isSeekable()
	{
		return true;
	}
	void WavStream::setPosition(unsigned int position)
	{
		fseek((FILE*)file, ((int)this->position - position) * framesize,
			SEEK_CUR);
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
