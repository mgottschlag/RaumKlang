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
#include "Mutex.hpp"

#include <cstdlib>
#include <cstring>

static rk::SoundFormat getFormat(rkSoundFormat format)
{
	return rk::SoundFormat(format.channels, format.samplerate,
		(rk::SampleFormat)format.format);
}

class CEventReceiver : public rk::SoundStopEventReceiver,
	public rk::SoundDataReceiver
{
	public:
		CEventReceiver(rkSoundEngine engine) : engine(engine)
		{
		}

		virtual void onSoundStopped(rk::Sound *sound);
		virtual void onDataReceived(void *data, unsigned int framecount,
			const rk::SoundFormat &format);

		rkSoundEngine engine;
};

struct rkiSoundEngine
{
	rk::Mutex mutex;
	rk::SoundEngine *engine;
	CEventReceiver *receiver;
	unsigned int eventcount;
	rkEvent **events;
};

static void rkSoundEngineAddEvent(rkSoundEngine engine, rkEvent *event)
{
	engine->mutex.lock();
	engine->events = (rkEvent**)realloc(engine->events,
		(engine->eventcount + 1) * sizeof(rkEvent*));
	engine->events[engine->eventcount] = event;
	engine->eventcount++;
	engine->mutex.unlock();
}

void CEventReceiver::onSoundStopped(rk::Sound *sound)
{
	// Grab sound so that it is not deleted before we have processed the event
	sound->grab();
	// Create event
	rkSoundStopEvent *event = new rkSoundStopEvent;
	event->event.type = rkEventSoundStopped;
	event->sound = sound;
	// Add the event to the event queue
	rkSoundEngineAddEvent(engine, (rkEvent*)event);
}
void CEventReceiver::onDataReceived(void *data, unsigned int framecount,
	const rk::SoundFormat &format)
{
	// TODO
}

rkSoundEngine rkSoundEngineCreate(rkSoundDriver driver, const char *device)
{
	// Create engine
	rk::SoundEngine *engine = rk::SoundEngine::create((rk::SoundDriver)driver,
		device);
	if (!engine)
		return 0;
	// Create container struct
	rkSoundEngine container = new rkiSoundEngine;
	container->eventcount = 0;
	container->events = 0;
	container->engine = engine;
	container->receiver = new CEventReceiver(container);
	return container;
}
void rkSoundEngineDestroy(rkSoundEngine engine)
{
	if (!engine)
		return;
	engine->engine->destroy();
	delete engine->receiver;
	delete engine;
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

rkEvent *rkSoundEngineGetEvent(rkSoundEngine engine)
{
	engine->mutex.lock();
	rkEvent *event = 0;
	if (engine->eventcount > 0)
	{
		// Get first event
		event = engine->events[0];
		// Remove the event from the queue
		rkEvent **oldevents = engine->events;
		engine->eventcount--;
		if (engine->eventcount == 0)
		{
			engine->events = 0;
		}
		else
		{
			engine->events = (rkEvent**)malloc(engine->eventcount
				* sizeof(rkEvent*));
			memcpy(engine->events, &oldevents[1],
				engine->eventcount * sizeof(rkEvent*));
		}
		free(oldevents);
	}
	engine->mutex.unlock();
	return event;
}
void rkEventDestroy(rkEvent *event)
{
	if (event->type == rkEventSoundStopped)
	{
		rkSoundStopEvent *stopevent = (rkSoundStopEvent*)event;
		((rk::Sound*)stopevent->sound)->drop();
		delete stopevent;
	}
	else if (event->type == rkEventDataReceived)
	{
		// TODO
	}
}

void rkSoundEnableStopEvents(rkSound sound, rkSoundEngine engine)
{
	((rk::Sound*)sound)->setStopEventReceiver(engine->receiver);
}
