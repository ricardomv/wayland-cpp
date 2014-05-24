#ifndef __SEAT_H_INCLUDED__
#define __SEAT_H_INCLUDED__

#include "Proxy.h"
#include "Keyboard.h"

class Seat : public Proxy
{
public:
	using Proxy::Proxy;

	struct wl_proxy *get_pointer(){
		return this->marshal_constructor(WL_SEAT_GET_POINTER, &wl_pointer_interface, NULL);
	}
	struct wl_proxy *get_keyboard(){
		return this->marshal_constructor(WL_SEAT_GET_KEYBOARD, &wl_keyboard_interface, NULL);
	}
	struct wl_proxy *get_touch(){
		return this->marshal_constructor(WL_SEAT_GET_KEYBOARD, &wl_touch_interface, NULL);
	}
};
#endif
