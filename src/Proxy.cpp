#include <stdarg.h>
#include <iostream>
#include <wayland-client.h>
#include "Proxy.h"

Proxy::~Proxy(){
	if (proxy_)
		wl_proxy_destroy(proxy_);
}

struct wl_proxy *Proxy::create(struct wl_proxy *factory,
					const struct wl_interface *interface){
	return wl_proxy_create(factory,interface);
}

struct wl_proxy *Proxy::marshal_constructor(uint32_t opcode,
					const struct wl_interface *interface,
					...){
	va_list args;
	va_start(args, interface);
	struct wl_proxy *aux = wl_proxy_vmarshal_constructor(proxy_, opcode, interface, args);
	va_end(args);
	return aux;
}

struct wl_proxy *Proxy::marshal_array_constructor(uint32_t opcode, union wl_argument *args,
					const struct wl_interface *interface){
	return NULL;
}

void Proxy::marshal(uint32_t opcode, ...){
	va_list args;
	va_start(args, opcode);
	wl_proxy_vmarshal_constructor(proxy_, opcode, NULL, args);
	va_end(args);
}

void Proxy::marshal_array(uint32_t opcode,
					union wl_argument *args){
}

int Proxy::add_listener(const struct wl_listener *listener, void *data){
	return wl_proxy_add_listener(proxy_, (void (**)(void)) listener, (void *)data);
}

const void *Proxy::get_listener(){
	return NULL;
}

int Proxy::add_dispatcher(wl_dispatcher_func_t dispatcher_func,
					const void * dispatcher_data, void *data){
	return 0;
}

void Proxy::set_user_data(void *user_data){
}

void *Proxy::get_user_data(){
	return NULL;
}

uint32_t Proxy::get_id(){
	return 0;
}

const char *Proxy::get_class(){
	return NULL;
}

void Proxy::set_queue(struct wl_event_queue *queue){
}
