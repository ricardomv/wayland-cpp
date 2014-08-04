#include <string.h>

class Global
{
public:
	Registry *registry;
	Compositor *compositor;
	Shell *shell;
	Seat *seat;

	Global(Registry *registry_) : 
		registry(registry_),
		compositor(NULL),
		shell(NULL),
		seat(NULL) {
		static const struct Registry::listener registry_all = {
			Global::HandleGlobal, 
			Global::HandleGlobalRemove
		};
		registry->add_listener((const struct wl_listener *)&registry_all, this);
	}

	~Global(){
		delete shell;
		delete compositor;
		delete seat;
		delete registry;
	}
	static void HandleGlobal(void *data,
				struct wl_registry *reg,
				uint32_t name,
				const char *interface,
				uint32_t version) {
		Global *global = static_cast<Global *>(data);
		if (strcmp(interface, "wl_compositor") == 0) {
			global->compositor = new Compositor(global->registry->bind(name, &wl_compositor_interface, version));
		} else if (strcmp(interface, "wl_output") == 0) {
		} else if (strcmp(interface, "wl_seat") == 0) {
			global->seat = new Seat(global->registry->bind(name, &wl_seat_interface, version));
		} else if (strcmp(interface, "wl_shm") == 0) {
		} else if (strcmp(interface, "wl_text_input_manager") == 0) {
		} else if (strcmp(interface, "wl_shell") == 0){
			global->shell = new Shell(global->registry->bind(name, &wl_shell_interface, version));
		}
	}
	static void HandleGlobalRemove(void *data,
				struct wl_registry *reg, 
				uint32_t name) {
	}
};