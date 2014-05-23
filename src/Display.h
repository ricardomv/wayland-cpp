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
					: Proxy((void *)display), 
					display_(display) {}

	static Display *connect(const char *name);
	static Display *connect_to_fd(int fd);
	void disconnect();
	int get_fd();
	int dispatch();
	int dispatch_queue(struct wl_event_queue *queue);
	int dispatch_queue_pending(struct wl_event_queue *queue);
	int dispatch_pending();
	int get_error();
	int flush();
	int roundtrip();
	struct wl_event_queue *create_queue();
	int prepare_read_queue(struct wl_event_queue *queue);
	int prepare_read();
	void cancel_read();
	int read_events();

	Registry *get_registry();
};
#endif
