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

#ifndef _RAUMKLANG_SOUNDDEVICE_HPP_INCLUDED_
#define _RAUMKLANG_SOUNDDEVICE_HPP_INCLUDED_

#include <string>

namespace rk
{
	/**
	 * Information about a single sound device.
	 */
	class SoundDevice
	{
		public:
			SoundDevice(const std::string &id, const std::string &description)
				: id(id), description(description)
			{
			}
			~SoundDevice()
			{
			}

			/**
			 * Returns the ID of the device which can be used with
			 * SoundEngine::create().
			 */
			const std::string &getID()
			{
				return id;
			}
			/**
			 * Returns a longer description of the device.
			 */
			const std::string &getDescription()
			{
				return description;
			}
		private:
			std::string id;
			std::string description;
	};
}

#endif
