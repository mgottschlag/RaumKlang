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

#include "SoundRecorderOpenAL.hpp"
#include "SoundEngineOpenAL.hpp"
#include "OpenAL.hpp"
#include "ScopedLock.hpp"
#include <raumklang/SoundDataReceiver.hpp>

#include <AL/alc.h>
#include <cstdlib>

namespace rk
{
	SoundRecorderOpenAL::SoundRecorderOpenAL(SoundEngineOpenAL *engine)
		: engine(engine), device(0), recordeddata(0), recordedsize(0),
		receiver(0)
	{
	}
	SoundRecorderOpenAL::~SoundRecorderOpenAL()
	{
	}

	bool SoundRecorderOpenAL::create(std::string device)
	{
		// Get default device
		if (device == "")
		{
			device = alcGetString(NULL, ALC_CAPTURE_DEFAULT_DEVICE_SPECIFIER);
		}
		engine->getLogger()->write(ELL_Information, "Capture device: %s\n",
			device.c_str());
		devicename = device;
		return true;
	}

	void SoundRecorderOpenAL::destroy()
	{
		// Remove from recorder list
		engine->removeSoundRecorder(this);
		// Stop recording
		if (isRecording())
		{
			stopRecording();
		}
		clearRecordedData();
		// Delete recorder
		delete this;
	}

	bool SoundRecorderOpenAL::startRecording(const SoundFormat &format,
				SoundDataReceiver *receiver, bool buffering)
	{
		if (device)
			stopRecording();
		ScopedLock lock(mutex);
		// 250 ms buffer
		unsigned int buffersize = format.samplerate / 4 * format.getFrameSize();
		// Open device
		device = alcCaptureOpenDevice(devicename.c_str(), format.samplerate,
			getOpenALFormat(format), buffersize);
		if (!device)
			return false;
		// Start recording
		alcCaptureStart((ALCdevice*)device);
		this->format = format;
		this->receiver = receiver;
		if (!receiver)
			buffering = true;
		this->buffering = buffering;
		return true;
	}
	void SoundRecorderOpenAL::stopRecording()
	{
		if (!isRecording())
			return;
		ScopedLock lock(mutex);
		// Stop recording
		alcCaptureStop((ALCdevice*)device);
		// Grab remaining samples
		int samplesleft;
		alcGetIntegerv((ALCdevice*)device, ALC_CAPTURE_SAMPLES, 1,
			&samplesleft);
		if (samplesleft != 0)
		{
			unsigned int datasize = samplesleft * format.getFrameSize();
			recordeddata = realloc(recordeddata, recordedsize + datasize);
			alcCaptureSamples((ALCdevice*)device,
				(char*)recordeddata + recordedsize, samplesleft);
			if (receiver)
			{
				// Data callback
				receiver->onDataReceived((char*)recordeddata + recordedsize,
					samplesleft, format);
			}
			recordedsize += datasize;
			if (!buffering)
			{
				// Free buffer again at once
				free(recordeddata);
				recordeddata = 0;
				recordedsize = 0;
			}
		}
		// Close device
		alcCaptureCloseDevice((ALCdevice*)device);
		device = 0;
		receiver = 0;
	}
	void *SoundRecorderOpenAL::getRecordedData()
	{
		ScopedLock lock(mutex);
		if (isRecording())
			return 0;
		return recordeddata;
	}
	unsigned int SoundRecorderOpenAL::getRecordedFrames()
	{
		ScopedLock lock(mutex);
		return recordedsize / format.getFrameSize();
	}
	void SoundRecorderOpenAL::clearRecordedData()
	{
		ScopedLock lock(mutex);
		if (recordeddata)
			free(recordeddata);
		recordeddata = 0;
		recordedsize = 0;
	}
	bool SoundRecorderOpenAL::isRecording()
	{
		return device != 0;
	}

	std::string SoundRecorderOpenAL::getDriverName()
	{
		return "OpenAL";
	}

	void SoundRecorderOpenAL::update()
	{
		ScopedLock lock(mutex);
		if (!isRecording())
			return;
		// Get number of recorded samples
		int samplesleft;
		alcGetIntegerv((ALCdevice*)device, ALC_CAPTURE_SAMPLES, 1,
			&samplesleft);
		if (samplesleft > (int)format.samplerate / 8)
		{
			// If we have more than 125 ms, load them into the buffer
			unsigned int datasize = samplesleft * format.getFrameSize();
			recordeddata = realloc(recordeddata, recordedsize + datasize);
			alcCaptureSamples((ALCdevice*)device,
				(char*)recordeddata + recordedsize, samplesleft);
			if (receiver)
			{
				// Data callback
				receiver->onDataReceived((char*)recordeddata + recordedsize,
					samplesleft, format);
			}
			recordedsize += datasize;
			if (!buffering)
			{
				// Free buffer again at once
				free(recordeddata);
				recordeddata = 0;
				recordedsize = 0;
			}
		}
	}
}
