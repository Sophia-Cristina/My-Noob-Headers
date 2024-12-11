#pragma once

#ifndef YSXSDLGRAPHS_H
#define YSXSDLGRAPHS_H

// #####################
// ####### By Sophia Cristina
// ####### Related to graph processing, manipulation, modulation and etc...
// #####################

/*#################################################
REFERENCES:
 [1]
#################################################*/


// ###############################################################################################################################################################################
// ###############################################################################################################################################################################
// ###############################################################################################################################################################################

// #################################################

struct ysxSDL_Texture_SpriteData { SDL_Rect Pos; SDL_Texture* Sprite; };

// #################################################

void ysxSDL_Surf_PlotInstant(uint64_t x, uint64_t y, SDL_Surface* Sprite, SDL_Surface* Surf, SDL_Window* Win)
{
	SDL_Rect Pos;
	if (Sprite && Surf && Win)
	{
		Pos.x = x; Pos.y = y;
		SDL_BlitSurface(Sprite, NULL, Surf, &Pos);
		//SDL_UpdateWindowSurface(Win);
	}
}

void ysxSDL_Texture_LoadImg(SDL_Texture* Sprite, std::string Path, SDL_Renderer* Renderer)
{
	//SDL_Surface* Get = IMG_Load(Path.data()); // Fix later, it is not letting me compile unrelated things
	//Sprite = SDL_CreateTextureFromSurface(Renderer, Get);
	//SDL_FreeSurface(Get);
}

void ysxSDL_Texture_Render(SDL_Renderer* Renderer, SDL_Texture* Texture, uint16_t x, uint16_t y)
{
    SDL_Rect Pos;
    Pos.x = x; Pos.y = y;
    
    // Get the width and height of the texture
    SDL_QueryTexture(Texture, NULL, NULL, &Pos.w, &Pos.h);
    
    // Render the texture to the screen
    SDL_RenderCopy(Renderer, Texture, NULL, &Pos);
}

void ysxSDL_Texture_Render(ysxSDL_Texture_SpriteData* Data, SDL_Renderer* Renderer)
{
    // Get the width and height of the texture
    SDL_QueryTexture(Data->Sprite, NULL, NULL, &Data->Pos.w, &Data->Pos.h);
    
    // Render the texture to the screen
    SDL_RenderCopy(Renderer, Data->Sprite, NULL, &Data->Pos);
}


// CLASS FOR SMALL USEFUL SPRITE FUNCTIONS, LIKE RENDERING:
// !!! Attention: 'SDL_Renderer*' is not cleaned by this class, because it should point to the renderer that you are currently using. !!!
class ysxSDL_SPRITE_Manager
{
public:
	std::vector<ysxSDL_Texture_SpriteData> Sprites;
	SDL_Renderer* Renderer;
	// #################################################

	
	void RenderAllSprites()
	{
		SDL_RenderClear(Renderer); // Clear the current rendering target with the drawing color.
		for (size_t n = 0; n < Sprites.size(); ++n)
		{
			SDL_RenderCopy(Renderer, Sprites[n].Sprite, NULL, &Sprites[n].Pos);
		}
	}
	

	// #################################################

	ysxSDL_SPRITE_Manager()
	{
	}

	~ysxSDL_SPRITE_Manager()
	{

		for (size_t n = 0; n < Sprites.size(); ++n)
		{
			SDL_DestroyTexture(Sprites[n].Sprite);
		}
	}
};

// ###############################################################################################################################################################################
// ####### MAIN #################################################################################################################################################################
// ###############################################################################################################################################################################

#endif // SCPARSE_
