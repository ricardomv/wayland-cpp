#ifndef __KEYBOARD_H_INCLUDED__
#define __KEYBOARD_H_INCLUDED__

#include <iostream>
using namespace std;

#include "Proxy.h"

class Keyboard : public Proxy
{
public:
	Keyboard() {}
	Keyboard(struct wl_proxy *proxy) : Proxy(proxy) {
		static const struct wl_keyboard_listener keyboard_listener = {
			Keyboard::HandleKeymap,
			Keyboard::HandleEnter,
			Keyboard::HandleLeave,
			Keyboard::HandleKey,
			Keyboard::HandleModifiers,
		};
		add_listener((const struct wl_listener *)&keyboard_listener, this);
	}
	static void HandleKeymap(void *data, struct wl_keyboard *keyboard,
		       uint32_t format, int fd, uint32_t size) {}
	static void HandleEnter(void *data, struct wl_keyboard *keyboard,
		      uint32_t serial, struct wl_surface *surface,
		      struct wl_array *keys) {cout << serial << endl;}
	static void HandleLeave(void *data, struct wl_keyboard *keyboard,
		      uint32_t serial, struct wl_surface *surface) {}
	static void HandleKey(void *data, struct wl_keyboard *keyboard,
		    uint32_t serial, uint32_t time, uint32_t key,
		    uint32_t state_w) {}
	static void HandleModifiers(void *data, struct wl_keyboard *keyboard,
			  uint32_t serial, uint32_t mods_depressed,
			  uint32_t mods_latched, uint32_t mods_locked,
			  uint32_t group) {}
};
#endif
