#include <iostream>
#include <string.h>

#include <wlplus>

using namespace wayland;
using namespace std;

class Global
{
	Registry *registry_ = NULL;
public:
	Compositor *compositor = NULL;
	Shell *shell = NULL;
	Seat *seat = NULL;
	Global(Registry *registry) : registry_(registry) {
		static const struct wl_registry_listener registry_all = { Global::HandleGlobal, Global::HandleGlobalRemove};
		registry_->add_listener((const struct wl_listener *)&registry_all, (void *)this);
	}
	~Global(){
		delete shell;
		delete compositor;
		delete seat;
	}
	static void HandleGlobal(void *data,
				struct wl_registry *reg,
				uint32_t name,
				const char *interface,
				uint32_t version) {
		Global *global = static_cast<Global *>(data);
		if (strcmp(interface, "wl_compositor") == 0) {
			global->compositor = new Compositor(global->registry_->bind(name, &wl_compositor_interface, version));
		} else if (strcmp(interface, "wl_output") == 0) {
		} else if (strcmp(interface, "wl_seat") == 0) {
			global->seat = new Seat(global->registry_->bind(name, &wl_seat_interface, version));
		} else if (strcmp(interface, "wl_shm") == 0) {
		} else if (strcmp(interface, "wl_text_input_manager") == 0) {
		} else if (strcmp(interface, "wl_shell") == 0){
			global->shell = new Shell(global->registry_->bind(name, &wl_shell_interface, version));
		}
	}
	static void HandleGlobalRemove(void *data, struct wl_registry *registry, uint32_t name){
		//Global *global = static_cast<Global *>(data);
	}
};