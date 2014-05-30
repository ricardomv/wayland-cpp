#include "wlplus"
using namespace wayland;

#include "Global.h"

class Window
{
public:
	Window();
	~Window();
	void run();
private:
	Display *display = NULL;
	Global *global = NULL;
};
