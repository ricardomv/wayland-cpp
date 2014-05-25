#ifndef __KEYBOARD_H_INCLUDED__
#define __KEYBOARD_H_INCLUDED__

#include "Proxy.h"

class Keyboard : public Proxy
{
public:
	Keyboard() {}
	Keyboard(struct wl_keyboard *proxy, void* data) : Proxy((struct wl_proxy *)proxy) {
		static const struct wl_keyboard_listener keyboard_listener = {
			Keyboard::_HandleKeymap,
			Keyboard::_HandleEnter,
			Keyboard::_HandleLeave,
			Keyboard::_HandleKey,
			Keyboard::_HandleModifiers,
		};
		add_listener((const struct wl_listener *)&keyboard_listener, data);
	}
	virtual void KbrdHandleKeymap(uint32_t format, int fd, uint32_t size) {}
	virtual void KbrdHandleEnter(uint32_t serial, struct wl_surface *surface,
						struct wl_array *keys) {}
	virtual void KbrdHandleLeave(uint32_t serial, struct wl_surface *surface) {}
	virtual void KbrdHandleKey(uint32_t serial, uint32_t time, uint32_t key,
						uint32_t state_w) {}
	virtual void KbrdHandleModifiers(uint32_t serial, uint32_t mods_depressed,
						uint32_t mods_latched, uint32_t mods_locked,
						uint32_t group) {}

	static void _HandleKeymap(void *data, struct wl_keyboard *keyboard,
		       uint32_t format, int fd, uint32_t size) {
		Keyboard *object = static_cast<Keyboard *>(data);
		object->KbrdHandleKeymap(format, fd, size);
	}
	static void _HandleEnter(void *data, struct wl_keyboard *keyboard,
		      uint32_t serial, struct wl_surface *surface,
		      struct wl_array *keys) {
		Keyboard *object = static_cast<Keyboard *>(data);
		object->KbrdHandleEnter(serial, surface, keys);
	}
	static void _HandleLeave(void *data, struct wl_keyboard *keyboard,
		      uint32_t serial, struct wl_surface *surface) {
		Keyboard *object = static_cast<Keyboard *>(data);
		object->KbrdHandleLeave(serial, surface);
	}
	static void _HandleKey(void *data, struct wl_keyboard *keyboard,
		    uint32_t serial, uint32_t time, uint32_t key,
		    uint32_t state_w) {
		Keyboard *object = static_cast<Keyboard *>(data);
		object->KbrdHandleKey(serial, time, key, state_w);
	}
	static void _HandleModifiers(void *data, struct wl_keyboard *keyboard,
			  uint32_t serial, uint32_t mods_depressed,
			  uint32_t mods_latched, uint32_t mods_locked,
			  uint32_t group) {
		Keyboard *object = static_cast<Keyboard *>(data);
		object->KbrdHandleModifiers(serial, mods_depressed, mods_latched, mods_locked, group);
	}
};
#endif
