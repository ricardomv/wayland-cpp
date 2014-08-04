#ifndef __PROXY_H_INCLUDED__
#define __PROXY_H_INCLUDED__

#define WL_CLOSURE_MAX_ARGS 20

class Proxy
{
protected:
	struct wl_proxy *proxy_;
	const struct wl_interface *interface_;
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
		union wl_argument args[WL_CLOSURE_MAX_ARGS];
		va_list ap;

		va_start(ap, interface);
		wl_argument_from_va_list(interface_->methods[opcode].signature,
					 args, WL_CLOSURE_MAX_ARGS, ap);
		va_end(ap);

		return marshal_array_constructor(opcode, args, interface);
	}

	struct wl_proxy *marshal_array_constructor(uint32_t opcode,
					union wl_argument *args,
					const struct wl_interface *interface){
		return wl_proxy_marshal_array_constructor(proxy_, opcode,
							args, interface);
	}

	void marshal(uint32_t opcode, ...){
		union wl_argument args[WL_CLOSURE_MAX_ARGS];
		va_list ap;

		va_start(ap, opcode);
		wl_argument_from_va_list(interface_->methods[opcode].signature,
					 args, WL_CLOSURE_MAX_ARGS, ap);
		va_end(ap);

		marshal_array_constructor(opcode, args, NULL);
	}

	void marshal_array(uint32_t opcode,
					union wl_argument *args) {
		wl_proxy_marshal_array_constructor(proxy_, opcode, args, NULL);
	}

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
private:
	struct argument_details {
		char type;
		int nullable;
	};
	const char *
	get_next_argument(const char *signature, struct argument_details *details)
	{
		details->nullable = 0;
		for(; *signature; ++signature) {
			switch(*signature) {
			case 'i':
			case 'u':
			case 'f':
			case 's':
			case 'o':
			case 'n':
			case 'a':
			case 'h':
				details->type = *signature;
				return signature + 1;
			case '?':
				details->nullable = 1;
			}
		}
		details->type = '\0';
		return signature;
	}
	void
	wl_argument_from_va_list(const char *signature, union wl_argument *args,
				 int count, va_list ap)
	{
		int i;
		const char *sig_iter;
		struct argument_details arg;

		sig_iter = signature;
		for (i = 0; i < count; i++) {
			sig_iter = get_next_argument(sig_iter, &arg);

			switch(arg.type) {
			case 'i':
				args[i].i = va_arg(ap, int32_t);
				break;
			case 'u':
				args[i].u = va_arg(ap, uint32_t);
				break;
			case 'f':
				args[i].f = va_arg(ap, wl_fixed_t);
				break;
			case 's':
				args[i].s = va_arg(ap, const char *);
				break;
			case 'o':
				args[i].o = va_arg(ap, struct wl_object *);
				break;
			case 'n':
				args[i].o = va_arg(ap, struct wl_object *);
				break;
			case 'a':
				args[i].a = va_arg(ap, struct wl_array *);
				break;
			case 'h':
				args[i].h = va_arg(ap, int32_t);
				break;
			case '\0':
				return;
			}
		}
	}

};
#endif
