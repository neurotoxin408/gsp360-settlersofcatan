#pragma once

//#include "dv_sdlgrafix.h"
#include "game.h"
#include "sdl/sdl.h"
#include "sdl/sdl_ttf.h"
#include "stndrd.h"
#include <iostream>
#include <string> 
#include <ctime>
#include <time.h>
using namespace std;

class sdlManager
{
public:
	
	static sdlManager& getInstance() { static sdlManager pInstance; return pInstance; }
	~sdlManager(void);
	void loadImages();
	void draw(SDL_Surface *, map *);
	void shutdown();
	sdlManager(void);
private:
	SDL_Surface *hexTile;
	SDL_Surface *woodTile;
	SDL_Surface *sheepTile;
	SDL_Surface *brickTile;
	SDL_Surface *stoneTile;
	SDL_Surface *wheatTile;
	SDL_Surface *load_image( std::string filename );
	void apply_surface(int x, int y,SDL_Surface* source, SDL_Surface* destination, SDL_Rect *clip);
};

//constructor
sdlManager::sdlManager(void)
{
	hexTile = NULL;
	woodTile = NULL;
	wheatTile = NULL;
	stoneTile = NULL;
	sheepTile = NULL;
	brickTile = NULL;
}
//sdlManager destructor
sdlManager::~sdlManager(void)
{
}

//Free up SDL and font
void sdlManager::shutdown()
{
	SDL_FreeSurface(hexTile);
	SDL_FreeSurface(woodTile);
	SDL_FreeSurface(wheatTile);
	SDL_FreeSurface(stoneTile);
	SDL_FreeSurface(sheepTile);
	SDL_FreeSurface(brickTile);
}

//function to load images
SDL_Surface* sdlManager::load_image( std::string filename ) 
{ 
	//Temporary storage for the image that's loaded
	SDL_Surface* loadedImage = NULL;
	//The optimized image that will be used
	SDL_Surface* optimizedImage = NULL;
	
	//Load the image
	loadedImage = SDL_LoadBMP( filename.c_str() ); 

	//If nothing went wrong in loading the image
	if( loadedImage != NULL ) 
	{
		//Create an optimized image
		optimizedImage = SDL_DisplayFormat( loadedImage );
		//Free the old image
		SDL_FreeSurface( loadedImage );
		if (optimizedImage != NULL)
		{
            Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0xC0, 0xC0, 0xC0 ); //GRAYSCALE COLOR KEY ( 192, 192, 192 )
			SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey );
		}
	} 
//Return the optimized image
return optimizedImage;
}

void sdlManager::apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect* clip = NULL) 
{ 
	//Make a temporary rectangle to hold the offsets
	SDL_Rect offset;

	//Give the offsets to the rectangle
	offset.x = x;
	offset.y = y;

	//Blit the surface
	SDL_BlitSurface( source, clip, destination, &offset ); 
}
//Image Loader
void sdlManager::loadImages()
{
	hexTile = load_image( "Hex_One.bmp" );
	woodTile = load_image( "WoodHex.bmp" );
	wheatTile = load_image( "WheatHex.bmp" );
	stoneTile = load_image( "StoneHex.bmp" );
	sheepTile = load_image( "SheepHex.bmp" );
	brickTile = load_image( "BrickHex.bmp" );
}

void sdlManager::draw(SDL_Surface * screen, map * underlyingBoard)
{
	SDL_FillRect(screen, 0, 0);			// black screen
	int x = 0;

	SDL_Rect colorCursor = {0,0,15,15};
	for (int i = 0; i < 19; ++i)
	{
		if(i == 0 || i == 4 || i == 9 || i == 14 || i == 18)
		{
			x = 64;
		}
		if(i == 1 || i == 6 || i == 11 || i == 16)
		{
			x = 32;
		}
		if(i == 2 || i == 7 || i == 12 || i == 17)
		{
			x = 96;
		}
		if(i == 3 || i == 8 || i == 13)
		{
			x = 0;
		}
		if(i == 5 || i == 10 || i == 15)
		{
			x = 128;
		}
		switch(underlyingBoard->myCenters[i].resource)
		{
		case WOOD:		apply_surface(	underlyingBoard->myCenters[i].x * (400 / 9) - x,
										underlyingBoard->myCenters[i].y * 50 - 55,
										woodTile,
										screen,
										NULL); break;
		case WHEAT:		apply_surface(	underlyingBoard->myCenters[i].x * (400 / 9) - x,
										underlyingBoard->myCenters[i].y * 50 - 55,
										wheatTile,
										screen,
										NULL); break;
		case STONE:		apply_surface(	underlyingBoard->myCenters[i].x * (400 / 9) - x,
										underlyingBoard->myCenters[i].y * 50 - 55,
										stoneTile,
										screen,
										NULL); break;
		case SHEEP:		apply_surface(	underlyingBoard->myCenters[i].x * (400 / 9) - x,
										underlyingBoard->myCenters[i].y * 50 - 55,
										sheepTile,
										screen,
										NULL); break;
		case BRICK:		apply_surface(	underlyingBoard->myCenters[i].x * (400 / 9) - x,
										underlyingBoard->myCenters[i].y * 50 - 55,
										brickTile,
										screen,
										NULL); break;
		case 'D':		apply_surface(	underlyingBoard->myCenters[i].x * (400 / 9) - x,
										underlyingBoard->myCenters[i].y * 50 - 55,
										hexTile,
										screen,
										NULL); break;
		}
	}
	/*
	for (int i = 0; i < 19; ++i)
	{
		colorCursor.x = underlyingBoard->myCenters[i].x * (400 / 9) - 64;
		colorCursor.y = underlyingBoard->myCenters[i].y * 50 - 55;
		SDL_FillRect(screen, &colorCursor, -1);
	}
	*/
	/*
	SDL_Rect colorCursor = {0,0,15,15};
	for(int h = 0; h < colorH; ++h)
	{
		for(int w = 0; w < colorW; ++w)
		{
			colorCursor.x = w * 20;
			colorCursor.y = h * 20;
			SDL_FillRect(screen, &colorCursor, colors[h][w]);
		}
	}
	*/

	/*
	SDL_Rect drawRect = {
		(short)playerLocation.x,
		(short)playerLocation.y,
		(short)playerSize.x, 
		(short)playerSize.y
	};
	SDL_FillRect(screen, &drawRect, -1);	// white player box
	*/
	SDL_Flip(screen);
}

		