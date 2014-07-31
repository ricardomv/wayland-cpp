#include "config.h"
#include "Window.h"
#include "Global.h"
#include "Input.h"
#include "Egl.h"
#include <GL/gl.h>

Window::Window(int width, int height)
		: Rectangle(0, 0, width, height)
		, running(true)
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

	font = new FTGLTextureFont("/usr/share/fonts/TTF/DejaVuSans.ttf");
	if(font->Error())
		throw "Could no load font";
	font->FaceSize(14);
}

Window::~Window() {
	delete font;
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
		shellsurface->set_fullscreen(ShellSurface::FULLSCREEN_METHOD_DEFAULT,0,NULL);
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
	float ratio;
	int width, height;
	char str[10];
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	while(running) {
		display->dispatch();
		GetSize(&width, &height); /* after configure event */
		ratio = width / (float) height;
		glViewport(0, 0, width, height);

		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0.0f, width,
					0.0f, height,
					-10000.0f, 10000.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glTranslatef(0.0f, (height - font->Ascender()) * 1.0f, 0.0f);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		sprintf(str,"%.1f fps", eglwindow->fps);
		font->Render(str);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
		glMatrixMode(GL_MODELVIEW);

		glLoadIdentity();
		glRotatef((input->pointer_x / width) * 360.0f, 0.f, 1.f, 0.f);
		glRotatef((input->pointer_y / height) * 360.0f, 1.f, 0.f, 0.f);

		//Multi-colored side - FRONT
		glBegin(GL_POLYGON);
			glColor3f( 1.0, 0.0, 0.0 ); glVertex3f(  0.5, -0.5, -0.5 ); // P1 is red
			glColor3f( 0.0, 1.0, 0.0 ); glVertex3f(  0.5,  0.5, -0.5 ); // P2 is green
			glColor3f( 0.0, 0.0, 1.0 ); glVertex3f( -0.5,  0.5, -0.5 ); // P3 is blue
			glColor3f( 1.0, 0.0, 1.0 ); glVertex3f( -0.5, -0.5, -0.5 ); // P4 is purple
		glEnd();

		// White side - BACK
		glBegin(GL_POLYGON);
			glColor3f(   1.0,  1.0, 1.0 );
			glVertex3f(  0.5, -0.5, 0.5 );
			glVertex3f(  0.5,  0.5, 0.5 );
			glVertex3f( -0.5,  0.5, 0.5 );
			glVertex3f( -0.5, -0.5, 0.5 );
		glEnd();

		// Purple side - RIGHT
		glBegin(GL_POLYGON);
			glColor3f(  1.0,  0.0,  1.0 );
			glVertex3f( 0.5, -0.5, -0.5 );
			glVertex3f( 0.5,  0.5, -0.5 );
			glVertex3f( 0.5,  0.5,  0.5 );
			glVertex3f( 0.5, -0.5,  0.5 );
		glEnd();

		// Green side - LEFT
		glBegin(GL_POLYGON);
			glColor3f(   0.0,  1.0,  0.0 );
			glVertex3f( -0.5, -0.5,  0.5 );
			glVertex3f( -0.5,  0.5,  0.5 );
			glVertex3f( -0.5,  0.5, -0.5 );
			glVertex3f( -0.5, -0.5, -0.5 );
		glEnd();

		// Blue side - TOP
		glBegin(GL_POLYGON);
			glColor3f(   0.0,  0.0,  1.0 );
			glVertex3f(  0.5,  0.5,  0.5 );
			glVertex3f(  0.5,  0.5, -0.5 );
			glVertex3f( -0.5,  0.5, -0.5 );
			glVertex3f( -0.5,  0.5,  0.5 );
		glEnd();

		// Red side - BOTTOM
		glBegin(GL_POLYGON);
			glColor3f(   1.0,  0.0,  0.0 );
			glVertex3f(  0.5, -0.5, -0.5 );
			glVertex3f(  0.5, -0.5,  0.5 );
			glVertex3f( -0.5, -0.5,  0.5 );
			glVertex3f( -0.5, -0.5, -0.5 );
		glEnd();
		eglwindow->SwapBuffers();
	}
}
