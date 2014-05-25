#include "wlplus"
using namespace wayland;

#include "Global.h"

class Window : public Keyboard
{
public:
	Window();
	~Window();
	void run();
private:
	Display *display = NULL;
	Registry *registry = NULL;
	Global *global = NULL;
	Surface *surface = NULL;
	ShellSurface *shellSurface = NULL;
};
