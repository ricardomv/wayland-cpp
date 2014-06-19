#ifndef __DISPLAY_H_INCLUDED__
#define __DISPLAY_H_INCLUDED__

#include "Proxy.h"

class Display : public Proxy
{
public:
	struct wl_display *cobj;
	Display(struct wl_display *display) 
					: Proxy((struct wl_proxy *)display)
					, cobj(display) {}

	static Display *connect(const char *name){
		return new Display(wl_display_connect(name));
	}
	static Display *connect_to_fd(int fd){
		return new Display(wl_display_connect_to_fd(fd));
	}
	void disconnect(){
		wl_display_disconnect(cobj);
		cobj = NULL;
		proxy_ = NULL;
	}
	int get_fd(){
		return wl_display_get_fd(cobj);
	}
	int dispatch(){
		return wl_display_dispatch(cobj);
	}
	int dispatch_queue(struct wl_event_queue *queue){
		return wl_display_dispatch_queue(cobj, queue);
	}
	int dispatch_queue_pending(struct wl_event_queue *queue){
		return wl_display_dispatch_queue_pending(cobj, queue);
	}
	int dispatch_pending(){
		return wl_display_dispatch_pending(cobj);
	}
	int get_error(){
		return wl_display_get_error(cobj);
	}
	int flush(){
		return wl_display_flush(cobj);
	}
	int roundtrip(){
		return wl_display_roundtrip(cobj);
	}
	struct wl_event_queue *create_queue(){
		return wl_display_create_queue(cobj);
	}
	int prepare_read_queue(struct wl_event_queue *queue){
		return wl_display_prepare_read_queue(cobj, queue);
	}
	int prepare_read(){
		return wl_display_prepare_read(cobj);
	}
	void cancel_read(){
		wl_display_cancel_read(cobj);
	}
	int read_events(){
		return wl_display_read_events(cobj);
	}

	enum error {
		WL_DISPLAY_ERROR_INVALID_OBJECT = 0, 
		WL_DISPLAY_ERROR_INVALID_METHOD = 1, 
		WL_DISPLAY_ERROR_NO_MEMORY = 2
	};
	Callback *sync() {
		return new Callback(marshal_constructor(WL_DISPLAY_SYNC, &wl_callback_interface, NULL));
	}
	Registry *get_registry() {
		return new Registry(marshal_constructor(WL_DISPLAY_GET_REGISTRY, &wl_registry_interface, NULL));
	}
};

#endif
