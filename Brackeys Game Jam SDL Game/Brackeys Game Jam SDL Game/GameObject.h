#pragma once
#include <SDL.h>
#include "Game.h"

class GameObject
{
public:
	GameObject(const char* textures, SDL_Renderer* renderer, int xpos, int ypos);

	void Update();
	void Render();
private:
	int x;
	int y;
	SDL_Texture* objectTexture;
	SDL_Rect src;
	SDL_Rect dst;
	SDL_Renderer* renderer;
};