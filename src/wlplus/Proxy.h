#ifndef __PROXY_H_INCLUDED__
#define __PROXY_H_INCLUDED__

class Proxy
{
protected:
	struct wl_proxy *proxy_ = NULL;
public:
	Proxy(struct wl_proxy *proxy) : proxy_(proxy) {}
	~Proxy(){
		if (proxy_)
			destroy();
	}

	struct wl_proxy *create(struct wl_proxy *factory,
					const struct wl_interface *interface){
		return wl_proxy_create(factory,interface);
	}

	struct wl_proxy *marshal_constructor(uint32_t opcode,
					const struct wl_interface *interface,
					...){
		va_list args;
		va_start(args, interface);
		struct wl_proxy *aux = wl_proxy_vmarshal_constructor(proxy_, opcode, interface, args);
		va_end(args);
		return aux;
	}

	struct wl_proxy *marshal_array_constructor(uint32_t opcode, union wl_argument *args,
					const struct wl_interface *interface){
		return NULL;
	}

	void marshal(uint32_t opcode, ...){
		va_list args;
		va_start(args, opcode);
		wl_proxy_vmarshal_constructor(proxy_, opcode, NULL, args);
		va_end(args);
	}

	void marshal_array(uint32_t opcode,
					union wl_argument *args) {}

	void destroy() {
		wl_proxy_destroy(proxy_);
	}

	int add_listener(const struct wl_listener *listener, void *data){
		return wl_proxy_add_listener(proxy_, (void (**)(void)) listener, (void *)data);
	}

	const void *get_listener(){
		return wl_proxy_get_listener(proxy_);
	}

	int add_dispatcher(wl_dispatcher_func_t dispatcher_func,
					const void * dispatcher_data, void *data){
		return wl_proxy_add_dispatcher(proxy_, dispatcher_func, dispatcher_data, data);
	}

	void set_user_data(void *user_data) {
		wl_proxy_set_user_data(proxy_, user_data);
	}

	void *get_user_data(){
		return wl_proxy_get_user_data(proxy_);
	}

	uint32_t get_id(){
		return wl_proxy_get_id(proxy_);
	}

	const char *get_class(){
		return wl_proxy_get_class(proxy_);
	}

	void set_queue(struct wl_event_queue *queue) {
		wl_proxy_set_queue(proxy_, queue);
	}
};
#endif
