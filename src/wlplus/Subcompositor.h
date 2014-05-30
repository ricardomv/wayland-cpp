#ifndef __SUBCOMPOSITOR_H_INCLUDED__
#define __SUBCOMPOSITOR_H_INCLUDED__

#include "Proxy.h"

class Subcompositor : public Proxy
{
public:
	using Proxy::Proxy;

	Subsurface *get_subsurface(Surface *surface, Surface *parent) {
		return new Subsurface(marshal_constructor(WL_SUBCOMPOSITOR_GET_SUBSURFACE, &wl_subsurface_interface, NULL, surface, parent));
	}
};

#endif
