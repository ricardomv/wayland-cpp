#ifndef __SUBSURFACE_H_INCLUDED__
#define __SUBSURFACE_H_INCLUDED__

#include "Proxy.h"

class Subsurface : public Proxy
{
public:
	using Proxy::Proxy;

	enum error {
		WL_SUBSURFACE_ERROR_BAD_SURFACE = 0
	};
	void set_position(int32_t x, int32_t y) {
		marshal(WL_SUBSURFACE_SET_POSITION, x, y);
	}
	void place_above(Surface *sibling) {
		marshal(WL_SUBSURFACE_PLACE_ABOVE, sibling);
	}
	void place_below(Surface *sibling) {
		marshal(WL_SUBSURFACE_PLACE_BELOW, sibling);
	}
	void set_sync() {
		marshal(WL_SUBSURFACE_SET_SYNC);
	}
	void set_desync() {
		marshal(WL_SUBSURFACE_SET_DESYNC);
	}
};

#endif
