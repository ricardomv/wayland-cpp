#ifndef __SHMPOOL_H_INCLUDED__
#define __SHMPOOL_H_INCLUDED__

#include "Proxy.h"

class ShmPool : public Proxy
{
public:
	using Proxy::Proxy;

	Buffer *create_buffer(int32_t offset, int32_t width, int32_t height, int32_t stride, uint32_t format) {
		return new Buffer(marshal_constructor(WL_SHM_POOL_CREATE_BUFFER, &wl_buffer_interface, NULL, offset, width, height, stride, format));
	}
	void resize(int32_t size) {
		marshal(WL_SHM_POOL_RESIZE, size);
	}
};

#endif
