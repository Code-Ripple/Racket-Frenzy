#pragma once
#include <SDL.h>
#include <SDL_image.h>

class RenderImage
{
public:
	SDL_Texture* loadTexture(const char* p_filename);

	void Clear();
	static void Render(SDL_Texture* p_texture);
	void Display();

};