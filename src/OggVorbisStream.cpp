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

#include "OggVorbisStream.hpp"

#include <ogg/ogg.h>
#include <vorbis/codec.h>
#include <vorbis/vorbisenc.h>
#include <vorbis/vorbisfile.h>
#include <iostream>

namespace rk
{
	// Wrapper functions to File class
	// TODO: Use proxy class here
	static size_t vorbisReadCallback(void *buffer, size_t size, size_t count, void *fileptr)
	{
		FILE *file = (FILE*)fileptr;
		return fread(buffer, size, count, file);
	}
	static int vorbisSeekCallback(void *fileptr, ogg_int64_t offset, int whence)
	{
		FILE *file = (FILE*)fileptr;
		return fseek(file, offset, whence);
	}
	static int vorbisCloseCallback(void *fileptr)
	{
		FILE *file = (FILE*)fileptr;
		return fclose(file);
	}
	static long vorbisTellCallback(void *fileptr)
	{
		FILE *file = (FILE*)fileptr;
		return ftell(file);
	}

	OggVorbisStream::OggVorbisStream() : SoundStream(), file(0), ovfile(0)
	{
	}
	OggVorbisStream::~OggVorbisStream()
	{
		if (ovfile)
		{
			ov_clear(ovfile);
			delete ovfile;
		}
	}

	bool OggVorbisStream::load(std::string filename)
	{
		// Open file
		file = fopen(filename.c_str(), "rb");
		if (!file)
		{
			printf("Could not open ogg vorbis file \"%s\".\n", filename.c_str());
			return false;
		}
		// Initialize file callbacks
		ov_callbacks callbacks;
		callbacks.read_func = vorbisReadCallback;
		callbacks.seek_func = vorbisSeekCallback;
		callbacks.close_func = vorbisCloseCallback;
		callbacks.tell_func = vorbisTellCallback;
		// Load file
		ovfile = new OggVorbis_File;
		int result = ov_open_callbacks(file, ovfile, 0, 0, callbacks);
		if(result < 0)
		{
			printf("Could not load ogg stream \"%s\".\n", filename.c_str());
			delete ovfile;
			ovfile = 0;
			return false;
		}
		// Read file info
		vorbis_info *vorbisinfo = ov_info(ovfile, -1);
		vorbis_comment *comment = ov_comment(ovfile, -1);
		std::cout
		<< "version         " << vorbisinfo->version         << "\n"
		<< "channels        " << vorbisinfo->channels        << "\n"
		<< "rate (hz)       " << vorbisinfo->rate            << "\n"
		<< "bitrate upper   " << vorbisinfo->bitrate_upper   << "\n"
		<< "bitrate nominal " << vorbisinfo->bitrate_nominal << "\n"
		<< "bitrate lower   " << vorbisinfo->bitrate_lower   << "\n"
		<< "bitrate window  " << vorbisinfo->bitrate_window  << "\n"
		<< "\n"
		<< "vendor " << comment->vendor << "\n";
		for(int i = 0; i < comment->comments; i++)
		std::cout << "   " << comment->user_comments[i] << "\n";
		std::cout << std::endl;
		if (vorbisinfo->channels == 2)
		{
			stereo = true;
		}
		else
		{
			stereo = false;
		}
		rate = vorbisinfo->rate;
		return true;
	}

	unsigned int OggVorbisStream::read(void *target, unsigned int count)
	{
		if (!ovfile)
			return 0;
		unsigned int size = 0;
		int section = 0;
		int result;
		char *data = (char*)target;
		// 16-bit samples
		unsigned int framesize = 2;
		// 2 channels
		if (stereo)
			framesize *= 2;
		count *= framesize;
		// Read data from file
		while(size < count)
		{
			result = ov_read(ovfile, data + size, count - size, 0, 2, 1, &section);
			if (result == 0)
			{
				// We are at the end of the file
				break;
			}
			else if (result < 0)
			{
				printf("Error while streaming ogg vorbis data.\n");
				return 0;
			}
			size += result;
		}
		return size / framesize;
	}
	bool OggVorbisStream::isSeekable()
	{
		return true;
	}
	void OggVorbisStream::setPosition(unsigned int position)
	{
		if (ov_pcm_seek(ovfile, position))
			printf("Warning: Could not seek (ogg vorbis stream).\n");
	}
	unsigned int OggVorbisStream::getPosition()
	{
		return ov_pcm_tell(ovfile);
	}
	SoundFormat OggVorbisStream::getFormat()
	{
		SoundFormat format;
		format.format = ESF_SignedWord;
		format.channels = stereo ? 2 : 1;
		format.samplerate = rate;
		return format;
	}

	unsigned int OggVorbisStream::getSize()
	{
		return ov_pcm_total(ovfile, -1);
	}
}
