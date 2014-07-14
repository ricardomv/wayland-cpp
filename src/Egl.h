#include <wayland-egl.h>
#include <EGL/egl.h>

class EglWindow;

class Egl
{
public:
	EGLDisplay display;
	EGLConfig argb_config;
	EGLContext argb_ctx;
	Egl(struct wl_display *wl_dpy);
	~Egl();
	EglWindow *CreateWindow(struct wl_surface* surface, int width, int height);
};

class EglWindow
{
	Egl *egl;
	EGLSurface egl_surface;
	struct wl_egl_window *egl_window;
public:
	EglWindow(Egl *egl, struct wl_egl_window *window);
	~EglWindow();
	void Resize(int width, int height);
	void SwapBuffers();
};
