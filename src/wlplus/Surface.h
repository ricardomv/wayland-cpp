#ifndef __SURFACE_H_INCLUDED__
#define __SURFACE_H_INCLUDED__

#include "Proxy.h"

class Surface : public Proxy
{
public:
	using Proxy::Proxy;

	void attach(Buffer *buffer, int32_t x, int32_t y) {
		marshal(WL_SURFACE_ATTACH, buffer, x, y);
	}
	void damage(int32_t x, int32_t y, int32_t width, int32_t height) {
		marshal(WL_SURFACE_DAMAGE, x, y, width, height);
	}
	Callback *frame() {
		return new Callback(marshal_constructor(WL_SURFACE_FRAME, &wl_callback_interface, NULL));
	}
	void set_opaque_region(Region *region) {
		marshal(WL_SURFACE_SET_OPAQUE_REGION, region);
	}
	void set_input_region(Region *region) {
		marshal(WL_SURFACE_SET_INPUT_REGION, region);
	}
	void commit() {
		marshal(WL_SURFACE_COMMIT);
	}
	void set_buffer_transform(int32_t transform) {
		marshal(WL_SURFACE_SET_BUFFER_TRANSFORM, transform);
	}
	void set_buffer_scale(int32_t scale) {
		marshal(WL_SURFACE_SET_BUFFER_SCALE, scale);
	}
};

#endif
