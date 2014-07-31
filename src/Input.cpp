#include "Input.h"
#include "Window.h"

Input::Input(Window *window_, Seat *seat_)
				: window(window_)
				, seat(seat_) {
	static const struct wl_seat_listener seat_listener = {
		Input::HandleCapabilities,
		Input::HandleName
	};
	seat->add_listener((const struct wl_listener *)&seat_listener, this);
}
Input::~Input() {
	delete keyboard;
	delete pointer;
}

void Input::add(Keyboard *kbrd) {
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
void Input::add(Pointer *ptr) {
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

//static
void Input::HandleCapabilities(void *data, struct wl_seat *wl_seat, uint32_t capabilities){
	Input *input = static_cast<Input*>(data);

	if (capabilities & Seat::CAPABILITY_POINTER)
		input->add(input->seat->get_pointer());

	if (capabilities & Seat::CAPABILITY_KEYBOARD)
		input->add(input->seat->get_keyboard());

	if (capabilities & Seat::CAPABILITY_TOUCH)
		cout << "Touch not implemented" << endl;
}

//static
void Input::HandleName(void *data, struct wl_seat *seat, const char *name){
	Input *input = static_cast<Input*>(data);
	input->name = name;
}

//static
void Input::KbrdHandleKeymap(void *data,
				struct wl_keyboard *kbd,
				uint32_t format,
				int fd,
				uint32_t size) {}

//static
void Input::KbrdHandleEnter(void *data,
				struct wl_keyboard *kbd,
				uint32_t serial,
				struct wl_surface *surface,
				struct wl_array *keys) {}

//static
void Input::KbrdHandleLeave(void *data,
				struct wl_keyboard *kbd,
				uint32_t serial,
				struct wl_surface *surface) {}

//static
void Input::KbrdHandleKey(void *data,
				struct wl_keyboard *kbd,
				uint32_t serial,
				uint32_t time,
				uint32_t key,
				uint32_t state_w) {
	Input *input = static_cast<Input*>(data);
	if (state_w == Keyboard::KEY_STATE_PRESSED){
		if (key == 1) /* Esc */
			input->window->running = 0;
		if (key == 33) /* F */
			input->window->Fullscreen(!input->window->fullscreen);
	}
}

//static
void Input::KbrdHandleModifiers(void *data,
				struct wl_keyboard *kbd,
				uint32_t serial,
				uint32_t mods_depressed,
				uint32_t mods_latched,
				uint32_t mods_locked,
				uint32_t group) {}


//static
void Input::PtrHandleEnter(void *data,
				struct wl_pointer *ptr,
				uint32_t serial,
				struct wl_surface *surface,
				wl_fixed_t sx_w,
				wl_fixed_t sy_w) {}

//static
void Input::PtrHandleLeave(void *data,
				struct wl_pointer *ptr,
				uint32_t serial,
				struct wl_surface *surface) {}

//static
void Input::PtrHandleMotion(void *data,
				struct wl_pointer *ptr,
				uint32_t time,
				wl_fixed_t sx_w,
				wl_fixed_t sy_w) {
	Input *input = static_cast<Input*>(data);
	input->pointer_x = wl_fixed_to_double(sx_w);
	input->pointer_y = wl_fixed_to_double(sy_w);
}

//static
void Input::PtrHandleButton(void *data,
				struct wl_pointer *ptr,
				uint32_t serial,
				uint32_t time,
				uint32_t button,
				uint32_t state_w) {}

//static
void Input::PtrHandleAxis(void *data,
				struct wl_pointer *ptr,
				uint32_t time,
				uint32_t axis,
				wl_fixed_t value) {}