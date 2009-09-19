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

#include <AL/al.h>
#include <AL/alut.h>

#include <raumklang/SoundFormat.hpp>

namespace rk
{
	static inline const char *getOpenALErrorString(ALenum error)
	{
		switch (error)
		{
			case AL_NO_ERROR:
				return "AL_NO_ERROR";
			case AL_INVALID_NAME:
				return "AL_INVALID_NAME";
			case AL_INVALID_ENUM:
				return "AL_INVALID_ENUM";
			case AL_INVALID_VALUE:
				return "AL_INVALID_VALUE";
			case AL_INVALID_OPERATION:
				return "AL_INVALID_OPERATION";
			case AL_OUT_OF_MEMORY:
				return "AL_OUT_OF_MEMORY";
			default:
				return "Unknown OpenAL error";
		}
	}

	static inline ALenum getOpenALFormat(const SoundFormat &format)
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
}
