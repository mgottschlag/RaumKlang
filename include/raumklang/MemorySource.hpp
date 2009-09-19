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

#ifndef _RAUMKLANG_MEMORYSOURCE_HPP_INCLUDED_
#define _RAUMKLANG_MEMORYSOURCE_HPP_INCLUDED_

#include <raumklang/DataSource.hpp>

#include <fstream>

namespace rk
{
	/**
	 * Data source which reads directly from a memory buffer.
	 */
	class MemorySource : public DataSource
	{
		public:
			/**
			 * Constructor.
			 * @param data Data buffer to read from.
			 * @param size Size of the data buffer.
			 * @param copy If set to true, the class creates a copy of the data,
			 * if not, it works with the original buffer.
			 * @param deletedata If set to true, the class will delete the
			 * buffer with free() when it does not need it any more. If copy
			 * is set to true, this parameter is always assumed to be true as
			 * the class then always has the full ownership of the data. Note
			 * that you have to care about deleting the data on your own usually
			 * if you specify false here in order to prevent memory leaks!
			 */
			MemorySource(void *data, unsigned int size, bool copy = true,
				bool deletedata = true);
			virtual ~MemorySource();

			virtual unsigned int read(void *buffer, unsigned int length);
			virtual bool seek(int position, bool relative = false);
			virtual unsigned int tell();
			virtual bool isSeekable();

			virtual unsigned int getSize();
		private:
			void *data;
			unsigned int size;
			bool deletedata;
			unsigned int position;
	};
}

#endif
