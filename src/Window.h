#include "wlplus"
using namespace wayland;

#include "xdg-shell-client-protocol.h"
#include "XdgPopup.h"
#include "XdgSurface.h"
#include "XdgShell.h"

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
