// Imports and stuff
#include "SDL2/SDL.h"
#include <stdio.h>
#include <iostream>
using namespace std;

// Window width and height
const int width = 1000;
const int height = 625;
// Main class
class Main
{
	public:
		// Defining variables
		bool init();
		bool gameLoop();
		void eventsHandling();
		void movement();
		void collision();
		SDL_Window* window = NULL;
		SDL_Surface* screenSurface = NULL;
		SDL_Event e;
		SDL_Surface* image = SDL_LoadBMP("images/Chboo1-sprites.bmp");
		SDL_Surface* flag = SDL_LoadBMP("images/flag.bmp");
		SDL_Surface* uwin = SDL_LoadBMP("images/uwin.bmp");
		SDL_Surface* title = SDL_LoadBMP("images/Title.bmp");
		SDL_Surface* playButton = SDL_LoadBMP("images/playButton.bmp");
		SDL_Surface* quitButton = SDL_LoadBMP("images/quitButton.bmp");
		SDL_Surface* resumeButton = SDL_LoadBMP("images/resumeButton.bmp");
		SDL_Surface* pauseBackground = SDL_LoadBMP("images/map-background.bmp");
		SDL_Surface* campfire = SDL_LoadBMP("images/campfire.bmp");
		SDL_Surface* villager = SDL_LoadBMP("images/villager.bmp");
		SDL_Rect imgRect, playButtonRect, rectRect, quitButtonRect, rect2Rect, imgSrcRect, campfireRect, villagerRect;
		SDL_Rect leftRect, rightRect, topRect, bottomRect;
		int speed = 20;
		int direction = 0;
		bool quit = false;
		bool bigquit = false;
		bool pause = false;
		bool wPressed = false;
		bool sPressed = false;
		bool aPressed = false;
		bool dPressed = false;
		bool playButtonClicked = false;
		int mx;
		int my;
		Main()
		{
			// Give all Rects (like coords) their values (x = x, y = y, w = width, h = height)
			bottomRect.x = 0;
			bottomRect.y = 612;
			bottomRect.w = width;
			bottomRect.h = height - 542;
			rectRect.x = (width / 2) - 100;
			rectRect.y = (height / 2) - 50;
			rectRect.w = 200;
			rectRect.h = 100;
			quitButtonRect.x = (width / 2) - 100;
			quitButtonRect.y = (height / 2) + 100;
			playButtonRect.x = (width / 2) - 100;
			playButtonRect.y = (height / 2) - 50;
			campfireRect.x = width / 2 - 50;
			campfireRect.y = height / 2 - 50;
			villagerRect.x = width / 2 - 25;
			villagerRect.y = height / 2 + (height / 4) - 50;
			SDL_SetSurfaceAlphaMod(pauseBackground, 0x7F);
			// Init SDL
			if (!init())
			{
				printf("Failed to start game, press Ctrl-C to quit");
			}
			// Display title screen elements
			SDL_BlitSurface(title, NULL, screenSurface, NULL);
			SDL_BlitSurface(playButton, NULL, screenSurface, &playButtonRect);
			SDL_BlitSurface(quitButton, NULL, screenSurface, &quitButtonRect);

			while (!bigquit)
			{
				playButtonClicked = false;
				quit = false;
				aPressed = false;
				dPressed = false;
				wPressed = false;
				sPressed = false;
				pause = false;
				imgRect.x = 0;
				imgRect.y = 562;
				// Title screen micro game loop
				while (!playButtonClicked)
				{
					SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface -> format, 0xFF, 0xFF, 0xFF));
					SDL_BlitSurface(title, NULL, screenSurface, NULL);
					SDL_FillRect(screenSurface, &rectRect, SDL_MapRGB(screenSurface -> format, 0xFF, 0x00, 0x00));
					SDL_BlitSurface(playButton, NULL, screenSurface, &playButtonRect);
					SDL_BlitSurface(quitButton, NULL, screenSurface, &quitButtonRect);
					// Events handling
					while (SDL_PollEvent(&e) != 0)
					{
						if (e.type == SDL_MOUSEBUTTONDOWN)
						{
							SDL_GetMouseState(&mx, &my);
							if (mx > (width / 2) - 100 && mx < (width / 2) + 100 && my > (height / 2) - 52 && my < (height / 2) + 52)
							{
								playButtonClicked = true;
							}
							else if (mx > (width / 2) - 100 && mx < (width / 2) + 100 && my > (height / 2) + 100 && my < (height / 2) + 200)
							{
								quit = true;
								playButtonClicked = true;
								bigquit = true;
							}
						}
						else if (e.type == SDL_QUIT)
						{
							playButtonClicked = true;
							quit = true;
							bigquit = true;
						}
						else if (e.type == SDL_KEYDOWN)
						{
							switch (e.key.keysym.sym)
							{
								case SDLK_ESCAPE:
									playButtonClicked = true;
									quit = true;
									bigquit = true;
									break;
								case SDLK_RETURN:
									playButtonClicked = true;
									break;

							}
						}
					}
					// Update window
					SDL_UpdateWindowSurface(window);
				}
				// Main loop
				while (!quit)
				{
					gameLoop();
				}
			}
			// Remove all things
			SDL_FreeSurface(image);
			SDL_FreeSurface(playButton);
			SDL_FreeSurface(quitButton);
			SDL_FreeSurface(title);
			SDL_FreeSurface(uwin);
			SDL_FreeSurface(flag);
			SDL_FreeSurface(screenSurface);
			SDL_DestroyWindow(window);
			SDL_Quit();


		}
};
// Func to init SDL and all it's things
bool Main::init()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Couldn't init SDL");
		success = false;
		
	}
	else
	{
		window = SDL_CreateWindow("Dinosaur Game :)", 0, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Couldn't init window");
			success = false;
		}
		else
		{
			screenSurface = SDL_GetWindowSurface(window);
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface -> format, 0xFF, 0xFF, 0xFF));
		}
	}
	return success;
}

// Every frame:
bool Main::gameLoop()
{
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface -> format, 0x00, 0x00, 0x00));
	SDL_FillRect(screenSurface, &bottomRect, SDL_MapRGB(screenSurface -> format, 0xA5, 0x4A, 0x2A));
	//printf("%d, %d\n", imgRect.x, imgRect.y);
	eventsHandling();
	movement();
	collision();
	SDL_BlitSurface(campfire, NULL, screenSurface, &campfireRect);
	SDL_BlitSurface(villager, NULL, screenSurface, &villagerRect);
	SDL_BlitSurface(image, &imgSrcRect, screenSurface, &imgRect);
	if (pause)
	{
		SDL_BlitSurface(pauseBackground, NULL, screenSurface, NULL);
		SDL_BlitSurface(resumeButton, NULL, screenSurface, &playButtonRect);
		SDL_BlitSurface(quitButton, NULL, screenSurface, &quitButtonRect);
	}
	SDL_UpdateWindowSurface(window);

}


void Main::eventsHandling()
{
	// Events handling
	while (SDL_PollEvent(&e) != 0)
	{
		// When u quit (makes me sad)
		if (e.type == SDL_QUIT)
		{
			quit = true;
			bigquit = true;
		}
		// Keyboard presses
		else if (e.type == SDL_KEYDOWN)
		{
			switch (e.key.keysym.sym)
			{
				case SDLK_RETURN:
					if (!pause)
					{
						printf("Pressed return\n");
					}
					else
					{
						pause = false;
					}
					break;
				case SDLK_ESCAPE:
					if (!pause)
					{
						pause = true;
					}
					else
					{
						pause = false;
					}
					break;
				case SDLK_w:
					if (!pause)
					{
						wPressed = true;
					}
					break;
				case SDLK_s:
					if (!pause)
					{
						sPressed = true;
					}
					break;
				case SDLK_a:
					if (!pause)
					{
						aPressed = true;
					}
					break;
				case SDLK_d:
					if (!pause)
					{
						dPressed = true;
					}
					break;
					
			}	
		}
		// Mouse events (when its paused)
		if (e.type == SDL_MOUSEBUTTONDOWN && pause)
		{
			SDL_GetMouseState(&mx, &my);
			if (mx > (width / 2) - 100 && mx < (width / 2) + 100 && my > (height / 2) - 52 && my < (height / 2) + 52)
			{
				pause = false;
			}
			else if (mx > (width / 2) - 100 && mx < (width / 2) + 100 && my > (height / 2) + 100 && my < (height / 2) + 200)
			{
				quit = true;
			}
		}
		// Keyboard releases
		else if (e.type == SDL_KEYUP)
		{
			switch (e.key.keysym.sym)
			{
				case SDLK_w:
					wPressed = false;
					break;
				case SDLK_s:
					sPressed = false;
					break;
				case SDLK_a:
					aPressed = false;
					break;
				case SDLK_d:
					dPressed = false;
					break;
				case SDLK_UP:
					wPressed = false;
					break;
				case SDLK_DOWN:
					sPressed = false;
					break;
				case SDLK_LEFT:
					aPressed = false;
					break;
				case SDLK_RIGHT:
					dPressed = false;
					break;
			}
		}
	}
}


void Main::movement()
{
	// Move :O
	if (wPressed)
	{
		imgRect.y -= speed;
	}
	if (sPressed)
	{
		imgRect.y += speed;
	}
	if (aPressed)
	{
		imgRect.x -= speed;
		imgSrcRect.x = 0;
	}
	if (dPressed)
	{
		imgRect.x += speed;
		imgSrcRect.x = 100;
	}
	if (dPressed && aPressed)
	{
		imgSrcRect.x = 50;
	}
	imgSrcRect.y = 0;
	imgSrcRect.w = 50;
	imgSrcRect.h = 50;
}


void Main::collision()
{
	// Collision
	// Outer boundaries (of da screen)
	if (imgRect.x < 0)
	{
		imgRect.x = 0;
	}
	if (imgRect.x > width - 50)
	{
		imgRect.x = width - 50;
	}
	if (imgRect.y < 0)
	{
		imgRect.y = 0;
	}
	if (imgRect.y > height - 50)
	{
		imgRect.y = height - 50;
	}
	// Collision of bottom border (almost of da screen but not of da screen it's just a tiny little bit of terrain)
	if (imgRect.y > 562)
	{
		imgRect.y = 562;
	}
}


// Where everything starts...
int main(int argc, char* args[]) {
	Main mainclass;
	return 0;
}
