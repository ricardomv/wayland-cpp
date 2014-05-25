#include <iostream>
#include <string.h>

#include <wlplus>

using namespace wayland;
using namespace std;

class Global : public Registry
{
public:
	using Registry::Registry;

	Compositor *compositor = NULL;
	Shell *shell = NULL;
	Seat *seat = NULL;
	~Global(){
		delete shell;
		delete compositor;
		delete seat;
	}
	void HandleGlobal(
				uint32_t name,
				const char *interface,
				uint32_t version) override {
		if (strcmp(interface, "wl_compositor") == 0) {
			compositor = new Compositor(bind(name, &wl_compositor_interface, version));
		} else if (strcmp(interface, "wl_output") == 0) {
		} else if (strcmp(interface, "wl_seat") == 0) {
			seat = new Seat(bind(name, &wl_seat_interface, version));
		} else if (strcmp(interface, "wl_shm") == 0) {
		} else if (strcmp(interface, "wl_text_input_manager") == 0) {
		} else if (strcmp(interface, "wl_shell") == 0){
			shell = new Shell(bind(name, &wl_shell_interface, version));
		}
	}
	void HandleGlobalRemove(uint32_t name) override {
	}
};