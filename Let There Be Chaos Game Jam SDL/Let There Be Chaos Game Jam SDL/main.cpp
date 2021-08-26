#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <string>
#include <iostream>

#define WIDTH 1280
#define HEIGHT 720
#define FONT_SIZE 50

#define SIZE 20
#define BALL_SPEED 25
#define PADDLE_SPEED 30

using std::string;

SDL_Renderer* renderer;
SDL_Window* window;
TTF_Font* font;
SDL_Color colour;
bool isRunning;
int frames, timerFPS, lastFrame, FPS;

SDL_Rect Paddle1;
SDL_Rect Paddle2;
SDL_Rect Ball;
SDL_Rect Score;

float VelocityX;
float VelocityY;

string score;
int l_s;
int r_s;

bool turn = 1;

void Write(string text, int x, int y)
{
	SDL_Surface* surface;
	SDL_Texture* texture;
	
	const char* t = text.c_str();
	surface = TTF_RenderText_Solid(font, t, colour);
	texture = SDL_CreateTextureFromSurface(renderer, surface);

	/*
	Score.h = surface->h;
	Score.w = surface->w;
	*/
	Score.x = x-Score.w;
	Score.y = y-Score.h;

	SDL_FreeSurface(surface);
	SDL_RenderCopy(renderer, texture, NULL, &Score);
	SDL_DestroyTexture(texture);

}

void Render()
{
	SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
	SDL_RenderClear(renderer);

	frames++;
	timerFPS = SDL_GetTicks() - lastFrame;

	if (timerFPS < (1000 / 60))
	{
		SDL_Delay((1000, 60)-timerFPS);
	}


	
	SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, 255);
	SDL_RenderFillRect(renderer, &Paddle1);
	SDL_RenderFillRect(renderer, &Paddle2);
	SDL_RenderFillRect(renderer, &Ball);
	SDL_RenderPresent(renderer);
}

void Serve()
{
	Paddle1.y = Paddle2.y = (HEIGHT / 2) - (Paddle1.h / 2);
	if (turn)
	{
		Ball.x = Paddle1.x + (Paddle1.w);
		VelocityX = BALL_SPEED / 2;
	}

	else
	{
		Ball.x = Paddle2.x + (Paddle2.w);
		VelocityX = -BALL_SPEED / 2;
	}

	VelocityY = 0;
	VelocityX = BALL_SPEED / 2;
	Ball.y = HEIGHT / 2 - (SIZE / 2);
	turn = !turn;
}

void Update()
{
	score = std::to_string(l_s + l_s);
	
	if (Paddle1.y <= 0)
	{
		Paddle1.y = 100;
	}


	if (Paddle1.y + Paddle1.h >= HEIGHT)
	{
		Paddle1.y -= 100;
	}

	if (Paddle2.y + Paddle2.h >= HEIGHT)
	{
		Paddle2.y -= 100;
	}

	if (Paddle2.y <= 0)
	{
		Paddle2.y = 100;
	}



}



void Input()
{
	SDL_Event event;
	const Uint8* keystates = SDL_GetKeyboardState(NULL); 

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			isRunning = false;
		}

		if (keystates[SDL_SCANCODE_ESCAPE])
		{
			isRunning = false;
		}

		if (keystates[SDL_SCANCODE_UP])
		{
			Paddle2.y -= PADDLE_SPEED;
		}

		if (keystates[SDL_SCANCODE_DOWN])
		{
			Paddle2.y += PADDLE_SPEED;
		}

		if (keystates[SDL_SCANCODE_W])
		{
			Paddle1.y -= PADDLE_SPEED;
		}

		if (keystates[SDL_SCANCODE_S])
		{
			Paddle1.y += PADDLE_SPEED;
		}
	}
}

int main(int argc, char* argv[])
{
	l_s = 0;
	r_s = 0;
	Paddle1.x = 32;
	Paddle1.h = HEIGHT / 4;
	Paddle1.y = (HEIGHT / 2) - (Paddle1.h / 2);
	Paddle2 = Paddle1;
	Paddle2.x = WIDTH - Paddle2.w - 32;
	Ball.w = Ball.h=SIZE;
	Ball.x = 
	Ball.y = 720 / 2;
	Paddle1.w = 20;
	Paddle2.w = 20;

	
	//Serve Ball

	if (font == NULL)
	{
		std::cout << "Font failed to initialise" << std::endl;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "Failed at SDL_INIT()" << std::endl;
	}

	if (SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer) < 0)
	{
		std::cout << "Window initialisation failed" << std::endl;
	}

	TTF_Init();
	font = TTF_OpenFont("TypeWriteFont.ttf", FONT_SIZE);

	isRunning = true;
	static int LastTime = 0;

	colour.r = 255;
	colour.g = 255;
	colour.b = 255;

	while (isRunning)
	{
		std::cout << Paddle1.x << std::endl;

		Write(score, WIDTH/2+FONT_SIZE, FONT_SIZE);

		lastFrame = SDL_GetTicks();
		if (lastFrame >= (LastTime + 1000))
		{
			LastTime = lastFrame;
			FPS = frames;
		}

		Render();
		Update();
		Input();
	}

	TTF_CloseFont(font);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();



	return 0;
}