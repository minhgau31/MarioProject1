#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Constant.h"

////Global variable
SDL_Window* g_Window;
SDL_Renderer* g_Renderer;
SDL_Texture* g_Texture;
int g_angle = 0;
//
//
//// FUNCTION PROTOTYPE
bool Init();
bool Update();
void Render();
void CloseSDL();


//function declaration 


void CloseSDL()
{
	//release window
	if (g_Texture != nullptr)
	{
		SDL_DestroyTexture(g_Texture);
		g_Texture = nullptr;
	}

	if (g_Renderer != nullptr)
	{
		SDL_DestroyRenderer(g_Renderer);
		g_Renderer = nullptr;

	}
	if (g_Window != nullptr)
	{
		SDL_DestroyWindow(g_Window);
		g_Window = nullptr;

		SDL_Quit();//system SDL require
	}


	
	 
}
bool Init()
{
	bool success = false;
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		success = false;
		printf("could not init SDL . E :%s\n", SDL_GetError());
	}
	g_Window = SDL_CreateWindow("Mario Project",
								SDL_WINDOWPOS_CENTERED,
								SDL_WINDOWPOS_CENTERED,
								SCREEN_WIDTH,
								SCREEN_HEIGHT,
								SDL_WINDOW_SHOWN);
	if (g_Window != nullptr)
	{
		g_Renderer = SDL_CreateRenderer(g_Window, -1, SDL_RENDERER_ACCELERATED);
		if (g_Renderer != nullptr)
		{
			//khoi tao renderer
			int flag = IMG_INIT_PNG;
			if (IMG_Init(IMG_INIT_PNG & flag))
			{
				
				//load anh tu file
				{
					 SDL_Surface* surface = IMG_Load("Images/quocanh1.png");
					 if (surface != nullptr)
					 {
						 success = true;
						g_Texture = SDL_CreateTextureFromSurface(g_Renderer, surface);
					 }
					 else
					 {
						 success = false;
						 printf("could not init png :%s\n", IMG_GetError());

						
					 }
					 SDL_FreeSurface(surface);

														
				}

			}
			else
			{
				success = false;
				printf("could not init png :%s\n", IMG_GetError());
			}
		}
		else
		{
			success = false;
			printf("could not create renderer :%s\n", SDL_GetError());
		}
	}
	else
	{
		success = false;
		printf("could not create window :%s\n", SDL_GetError());
	}

	return success;
}
bool Update()
{

	bool success = false;
	//Handle Event
	SDL_Event e;
	//Get Event
	SDL_PollEvent(&e);
	switch (e.type)
	{
	case SDL_KEYDOWN:
	{
   		switch (e.key.keysym.sym)
		{
			SDLK_q;
			break;
		default:
			break;
			SDLK_a;
			break;
			g_angle = g_angle + 5;
				break;
			
			



		}
		if (e.key.keysym.sym==SDLK_LEFT)
		{
			g_angle = g_angle + 5;
		}
	}

	/*case SDL_QUIT:
	{
	success = true;
	break;
	default:
		break;
	}*/
	
	
	case SDL_MOUSEBUTTONDOWN:
		
		if(e.button.clicks == 2)
		{ 
			
			success = true;
				
		}
		break;
			
	}	
	return success;
}

void Render()
{
	SDL_SetRenderDrawColor(g_Renderer, 0xFF,0xFF,0xFF,0xFF);
	SDL_RenderClear(g_Renderer);
	SDL_Rect rec;
	rec.x = 0;
	rec.y = 0;
	rec.w = SCREEN_WIDTH;
	rec.h = SCREEN_HEIGHT;
	SDL_RenderCopyEx(g_Renderer, g_Texture, NULL, &rec, g_angle,NULL, SDL_FLIP_NONE);
	SDL_RenderPresent(g_Renderer);

	


	

}

int main(int argc, char* argv[])
{

	Init();
	bool isQuit = false;
	if ( !Init() )
	{
		//print log sai
		printf("Could log init\n");
	}
	else
	{
		while (!isQuit)
		{
			Render();
			isQuit = Update();
		}
		
	}
		

	CloseSDL();
	
	system("PAUSE");
	return 0;
}
