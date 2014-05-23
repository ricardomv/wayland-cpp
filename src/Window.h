#include <wayland-client.h>

#include "Proxy.h"
#include "Registry.h"
#include "Display.h"
#include "Surface.h"
#include "ShellSurface.h"
#include "Shell.h"
#include "Compositor.h"
#include "Seat.h"
#include "Global.h"
#include "Keyboard.h"

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
	static void HandleGlobal(void *data,
				struct wl_registry *reg,
				uint32_t name,
				const char *interface,
				uint32_t version);
	static void HandleGlobalRemove(void *data,
				struct wl_registry *registry,
				uint32_t name);
};
