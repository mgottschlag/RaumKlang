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

#ifndef _RAUMKLANG_HPP_INCLUDED_
#define _RAUMKLANG_HPP_INCLUDED_

#include <raumklang/SoundEngine.hpp>
#include <raumklang/SoundRecorder.hpp>

/**
 * \mainpage RaumKlang
 *
 * \section about About
 * RaumKlang is an easy-to-use, platform independent 3D sound engine. It is
 * highly modular and will support several backends, currently it only makes
 * use of the OpenAL sound library to output sound though. It has support for
 * both ogg vorbis and wav files and does not make any changes to the program's
 * main loop necessary as the sound engine runs in its own thread.
 *
 * \section design Design
 * \subsection overview Overview
 * The engine is centered around the rk::SoundEngine class which holds methods
 * to load sound sources and play sounds. Sounds are represented by the
 * rk::Sound class and get their data from rk::SoundSource which again gets
 * the raw stream from the underlying rk::SoundStream.
 * \subsection example Example
 * \code
 * #include <RaumKlang.hpp>
 * 
 * int main(int argc, char **argv)
 * {
 *     // Create sound engine
 *     rk::SoundEngine *soundengine = rk::SoundEngine::create();
 *     // Play an ogg vorbis file
 *     soundengine->play2D("helloworld.ogg");
 *     // Wait for a key hit
 *     getchar();
 *     // Destroy sound engine
 *     soundengine->destroy();
 *     return 0;
 * }
 * \endcode
 */

/**
 * Main namespace of the RaumKlang sound engine.
 */
namespace rk
{
}

#endif
