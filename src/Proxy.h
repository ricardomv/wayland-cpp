#ifndef __PROXY_H_INCLUDED__
#define __PROXY_H_INCLUDED__

class Proxy
{
protected:
	struct wl_proxy *proxy_ = NULL;
public:
	Proxy(struct wl_proxy *proxy) : proxy_(proxy) {}
	Proxy() {}
	~Proxy();

	struct wl_proxy *create(struct wl_proxy *factory,
					const struct wl_interface *interface);
	struct wl_proxy *marshal_constructor(uint32_t opcode,
					const struct wl_interface *interface,
					...);
	struct wl_proxy *marshal_array_constructor(uint32_t opcode, union wl_argument *args,
					const struct wl_interface *interface);
	void marshal(uint32_t opcode, ...);
	void marshal_array(uint32_t opcode,
					union wl_argument *args);
	void destroy();
	int add_listener(const struct wl_listener *listener, void *data);
	const void *get_listener();
	int add_dispatcher(wl_dispatcher_func_t dispatcher_func,
					const void * dispatcher_data, void *data);
	void set_user_data(void *user_data);
	void *get_user_data();
	uint32_t get_id();
	const char *get_class();
	void set_queue(struct wl_event_queue *queue);
};
#endif
