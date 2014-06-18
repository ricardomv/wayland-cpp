#include "wlplus"
using namespace wayland;

#include "Global.h"
#include "Input.h"

class Window
{
public:
	Window();
	~Window();
	static void HandlePing(void *data, struct wl_shell_surface *shell_surface, uint32_t serial);
	static void HandleConfigure(void *data, struct wl_shell_surface *shell_surface, uint32_t edges, int32_t width, int32_t height);
	static void HandlePopupDone(void *data, struct wl_shell_surface *shell_surface);
	void run();
private:
	Display *display;
	Global *global;
	Input *input;
	Surface *surface;
	ShellSurface *shellsurface;
	int width, height;
};
