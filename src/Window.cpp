#include "config.h"
#include "Window.h"

#if TEST_EGL
void test_egl(int width, int height, struct wl_display *display, struct wl_surface *surface);
#endif

Window::Window()
		: width(300)
		, height(300){
	display = Display::connect(NULL);
	global = new Global(display->get_registry());
	display->roundtrip();
	input = new Input(global->seat);
	surface = global->compositor->create_surface();
	shellsurface = global->shell->get_shell_surface(surface);
	static const struct wl_shell_surface_listener shell_surface_listener = {
		Window::HandlePing,
		Window::HandleConfigure,
		Window::HandlePopupDone
	};
	shellsurface->add_listener((const struct wl_listener *)&shell_surface_listener, this);
	shellsurface->set_title("cairo-wayland-cpp");
	shellsurface->set_toplevel();
	//shellsurface->set_fullscreen(WL_SHELL_SURFACE_FULLSCREEN_METHOD_DEFAULT,0,NULL);
	//display->dispatch(); /* update window size after fullscreen */
#if TEST_EGL
	test_egl(width, height, display->cobj, surface->cobj);
#else
	display->roundtrip(); /* wait for all input and surface initializations */
#endif
}

Window::~Window() {
	delete shellsurface;
	delete surface;
	delete input;
	delete global;
	delete display;
}

void Window::HandlePing(void *data,
					struct wl_shell_surface *shell_surface,
					uint32_t serial){
	Window *window = static_cast<Window *>(data);
	window->shellsurface->pong(serial);
}

void Window::HandleConfigure(void *data,
					struct wl_shell_surface *shell_surface,
					uint32_t edges,
					int32_t width,
					int32_t height){
	Window *window = static_cast<Window *>(data);
	window->width = width;
	window->height = height;
}

void Window::HandlePopupDone(void *data,
					struct wl_shell_surface *shell_surface){
	//Window *window = static_cast<Window *>(data);
}

void Window::run(){
	while(TEST_EGL && input->running) {
		display->dispatch();
	}
}
