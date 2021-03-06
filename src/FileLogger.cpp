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

#include <raumklang/FileLogger.hpp>

namespace rk
{
	FileLogger::FileLogger() : Logger()
	{
	}
	FileLogger::~FileLogger()
	{
		if (file.is_open())
		{
			if (html)
			{
				// Write footer
				file << "</body></html>" << std::endl;
			}
		}
	}

	bool FileLogger::init(std::string filename, bool html)
	{
		this->html = html;
		// Open file
		file.open(filename.c_str());
		if (!file)
			return false;
		if (html)
		{
			// Write header
			// TODO: Can look better than this.
			file << "<html><head><title>RaumKlang log</title></head><body>" << std::endl;
		}
		return true;
	}

	void FileLogger::setLogLevel(LogLevel level)
	{
		this->level = level;
	}
	void FileLogger::writeLine(LogLevel level, std::string msg)
	{
		if (level < this->level)
			return;
		// Write line
		// TODO: Can look better than this.
		file << msg;
		if (html)
			file << "<br/>" << std::endl;
		else
			file << std::endl;
	}
}
