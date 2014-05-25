#ifndef __SURFACE_H_INCLUDED__
#define __SURFACE_H_INCLUDED__

#include "Proxy.h"

class Surface : public Proxy
{
public:
	struct wl_surface *surface;
	Surface(struct wl_proxy *proxy)  {
		surface = (struct wl_surface *)proxy;
	}
};
#endif
