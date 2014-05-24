#ifndef __SHELLSURFACE_H_INCLUDED__
#define __SHELLSURFACE_H_INCLUDED__

#include "Proxy.h"

class ShellSurface : public Proxy
{
public:
	using Proxy::Proxy;

	void pong(uint32_t serial){
		this->marshal(WL_SHELL_SURFACE_PONG, serial);
	}

	void move(struct wl_seat *seat, uint32_t serial){
		this->marshal(WL_SHELL_SURFACE_MOVE, seat, serial);
	}

	void resize(struct wl_seat *seat, uint32_t serial, uint32_t edges){
		this->marshal(WL_SHELL_SURFACE_RESIZE, seat, serial, edges);
	}

	void set_toplevel(){
		this->marshal(WL_SHELL_SURFACE_SET_TOPLEVEL);
	}

	void set_transient(struct wl_surface *parent, int32_t x, int32_t y, uint32_t flags){
		this->marshal(WL_SHELL_SURFACE_SET_TRANSIENT, parent, x, y, flags);
	}

	void set_fullscreen(uint32_t method, uint32_t framerate, struct wl_output *output){
		this->marshal(WL_SHELL_SURFACE_SET_FULLSCREEN, method, framerate, output);
	}

	void set_popup(struct wl_seat *seat, uint32_t serial, struct wl_surface *parent, int32_t x, int32_t y, uint32_t flags){
		this->marshal(WL_SHELL_SURFACE_SET_POPUP, seat, serial, parent, x, y, flags);
	}

	void set_maximized(struct wl_output *output){
		this->marshal(WL_SHELL_SURFACE_SET_MAXIMIZED, output);
	}

	void set_title(const char *title){
		this->marshal(WL_SHELL_SURFACE_SET_TITLE, title);
	}

	void set_class(const char *class_){
		this->marshal(WL_SHELL_SURFACE_SET_CLASS, class_);
	}
};
#endif
