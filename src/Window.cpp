#include "Window.h"

Window::Window()
		: width(300)
		, height(300){
	display = Display::connect(NULL);
	global = new Global(display->get_registry());
	display->roundtrip();
	input = new Input();
	input->add(global->seat->get_keyboard());
	input->add(global->seat->get_pointer());
	surface = global->compositor->create_surface();
	shellsurface = global->shell->get_shell_surface(surface);
	static const struct wl_shell_surface_listener shell_surface_listener = {
		Window::HandlePing,
		Window::HandleConfigure
	};
	shellsurface->add_listener((const struct wl_listener *)&shell_surface_listener, this);
	shellsurface->set_toplevel();
	//shellsurface->set_fullscreen(WL_SHELL_SURFACE_FULLSCREEN_METHOD_DEFAULT,0,NULL);
}

Window::~Window() {
	delete shellsurface;
	delete surface;
	delete input;
	delete global;
	display->disconnect();
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
	while(input->running) {
		display->dispatch();
	}
}
