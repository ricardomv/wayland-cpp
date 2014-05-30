#ifndef __DATADEVICE_H_INCLUDED__
#define __DATADEVICE_H_INCLUDED__

#include "Proxy.h"

class DataDevice : public Proxy
{
public:
	using Proxy::Proxy;

	void start_drag(DataSource *source, Surface *origin, Surface *icon, uint32_t serial) {
		marshal(WL_DATA_DEVICE_START_DRAG, source, origin, icon, serial);
	}
	void set_selection(DataSource *source, uint32_t serial) {
		marshal(WL_DATA_DEVICE_SET_SELECTION, source, serial);
	}
};

#endif
