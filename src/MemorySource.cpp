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

#include <raumklang/MemorySource.hpp>

#include <cstdlib>
#include <cstring>

namespace rk
{
	MemorySource::MemorySource(void *data, unsigned int size, bool copy,
		bool deletedata) : DataSource(), position(0)
	{
		if (copy)
		{
			this->data = malloc(size);
			memcpy(this->data, data, size);
			this->deletedata = true;
		}
		else
		{
			this->data = data;
			this->deletedata = deletedata;
		}
		this->size = size;
	}
	MemorySource::~MemorySource()
	{
	}

	unsigned int MemorySource::read(void *buffer, unsigned int length)
	{
		if (length > size - position)
			length = size - position;
		memcpy(buffer, (char*)data + position, length);
		return length;
	}
	bool MemorySource::seek(int position, bool relative)
	{
		if (relative)
			position += this->position;
		if (position > (int)this->size || position < 0)
			return false;
		this->position = position;
		return true;
	}
	unsigned int MemorySource::tell()
	{
		return position;
	}
	bool MemorySource::isSeekable()
	{
		return true;
	}

	unsigned int MemorySource::getSize()
	{
		return size;
	}
}
