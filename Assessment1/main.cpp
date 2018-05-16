#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <list>
#include <iostream>
#include <string>
#include "Animation.h"
#include "Character.h"
#include "Controller.h"
#include "Entity.h"
#include "InputHandler.h"
#include "Jump.h"


using namespace std;


SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

SDL_Texture* texture;
SDL_Rect sourceRectangle;
SDL_Rect destinationRectangle;

int main(int argc, char **argv)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout << "SDL Fail initialized!!!\n";
		return -1; //failed, dont continue rest of main code
	}
	else
	{
		cout << "SDL initialized success!!!\n";
	}

	window = SDL_CreateWindow("Assessment 1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1800, 860, SDL_WINDOW_SHOWN);

	if (window != NULL)
	{
		cout << "Window created!" << endl;
	}
	else
	{
		cout << "Failed to create window!" << endl;
		return -1;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer != NULL)
	{
		cout << "Renderer created!" << endl;
	}
	else
	{
		cout << "Renderer FAILED!" << endl;
		return -1;
	}

	//INIT sdl ttf
	if (TTF_Init() != 0)
	{
		//if failed, complain abot it
		cout << "SDL TTF FAILED!" << endl;
		system("pause");
		SDL_Quit();
		return -1;
	}


	//GET CONTROLLER MAPPING
	SDL_GameControllerAddMappingsFromFile("assets/gamecontrollerdb.txt");

	//NEED TO INTI SDL_Image
	if (!(IMG_Init(IMG_INIT_PNG)&IMG_INIT_PNG)){
		cout << "sdl image did not load: " << IMG_GetError() << endl;
		SDL_Quit();
		std::system("pause");
		return -1;
	}


	//to load up an image, first load it up as a surface
	SDL_Surface* knightSurface = SDL_LoadBMP("assets/knight.bmp");
	//then convert to texture
	SDL_Texture* knightTexture = SDL_CreateTextureFromSurface(renderer, knightSurface);
	//dont need surface anymore, free memory up
	SDL_FreeSurface(knightSurface);

	//SDL_Surface* treeTrxture = SDL_LoadBMP("assets/tree.bmp");
	//SDL_Texture* treeTrxture = SDL_CreateTextureFromSurface(renderer, treeTrxture);



	//lets use pass by reference to work the width and height of our texture in pixels
	SDL_QueryTexture(knightTexture, NULL, NULL, &sourceRectangle.w, &sourceRectangle.h);
	cout << "texture size is: " << sourceRectangle.w << "x" << sourceRectangle.h << endl;

	sourceRectangle.x = 100;
	sourceRectangle.y = 100;
	sourceRectangle.w = 100;
	sourceRectangle.h = 100;
	destinationRectangle.x = 100;
	destinationRectangle.y = 50;
	destinationRectangle.w = sourceRectangle.w * 1; //copy the width of our texture
	destinationRectangle.h = sourceRectangle.h * 1; //copy the height of our texture

	//RUN TEXTURE
	SDL_Texture* runSpriteSheet = IMG_LoadTexture(renderer, "assets/run.png");
	//this time, lets make a soure rectanglecopying just 1 frame in size at a time
	SDL_Rect runClipRect = { 0, 0, 32, 32 }; //x:0, y:0, w:32, h:32
	SDL_Rect runDestRect = { 0, 0, 128, 128 }; //x y, get image to bottom right of screen. w/h match clip/frame size

	SDL_Surface* runSurface = IMG_Load("assets/run.png");

	//params:surface, 1/0 to set or unset colour key, RGB value to make colour key. mapRGB just does its best to find colsest match to a surfaces pixel dormat e.g 8bit, 16bit and what colours are in that set
	SDL_SetColorKey(runSurface, 1, SDL_MapRGB(runSurface->format, 128, 128, 255));

	//now convert to texture
	SDL_Texture* runSpriteSheetWithNoBG = SDL_CreateTextureFromSurface(renderer, runSurface);
	//free the surface : 0
	SDL_FreeSurface(runSurface);



	//Animation Objects
	Animation anim(runSpriteSheet, renderer, 3, 97, 144, 0.1); //50ms per frame



	//setup time stuff
	Uint32 lastUpdate = SDL_GetTicks(); //set last update to current time (milliseconds to reach this bit of code)

	//list of game entities
	list<Entity*> entities;
	Character* character = new Character();
	character->setAnimation(&anim);
	character->setRenderer(renderer);

	

	//build vector to represent starting position for hero
	Vector characterStartPos(0, 500);
	character->setPosition(characterStartPos);

	//add to entities list
	entities.push_back(character);

	//CRAETE INPUT HANDLERS
	Controller controller;
	controller.character = character; //let it reference our hero

	TTF_Font* font = TTF_OpenFont("assets/vermin_vibes_1989.ttf", 35); //params: font file, font size
	//create a surface using this font to display some sort of message
	SDL_Color textColor = { 123, 0, 34, 0 };
	SDL_Surface* textSurface = TTF_RenderText_Blended(font, "Lets Play Game!", textColor);
	//convert surface to texture
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	//delete surface properly
	SDL_FreeSurface(textSurface);

	//text destination
	SDL_Rect textDestination;
	textDestination.x = 50;
	textDestination.y = 50;
	//get width and height from texture and set it for the destination
	SDL_QueryTexture(textTexture, NULL, NULL, &textDestination.w, &textDestination.h);

	bool loop = true;
	while (loop){

		//difference is current time running minus the last update time
		Uint32 timeDiff = SDL_GetTicks() - lastUpdate;
		//convert into deltaTime(decimal)
		float DT = timeDiff / 1000.0; //e.g 200ms now 0.2 for DT
		//now update lastUpdate to the current time so the next loop calculate correctly
		lastUpdate = SDL_GetTicks();

		cout << "dt = " << DT << endl;

		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 228, 255, 255);
		SDL_Rect rect = { 100, 50, 300, 240 };

		SDL_RenderFillRect(renderer, &rect);

		SDL_RenderCopy(renderer, knightTexture, NULL, &destinationRectangle);

		int const runNumOffFrames = 4;
		runClipRect.x = runClipRect.w*int((SDL_GetTicks() / 100) % runNumOffFrames);

		SDL_Event e;
		//loops through all events and temporarily stores event details in an SDL_Event object
		while (SDL_PollEvent(&e))
		{
			//check if user has clicked on the close window button
			if (e.type == SDL_QUIT)
			{
				//exit our loop,
				loop = false;
			}
			//check if user has 'pressed' a button(not held)
			if (e.type == SDL_KEYDOWN)
			{
				//see if ESC key was pressed
				if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				{
					//exit loop
					loop = false;
				}

			}
			controller.update(&e);
		}

		for (list<Entity*>::iterator eIt = entities.begin(); eIt != entities.end(); eIt++)
		{
			(*eIt)->update(DT);
			(*eIt)->draw();
		}

		SDL_RenderCopy(renderer, textTexture, NULL, &textDestination);
		SDL_RenderPresent(renderer);
	}
	//after game loop
	delete character;

	//cleanup font
	TTF_CloseFont(font);
	//clean up texture
	SDL_DestroyTexture(textTexture);
	SDL_DestroyTexture(runSpriteSheet);
	SDL_DestroyTexture(runSpriteSheetWithNoBG);
	SDL_DestroyTexture(knightTexture);

	//clean up renderer and window proprely (aka clean up dynamic memory)
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	//shut down subsytems and cleanup any setup it did earlier in sdl_init
	SDL_Quit();
	

	system("pause");
	return 0;
}