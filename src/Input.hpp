#include "wlplus"
#include <iostream>
using namespace wayland;
using namespace std;

class Window;

class Input
{
	Window *window;
	Seat *seat = NULL;
	Keyboard *keyboard = NULL;
	Pointer *pointer = NULL;
public:
	string name;
	float pointer_x;
	float pointer_y;

	Input(Window *window_, Seat *seat_);
	~Input();

	void add(Keyboard *kbrd);
	void add(Pointer *ptr);

	static void HandleCapabilities(void *data, struct wl_seat *seat, uint32_t capabilities);
	static void HandleName(void *data, struct wl_seat *seat, const char *name);

	static void KbrdHandleKeymap(void *data,
					struct wl_keyboard *kbd,
					uint32_t format,
					int fd,
					uint32_t size);
	static void KbrdHandleEnter(void *data,
					struct wl_keyboard *kbd,
					uint32_t serial,
					struct wl_surface *surface,
					struct wl_array *keys);
	static void KbrdHandleLeave(void *data,
					struct wl_keyboard *kbd,
					uint32_t serial,
					struct wl_surface *surface);
	static void KbrdHandleKey(void *data,
					struct wl_keyboard *kbd,
					uint32_t serial,
					uint32_t time,
					uint32_t key,
					uint32_t state_w);
	static void KbrdHandleModifiers(void *data,
					struct wl_keyboard *kbd,
					uint32_t serial,
					uint32_t mods_depressed,
					uint32_t mods_latched,
					uint32_t mods_locked,
					uint32_t group);
	static void KbrdHandleRepeatInfo(void *data,
					struct wl_keyboard *wl_keyboard,
					int32_t rate,
					int32_t delay);

	static void PtrHandleEnter(void *data,
					struct wl_pointer *ptr,
					uint32_t serial,
					struct wl_surface *surface,
					wl_fixed_t sx_w,
					wl_fixed_t sy_w);
	static void PtrHandleLeave(void *data,
					struct wl_pointer *ptr,
					uint32_t serial,
					struct wl_surface *surface);
	static void PtrHandleMotion(void *data,
					struct wl_pointer *ptr,
					uint32_t time,
					wl_fixed_t sx_w,
					wl_fixed_t sy_w);
	static void PtrHandleButton(void *data,
					struct wl_pointer *ptr,
					uint32_t serial,
					uint32_t time,
					uint32_t button,
					uint32_t state_w);
	static void PtrHandleAxis(void *data,
					struct wl_pointer *ptr,
					uint32_t time,
					uint32_t axis,
					wl_fixed_t value);
};
