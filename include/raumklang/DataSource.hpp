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

#ifndef _RAUMKLANG_DATASOURCE_HPP_INCLUDED_
#define _RAUMKLANG_DATASOURCE_HPP_INCLUDED_

#include <raumklang/ReferenceCounted.hpp>

namespace rk
{
	/**
	 * General source for sound data. Can be a file, a memory buffer or even
	 * a network stream.
	 */
	class DataSource : public ReferenceCounted
	{
		public:
			virtual ~DataSource()
			{
			}

			/**
			 * Reads some data.
			 * @param buffer Buffer to enough allocated data to hold the
			 * specified number of bytes.
			 * @param length Number of bytes to be read.
			 * @return Number of bytes actually read. Can be less than length
			 * if not as much data could be read, can even be 0 if for example
			 * the end of the file has been reached.
			 */
			virtual unsigned int read(void *buffer, unsigned int length) = 0;
			/**
			 * Changes the position in the data source. Check that isSeekable()
			 * returns true before using this function!
			 * @param position Absolute or relative offset to change to.
			 * @param relative If set to true, position is relative to the
			 * current reading position, else it is an absolute value starting
			 * at the beginning of the stream.
			 * @return Returns true if the position has successfully been
			 * changed.
			 */
			virtual bool seek(int position, bool relative = false) = 0;
			/**
			 * Returns the current reading position in the stream. Can also be
			 * 0 if the data source does not support seeking.
			 */
			virtual unsigned int tell() = 0;
			/**
			 * Returns true if the data source supports seeking.
			 */
			virtual bool isSeekable() = 0;

			/**
			 * Returns the size of the data source, or 0 if the size is not
			 * known (for example for network streams).
			 */
			virtual unsigned int getSize() = 0;
	};
}

#endif
