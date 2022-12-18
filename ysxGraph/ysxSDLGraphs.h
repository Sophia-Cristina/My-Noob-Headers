#pragma once

#ifndef YSXSDLGRAPHS_H
#define YSXSDLGRAPHS_H

// #####################
// ####### By Sophia Cristina
// #######
// #####################

/*#################################################
REFERENCES:
[1] Window: https://www.youtube.com/watch?v=qPHKWsZK2Jc
#################################################*/


// ###############################################################################################################################################################################
// ###############################################################################################################################################################################
// ###############################################################################################################################################################################

/* CREATE WINDOW AND SHOW IT RIGHT AT CLASS CONSTRUCTION:
FLAGS:
SDL_WINDOW_FULLSCREEN: fullscreen window
SDL_WINDOW_FULLSCREEN_DESKTOP: fullscreen window at desktop resolution
SDL_WINDOW_OPENGL: window usable with an OpenGL context
SDL_WINDOW_VULKAN: window usable with a Vulkan instance
SDL_WINDOW_METAL: window usable with a Metal instance
SDL_WINDOW_HIDDEN: window is not visible
SDL_WINDOW_BORDERLESS: no window decoration
SDL_WINDOW_RESIZABLE: window can be resized
SDL_WINDOW_MINIMIZED: window is minimized
SDL_WINDOW_MAXIMIZED: window is maximized
SDL_WINDOW_INPUT_GRABBED: window has grabbed input focus
SDL_WINDOW_ALLOW_HIGHDPI: window should be created in high-DPI mode if supported (>= SDL 2.0.1)

SDL_WINDOW_SHOWN is ignored by SDL_CreateWindow(). The SDL_Window is implicitly shown if SDL_WINDOW_HIDDEN is not set.
SDL_WINDOW_SHOWN may be queried later using SDL_GetWindowFlags().*/
template <const uint16_t xpos, const uint16_t ypos, const uint16_t xsize, const uint16_t ysize>
class ysxSDL_Window
{
public:
	SDL_Window* Win = nullptr;

	ysxSDL_Window(std::string Title, uint32_t Flags)
	{
		Win = SDL_CreateWindow(Title.data(), xpos, ypos, xsize, ysize, Flags);
		if (!Win)
		{
			std::cerr << "Window not created! " << SDL_GetError() << "!\n";
		}
	}

	~ysxSDL_Window()
	{
		SDL_DestroyWindow(Win);
	}
};

// ###############################################################################################################################################################################
// ####### MAIN #################################################################################################################################################################
// ###############################################################################################################################################################################

#endif // SCPARSE_