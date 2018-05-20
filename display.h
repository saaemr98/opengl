#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include <SDL2\SDL.h>

class Display {
public:
	Display(int width, int height, const std::string& title);	// SDL will ask OS to make a window, as OS is in control of that

	void Update();
	bool IsClosed();
	void Clear(float r, float b, float g, float a);

	virtual ~Display();

private:
	Display(const Display& other) {};
	Display& operator=(const Display& rhs){};

	SDL_Window* m_window; // this will hold in some of the variable of our window check display.cpp (the actual window)
	SDL_GLContext m_glContext; // this will allow OpenGL to edit a window using the GPU, explained at the bottom of why it is needed
	bool m_isClosed;
};

#endif

// As discussed SDL normally asks OS to make a window
// However we have an issue when using OpenGL
// OpenGL send its instructions to the GPU (makes sense)
// GPU has no control over what happens to the window
// Therefore OS allows access to the window for the GPU (this will reduces some control of the OS on the window)
