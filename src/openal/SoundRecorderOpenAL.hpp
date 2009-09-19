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

#ifndef _RAUMKLANG_SOUNDRECORDEROPENAL_HPP_INCLUDED_
#define _RAUMKLANG_SOUNDRECORDEROPENAL_HPP_INCLUDED_

#include <raumklang/SoundRecorder.hpp>

#include "Mutex.hpp"

namespace rk
{
	class SoundEngineOpenAL;

	class SoundRecorderOpenAL: public SoundRecorder
	{
		public:
			SoundRecorderOpenAL(SoundEngineOpenAL *engine);
			virtual ~SoundRecorderOpenAL();

			bool create(std::string device = "");

			virtual void destroy();

			virtual bool startRecording(const SoundFormat &format);
			virtual void stopRecording();
			virtual void *getRecordedData();
			virtual unsigned int getRecordedFrames();
			virtual void clearRecordedData();
			virtual bool isRecording();

			virtual std::string getDriverName();

			void update();
		private:
			SoundEngineOpenAL* engine;
			void *device;
			std::string devicename;

			void *recordeddata;
			unsigned int recordedsize;
			SoundFormat format;

			Mutex mutex;
	};
}

#endif
