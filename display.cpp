#include <iostream>
#include <string>
#include <GL/glew.h>
#include "display.h"

Display::Display( int width, int height, const std::string& title) {
	SDL_Init(SDL_INIT_EVERYTHING); // initialises everything for the window

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);	// sets the number of red shades to 2^8, 2^8 shades of any colour is good enough, gives you atleast 8 bits not exactly 8 bits.
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);	// transparency
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32); // how much data in bits that SDL will allocate for a single pixel (8 + 8 + 8 + 8)
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // allocate space for 2 windows, but will only create 1, to understand more read on the Update() function

	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL); // SDL does not take in a C++ string, but instead takes in C. SDL is a C API
	m_glContext = SDL_GL_CreateContext(m_window); // allows gpu to access window (basically for OpenGL to make changes to the window)

	GLenum status = glewInit(); // initialise glew, searches through OS for every single OpenGL function that we support

	if (status != GLEW_OK) {
		std::cerr << "GLEW failed to initialise" << std::endl;
	}

	m_isClosed = false;
}

Display::~Display() {
	SDL_GL_DeleteContext(m_glContext); // delete the context, we dont want the GPU to have further control
	SDL_DestroyWindow(m_window);	   // delete the window,
	SDL_Quit();							// delete the variable the in the opposite direction you created them
}

void Display::Update() {
	SDL_GL_SwapWindow(m_window);	// We said that we have allocated memory for 2 windows, 1 half of the memory is used to display the drawing the other half of memory is used by OpenGL to make a drawing
									// when we swap the buffers the memory initially allocated for OpenGL goes to the memory allocated for the window, and the memory initially allocated for the window 
									// goes to OpenGL, therefore the window will never display an incomplete/half done drawing

	SDL_Event e;					// the below code will help us handle events done to the window by the OS, or the OS will think that the program is not repsonding and crash

	while (SDL_PollEvent(&e)) {		// Will poll for any OS events, e, the event is stored in the address of e
		if (e.type == SDL_QUIT) {	// at the moment we are just handling whether the window is closed or not
			m_isClosed = true;
		}
	}
}

bool Display::IsClosed() {
	return m_isClosed;
}

void Display::Clear(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);		// clears the colour buffer, all the pixels are the colour stated above
}