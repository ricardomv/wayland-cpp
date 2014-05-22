class Compositor : public Proxy
{
public:
	Compositor(void *proxy): Proxy(proxy) {}

	Surface *create_surface() {
		return new Surface(this->marshal_constructor(WL_COMPOSITOR_CREATE_SURFACE, &wl_surface_interface, this));
	}
};
