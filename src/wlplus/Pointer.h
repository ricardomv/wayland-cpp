#ifndef __POINTER_H_INCLUDED__
#define __POINTER_H_INCLUDED__

#include "Proxy.h"

class Pointer : public Proxy
{
public:
	Pointer() {}
	Pointer(struct wl_pointer *proxy, void *data) : Proxy((struct wl_proxy *)proxy) {
		static const struct wl_pointer_listener pointer_listener = {
			Pointer::_HandleEnter,
			Pointer::_HandleLeave,
			Pointer::_HandleMotion,
			Pointer::_HandleButton,
			Pointer::_HandleAxis,
		};
		add_listener((const struct wl_listener *)&pointer_listener, data);
	}

	virtual void PtrHandleEnter(uint32_t serial, struct wl_surface *surface,
					wl_fixed_t sx_w, wl_fixed_t sy_w) {}
	virtual void PtrHandleLeave(uint32_t serial, struct wl_surface *surface) {}
	virtual void PtrHandleMotion(uint32_t time, wl_fixed_t sx_w, wl_fixed_t sy_w) {}
	virtual void PtrHandleButton(uint32_t time, uint32_t button, uint32_t state_w) {}
	virtual void PtrHandleAxis(uint32_t time, uint32_t axis, wl_fixed_t value) {}

	static void
	_HandleEnter(void *data, struct wl_pointer *pointer,
					uint32_t serial, struct wl_surface *surface,
					wl_fixed_t sx_w, wl_fixed_t sy_w){
		Pointer *object = static_cast<Pointer *>(data);
		object->PtrHandleEnter(serial, surface, sx_w, sy_w);
	}

	static void
	_HandleLeave(void *data, struct wl_pointer *pointer,
		     uint32_t serial, struct wl_surface *surface){
		Pointer *object = static_cast<Pointer *>(data);
		object->PtrHandleLeave(serial, surface);
	}

	static void
	_HandleMotion(void *data, struct wl_pointer *pointer,
		      uint32_t time, wl_fixed_t sx_w, wl_fixed_t sy_w){
		Pointer *object = static_cast<Pointer *>(data);
		object->PtrHandleMotion(time, sx_w, sy_w);
	}

	static void
	_HandleButton(void *data, struct wl_pointer *pointer, uint32_t serial,
		      uint32_t time, uint32_t button, uint32_t state_w){
		Pointer *object = static_cast<Pointer *>(data);
		object->PtrHandleButton(time, button, state_w);
	}

	static void
	_HandleAxis(void *data, struct wl_pointer *pointer,
		    uint32_t time, uint32_t axis, wl_fixed_t value){
		Pointer *object = static_cast<Pointer *>(data);
		object->PtrHandleAxis(time, axis, value);
	}
};
#endif
