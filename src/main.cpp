#include "Window.h"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
	try {
		Window *window = new Window(300, 300);

		window->run();
		delete window;
	}
	catch (const char *msg) {
    cerr << "Error: " << msg << endl;
  }

	return 0;
}
