#ifndef __SEAT_H_INCLUDED__
#define __SEAT_H_INCLUDED__

#include "Proxy.h"

class Seat : public Proxy
{
public:
	using Proxy::Proxy;

	Pointer *get_pointer() {
		return new Pointer(marshal_constructor(WL_SEAT_GET_POINTER, &wl_pointer_interface, NULL));
	}
	Keyboard *get_keyboard() {
		return new Keyboard(marshal_constructor(WL_SEAT_GET_KEYBOARD, &wl_keyboard_interface, NULL));
	}
	Touch *get_touch() {
		return new Touch(marshal_constructor(WL_SEAT_GET_TOUCH, &wl_touch_interface, NULL));
	}
};

#endif
