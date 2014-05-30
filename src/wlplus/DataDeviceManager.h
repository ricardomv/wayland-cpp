#ifndef __DATADEVICEMANAGER_H_INCLUDED__
#define __DATADEVICEMANAGER_H_INCLUDED__

#include "Proxy.h"

class DataDeviceManager : public Proxy
{
public:
	using Proxy::Proxy;

	DataSource *create_data_source() {
		return new DataSource(marshal_constructor(WL_DATA_DEVICE_MANAGER_CREATE_DATA_SOURCE, &wl_data_source_interface, NULL));
	}
	DataDevice *get_data_device(Seat *seat) {
		return new DataDevice(marshal_constructor(WL_DATA_DEVICE_MANAGER_GET_DATA_DEVICE, &wl_data_device_interface, NULL, seat));
	}
};

#endif
