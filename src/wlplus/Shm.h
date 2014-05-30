#ifndef __SHM_H_INCLUDED__
#define __SHM_H_INCLUDED__

#include "Proxy.h"

class Shm : public Proxy
{
public:
	using Proxy::Proxy;

	ShmPool *create_pool(uint32_t fd, int32_t size) {
		return new ShmPool(marshal_constructor(WL_SHM_CREATE_POOL, &wl_shm_pool_interface, NULL, fd, size));
	}
};

#endif
