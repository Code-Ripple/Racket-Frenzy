#include <SDL.h>
#include <SDL_image.h>
#include <cstdlib>
#include <stdlib.h>
#include <iostream>

#include "BlockSpawner.h"



BlockSpawner::BlockSpawner(float p_x, float p_y, SDL_Texture* p_texture)
{
	rect.h = 10;
	rect.w = 10;
}

void BlockSpawner::UpdateObject()
{
	
}

SDL_Texture* BlockSpawner::getTexture()
{
	return texture;
}

SDL_Rect BlockSpawner::getRect()
{
	return rect;
}