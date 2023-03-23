#pragma once

#ifndef YSXSDL_H
#define YSXSDL_H

// SDL LIBS:
#pragma comment (lib, "SDL2test.lib")
#pragma comment (lib, "SDL2main.lib")
#pragma comment (lib, "SDL2.lib") // Be sure that you have built SDL2 lib!
#pragma comment (lib, "SDL3_test.lib")
#pragma comment (lib, "SDL3.lib") // Be sure that you have built SDL3 lib!

// SDL STUFFS:
#ifdef USE_SDL3
#include "include/SDL3/SDL.h"
#include "include/SDL3/SDL_syswm.h"
#endif
#ifdef USE_SDL2
#include "SDL-SDL2/include/SDL.h"
#include "SDL-SDL2/include/SDL_syswm.h"
#endif

// MY HEADERS AS A GUIDE TO USE SDL:
#include "ysxLibsUtils/SDL/ysxSDLWindow.h"
#include "ysxLibsUtils/SDL/Audio/ysxSDLAudio.h"
#ifdef main
#undef main
#endif

// #####################
// ####### By Sophia Cristina
// #######
// #####################

/*#################################################
REFERENCES:
[1] PollEvent: https://www.youtube.com/watch?v=FwRfH2bA48M
	[1.1] Examples: https://www.youtube.com/watch?v=EBHmMmiVtCk
	SDL_AUDIODEVICEADDED
	SDL_AUDIODEVICEREMOVED
	
	SDL_CONTROLLERAXISMOTION
	
	SDL_CONTROLLERBUTTONDOWN
	SDL_CONTROLLERBUTTONUP
	
	SDL_CONTROLLERDEVICEADDED
	SDL_CONTROLLERDEVICEREMOVED
	SDL_CONTROLLERDEVICEREMAPPED
	
	SDL_DOLLARGESTURE
	SDL_DOLLARRECORD
	
	SDL_DROPFILE
	SDL_DROPTEXT
	SDL_DROPBEGIN
	SDL_DROPCOMPLETE
	
	SDL_FINGERMOTION
	SDL_FINGERDOWN
	SDL_FINGERUP
	
	SDL_KEYDOWN
	SDL_KEYUP

	SDL_JOYAXISMOTION
	
	SDL_JOYBALLMOTION

	SDL_JOYHATMOTION

	SDL_JOYBUTTONDOWN
	SDL_JOYBUTTONUP

	SDL_JOYDEVICEADDED
	SDL_JOYDEVICEREMOVED

	SDL_MOUSEMOTION

	SDL_MOUSEBUTTONDOWN
	SDL_MOUSEBUTTONUP

	SDL_MOUSEWHEEL

	SDL_MULTIGESTURE

	SDL_QUIT

	SDL_SYSWMEVENT

	SDL_TEXTEDITING

	SDL_TEXTINPUT

	SDL_USEREVENT

	SDL_WINDOWEVENT
#################################################*/

// #################################################
// #################################################
// #################################################

#endif // SCPARSE_