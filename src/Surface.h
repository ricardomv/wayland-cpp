class Surface : public Proxy
{
public:
	struct wl_surface *surface;
	Surface(void *proxy) : Proxy(proxy) {
		surface = (struct wl_surface *)proxy_;
	}
};
