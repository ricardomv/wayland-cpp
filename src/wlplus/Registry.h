#ifndef __REGISTRY_H_INCLUDED__
#define __REGISTRY_H_INCLUDED__

#include "Proxy.h"

class Registry : public Proxy
{
public:
	Registry() {}
	Registry(struct wl_registry *proxy) : Proxy((struct wl_proxy *)proxy) {
		static const struct wl_registry_listener registry_listener = {
			Registry::_HandleGlobal,
			Registry::_HandleGlobalRemove
		};
		add_listener((const struct wl_listener *)&registry_listener, this);
	}

	virtual void HandleGlobal(uint32_t name,
				const char *interface,
				uint32_t version) {}
	virtual void HandleGlobalRemove(uint32_t name) {}
	
	static void _HandleGlobal(void *data,
				struct wl_registry *reg,
				uint32_t name,
				const char *interface,
				uint32_t version) {
		Registry *object = static_cast<Registry *>(data);
		object->HandleGlobal(name, interface, version);
	}
	static void _HandleGlobalRemove(void *data, struct wl_registry *reg, uint32_t name){
		Registry *object = static_cast<Registry *>(data);
		object->HandleGlobalRemove(name);
	}

	struct wl_proxy *bind(uint32_t name,const struct wl_interface *interface, uint32_t version) {
		return marshal_constructor(WL_REGISTRY_BIND, interface, name, interface->name, version, NULL);
	}
};
#endif
