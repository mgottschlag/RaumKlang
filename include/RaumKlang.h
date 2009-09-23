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

#ifndef _RAUMKLANG_H_INCLUDED_
#define _RAUMKLANG_H_INCLUDED_

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @defgroup cbinding
 * C bindings for RaumKlang
 * @{
 */

typedef struct rkiSoundEngine *rkSoundEngine;
typedef void *rkListener;
typedef void *rkSound;
typedef void *rkSoundSource;

/**
 * Sound driver identifier.
 */
typedef enum rkSoundDriver
{
	/**
	 * Null device. No sound is outputted, but the engine works as if a
	 * real driver was used. Not yet implemented.
	 */
	rkDriverNone,
	/**
	 * ALSA backend. Not yet implemented.
	 */
	rkDriverALSA,
	/**
	 * Backend using the OpenAL 3D sound library.
	 */
	rkDriverOpenAL,
	/**
	 * A sound driver is chosen automatically, ESD_None is used if no
	 * working driver is available.
	 */
	rkDriverAutoDetect
} rkSoundDriver;

typedef enum rkSampleFormat
{
	rkUnsignedByte,
	rkSignedWord
} rkSampleFormat;

/**
 * Struct describing the format of a sound stream.
 */
typedef struct rkSoundFormat
{
	/**
	 * Number of channels. Supported values are 1 (mono) and 2 (stereo).
	 */
	unsigned int channels;
	/**
	 * Sample rate of the stream. A common value for example is 44100.
	 */
	unsigned int samplerate;
	/**
	 * Format and size of the single samples.
	 */
	rkSampleFormat format;
} rkSoundFormat;

typedef struct rkVector3
{
	float x;
	float y;
	float z;
} rkVector3;

rkSoundEngine rkSoundEngineCreate(rkSoundDriver driver, const char *device);
void rkSoundEngineDestroy(rkSoundEngine engine);
const char *rkSoundEngineGetDriverName(rkSoundEngine engine);
rkListener rkSoundEngineGetListener(rkSoundEngine engine);
rkSoundSource rkSoundEngineGetSourceFromFile(rkSoundEngine engine,
	const char *filename, int reuse);
rkSoundSource rkSoundEngineGetSourcePCMFromFile(rkSoundEngine engine,
	const char *filename, rkSoundFormat format);
rkSoundSource rkSoundEngineGetSource(rkSoundEngine engine,
	const char *name, void *data, unsigned int size, int reuse);
rkSoundSource rkSoundEngineGetSourcePCM(rkSoundEngine engine,
	const char *name, void *data, unsigned int size, rkSoundFormat format);
rkSound rkSoundEnginePlay2D(rkSoundEngine engine, rkSoundSource source,
	int looped, int paused);
rkSound rkSoundEnginePlay2DFromFile(rkSoundEngine engine, const char *file,
	int looped, int paused);
rkSound rkSoundEnginePlay3D(rkSoundEngine engine, rkSoundSource source,
	int looped, int paused);
rkSound rkSoundEnginePlay3DFromFile(rkSoundEngine engine, const char *file,
	int looped, int paused);
void rkSoundEngineSetVolume(rkSoundEngine engine, float volume);
float rkSoundEngineGetVolume(rkSoundEngine engine);
void rkSoundEngineSetAllPaused(rkSoundEngine engine, int paused);
void rkSoundEngineStopAll(rkSoundEngine engine);

// TODO: Events

void rkSoundGrab(rkSound sound);
void rkSoundDrop(rkSound sound);
void rkSoundSetPaused(rkSound sound, int paused);
int rkSoundIsPaused(rkSound sound);
void rkSoundStop(rkSound sound);
int rkSoundIsStopped(rkSound sound);
void rkSoundSetPosition(rkSound sound, rkVector3 position);
rkVector3 rkSoundGetPosition(rkSound sound);
void rkSoundSetVelocity(rkSound sound, rkVector3 velocity);
rkVector3 rkSoundGetVelocity(rkSound sound);
int rkSoundIs3D(rkSound sound);
void rkSoundSetVolume(rkSound sound, float volume);
float rkSoundGetVolume(rkSound sound);
void rkSoundSetLooped(rkSound sound, int looped);
int rkSoundIsLooped(rkSound sound);
void rkSoundSetPan(rkSound sound, float pan);
float rkSoundGetPan(rkSound sound);
void rkSoundSetPitch(rkSound sound, float pitch);
float rkSoundGetPitch(rkSound sound);
unsigned int rkSoundGetLength(rkSound sound);
void rkSoundSetPlayPosition(rkSound sound, unsigned int msecs);
unsigned int rkSoundGetPlayPosition(rkSound sound);
rkSoundSource rkSoundGetSoundSource(rkSound sound);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
