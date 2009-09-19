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

#ifndef _RAUMKLANG_SOUNDRECORDER_HPP_INCLUDED_
#define _RAUMKLANG_SOUNDRECORDER_HPP_INCLUDED_

#include <raumklang/SoundFormat.hpp>

#include <string>

namespace rk
{
	/**
	 * Class to capture sound from any sound input device.
	 */
	class SoundRecorder
	{
		public:
			/**
			 * Destroys the sound recorder. This is automatically called if the
			 * SoundEngine which was used to create this recorder is destroyed.
			 */
			virtual void destroy() = 0;

			/**
			 * Starts recording sound with the given format.
			 */
			virtual void startRecording(const SoundFormat &format) = 0;
			/**
			 * Stops recording.
			 */
			virtual void stopRecording() = 0;
			/**
			 * Returns a pointer to the recorded data. Can only be called when
			 * recording was stopped.
			 */
			virtual void *getRecordedData() = 0;
			/**
			 * Returns the number of recorded frames.
			 */
			virtual unsigned int getRecordedFrames() = 0;
			/**
			 * Clears the recorded data in order to start again with an empty
			 * buffer.
			 */
			virtual void clearRecordedData() = 0;

			/**
			 * Returns the number of the driver used for this recorder, e.g.
			 * "OpenAL".
			 */
			virtual std::string getDriverName() = 0;

			virtual ~SoundRecorder()
			{
			}
	};
}

#endif
