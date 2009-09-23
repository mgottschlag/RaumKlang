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

void rkSoundGrab(rkSound sound)
{
	((rk::Sound*)sound)->grab();
}
void rkSoundDrop(rkSound sound)
{
	((rk::Sound*)sound)->drop();
}
void rkSoundSetPaused(rkSound sound, int paused)
{
	((rk::Sound*)sound)->setPaused(paused);
}
int rkSoundIsPaused(rkSound sound)
{
	return ((rk::Sound*)sound)->isPaused();
}
void rkSoundStop(rkSound sound)
{
	((rk::Sound*)sound)->stop();
}
int rkSoundIsStopped(rkSound sound)
{
	return ((rk::Sound*)sound)->isStopped();
}
void rkSoundSetPosition(rkSound sound, rkVector3 position)
{
	((rk::Sound*)sound)->setPosition(rk::Vector3F(position.x, position.y,
		position.z));
}
rkVector3 rkSoundGetPosition(rkSound sound)
{
	rkVector3 pos;
	rk::Vector3F pos2 = ((rk::Sound*)sound)->getPosition();
	pos.x = pos2.x;
	pos.y = pos2.y;
	pos.z = pos2.z;
	return pos;
}
void rkSoundSetVelocity(rkSound sound, rkVector3 velocity)
{
	((rk::Sound*)sound)->setVelocity(rk::Vector3F(velocity.x, velocity.y,
		velocity.z));
}
rkVector3 rkSoundGetVelocity(rkSound sound)
{
	rkVector3 vel;
	rk::Vector3F vel2 = ((rk::Sound*)sound)->getVelocity();
	vel.x = vel2.x;
	vel.y = vel2.y;
	vel.z = vel2.z;
	return vel;
}
int rkSoundIs3D(rkSound sound)
{
	return ((rk::Sound*)sound)->is3D();
}
void rkSoundSetVolume(rkSound sound, float volume)
{
	((rk::Sound*)sound)->setVolume(volume);
}
float rkSoundGetVolume(rkSound sound)
{
	return ((rk::Sound*)sound)->getVolume();
}
void rkSoundSetLooped(rkSound sound, int looped)
{
	((rk::Sound*)sound)->setLooped(looped);
}
int rkSoundIsLooped(rkSound sound)
{
	return ((rk::Sound*)sound)->isLooped();
}
void rkSoundSetPan(rkSound sound, float pan)
{
	((rk::Sound*)sound)->setPan(pan);
}
float rkSoundGetPan(rkSound sound)
{
	return ((rk::Sound*)sound)->getPan();
}
void rkSoundSetPitch(rkSound sound, float pitch)
{
	((rk::Sound*)sound)->setPitch(pitch);
}
float rkSoundGetPitch(rkSound sound)
{
	return ((rk::Sound*)sound)->getPitch();
}
unsigned int rkSoundGetLength(rkSound sound)
{
	return ((rk::Sound*)sound)->getLength();
}
void rkSoundSetPlayPosition(rkSound sound, unsigned int msecs)
{
	((rk::Sound*)sound)->setPlayPosition(msecs);
}
unsigned int rkSoundGetPlayPosition(rkSound sound)
{
	return ((rk::Sound*)sound)->getPlayPosition();
}
rkSoundSource rkSoundGetSoundSource(rkSound sound)
{
	return ((rk::Sound*)sound)->getSoundSource();
}
