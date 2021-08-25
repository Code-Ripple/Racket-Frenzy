#include <SDL.h>
#include <SDL_image.h>

#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* texture, SDL_Renderer* render)
{
	SDL_Surface* tempSurface = IMG_Load(texture);
	SDL_Texture* theTexture = SDL_CreateTextureFromSurface(render, tempSurface);
	SDL_FreeSurface(tempSurface);

	return theTexture;
}