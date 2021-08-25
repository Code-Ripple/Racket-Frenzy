#include <SDL.h>
#include <SDL_image.h>

#include "Game.h"


Game* game = nullptr;

int main(int argc, char* argv[])
{
	const int FPS = 60;
	const int Delay = 1000 / FPS;
	
	Uint32 frameStart{};
	int frameTime;

	game = new Game();
	game->init("Brackeys Game Jam", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, false);

	while (game->running())
	{
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (Delay > frameTime)
		{
			SDL_Delay(Delay - frameTime);
		}
	}

	game->clean();

	return 0;
}