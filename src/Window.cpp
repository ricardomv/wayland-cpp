#include "Window.h"

Window::Window(){
	display = Display::connect(NULL);
	global = new Global(display->get_registry());
	display->roundtrip();
	//global->seat->get_keyboard();
}

Window::~Window() {
	delete global;
	display->disconnect();
	delete display;
}

void Window::run(){
	while(1) {
		display->dispatch();
	}
}
