#ifndef __SHELLSURFACE_H_INCLUDED__
#define __SHELLSURFACE_H_INCLUDED__

#include "Proxy.h"

class Seat;

class ShellSurface : public Proxy
{
public:
	using Proxy::Proxy;

	void pong(uint32_t serial) {
		marshal(WL_SHELL_SURFACE_PONG, serial);
	}
	void move(Seat *seat, uint32_t serial) {
		marshal(WL_SHELL_SURFACE_MOVE, seat, serial);
	}
	void resize(Seat *seat, uint32_t serial, uint32_t edges) {
		marshal(WL_SHELL_SURFACE_RESIZE, seat, serial, edges);
	}
	void set_toplevel() {
		marshal(WL_SHELL_SURFACE_SET_TOPLEVEL);
	}
	void set_transient(Surface *parent, int32_t x, int32_t y, uint32_t flags) {
		marshal(WL_SHELL_SURFACE_SET_TRANSIENT, parent, x, y, flags);
	}
	void set_fullscreen(uint32_t method, uint32_t framerate, Output *output) {
		marshal(WL_SHELL_SURFACE_SET_FULLSCREEN, method, framerate, output);
	}
	void set_popup(Seat *seat, uint32_t serial, Surface *parent, int32_t x, int32_t y, uint32_t flags) {
		marshal(WL_SHELL_SURFACE_SET_POPUP, seat, serial, parent, x, y, flags);
	}
	void set_maximized(Output *output) {
		marshal(WL_SHELL_SURFACE_SET_MAXIMIZED, output);
	}
	void set_title(const char *title) {
		marshal(WL_SHELL_SURFACE_SET_TITLE, title);
	}
	void set_class(const char *class_) {
		marshal(WL_SHELL_SURFACE_SET_CLASS, class_);
	}
};

#endif
