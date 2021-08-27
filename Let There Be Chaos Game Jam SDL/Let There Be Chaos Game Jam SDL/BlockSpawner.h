#pragma once
#include <SDL.h>
#include <SDL_image.h>

class BlockSpawner
{
public:
	
	BlockSpawner(float p_x, float p_y, SDL_Texture* p_texture);

	static void UpdateObject();

	SDL_Rect getRect();
	SDL_Texture* getTexture();
	bool getHitObject();


private:
	SDL_Texture* texture;
	SDL_Rect rect;
	bool hitObject = false;
};