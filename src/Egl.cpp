#include "Egl.h"
#include <GL/gl.h>
#include <sys/time.h>

Egl::Egl(struct wl_display *wl_dpy) {
	EGLint major, minor, n;
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

	display = eglGetDisplay(wl_dpy);
	if (!eglInitialize(display, &major, &minor)) {
		fprintf(stderr, "failed to initialize EGL\n");
	}

	if (!eglBindAPI(EGL_OPENGL_API)) {
		fprintf(stderr, "failed to bind EGL client API\n");
	}

	if (!eglChooseConfig(display, argb_cfg_attribs,
				&argb_config, 1, &n) || n != 1) {
		fprintf(stderr, "failed to choose argb EGL config\n");
	}
	argb_ctx = eglCreateContext(display, argb_config,
				EGL_NO_CONTEXT, NULL);
	if (!argb_ctx) {
		fprintf(stderr, "failed to create EGL context\n");
	}
}

Egl::~Egl(){
	eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
	eglDestroyContext(display, argb_ctx);
	eglTerminate(display);
	eglReleaseThread();
}

EglWindow *Egl::CreateWindow(struct wl_surface* surface, int width, int height){
	return new EglWindow(this,
		wl_egl_window_create(surface,
							width,
							height));
}


EglWindow::EglWindow(Egl *egl_, struct wl_egl_window *window)
					: egl(egl_)
					, egl_window(window)
					, frames(0)
					, benchmark_time(0) {
	egl_surface = eglCreateWindowSurface(egl->display,
							egl->argb_config,
							window,
							NULL);
	eglMakeCurrent(egl->display, egl_surface, egl_surface, egl->argb_ctx);
	eglSwapInterval(egl->display, 1);
}

EglWindow::~EglWindow(){
	eglMakeCurrent(egl->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
	eglDestroySurface(egl->display, egl_surface);
	wl_egl_window_destroy(egl_window);
}

void EglWindow::Resize(int width, int height){
	wl_egl_window_resize(egl_window, width, height, 0, 0);
}

void EglWindow::SwapBuffers(){
	struct timeval tv;
	uint32_t mstime;

	gettimeofday(&tv, NULL);
	mstime = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	frames++;

	if((mstime - benchmark_time) > 200) /* update fps every 200 ms */
	{
		//  calculate the number of frames per second
		fps = frames / ((mstime - benchmark_time) / 1000.0f);
		//  Set time
		benchmark_time = mstime;
		//  Reset frame count
		frames = 0;
	}
	eglSwapBuffers(egl->display, egl_surface);
}
