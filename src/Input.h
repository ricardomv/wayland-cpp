#include <iostream>
using namespace std;

class Input
{
	Seat *seat = NULL;
	Keyboard *keyboard = NULL;
	Pointer *pointer = NULL;
public:
	string name;
	int running = 1;
	Input(Seat *seat_) : seat(seat_) {
		static const struct wl_seat_listener seat_listener = {
			Input::HandleCapabilities,
			Input::HandleName
		};
		seat->add_listener((const struct wl_listener *)&seat_listener, this);
	}
	~Input() {
		delete keyboard;
		delete pointer;
	}

	void add(Keyboard *kbrd) {
		keyboard = kbrd;
		static const struct wl_keyboard_listener kbrd_listeners = {
			Input::KbrdHandleKeymap,
			Input::KbrdHandleEnter,
			Input::KbrdHandleLeave,
			Input::KbrdHandleKey,
			Input::KbrdHandleModifiers
		};
		keyboard->add_listener((const struct wl_listener *)&kbrd_listeners, this);
	}
	void add(Pointer *ptr) {
		pointer = ptr;
		static const struct wl_pointer_listener ptr_listeners = {
			Input::PtrHandleEnter,
			Input::PtrHandleLeave,
			Input::PtrHandleMotion,
			Input::PtrHandleButton,
			Input::PtrHandleAxis
		};
		pointer->add_listener((const struct wl_listener *)&ptr_listeners, this);
	}

	static void HandleCapabilities(void *data, struct wl_seat *seat, uint32_t capabilities){
		Input *input = static_cast<Input*>(data);

		if (capabilities & WL_SEAT_CAPABILITY_POINTER)
			input->add(input->seat->get_pointer());

		if (capabilities & WL_SEAT_CAPABILITY_KEYBOARD)
			input->add(input->seat->get_keyboard());

		if (capabilities & WL_SEAT_CAPABILITY_TOUCH)
			cout << "Touch not implemented" << endl;
	}

	static void HandleName(void *data, struct wl_seat *seat, const char *name){
		Input *input = static_cast<Input*>(data);
		input->name = name;
	}

	static void KbrdHandleKeymap(void *data,
					struct wl_keyboard *kbd,
					uint32_t format,
					int fd,
					uint32_t size) {}

	static void KbrdHandleEnter(void *data,
					struct wl_keyboard *kbd,
					uint32_t serial,
					struct wl_surface *surface,
					struct wl_array *keys) {}

	static void KbrdHandleLeave(void *data,
					struct wl_keyboard *kbd,
					uint32_t serial,
					struct wl_surface *surface) {}

	static void KbrdHandleKey(void *data,
					struct wl_keyboard *kbd,
					uint32_t serial,
					uint32_t time,
					uint32_t key,
					uint32_t state_w) {
		Input *input = static_cast<Input*>(data);
		input->running = 0;
	}

	static void KbrdHandleModifiers(void *data,
					struct wl_keyboard *kbd,
					uint32_t serial,
					uint32_t mods_depressed,
					uint32_t mods_latched,
					uint32_t mods_locked,
					uint32_t group) {}


	static void PtrHandleEnter(void *data,
					struct wl_pointer *ptr,
					uint32_t serial,
					struct wl_surface *surface,
					wl_fixed_t sx_w,
					wl_fixed_t sy_w) {}

	static void PtrHandleLeave(void *data,
					struct wl_pointer *ptr,
					uint32_t serial,
					struct wl_surface *surface) {}

	static void PtrHandleMotion(void *data,
					struct wl_pointer *ptr,
					uint32_t time,
					wl_fixed_t sx_w,
					wl_fixed_t sy_w) {}

	static void PtrHandleButton(void *data,
					struct wl_pointer *ptr,
					uint32_t serial,
					uint32_t time,
					uint32_t button,
					uint32_t state_w) {}

	static void PtrHandleAxis(void *data,
					struct wl_pointer *ptr,
					uint32_t time,
					uint32_t axis,
					wl_fixed_t value) {}
};
