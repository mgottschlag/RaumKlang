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

/*
 * This is the central herader of RaumKlang, you need to include this file
 * before using any functions from the library.
 */
#include <RaumKlang.hpp>

int main(int argc, char **argv)
{
	/*
	 * First we will create a sound engine with the default driver and all
	 * default settings.
	 */
	rk::SoundEngine *soundengine = rk::SoundEngine::create();
	/*
	 * We now load a simple sound from a wav file. We do not care whether the
	 * sound is streamed or buffered directly, the engine will do this for us.
	 */
	rk::Sound *sound = soundengine->play2D("media/rain.wav");
	/*
	 * The returned reference can be used to change the sound currently played.
	 * Note that the pointer gets invalid as soon as the sound stops. If we want
	 * to continue using the pointer then, we have to call sound.>grab() before
	 * that.
	 * For now we just enable looping.
	 */
	sound->setLooped(true);
	/*
	 * Wait for a key hit.
	 */
	getchar();
	/*
	 * SoundEngine::destroy() will delete all sounds, sound sources, open files
	 * and will close the sound driver for us.
	 */
	soundengine->destroy();
	return 0;
}
