#ifndef __POINTER_H_INCLUDED__
#define __POINTER_H_INCLUDED__

#include "Proxy.h"

class Pointer : public Proxy
{
public:
	using Proxy::Proxy;

	enum button_state {
		WL_POINTER_BUTTON_STATE_RELEASED = 0, 
		WL_POINTER_BUTTON_STATE_PRESSED = 1
	};
	enum axis {
		WL_POINTER_AXIS_VERTICAL_SCROLL = 0, 
		WL_POINTER_AXIS_HORIZONTAL_SCROLL = 1
	};
	void set_cursor(uint32_t serial, Surface *surface, int32_t hotspot_x, int32_t hotspot_y) {
		marshal(WL_POINTER_SET_CURSOR, serial, surface, hotspot_x, hotspot_y);
	}
};

#endif
