#include "config.h"
#include "Window.h"
#include "Global.h"
#include "Input.h"
#include "Egl.h"
#include <GL/gl.h>

Window::Window()
		: width(300)
		, height(300){
	display = new Display;
	global = new Global(display->get_registry());
	display->roundtrip();
	input = new Input(global->seat);
	surface = global->compositor->create_surface();
	shellsurface = global->shell->get_shell_surface(surface);
	static const struct wl_shell_surface_listener shell_surface_listener = {
		Window::HandlePing,
		Window::HandleConfigure,
		Window::HandlePopupDone
	};
	shellsurface->add_listener((const struct wl_listener *)&shell_surface_listener, this);
	shellsurface->set_title("cairo-wayland-cpp");
	shellsurface->set_toplevel();
	egl = new Egl(display->cobj);
	eglwindow = egl->CreateWindow(surface->cobj,width,height);
}

Window::~Window() {
	delete eglwindow;
	delete egl;
	delete shellsurface;
	delete surface;
	delete input;
	delete global;
	delete display;
}

void Window::HandlePing(void *data,
					struct wl_shell_surface *shell_surface,
					uint32_t serial){
	Window *window = static_cast<Window *>(data);
	window->shellsurface->pong(serial);
}

void Window::HandleConfigure(void *data,
					struct wl_shell_surface *shell_surface,
					uint32_t edges,
					int32_t width,
					int32_t height){
	Window *window = static_cast<Window *>(data);
	window->width = width;
	window->height = height;
	if (window->eglwindow)
		window->eglwindow->Resize(width, height);
}

void Window::HandlePopupDone(void *data,
					struct wl_shell_surface *shell_surface){
	//Window *window = static_cast<Window *>(data);
}

void Window::run(){
	while(input->running) {
		display->dispatch();
		glViewport(0,0,width,height);
		glClearColor(0.0f, 0.8f, 0.0f, 0.5f);
		glClear(GL_COLOR_BUFFER_BIT);
		glBegin(GL_TRIANGLES);
	        glColor3f(1.f, 0.f, 0.f);
	        glVertex3f(-0.6f, -0.4f, 0.f);
	        glColor3f(0.f, 1.f, 0.f);
	        glVertex3f(0.6f, -0.4f, 0.f);
	        glColor3f(0.f, 0.f, 1.f);
	        glVertex3f(0.f, 0.6f, 0.f);
	    glEnd();
		eglwindow->SwapBuffers();
	}
}
