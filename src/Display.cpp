#include <wayland-client.h>
#include "Display.h"

Display *Display::connect(const char *name){
	return new Display(wl_display_connect(name));
}

Display *Display::connect_to_fd(int fd){
	return new Display(wl_display_connect_to_fd(fd));
}

void Display::disconnect(){
	wl_display_disconnect(display_);
	display_ = NULL;
	proxy_ = NULL;
}
int Display::get_fd(){
	return wl_display_get_fd(display_);
}

int Display::dispatch(){
	return wl_display_dispatch(display_);
}

int Display::dispatch_queue(struct wl_event_queue *queue){
	return wl_display_dispatch_queue(display_, queue);
}

int Display::dispatch_queue_pending(struct wl_event_queue *queue){
	return wl_display_dispatch_queue_pending(display_, queue);
}

int Display::dispatch_pending(){
	return wl_display_dispatch_pending(display_);
}

int Display::get_error(){
	return wl_display_get_error(display_);
}

int Display::flush(){
	return wl_display_flush(display_);
}

int Display::roundtrip(){
	return wl_display_roundtrip(display_);
}

struct wl_event_queue *Display::create_queue(){
	return wl_display_create_queue(display_);
}

int Display::prepare_read_queue(struct wl_event_queue *queue){
	return wl_display_prepare_read_queue(display_, queue);
}

int Display::prepare_read(){
	return wl_display_prepare_read(display_);
}

void Display::cancel_read(){
	wl_display_cancel_read(display_);
}

int Display::read_events(){
	return wl_display_read_events(display_);
}

Registry *Display::get_registry(){
	return new Registry(marshal_constructor( 
										WL_DISPLAY_GET_REGISTRY, 
										&wl_registry_interface, 
										NULL));
}
