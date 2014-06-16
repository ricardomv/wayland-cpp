#include "Window.h"

void test_egl(struct wl_display *display, struct wl_surface *surface);

Window::Window(){
	display = Display::connect(NULL);
	global = new Global(display->get_registry());
	display->roundtrip();
	input = new Input();
	input->add(global->seat->get_keyboard());
	input->add(global->seat->get_pointer());
	Surface *surface = global->compositor->create_surface();
	ShellSurface *shellsurface = global->shell->get_shell_surface(surface);
	shellsurface->set_toplevel();
	shellsurface->set_fullscreen(WL_SHELL_SURFACE_FULLSCREEN_METHOD_DEFAULT,0,NULL);

	test_egl((struct wl_display *)display->proxy_, (struct wl_surface *)surface->proxy_);

}

Window::~Window() {
	delete input;
	delete global;
	display->disconnect();
	delete display;
}

void Window::run(){
	while(1) {
		display->dispatch();
	}
}
