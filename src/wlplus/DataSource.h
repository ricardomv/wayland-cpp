#ifndef __DATASOURCE_H_INCLUDED__
#define __DATASOURCE_H_INCLUDED__

#include "Proxy.h"

class DataSource : public Proxy
{
public:
	using Proxy::Proxy;

	void offer(const char *mime_type) {
		marshal(WL_DATA_SOURCE_OFFER, mime_type);
	}
};

#endif
