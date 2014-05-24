#ifndef __COMPOSITOR_H_INCLUDED__
#define __COMPOSITOR_H_INCLUDED__

#include "Proxy.h"
#include "Surface.h"

class Compositor : public Proxy
{
public:
	using Proxy::Proxy;

	Surface *create_surface() {
		return new Surface(this->marshal_constructor(WL_COMPOSITOR_CREATE_SURFACE, &wl_surface_interface, this));
	}
};
#endif
