#ifndef __SEAT_H_INCLUDED__
#define __SEAT_H_INCLUDED__

#include "Proxy.h"

class Seat : public Proxy
{
public:
	using Proxy::Proxy;

	enum capability {
		WL_SEAT_CAPABILITY_POINTER = 1, 
		WL_SEAT_CAPABILITY_KEYBOARD = 2, 
		WL_SEAT_CAPABILITY_TOUCH = 4
	};
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
