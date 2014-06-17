#include "wlplus"
using namespace wayland;

#include "Global.h"
#include "Input.h"

class Window
{
public:
	Window();
	~Window();
	void run();
private:
	Display *display;
	Global *global;
	Input *input;
	Surface *surface;
	ShellSurface *shellsurface;
};
