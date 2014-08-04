#ifndef __DISPLAY_H_INCLUDED__
#define __DISPLAY_H_INCLUDED__

#include "Proxy.hpp"

class Display : public Proxy
{
public:
	struct wl_display *cobj;
	Display(const char *name = NULL)
					: Proxy((struct wl_proxy *)wl_display_connect(name))
					, cobj((struct wl_display *)proxy_) {
		if (!cobj)
			throw "Failed to connect to Wayland display";
		interface_ = &wl_display_interface;
	}
	Display(int fd)
					: Proxy((struct wl_proxy *)wl_display_connect_to_fd(fd))
					, cobj((struct wl_display *)proxy_) {
		if (!cobj)
			throw "Failed to connect to Wayland display";
		interface_ = &wl_display_interface;
	}
	~Display() {
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

	Callback *sync() {
		return new Callback(marshal_constructor(SYNC, &wl_callback_interface, NULL));
	}
	Registry *get_registry() {
		return new Registry(marshal_constructor(GET_REGISTRY, &wl_registry_interface, NULL));
	}
	enum error {
		ERROR_INVALID_OBJECT = 0,
		ERROR_INVALID_METHOD = 1,
		ERROR_NO_MEMORY = 2
	};
	struct listener {
		void (*error)(void *data,
					struct wl_display *wl_display,
					struct wl_display *object_id,
					uint32_t code,
					const char *message);		void (*delete_id)(void *data,
					struct wl_display *wl_display,
					uint32_t id);
	};
private:
	enum requests {
		SYNC,
		GET_REGISTRY
	};
};
#endif
