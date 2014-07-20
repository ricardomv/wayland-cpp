#include "Window.h"

int main(int argc, char const *argv[])
{
	Window *window = new Window(300, 300);

	window->run();
	delete window;

	return 0;
}
