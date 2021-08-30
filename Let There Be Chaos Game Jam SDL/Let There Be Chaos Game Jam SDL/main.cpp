#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <string>
#include <iostream>

#include "RenderImage.h"

#define PI 3.14159265358979323846

#define WIDTH 1280
#define HEIGHT 720
#define FONT_SIZE 50

#define SIZE 12
#define BALL_SPEED 40
#define PADDLE_SPEED 44

using std::string;

SDL_Renderer* renderer;
SDL_Window* window;
TTF_Font* font;
SDL_Color colour;
bool isRunning;
bool isInMenu;
int frames, timerFPS, lastFrame, FPS;

SDL_Rect Paddle1;
SDL_Rect Paddle2;
SDL_Rect Ball;
SDL_Rect Score;

SDL_Rect ObjectTest;
SDL_Rect Object1;
SDL_Rect Object2;
SDL_Rect Object3;
SDL_Rect Object4;
SDL_Rect Object5;
SDL_Rect Object6;
SDL_Rect Object7;

SDL_Rect DeathObject;

float VelocityX;
float VelocityY;


string score;
int l_s;
int r_s;

bool turn = 0;


int PlayerScore = 0;
const char* PlayerScoreString = " " + PlayerScore;

int randomY;
int randomX;

int randomY1;
int randomX1;

int randomY2;
int randomX2;

int randomY3;
int randomX3;

int randomY4;
int randomX4;

int randomY5;
int randomX5;

int randomY6;
int randomX6;

int randomX7;
int randomY7;

int DeathRandom;
int DeathRandomY;

int Object1Height = 15;
int Object1Width = 15;

int Object2Height = 15;
int Object2Width = 15;

int Object3Height = 15;
int Object3Width = 15;

int Object4Height = 0;
int Object4Width = 0;

int Object5Height = 0;
int Object5Width = 0;

int Object6Height = 0;
int Object6Width = 0;

int Object7Height = 0;
int Object7Width = 0;

int Object8Height = 0;
int Object8Width = 0;

int DeathDimensions = 15;

bool GameOver = false;

bool Object4Gone = false;
bool Object5Gone = false;
bool Object6Gone = false;
bool Object7Gone = false;

bool DeathObjectSpawned = false;
bool WonGame = false;




void RenderImage::Render(SDL_Texture* p_texture)
{
	SDL_RenderCopy(renderer, p_texture, NULL, NULL);
}



void RenderMenuText()
{
	RenderImage renderImage;

	SDL_Surface* surface = IMG_Load("Front Menu.png");
	SDL_Texture* MenuText = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_RenderCopy(renderer, MenuText, NULL, NULL);
}

void RenderMenu()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 21, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

}

void Render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 21, 255);
	SDL_RenderClear(renderer);

	if (isInMenu)
	{
		RenderImage renderImage;
		SDL_RenderClear(renderer);
		SDL_Surface* surface = IMG_Load("Front Menu.png");
		SDL_Texture* MenuText = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_RenderCopy(renderer, MenuText, NULL, NULL);
		SDL_RenderPresent(renderer);
	}

	if (isRunning)
	{
		bool Object4and5Gone = false;
		bool Object6and7Gone = false;

		srand(time(0));

		SDL_SetRenderDrawColor(renderer, 0, 0, 21, 255);


		frames++;
		timerFPS = SDL_GetTicks() - lastFrame;

		if (timerFPS < (1000 / 100))
		{
			SDL_Delay((1000, 10) - timerFPS);
		}

		SDL_Surface* tmp_surface;
		tmp_surface = SDL_LoadBMP("TestSprite.png");

		SDL_Texture* OneBlock = SDL_CreateTextureFromSurface(renderer, tmp_surface);






		SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, 255);
		SDL_RenderFillRect(renderer, &Paddle1);
		SDL_RenderFillRect(renderer, &Paddle2);
		SDL_RenderFillRect(renderer, &Ball);
		SDL_SetRenderDrawColor(renderer, 173, 78, 31, 255);
		SDL_RenderFillRect(renderer, &ObjectTest);
		SDL_RenderFillRect(renderer, &Object1);
		SDL_RenderFillRect(renderer, &Object2);
		SDL_RenderFillRect(renderer, &Object3);
		SDL_SetRenderDrawColor(renderer, 132, 98, 98, 255);
		SDL_RenderFillRect(renderer, &DeathObject);
		SDL_SetRenderDrawColor(renderer, 173, 78, 31, 255);


		if (Object4Gone == true || Object5Gone == true)
		{
			Object4and5Gone = true;
			if (Object4Gone == true)
			{
				Object5.h = Object6Height;
				Object5.w = Object6Width;
			}

			if (Object5Gone == true)
			{
				Object4.h = Object5Height;
				Object4.w = Object5Width;
			}
		}

		if (Object6Gone == true || Object7Gone == true)
		{
			Object6and7Gone = true;

			if (Object6Gone == true)
			{
				Object6.h = Object7Height;
				Object6.w = Object7Width;
			}

			if (Object7Gone == true)
			{
				Object7.h = Object8Height;
				Object7.w = Object8Width;
			}
		}

		if (Object4and5Gone == false)
		{
			SDL_RenderFillRect(renderer, &Object4);
			SDL_RenderFillRect(renderer, &Object5);

			Object5Width = 15;
			Object5Height = 15;
			Object6Width = 15;
			Object6Height = 15;

		}


		SDL_SetRenderDrawColor(renderer, 51, 51, 77, 255);

		if (Object6and7Gone == false)
		{
			SDL_SetRenderDrawColor(renderer, 173, 78, 31, 255);

			SDL_RenderFillRect(renderer, &Object6);
			SDL_RenderFillRect(renderer, &Object7);

			Object7Width = 15;
			Object7Height = 15;
			Object8Width = 15;
			Object8Height = 15;

		}

		if (DeathObjectSpawned == false && PlayerScore >= 4)
		{
			DeathDimensions = 15;
			SDL_SetRenderDrawColor(renderer, 132, 98, 98, 255);
			SDL_RenderFillRect(renderer, &DeathObject);
			DeathObjectSpawned = true;
		}

		SDL_RenderPresent(renderer);
	}


}

void Serve()
{
	Paddle1.y = Paddle2.y = (HEIGHT / 2) - (Paddle1.h / 2);
	if (turn)
	{
		Ball.x = Paddle1.x;
		VelocityX = BALL_SPEED;
	}

	else
	{
		Ball.x = Paddle2.x;
		VelocityX = -BALL_SPEED;
	}

	VelocityY = 0;
	VelocityX = BALL_SPEED / 2;
	Ball.y = HEIGHT / 2 - (SIZE / 2);
	turn = !turn;
}

void PlayHitSound()
{
	Mix_Chunk* HitSound = Mix_LoadWAV("HitSound.wav");
	Mix_PlayChannel(-1, HitSound, 0);
}

void PlayDeathSound()
{
	Mix_Chunk* DeathSound = Mix_LoadWAV("DeathSound.wav");
	Mix_PlayChannel(1, DeathSound, 0);
}

void PlayWinSound()
{
	Mix_Chunk* WinSound = Mix_LoadWAV("PossibleWinSound.wav");
	Mix_PlayChannel(2, WinSound, 0);
}

void Update()
{
	if (PlayerScore >= 6 && GameOver == false)
	{
		PlayWinSound();
		WonGame = true;
	}

	srand(time(0));
	randomY = rand() % HEIGHT;
	randomX = rand() % WIDTH;
	srand(time(0));
	
	randomX1 = rand() % WIDTH + 10;
	randomY1 = rand() % HEIGHT + 50;

	randomY2 = rand() % HEIGHT + 50;
	randomX2 = rand() % WIDTH + 10;

	randomX3 = rand() % WIDTH + 50;
	randomY3 = rand() % HEIGHT + 10;

	randomX4 = rand() % WIDTH + 20;
	randomY4 = rand() % HEIGHT + 20;

	randomX5 = rand() % WIDTH + 15;
	randomY5 = rand() % HEIGHT + 20;
	
	randomX6 = rand() % WIDTH + 17;
	randomY6 = rand() % HEIGHT + 20;

	randomX7 = rand() % WIDTH + 18;
	randomY7 = rand() % HEIGHT + 20;

	DeathRandom = rand() % WIDTH + 30;
	DeathRandomY = rand() % HEIGHT + 23;
	

	randomY++;
	
	Object1.x = randomX1;
	Object1.y = randomY1;
	Object1.w = Object2Width;
	Object1.h = Object2Height;

	
	ObjectTest.y = randomY;
	ObjectTest.x = randomX;
	ObjectTest.w = Object1Height;
	ObjectTest.h = Object1Width;

	Object2.y = randomY2;
	Object2.x = randomX2;
	Object2.w = Object3Width;
	Object2.h = Object3Height;

	Object2.y++;

	Object3.x = randomX3;
	Object3.y = randomY3;
	Object3.w = Object4Width;
	Object3.h = Object4Height;

	Object3.y += 100;
	Object3.y++;

	Object4.x = randomX4;
	Object4.y = randomY4;
	Object4.w = Object5Width;
	Object4.h = Object5Height;

	Object4.y++;

	Object5.x = randomX5;
	Object5.y = randomY5;
	Object5.w = Object6Width;
	Object5.h = Object6Height;

	Object5.y++;

	Object6.x = randomX6;
	Object6.y = randomY6;
	Object6.w = Object7Width;
	Object6.h = Object7Height;

	Object6.y++;

	Object7.x = randomX7;
	Object7.y = randomY7;
	Object7.w = Object8Width;
	Object7.h = Object8Height;

	DeathObject.x = DeathRandom;
	DeathObject.y = DeathRandomY;
	DeathObject.w = DeathDimensions;
	DeathObject.h = DeathDimensions;


	

	SDL_Surface* surface_tmp;
	surface_tmp = SDL_LoadBMP("TestSprite.png");
	SDL_Texture* block = SDL_CreateTextureFromSurface(renderer, surface_tmp);
	
	



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

	if (Ball.x <= 0)
	{
		r_s += 1;
		Serve();
	}

	if (Ball.x >= WIDTH)
	{
		l_s += 1;
		Serve();
	}


	if (Ball.x == WIDTH)
	{
		VelocityX = -VelocityX;
	}

	if (Ball.y <= 0)
	{
		VelocityY = -VelocityY;
	}

	if (Ball.y + SIZE >= HEIGHT)
	{
		VelocityY = -VelocityY;
	}

	if (Ball.x + SIZE == HEIGHT)
	{
		VelocityY = -VelocityY;
	}

	if (SDL_HasIntersection(&Ball, &Paddle2))
	{
		double relativeYInter = (Paddle2.y + (Paddle2.h / 2)) - (Ball.y + (SIZE / 2));
		double norm = relativeYInter / (Paddle2.h / 2);
		double bounce = norm * (5 * PI / 2);
		VelocityX = -BALL_SPEED * cos(bounce);
		VelocityY = BALL_SPEED * -sin(bounce);

	}

	if (SDL_HasIntersection(&Ball, &Paddle1))
	{
		double relativeYInter = (Paddle1.y + (Paddle1.h / 2)) - (Ball.y + (SIZE / 2));
		double norm = relativeYInter / (Paddle1.h / 2);
		double bounce = norm * (5 * PI / 2);
		VelocityX = BALL_SPEED * cos(bounce);
		VelocityY = BALL_SPEED * -sin(bounce);

	}

	if (SDL_HasIntersection(&Ball, &ObjectTest))
	{
		VelocityX = -VelocityX;
		Object1Height = 0;
		Object1Width = 0;
		PlayerScore += 1;

		PlayHitSound();
	}

	if (SDL_HasIntersection(&Ball, &Object1))
	{
		VelocityX = -VelocityX;
		Object2Width = 0;
		Object2Height = 0;
		PlayerScore += 1;
		
		PlayHitSound();
	}

	if (SDL_HasIntersection(&Ball, &Object2))
	{
		VelocityX = -VelocityX;
		Object3Width = 0;
		Object3Height = 0;
		PlayerScore += 1;

		PlayHitSound();
	}

	if (SDL_HasIntersection(&Ball, &Object3))
	{
		VelocityX = -VelocityX;
		Object4Width = 0;
		Object4Height = 0;
		PlayerScore += 1;

		PlayHitSound();
	}

	if (SDL_HasIntersection(&Ball, &Object4))
	{
		VelocityX = -VelocityX;
		Object5Width = 0;
		Object5Height = 0;
		PlayerScore += 1;

		PlayHitSound();

		Object4Gone = true;
	}

	if (SDL_HasIntersection(&Ball, &Object5))
	{
		VelocityX = -VelocityX;
		Object6Width = 0;
		Object6Height = 0;
		PlayerScore += 1;

		PlayHitSound();

		Object5Gone = true;
	}

	if (SDL_HasIntersection(&Ball, &Object6))
	{
		VelocityX = -VelocityX;
		Object7Width = 0;
		Object7Height = 0;
		PlayerScore += 1;

		PlayHitSound();

		Object6Gone = true;
	}

	if (SDL_HasIntersection(&Ball, &Object7))
	{
		VelocityX = -VelocityX;
		Object8Width = 0;
		Object8Height = 0;
		PlayerScore += 1;

		PlayHitSound();

		Object7Gone = true;
	}

	if (SDL_HasIntersection(&Ball, &DeathObject))
	{
		PlayDeathSound();

		GameOver = true;
		DeathDimensions = 0;

		Ball.x = 600;
		Ball.y++;

		Ball.w = 0;
		Ball.h = 0;
	}

	Ball.x += VelocityX;
	Ball.y += VelocityY;


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
			isInMenu = false;
		}

		if (isRunning && GameOver == false)
		{
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

		if (isInMenu)
		{
			if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_KEYDOWN)
			{
				isRunning = true;
				isInMenu = false;
			}
		}


	}
}



int main(int argc, char* argv[])
{
	RenderImage renderImage;

	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);

	randomY = 100;

	int textW = 0;
	int textH = 0;

	colour = { 255, 255, 255 };
	SDL_Surface* surface = TTF_RenderText_Solid(font, PlayerScoreString, colour);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	SDL_QueryTexture(texture, NULL, NULL, &textW, &textH);
	SDL_Rect dstRect = { 0, 0, textW, textH };

	std::cout << PlayerScoreString << std::endl;

	l_s = 0;
	r_s = 0;
	Paddle1.x = 32;
	Paddle1.h = HEIGHT / 4;
	Paddle1.y = (HEIGHT / 1.8) - (Paddle1.h / 2);
	Paddle2 = Paddle1;
	Paddle2.x = WIDTH - Paddle2.w - 32;
	Ball.w = Ball.h=SIZE;
	Ball.y = 720 / 2;
	Paddle1.w = 20;
	Paddle2.w = 20;

	SDL_SetWindowTitle(window, "Brackeys Game Jam");

	Serve();

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

	isInMenu = true;
	static int LastTime = 0;

	colour.r = 255;
	colour.g = 255;
	colour.b = 255;

	SDL_RenderClear(renderer);
	while (isInMenu)
	{
		Input();
		RenderMenu();
		RenderMenuText();
		Render();

		RenderImage renderImage;
		
		SDL_Surface* surface = IMG_Load("Front Menu.png");
		SDL_Texture* MenuText = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_RenderCopy(renderer, MenuText, NULL, NULL);
		SDL_RenderPresent(renderer);

	}
	
	while (isRunning)
	{
		SDL_RenderCopy(renderer, texture, NULL, &dstRect);
		SDL_RenderPresent(renderer);




		lastFrame = SDL_GetTicks();
		if (lastFrame >= (LastTime + 1000))
		{
			LastTime = lastFrame;
			FPS = frames;
		}

		Render();
		Update();
		Input();

		if (GameOver == true)
		{		
			std::cout << "Fail. You touched the death block." << std::endl;
			isRunning = true;
			

		}
	}

	while (GameOver)
	{
		SDL_Surface* surface = IMG_Load("GameOver");
		SDL_Texture* MenuText = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_RenderCopy(renderer, MenuText, NULL, NULL);
		SDL_RenderPresent(renderer);
	}

	while (WonGame)
	{
		SDL_Surface* surface = IMG_Load("Victory.png");
		SDL_Texture* MenuText = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_RenderCopy(renderer, MenuText, NULL, NULL);
		SDL_RenderPresent(renderer);

		Ball.w = 0;
		Ball.h = 0;
	}

	TTF_CloseFont(font);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	Mix_Quit();
	Mix_CloseAudio();
	SDL_Quit();



	return 0;
}