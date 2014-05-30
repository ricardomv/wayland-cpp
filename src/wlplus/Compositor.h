#ifndef __COMPOSITOR_H_INCLUDED__
#define __COMPOSITOR_H_INCLUDED__

#include "Proxy.h"

class Compositor : public Proxy
{
public:
	using Proxy::Proxy;

	Surface *create_surface() {
		return new Surface(marshal_constructor(WL_COMPOSITOR_CREATE_SURFACE, &wl_surface_interface, NULL));
	}
	Region *create_region() {
		return new Region(marshal_constructor(WL_COMPOSITOR_CREATE_REGION, &wl_region_interface, NULL));
	}
};

#endif
