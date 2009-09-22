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

#include <raumklang/FileSource.hpp>

namespace rk
{
	FileSource::FileSource() : DataSource()
	{
	}
	FileSource::~FileSource()
	{
	}

	bool FileSource::open(std::string filename)
	{
		file.open(filename.c_str(),
			std::ios_base::in | std::ios_base::binary);
		return file;
	}

	unsigned int FileSource::read(void *buffer, unsigned int length)
	{
		file.read((char*)buffer, length);
		return file.gcount();
	}
	bool FileSource::seek(int position, bool relative)
	{
		file.clear();
		if (relative)
			file.seekg(position, std::ios_base::cur);
		else
			file.seekg(position);
		return !file.bad();
	}
	unsigned int FileSource::tell()
	{
		return file.tellg();
	}
	bool FileSource::isSeekable()
	{
		return true;
	}

	unsigned int FileSource::getSize()
	{
		unsigned int position = file.tellg();
		file.seekg(0, std::ios::end);
		unsigned int size = file.tellg();
		file.seekg(position);
		return size;
	}
}
