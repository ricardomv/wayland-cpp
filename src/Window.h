#include <wayland-client.h>

#include "Proxy.h"
#include "Registry.h"
#include "Display.h"
#include "Global.h"
#include "Surface.h"
#include "ShellSurface.h"

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
