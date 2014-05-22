#include <wayland-client.h>

#include "Proxy.h"
#include "Registry.h"
#include "Display.h"
#include "Surface.h"
#include "ShellSurface.h"
#include "Shell.h"
#include "Compositor.h"

class Window
{
public:
	Window();
	~Window();
	void run();
private:
	Display *display = NULL;
	Registry *registry = NULL;
	Compositor *compositor = NULL;
	Surface *surface = NULL;
	Shell *shell = NULL;
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
