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

#ifndef _RAUMKLANG_FILESOURCE_HPP_INCLUDED_
#define _RAUMKLANG_FILESOURCE_HPP_INCLUDED_

#include <raumklang/DataSource.hpp>

#include <fstream>

namespace rk
{
	/**
	 * Data source which reads from a file.
	 */
	class FileSource : public DataSource
	{
		public:
			/**
			 *Constructor.
			 */
			FileSource();
			virtual ~FileSource();

			/**
			 * Opens a file to read data from.
			 * @param filename Path to the file.
			 * @return True, if the file could be opened successfully.
			 */
			bool open(std::string filename);

			virtual unsigned int read(void *buffer, unsigned int length);
			virtual bool seek(int position, bool relative = false);
			virtual unsigned int tell();
			virtual bool isSeekable();

			virtual unsigned int getSize();
		private:
			std::ifstream file;
	};
}

#endif
