#include "Window.h"

int main(int argc, char const *argv[])
{
	Window *window = new Window;

	window->run();
	delete window;

	return 0;
}
