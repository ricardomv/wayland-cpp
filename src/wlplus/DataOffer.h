#ifndef __DATAOFFER_H_INCLUDED__
#define __DATAOFFER_H_INCLUDED__

#include "Proxy.h"

class DataOffer : public Proxy
{
public:
	using Proxy::Proxy;

	void accept(uint32_t serial, const char *mime_type) {
		marshal(WL_DATA_OFFER_ACCEPT, serial, mime_type);
	}
	void receive(const char *mime_type, uint32_t fd) {
		marshal(WL_DATA_OFFER_RECEIVE, mime_type, fd);
	}
};

#endif
