#ifndef __SHELL_H_INCLUDED__
#define __SHELL_H_INCLUDED__

#include "Proxy.h"

class Shell : public Proxy
{
public:
	using Proxy::Proxy;

	ShellSurface *get_shell_surface(Surface *surface) {
		return new ShellSurface(marshal_constructor(WL_SHELL_GET_SHELL_SURFACE, &wl_shell_surface_interface, NULL, surface));
	}
};

#endif
