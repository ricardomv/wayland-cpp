#ifndef __POINTER_H_INCLUDED__
#define __POINTER_H_INCLUDED__

#include "Proxy.h"

class Pointer : public Proxy
{
public:
	using Proxy::Proxy;

	void set_cursor(uint32_t serial, Surface *surface, int32_t hotspot_x, int32_t hotspot_y) {
		marshal(WL_POINTER_SET_CURSOR, serial, surface, hotspot_x, hotspot_y);
	}
};

#endif
