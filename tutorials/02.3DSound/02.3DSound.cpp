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

#include <RaumKlang.hpp>

#include <cstdlib>
#include <ctime>

int main(int argc, char **argv)
{
	/*
	 * Basic initializazion.
	 */
	rk::SoundEngine *soundengine = rk::SoundEngine::create();
	/*
	 * Background noise.
	 */
	rk::Sound *sound = soundengine->play2D("media/rain.wav");
	sound->setLooped(true);

	srand(time(0));
	for (unsigned int i = 0; i < 10; i++)
	{
		/*
		 * Wait some time.
		 */
		sleep(4 + rand() % 4);
		/*
		 * Play a 3D sound sound at a random position.
		 */
		rk::Sound *thunder = soundengine->play3D("media/thunder.ogg");
		thunder->setVolume(2.0);
		thunder->setPosition(rk::Vector3F(rand() % 10 - 5, 0, rand() % 10 - 5));
	}
	sleep(4);

	soundengine->destroy();
	return 0;
}
