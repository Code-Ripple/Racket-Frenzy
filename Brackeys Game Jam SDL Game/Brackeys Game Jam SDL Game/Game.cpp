#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "ECS.h"
#include "Components.h"

GameObject* Player;
GameObject* GoldPlayer;

Manager manager;
auto& newPlayer(manager.addEntity());

Game::Game()
{
	
}

void Game::init(const char* title, int x, int y, int w, int h, bool fullScreen)
{
	int flags = 0;

	if (fullScreen == true)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, x, y, w, h, flags);

		renderer = SDL_CreateRenderer(window, -1, 0);
		isRunning = true;

		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 77, 77, 77, 255);
		}
	}

	else
	{
		isRunning = false;
	}

	Player = new GameObject("PlayerSprite.png", renderer, 600, 500);
	GoldPlayer = new GameObject("PlayerGold.png", renderer, 300, 200);

	newPlayer.addComponent<positionComponent>();
	
}

void Game::update()
{
	Player->Update();
	GoldPlayer->Update();
	manager.Update();
	std::cout << newPlayer.getComponentID<positionComponent>().x() << " " << newPlayer.getComponentID<positionComponent>().y() << std::endl;
}

void Game::render()
{
	SDL_RenderClear(renderer);
	Player->Render();
	GoldPlayer->Render();
	SDL_RenderPresent(renderer);

}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
		case SDL_QUIT:
			isRunning = false;
			break;
	}
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

}

