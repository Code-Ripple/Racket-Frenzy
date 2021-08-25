#include <SDL.h>
#include <SDL_image.h>

#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* textures, SDL_Renderer* rendererHere, int xpos, int ypos)
{
	renderer = rendererHere;
	objectTexture = TextureManager::LoadTexture(textures, rendererHere);
	
	x = xpos;
	y = ypos;

}

void GameObject::Update()
{


	src.h = 100;
	src.w = 100;
	src.x = 0;
	src.y = 0;

	dst.x = x;
	dst.y = y;
	dst.w = src.w;
	dst.h = src.h;
	
	x--;
	y--;
}

void GameObject::Render()
{
	SDL_RenderCopy(renderer, objectTexture, &src, &dst);
}