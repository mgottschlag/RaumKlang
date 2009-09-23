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

#include <RaumKlang.h>
#include <RaumKlang.hpp>

#include <cstdlib>
#include <cstring>

struct rkiSoundEngine
{
	rk::SoundEngine *engine;
};

static rk::SoundFormat getFormat(rkSoundFormat format)
{
	return rk::SoundFormat(format.channels, format.samplerate,
		(rk::SampleFormat)format.format);
}

rkSoundEngine rkSoundEngineCreate(rkSoundDriver driver, const char *device)
{
	// Create engine
	rk::SoundEngine *engine = rk::SoundEngine::create((rk::SoundDriver)driver,
		device);
	if (!engine)
		return 0;
	// Create container struct
	rkSoundEngine container = (rkSoundEngine)malloc(sizeof(rkiSoundEngine*));
	memset(container, 0, sizeof(rkiSoundEngine));
	container->engine = engine;
	return container;
}
void rkSoundEngineDestroy(rkSoundEngine engine)
{
	if (!engine)
		return;
	engine->engine->destroy();
	free(engine);
}
const char *rkSoundEngineGetDriverName(rkSoundEngine engine)
{
	return engine->engine->getDriverName();
}
rkListener rkSoundEngineGetListener(rkSoundEngine engine)
{
	return engine->engine->getListener();
}
rkSoundSource rkSoundEngineGetSourceFromFile(rkSoundEngine engine,
	const char *filename, int reuse)
{
	return engine->engine->getSource(filename, reuse);
}
rkSoundSource rkSoundEngineGetSourcePCMFromFile(rkSoundEngine engine,
	const char *filename, rkSoundFormat format)
{
	return engine->engine->getSourcePCM(filename, getFormat(format));
}
rkSoundSource rkSoundEngineGetSource(rkSoundEngine engine,
	const char *name, void *data, unsigned int size, int reuse)
{
	return engine->engine->getSource(name, data, size, reuse);
}
rkSoundSource rkSoundEngineGetSourcePCM(rkSoundEngine engine,
	const char *name, void *data, unsigned int size, rkSoundFormat format)
{
	return engine->engine->getSourcePCM(name, data, size, getFormat(format));
}
rkSound rkSoundEnginePlay2D(rkSoundEngine engine, rkSoundSource source,
	int looped, int paused)
{
	return engine->engine->play2D((rk::SoundSource*)source, looped, paused);
}
rkSound rkSoundEnginePlay2DFromFile(rkSoundEngine engine, const char *file,
	int looped, int paused)
{
	return engine->engine->play2D(file, looped, paused);
}
rkSound rkSoundEnginePlay3D(rkSoundEngine engine, rkSoundSource source,
	int looped, int paused)
{
	return engine->engine->play3D((rk::SoundSource*)source, looped, paused);
}
rkSound rkSoundEnginePlay3DFromFile(rkSoundEngine engine, const char *file,
	int looped, int paused)
{
	return engine->engine->play3D(file, looped, paused);
}
void rkSoundEngineSetVolume(rkSoundEngine engine, float volume)
{
	engine->engine->setVolume(volume);
}
float rkSoundEngineGetVolume(rkSoundEngine engine)
{
	return engine->engine->getVolume();
}
void rkSoundEngineSetAllPaused(rkSoundEngine engine, int paused)
{
	engine->engine->setAllPaused(paused);
}
void rkSoundEngineStopAll(rkSoundEngine engine)
{
	engine->engine->stopAll();
}
