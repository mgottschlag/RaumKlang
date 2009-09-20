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

#ifndef _RAUMKLANG_LOGGER_HPP_INCLUDED_
#define _RAUMKLANG_LOGGER_HPP_INCLUDED_

#include "ReferenceCounted.hpp"

#include <string>

namespace rk
{
	/**
	 * Importance of a log message.
	 */
	enum LogLevel
	{
		/**
		 * Debug information.
		 */
		ELL_Debug,
		/**
		 * General information.
		 */
		ELL_Information,
		/**
		 * Warning.
		 */
		ELL_Warning,
		/**
		 * Error.
		 */
		ELL_Error
	};
	/**
	 * Base class for all log file writers. If you want to supply your own
	 * logger, just implement setLogLevel() and writeLine(). A logger can be
	 * selected with SoundEngine::setLogger(). This class uses reference
	 * counting, do not forget to register your own reference if you do not
	 * want the logger to be deleted on SoundEngine::destroy().
	 */
	class Logger : public ReferenceCounted
	{
		public:
			virtual ~Logger()
			{
			}

			/**
			 * Sets the minimum log level. Log messages which are less important
			 * are ignored.
			 */
			virtual void setLogLevel(LogLevel level) = 0;

			/**
			 * Writes a line to the log, using printf-like formatting. This
			 * calls writeLine() after it has assembled the message. A newline
			 * is inserted after the message.
			 */
			void write(LogLevel level, const char *fmt, ...);
			/**
			 * Writes a string to the log. A newline is inserted after the
			 * message.
			 */
			virtual void writeLine(LogLevel level, std::string msg) = 0;
	};

	typedef SharedPointer<Logger> LoggerPointer;
}

#endif
