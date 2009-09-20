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


#include "ListenerOpenAL.hpp"

#include <AL/al.h>

namespace rk
{
	ListenerOpenAL::ListenerOpenAL()
	{
	}
	ListenerOpenAL::~ListenerOpenAL()
	{
	}

	void ListenerOpenAL::setPosition(const Vector3F &position)
	{
		alListener3f(AL_POSITION, position.x, position.y, position.z);
	}
	Vector3F ListenerOpenAL::getPosition()
	{
		Vector3F pos;
		alGetListener3f(AL_POSITION, &pos.x, &pos.y, &pos.z);
		return pos;
	}

	void ListenerOpenAL::setOrientation(const Vector3F &orientation)
	{
		// TODO
	}
	void ListenerOpenAL::setOrientation(const Vector3F &forward,
		const Vector3F &up)
	{
		float atup[6] = {forward.x, forward.y, forward.z, up.x, up.y, up.z};
		alListenerfv(AL_ORIENTATION, atup);
	}
	Vector3F ListenerOpenAL::getOrientation()
	{
		// TODO
		return Vector3F(0, 0, 0);
	}
	void ListenerOpenAL::getOrientation(Vector3F &forward, Vector3F &up)
	{
		float atup[6];
		alGetListenerfv(AL_ORIENTATION, atup);
		forward.x = atup[0];
		forward.y = atup[1];
		forward.z = atup[2];
		up.x = atup[3];
		up.y = atup[4];
		up.z = atup[5];
	}

	void ListenerOpenAL::setVelocity(const Vector3F &velocity)
	{
		alListener3f(AL_VELOCITY, velocity.x, velocity.y, velocity.z);
	}
	Vector3F ListenerOpenAL::getVelocity()
	{
		Vector3F vel;
		alGetListener3f(AL_VELOCITY, &vel.x, &vel.y, &vel.z);
		return vel;
	}
}
