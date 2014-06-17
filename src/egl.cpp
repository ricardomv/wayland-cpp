#include <wayland-egl.h>
#include <cairo-gl.h>
#include <stdio.h>

struct egl_ui {
	EGLDisplay dpy;
	EGLConfig argb_config;
	EGLContext argb_ctx;
	cairo_device_t *argb_device;
};

struct window{
	int width, height;

	struct wl_egl_window *egl_window;
	EGLSurface egl_surface;
	EGLDisplay dpy;

	cairo_surface_t *cairo_surface;
};

void test_egl(struct wl_display *display, struct wl_surface *surface){
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


	egl.dpy = eglGetDisplay(display);
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
	egl.argb_device = cairo_egl_device_create(egl.dpy, egl.argb_ctx);
	if (cairo_device_status(egl.argb_device) != CAIRO_STATUS_SUCCESS) {
		fprintf(stderr, "failed to get cairo EGL argb device\n");
	}
	struct window window;

	window.width = 300;
	window.height = 300;

	window.dpy = egl.dpy;

	window.egl_window = wl_egl_window_create(surface,
							window.width,
							window.height);

	window.egl_surface = eglCreateWindowSurface(egl.dpy,
							egl.argb_config,
							window.egl_window,
							NULL);
	window.cairo_surface =
		cairo_gl_surface_create_for_egl(egl.argb_device,
							window.egl_surface,
							window.width,
							window.height);

	cairo_t *cr;
	cr = cairo_create(window.cairo_surface);

	cairo_save(cr); // save the state of the context
	cairo_set_source_rgb(cr, 0.86, 0.85, 0.47);
	cairo_paint(cr); // fill image with the color
	cairo_restore(cr); // color is back to black now

	cairo_save(cr);
	// draw a border around the image
	cairo_set_line_width(cr, 20.0); // make the line wider
	cairo_rectangle(cr, 0.0, 0.0, window.width, window.height);
	cairo_stroke(cr);

	cairo_set_source_rgba(cr, 0.0, 0.0, 0.0, 0.7);
	// draw a circle in the center of the image
	cairo_arc(cr, window.width / 2.0, window.height / 2.0, window.height / 4.0, 0.0, 2.0 * 3.142);
	cairo_stroke(cr);

	// draw a diagonal line
	cairo_move_to(cr, window.width / 4.0, window.height / 4.0);
	cairo_line_to(cr, window.width * 3.0 / 4.0, window.height * 3.0 / 4.0);
	cairo_stroke(cr);
	cairo_restore(cr);

	cairo_destroy(cr);

	cairo_gl_surface_swapbuffers(window.cairo_surface);

	wl_egl_window_destroy(window.egl_window);
	eglDestroySurface(window.dpy,window.egl_surface);
	cairo_surface_destroy(window.cairo_surface);

	cairo_device_destroy(egl.argb_device);
	eglMakeCurrent(egl.dpy, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
	eglTerminate(egl.dpy);
	eglReleaseThread();
}
