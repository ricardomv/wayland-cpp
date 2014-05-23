#include "Window.h"

Window::Window(){
	display = Display::connect(NULL);
	registry = display->get_registry();
	global = new Global(registry); 
	display->roundtrip();
	Keyboard(global->seat->get_keyboard());
	surface = global->compositor->create_surface();
	shellSurface = global->shell->get_shell_surface(surface);
	shellSurface->set_title("new window");
	shellSurface->set_toplevel();
}

Window::~Window() {
	delete shellSurface;
	delete surface;
	delete registry;
	delete global;
	display->disconnect();
	delete display;
}

void Window::run(){
	while(1){
		display->dispatch();	
	}
}
