#include <iostream>
using namespace std;

class Input
{
	Keyboard *keyboard = NULL;
	Pointer *pointer = NULL;
public:
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

	static void KbrdHandleKeymap(void *data, struct wl_keyboard *kbd, uint32_t format, int fd, uint32_t size) {
		cout << "KbrdHandleKeymap" << endl;
	}
	static void KbrdHandleEnter(void *data, struct wl_keyboard *kbd, uint32_t serial, struct wl_surface *surface,
						struct wl_array *keys) {}
	static void KbrdHandleLeave(void *data, struct wl_keyboard *kbd, uint32_t serial, struct wl_surface *surface) {}
	static void KbrdHandleKey(void *data, struct wl_keyboard *kbd, uint32_t serial, uint32_t time, uint32_t key,
						uint32_t state_w) {}
	static void KbrdHandleModifiers(void *data, struct wl_keyboard *kbd, uint32_t serial, uint32_t mods_depressed,
						uint32_t mods_latched, uint32_t mods_locked,
						uint32_t group) {}

	static void PtrHandleEnter(void *data, struct wl_pointer *ptr, uint32_t serial, struct wl_surface *surface,
					wl_fixed_t sx_w, wl_fixed_t sy_w) {
		cout << "Ptr" << endl;
	}
	static void PtrHandleLeave(void *data, struct wl_pointer *ptr, uint32_t serial, struct wl_surface *surface) {}
	static void PtrHandleMotion(void *data, struct wl_pointer *ptr, uint32_t time, wl_fixed_t sx_w, wl_fixed_t sy_w) {}
	static void PtrHandleButton(void *data, struct wl_pointer *ptr, uint32_t serial, uint32_t time, uint32_t button, uint32_t state_w) {}
	static void PtrHandleAxis(void *data, struct wl_pointer *ptr, uint32_t time, uint32_t axis, wl_fixed_t value) {}
};
