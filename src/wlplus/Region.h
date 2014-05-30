#ifndef __REGION_H_INCLUDED__
#define __REGION_H_INCLUDED__

#include "Proxy.h"

class Region : public Proxy
{
public:
	using Proxy::Proxy;

	void add(int32_t x, int32_t y, int32_t width, int32_t height) {
		marshal(WL_REGION_ADD, x, y, width, height);
	}
	void subtract(int32_t x, int32_t y, int32_t width, int32_t height) {
		marshal(WL_REGION_SUBTRACT, x, y, width, height);
	}
};

#endif
