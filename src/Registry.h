#ifndef __REGISTRY_H_INCLUDED__
#define __REGISTRY_H_INCLUDED__

#include "Proxy.h"

class Registry : public Proxy
{
public:
	Registry(void *proxy) : Proxy(proxy) {}

	void *bind(uint32_t name,const struct wl_interface *interface, uint32_t version) {
		return (void *)this->marshal_constructor(WL_REGISTRY_BIND, interface, name, interface->name, version, NULL);
	}
};
#endif
