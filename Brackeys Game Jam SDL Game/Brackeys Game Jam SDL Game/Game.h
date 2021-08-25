#pragma once

#include <SDL.h>

class Game 
{
public:
	Game();
	
	void init(const char* title, int x, int y, int w, int h, bool fullScreen);
	
	void handleEvents();
	void update();
	void render();
	void clean();

	bool running() { return isRunning; }
private:
	int counter;
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
};