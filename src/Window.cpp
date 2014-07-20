#include "config.h"
#include "Window.h"
#include "Global.h"
#include "Input.h"
#include "Egl.h"
#include <GL/gl.h>

Window::Window(int width, int height)
		: Rectangle(0, 0, width, height)
		, fullscreen(false) {
	display = new Display;
	global = new Global(display->get_registry());
	display->roundtrip();
	input = new Input(this, global->seat);
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
	eglwindow = egl->CreateWindow(surface->cobj, width, height);
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
	window->Resize(width, height);
}

void Window::HandlePopupDone(void *data,
					struct wl_shell_surface *shell_surface){
	//Window *window = static_cast<Window *>(data);
}

void Window::Fullscreen(bool value){
	if(fullscreen == value)
		return;
	fullscreen = value;
	if (value){
		shellsurface->set_fullscreen(WL_SHELL_SURFACE_FULLSCREEN_METHOD_DEFAULT,0,NULL);
		display->dispatch(); /* get configure event and update window size */
	} else {
		shellsurface->set_toplevel();
		Resize(oldwidth, oldheight);
	}
}

void Window::Resize(int w, int h){
	if(SetSize(w, h)){
		eglwindow->Resize(w, h);
		glViewport(0, 0, w, h);
	}
}

void Window::run(){
	while(input->running) {
		display->dispatch();
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
