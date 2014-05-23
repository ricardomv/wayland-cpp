#ifndef __SHELL_H_INCLUDED__
#define __SHELL_H_INCLUDED__

#include "Proxy.h"
#include "ShellSurface.h"
#include "Surface.h"

class Shell : public Proxy
{
public:
	Shell(void *proxy): Proxy(proxy) {}
	
	ShellSurface *get_shell_surface(Surface *surface){
		return new ShellSurface(this->marshal_constructor(WL_SHELL_GET_SHELL_SURFACE, &wl_shell_surface_interface, this, surface->surface));
	}
};
#endif
