#include "Window.h"

Window::Window(){
	display = Display::connect(NULL);
	global = new Global(display->get_registry());
	display->roundtrip();
	input = new Input();
	input->add(global->seat->get_keyboard());
	input->add(global->seat->get_pointer());
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
