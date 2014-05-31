#ifndef __KEYBOARD_H_INCLUDED__
#define __KEYBOARD_H_INCLUDED__

#include "Proxy.h"

class Keyboard : public Proxy
{
public:
	using Proxy::Proxy;

	enum keymap_format {
		WL_KEYBOARD_KEYMAP_FORMAT_NO_KEYMAP = 0, 
		WL_KEYBOARD_KEYMAP_FORMAT_XKB_V1 = 1
	};
	enum key_state {
		WL_KEYBOARD_KEY_STATE_RELEASED = 0, 
		WL_KEYBOARD_KEY_STATE_PRESSED = 1
	};
};

#endif
