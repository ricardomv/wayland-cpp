#include "Window.h"
#include <wayland-egl.h>
#include <egl.h>

struct egl_ui {
	EGLDisplay dpy;
	EGLConfig argb_config;
	EGLContext argb_ctx;
};

struct window{
	int width, height;
	struct wayland_t *ui;

	struct wl_egl_window *egl_window;
	EGLSurface egl_surface;
	EGLDisplay dpy;

};

Window::Window(){
	display = Display::connect(NULL);
	global = new Global(display->get_registry());
	display->roundtrip();
	input = new Input();
	input->add(global->seat->get_keyboard());
	input->add(global->seat->get_pointer());
	Surface *surface = global->compositor->create_surface();
	ShellSurface *shellsurface = global->shell->get_shell_surface(surface);
	shellsurface->set_toplevel();
	shellsurface->set_fullscreen(WL_SHELL_SURFACE_FULLSCREEN_METHOD_DEFAULT,0,NULL);

	struct egl_ui egl;
	EGLint major, minor;
	EGLint n;
	EGLint *context_attribs = NULL;

	static const EGLint argb_cfg_attribs[] = {
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		EGL_RED_SIZE, 1,
		EGL_GREEN_SIZE, 1,
		EGL_BLUE_SIZE, 1,
		EGL_ALPHA_SIZE, 1,
		EGL_DEPTH_SIZE, 1,
		EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
		EGL_NONE
	};


	egl.dpy = eglGetDisplay((struct wl_display *)display->proxy_);
	if (!eglInitialize(egl.dpy, &major, &minor)) {
		fprintf(stderr, "failed to initialize EGL\n");
	}

	if (!eglBindAPI(EGL_OPENGL_API)) {
		fprintf(stderr, "failed to bind EGL client API\n");
	}

	if (!eglChooseConfig(egl.dpy, argb_cfg_attribs,
			     &egl.argb_config, 1, &n) || n != 1) {
		fprintf(stderr, "failed to choose argb EGL config\n");
	}
	egl.argb_ctx = eglCreateContext(egl.dpy, egl.argb_config,
				       EGL_NO_CONTEXT, context_attribs);
	if (!egl.argb_ctx) {
		fprintf(stderr, "failed to create EGL context\n");
	}
	struct window window;

	window.width = 300;
	window.height = 300;

	window.dpy = egl.dpy;

	window.egl_window = wl_egl_window_create((struct wl_surface *)surface->proxy_,
							window.width,
							window.height);

	window.egl_surface = eglCreateWindowSurface(egl.dpy,
							egl.argb_config,
							window.egl_window,
							NULL);
}

Window::~Window() {
	delete input;
	delete global;
	display->disconnect();
	delete display;
}

void Window::run(){
	while(1) {
		display->dispatch();
	}
}
