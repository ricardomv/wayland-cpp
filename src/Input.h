#include <iostream>
using namespace std;

class Input : public Keyboard, public Pointer
{
	Keyboard *keyboard = NULL;
	Pointer *pointer = NULL;
public:
	~Input() {
		delete keyboard;
		delete pointer;
	}

	void add(struct wl_keyboard *kbrd) {
		keyboard = new Keyboard(kbrd,this);
	}
	void add(struct wl_pointer *ptr) {
		pointer = new Pointer(ptr,this);
	}

	void KbrdHandleKeymap(uint32_t format, int fd, uint32_t size) {
		cout << "HandleKeymap" << endl;
	}
	void KbrdHandleEnter(uint32_t serial, struct wl_surface *surface,
						struct wl_array *keys) {}
	void KbrdHandleLeave(uint32_t serial, struct wl_surface *surface) {}
	void KbrdHandleKey(uint32_t serial, uint32_t time, uint32_t key,
						uint32_t state_w) {}
	void KbrdHandleModifiers(uint32_t serial, uint32_t mods_depressed,
						uint32_t mods_latched, uint32_t mods_locked,
						uint32_t group) {}

	void PtrHandleEnter(uint32_t serial, struct wl_surface *surface,
					wl_fixed_t sx_w, wl_fixed_t sy_w) {}
	void PtrHandleLeave(uint32_t serial, struct wl_surface *surface) {}
	void PtrHandleMotion(uint32_t time, wl_fixed_t sx_w, wl_fixed_t sy_w) {}
	void PtrHandleButton(uint32_t time, uint32_t button, uint32_t state_w) {}
	void PtrHandleAxis(uint32_t time, uint32_t axis, wl_fixed_t value) {}
};