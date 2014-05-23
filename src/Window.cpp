#include <iostream>
#include <string.h>

#include "Window.h"

using namespace std;

Window::Window(){
	display = Display::connect(NULL);
	registry = display->get_registry();
	static const struct wl_registry_listener registry_all = { Window::HandleGlobal, Window::HandleGlobalRemove};
	registry->add_listener((const struct wl_listener *)&registry_all, (void *)this);
	display->roundtrip();
	surface = compositor->create_surface();
	shellSurface = shell->get_shell_surface(surface);
	shellSurface->set_title("new window");
	shellSurface->set_toplevel();
}

Window::~Window() {
	delete shellSurface;
	delete surface;
	if (compositor)
		delete compositor;
	if (shell)
		delete shell;
	delete registry;
	display->disconnect();
	delete display;
}

void Window::HandleGlobal(void *data,
				struct wl_registry *reg,
				uint32_t name,
				const char *interface,
				uint32_t version) {
	Window *window = static_cast<Window *>(data);
	if (strcmp(interface, "wl_compositor") == 0) {
		window->compositor = new Compositor(window->registry->bind(name, &wl_compositor_interface, version));
	} else if (strcmp(interface, "wl_output") == 0) {
	} else if (strcmp(interface, "wl_seat") == 0) {
	} else if (strcmp(interface, "wl_shm") == 0) {
	} else if (strcmp(interface, "wl_text_input_manager") == 0) {
	} else if (strcmp(interface, "wl_shell") == 0){
		window->shell = new Shell(window->registry->bind(name, &wl_shell_interface, version));
	}
}
void Window::HandleGlobalRemove(void *data, struct wl_registry *registry, uint32_t name){
	//Window *window = static_cast<Window *>(data);
}

void Window::run(){
	while(1){
		display->dispatch();	
	}
}
