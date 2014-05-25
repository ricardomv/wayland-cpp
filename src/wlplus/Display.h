#ifndef __DISPLAY_H_INCLUDED__
#define __DISPLAY_H_INCLUDED__

#include "Proxy.h"
#include "Registry.h"

class Display : public Proxy
{
private:
	struct wl_display *display_;
public:
	Display(struct wl_display *display) 
					: Proxy((struct wl_proxy *)display), 
					display_(display) {}

	static Display *connect(const char *name){
		return new Display(wl_display_connect(name));
	}
	static Display *connect_to_fd(int fd){
		return new Display(wl_display_connect_to_fd(fd));
	}
	void disconnect(){
		wl_display_disconnect(display_);
		display_ = NULL;
		proxy_ = NULL;
	}
	int get_fd(){
		return wl_display_get_fd(display_);
	}
	int dispatch(){
		return wl_display_dispatch(display_);
	}
	int dispatch_queue(struct wl_event_queue *queue){
		return wl_display_dispatch_queue(display_, queue);
	}
	int dispatch_queue_pending(struct wl_event_queue *queue){
		return wl_display_dispatch_queue_pending(display_, queue);
	}
	int dispatch_pending(){
		return wl_display_dispatch_pending(display_);
	}
	int get_error(){
		return wl_display_get_error(display_);
	}
	int flush(){
		return wl_display_flush(display_);
	}
	int roundtrip(){
		return wl_display_roundtrip(display_);
	}
	struct wl_event_queue *create_queue(){
		return wl_display_create_queue(display_);
	}
	int prepare_read_queue(struct wl_event_queue *queue){
		return wl_display_prepare_read_queue(display_, queue);
	}
	int prepare_read(){
		return wl_display_prepare_read(display_);
	}
	void cancel_read(){
		wl_display_cancel_read(display_);
	}
	int read_events(){
		return wl_display_read_events(display_);
	}
	Registry *get_registry(){
		return new Registry(marshal_constructor( 
										WL_DISPLAY_GET_REGISTRY, 
										&wl_registry_interface, 
										NULL));
	}

};
#endif
