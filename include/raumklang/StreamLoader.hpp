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

#ifndef _RAUMKLANG_STREAMLOADER_HPP_INCLUDED_
#define _RAUMKLANG_STREAMLOADER_HPP_INCLUDED_

#include <string>

namespace rk
{
	class SoundStream;
	class DataSource;

	class StreamLoader
	{
		public:
			virtual SoundStream *open(std::string name, DataSource *source) = 0;
			virtual bool isExtensionSupported(std::string extension) = 0;
			virtual std::string getSupportedExtensions() = 0;

			virtual ~StreamLoader()
			{
			}
	};
}

#endif
