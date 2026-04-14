#pragma once

#ifndef YSXSDLTEXT_H
#define YSXSDLTEXT_H


// SDL STUFFS:
// Uncomment if you have that directory tree:
#ifdef USE_SDL3
#include "SDL3/SDL.h"
//#include "SDL3_ttf/SDL_ttf.h"
#include "SDL3_ttf/SDL_textengine.h"
#endif
#ifdef USE_SDL2
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#endif


// #####################
// ####### By Sophia Cristina
// ####### Using TTF lib to make functions for different types of text plotting.
// #####################

#include "../Graph/ysxSDLGraphs.h"

// #################################################
// REFERENCES:
// [1] https://www.libsdl.org/projects/old/SDL_ttf/docs/SDL_ttf_frame.html
// #################################################


// #################################################
// FUNCTIONS:
// #################################################

// #################################################
// CLASSES:
// #################################################

/*class A
{
public:
	A()
	{
	}

	~A()
	{
	}
};*/


// #################################################
// #################################################
// #################################################

#endif
