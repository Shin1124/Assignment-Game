#include "Animation.h"


Animation::Animation(SDL_Texture* spriteSheet, SDL_Renderer* renderer, int numberOfFrames, int frameWidth, int frameHeight, float frameDuration)
{
	this->spriteSheet = spriteSheet;
	this->renderer = renderer;
	this->numberOfFrames = numberOfFrames;
	this->frameWidth = frameWidth;
	this->frameHeight = frameHeight;
	this->frameDuration = frameDuration;

	currentFrame = 0;
	frameTimer = 0;
}
void Animation::update(float dt)
{
	//using update to cycle through animation frames

	//update frameTimer
	frameTimer += dt;

	//if this frame has been shown long enough
	if (frameTimer >= frameDuration)
	{
		//move onto next frame
		currentFrame++;
		//reset frame timer
		frameTimer = 0;

		if (currentFrame >= numberOfFrames)
		{
			//if cycle through all frames, go back to the beginning(rest animation)
			currentFrame = 0;
		}
	}
}
void Animation::draw(int x, int y)
{
	//get current frame clipping region
	SDL_Rect clip;
	clip.x = currentFrame*frameWidth;
	clip.y = 0;
	clip.w = frameWidth;
	clip.h = frameHeight;

	//setup where frame will be drawn
	SDL_Rect dest = { x, y, frameWidth, frameHeight };

	//draw
	SDL_RenderCopy(renderer, spriteSheet, &clip, &dest);
}
void Animation::draw(int x, int y, float scale)
{
	//get current frame clipping region
	SDL_Rect clip;
	clip.x = currentFrame*frameWidth;
	clip.y = 0;
	clip.w = frameWidth;
	clip.h = frameHeight;

	//setup where frame will be drawn
	SDL_Rect dest = { x, y, frameWidth*scale, frameHeight*scale };

	//draw
	SDL_RenderCopy(renderer, spriteSheet, &clip, &dest);
}
void Animation::draw(int x, int y, bool flip)
{
	//get current frame clipping region
	SDL_Rect clip;
	clip.x = currentFrame*frameWidth;
	clip.y = 0;
	clip.w = frameWidth;
	clip.h = frameHeight;

	//setup where frame will be drawn
	SDL_Rect dest = { x, y, frameWidth, frameHeight };

	//get the correct flip flag to help mirror our image if we want to 
	SDL_RendererFlip flipType = SDL_FLIP_NONE;
	if (flip)
		flipType = SDL_FLIP_HORIZONTAL;

	//draw					angle, rotationPoint, flip flag
	SDL_RenderCopyEx(renderer, spriteSheet, &clip, &dest, 0, 0, flipType);
}
