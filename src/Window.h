#include <wlplus>
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
	Display *display = NULL;
	Global *global = NULL;
	Input *input = NULL;
	Surface *surface = NULL;
	ShellSurface *shellSurface = NULL;
};
