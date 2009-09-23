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

void rkListenerSetPosition(rkListener listener, rkVector3 position)
{
	((rk::Listener*)listener)->setPosition(rk::Vector3F(position.x, position.y,
		position.z));
}
rkVector3 rkListenerGetPosition(rkListener listener)
{
	rkVector3 pos;
	rk::Vector3F pos2 = ((rk::Listener*)listener)->getPosition();
	pos.x = pos2.x;
	pos.y = pos2.y;
	pos.z = pos2.z;
	return pos;
}
void rkListenerSetVelocity(rkListener listener, rkVector3 velocity)
{
	((rk::Listener*)listener)->setVelocity(rk::Vector3F(velocity.x, velocity.y,
		velocity.z));
}
rkVector3 rkListenerGetVelocity(rkListener listener)
{
	rkVector3 vel;
	rk::Vector3F vel2 = ((rk::Listener*)listener)->getVelocity();
	vel.x = vel2.x;
	vel.y = vel2.y;
	vel.z = vel2.z;
	return vel;
}
void rkListenerSetOrientationEuler(rkListener listener, rkVector3 orientation)
{
	((rk::Listener*)listener)->setOrientation(rk::Vector3F(orientation.x,
		orientation.y, orientation.z));
}
rkVector3 rkListenerGetOrientationEuler(rkListener listener)
{
	rkVector3 ori;
	rk::Vector3F ori2 = ((rk::Listener*)listener)->getOrientation();
	ori.x = ori2.x;
	ori.y = ori2.y;
	ori.z = ori2.z;
	return ori;
}
void rkListenerSetOrientation(rkListener listener, rkVector3 forward,
	rkVector3 up)
{
	((rk::Listener*)listener)->setOrientation(rk::Vector3F(forward.x,
		forward.y, forward.z), rk::Vector3F(up.x, up.y, up.z));
}
void rkListenerGetOrientation(rkListener listener, rkVector3 *forward,
	rkVector3 *up)
{
	rk::Vector3F forward2;
	rk::Vector3F up2;
	((rk::Listener*)listener)->getOrientation(forward2, up2);
	forward->x = forward2.x;
	forward->y = forward2.y;
	forward->z = forward2.z;
	up->x = up2.x;
	up->y = up2.y;
	up->z = up2.z;
}
