#include "map.h"

#define _EDGE(c,d) Edge(getNode(tempNodes, count, c),\
							getNode(tempNodes, count, d))

#define _CENTER(c,d,e) Center(getNode(tempNodes, count, c),\
							getNode(tempNodes, count, d), e)

map::map()
{
	//=====NODE ASSIGNMENT==================
	int count;
	mapState = map::TURNONESETTLEMENT;
	overallTurn = 1;

	Node tempNodes[54] = {
							 	 Node(8,1,1),Node(10,1,2),
					 Node(5,2,3),Node(7,2,4),Node(11,2,5),Node(13,2,6),
		 Node(2,3,7),Node(4,3,8),Node(8,3,9),Node(10,3,10),Node(14,3,11),Node(16,3,12),
		Node(1,4,13),Node(5,4,14),Node(7,4,15),Node(11,4,16),Node(13,4,17),Node(17,4,18),
		 Node(2,5,19),Node(4,5,20),Node(8,5,21),Node(10,5,22),Node(14,5,23),Node(16,5,24),
		Node(1,6,25),Node(5,6,26),Node(7,6,27),Node(11,6,28),Node(13,6,29),Node(17,6,30),
		 Node(2,7,31),Node(4,7,32),Node(8,7,33),Node(10,7,34),Node(14,7,35),Node(16,7,36),
		Node(1,8,37),Node(5,8,38),Node(7,8,39),Node(11,8,40),Node(13,8,41),Node(17,8,42),
		 Node(2,9,43),Node(4,9,44),Node(8,9,45),Node(10,9,46),Node(14,9,47),Node(16,9,48),
					 Node(5,10,49),Node(7,10,50),Node(11,10,51),Node(13,10,52),
								 Node(8,11,53),Node(10,11,54),
	};

	for(int i = 0; i < 54; ++i)
	{
		myNodes[i] = tempNodes[i];
		myNodes[i].owner = 4;
	}
		

	//===========SETTING THE NODES IN TERMS OF PIXELS=========================
	int x = 0;

	for (int i = 0; i < 54; ++i)
	{
		switch(myNodes[i].x)
		{
			case 8:		x = 0;		break;
			case 10:	x = 0;		break;
			case 7:		x = 24;		break;
			case 11:	x = -24;	break;
			case 4:		x = 48;		break;
			case 5:		x = 36;		break;
			case 13:	x = -36;	break;
			case 14:	x = -48;	break;
			case 16:	x = -64;	break;
			case 2:		x = 64;		break;
			case 17:	x = -96;	break;
			case 1:		x = 96;		break;
			default:	x = -200;	break;
		}
		myNodes[i].pixelX = myNodes[i].x * (400/9) - 16 + x;
		myNodes[i].pixelY = myNodes[i].y * 50 - 16;
	}

	count = 54;

	//========CENTER ASSIGNMENT==================

	Center tempCenters[19] = 
	{
						_CENTER(4, 5, 1),
				_CENTER(8, 9, 2),_CENTER(10, 11, 3),
		_CENTER(13, 14, 4),_CENTER(15, 16, 5),_CENTER(17, 18, 6),
				_CENTER(20, 21, 7),_CENTER(22, 23, 8),
		_CENTER(25, 26, 9),_CENTER(27, 28, 10),_CENTER(29, 30, 11),
				_CENTER(32, 33, 12),_CENTER(34, 35, 13),
		_CENTER(37, 38, 14),_CENTER(39, 40, 15),_CENTER(41, 42, 16),
				_CENTER(44, 45, 17),_CENTER(46, 47, 18),
						_CENTER(50, 51, 19),
	};

	for(int i = 0; i < 19; ++i)
		myCenters[i] = tempCenters[i];

	//=============CENTER GETTING NODES====================

	for(int i = 0; i < 19; ++i)
	{
		int allotedCenters = 0;
		for (int j = 0; j < 54; j++)
		{
			if (myNodes[j].y == myCenters[i].y)
			{
				if (myNodes[j].x + 2 == myCenters[i].x ||
					myNodes[j].x - 2 == myCenters[i].x)
				{
					myCenters[i].connectedNodes[allotedCenters] = &myNodes[j];
					allotedCenters++;
				}
			}
			else if (myNodes[j].y + 1 == myCenters[i].y)
			{
				if (myNodes[j].x + 1 == myCenters[i].x ||
					myNodes[j].x - 1 == myCenters[i].x)
				{
					myCenters[i].connectedNodes[allotedCenters] = &myNodes[j];
					allotedCenters++;
				}
			}
			else if (myNodes[j].y - 1 == myCenters[i].y)
			{
				if (myNodes[j].x + 1 == myCenters[i].x ||
					myNodes[j].x - 1 == myCenters[i].x)
				{
					myCenters[i].connectedNodes[allotedCenters] = &myNodes[j];
					allotedCenters++;
				}
			}
		}
	}

	//=============EDGE ASSIGNMENT=========================

	int amountEdges = 0;

	Edge * tempEdges;

	tempEdges = new Edge [1000];

	for(int i = 0; i < count; ++i)
	{
		for(int j = 0; j < count; ++j)
		{
			if(j != i)
			{

				if ((myNodes[i].y) == (myNodes[j].y) || // all these / scale
					(myNodes[i].y) + 1 == (myNodes[j].y) ||
					(myNodes[i].y) - 1 == (myNodes[j].y) )
				{
					if( (myNodes[i].x) + 2 == (myNodes[j].x) || //ALL THESE / scale
						(myNodes[i].x) + 1 == (myNodes[j].x) ||
						(myNodes[i].x) - 2 == (myNodes[j].x) ||
						(myNodes[i].x) - 1 == (myNodes[j].x) )
					{
						getNode(myNodes,count, i + 1)->numOfEdges++;
						tempEdges[amountEdges].from = getNode(myNodes, count, i + 1);
						tempEdges[amountEdges].to = getNode(myNodes, count, j + 1);
						amountEdges++;
					}
				}
			}
		}
	}


	const int eCount = amountEdges;

	for (int i = 0; i < eCount; ++i)
	{
		myEdges[i] = tempEdges[i];
		myEdges[i].ID = i;
		myEdges[i].owner = 4; // 4 means player 5, and is treated as never.
		myEdges[i].from->addNewEdge(&myEdges[i]);
		myEdges[i].to->addNewEdge(&myEdges[i]);
	}

	delete tempEdges;

	//=========CHIT ASSIGNMENT=================

	int tempInts[] = {5, 2, 6, 3, 8, 10, 9, 12, 11, 4, 8, 10, 9, 4, 5, 6, 3, 11};
	for (int i = 0; i < 19; ++i)
	{
		myChits[i] = tempInts[i];
	}

	//=========IMAGE ASSIGNMENT==================

	resourceCard = NULL;
	buildCard = NULL;
	testSelect = NULL;
	hexTile = NULL;
	woodTile = NULL;
	wheatTile = NULL;
	stoneTile = NULL;
	sheepTile = NULL;
	brickTile = NULL;
	for (int i = 0; i < 10; ++i)
	{
		chitTile[i] = NULL;
	}
	for (int i = 0; i < 4; ++i)
	{
		settlementTile[i] = NULL;
		cityTile[i] = NULL;
		roadTile[i] = NULL;
	}

	//===========SELECTRON====================
	nodeSelectron = NULL;
	roadSelectron = NULL;

	//============SETTING THE EDGES IN TERMS OF PIXELS=========================

	for (int i = 0; i < 144; ++i)
	{
		myEdges[i].pixelX = ( (myEdges[i].from->pixelX + myEdges[i].to->pixelX) / 2 );
		myEdges[i].pixelY = ( myEdges[i].from->pixelY + myEdges[i].to->pixelY ) / 2 ;
	}

}

Node * map::getNode(Node * population, int popCount, int ID)
{
	for(int i = 0; i < popCount; i++)
		if(population[i].ID == ID)
			return &population[i];
	return 0;
}

int map::getEdge(Edge * population, int popCount, int start, Node * from)
{
	for(int i = start; i < popCount; ++i)
		if(population[i].from == from)
			return i;
	return -1;
}

int map::getEdgeFromCount(Edge * population, int popCount, Node * from)
{
	int count =0;
	for(int i = 0; i < popCount; ++i)
		if(population[i].from == from)
			count++;
	return count;
}

int map::randomHarbor(int resource[])
{
	srand(0);
	int num;
	bool acceptable = false;

	//determine if the harbor has already been placed
	while(acceptable != true)
	{
		num = (rand() % 6);
		if(num < 5)
		{
			if(resource[num] < 1)
			{
				acceptable = true;
				resource[num]++;
			}
			else
			{
				acceptable = false;
			}
		}
		else
		{
			if(resource[num] < 5)
			{
				resource[num]++;
				acceptable = true;
			}
			else
			{
				acceptable = false;
			}
		}
	}
	return num;
}

void map::setHarbor(Node* harbor)
{
	int num, resource[6] = {0, 0, 0, 0, 0, 0};

	for(int i = 0; i < 54; i++)
	{
		//places harbor on pre-determined nodes
		switch(i)
		{
		case 2:
			num = randomHarbor(resource);
			harbor[i].harborType = num;
			break;
		case 3:
			harbor[i].harborType = harbor[2].harborType;
			break;
		case 4:
			num = randomHarbor(resource);
			harbor[i].harborType = num;
			break;
		case 5:
			harbor[i].harborType = harbor[4].harborType;
			break;
		case 6:
			num = randomHarbor(resource);
			harbor[i].harborType = num;
			break;
		case 12:
			harbor[i].harborType = harbor[6].harborType;
			break;
		case 11:
			num = randomHarbor(resource);
			harbor[i].harborType = num;
			break;
		case 17:
			harbor[i].harborType = harbor[11].harborType;
			break;
		case 24:
			num = randomHarbor(resource);
			harbor[i].harborType = num;
			break;
		case 30:
			harbor[i].harborType = harbor[24].harborType;
			break;
		case 29:
			num = randomHarbor(resource);
			harbor[i].harborType = num;
			break;
		case 35:
			harbor[i].harborType = harbor[29].harborType;
			break;
		case 43:
			num = randomHarbor(resource);
			harbor[i].harborType = num;
			break;
		case 49:
			harbor[i].harborType = harbor[43].harborType;
			break;
		case 46:
			num = randomHarbor(resource);
			harbor[i].harborType = num;
			break;
		case 51:
			harbor[i].harborType = harbor[46].harborType;
			break;
		case 52:
			num = randomHarbor(resource);
			harbor[i].harborType = num;
			break;
		case 53:
			harbor[i].harborType = harbor[52].harborType;
			break;
		default:
			harbor[i].harborType = NULL;
		}
	}
}

void map::initializeCenters(void)
{
	srand(time(0));
	rand();
	int woodLeft = 4;
	int stoneLeft = 3;
	int brickLeft = 3;
	int wheatLeft = 4;
	int sheepLeft = 4;
	int desertLeft = 1;
	int selector = 0;
	int desertPass = 0;
	// SELECTS A RANDOM NUMBER OUT OF ALL THE REMAINING AVAILABLE TILES AND ASSIGNS RESOURCES. INCLUDING 'D', DESERT
	for (int i = 0; i < 19; i++)
	{
		selector = rand();
		selector = selector % (woodLeft + sheepLeft + brickLeft + stoneLeft + wheatLeft + desertLeft);
		if (selector < woodLeft){myCenters[i].resource = WOOD; woodLeft--;}
		else if (selector < woodLeft + sheepLeft){myCenters[i].resource = SHEEP; sheepLeft--;}
		else if (selector < woodLeft + sheepLeft + brickLeft){myCenters[i].resource = BRICK; brickLeft--;}
		else if (selector < woodLeft + sheepLeft + brickLeft + stoneLeft){myCenters[i].resource = STONE; stoneLeft--;}
		else if (selector < woodLeft + sheepLeft + brickLeft + stoneLeft + wheatLeft){myCenters[i].resource = WHEAT; wheatLeft--;}
		else {myCenters[i].resource = 'D'; desertLeft--;}
	}

	int tempInts[] = {5, 2, 6, 3, 8, 10, 9, 12, 11, 4, 8, 10, 9, 4, 5, 6, 3, 11};
	int tempIntCenters[] = {13, 16, 18, 17, 15, 10, 5, 2, 0, 1, 3, 8, 11, 14, 12, 7, 4, 6, 9};
	for (int i = 0; i < 19; ++i)
	{
		if (myCenters[tempIntCenters[i]].resource == 'D'){desertPass = 1; myCenters[tempIntCenters[i]].chitWorth = 0;}
		else {myCenters[tempIntCenters[i]].chitWorth = tempInts[i - desertPass];}
	}
}

void map::loadImages()
{
	resourceCard = load_image( "resourceCard.bmp" );
	buildCard = load_image( "buildCard.bmp" );
	roadTile[0] = load_image( "roadRed.bmp" );
	roadTile[1] = load_image( "roadBlue.bmp" );
	roadTile[2] = load_image( "roadWhite.bmp" );
	roadTile[3] = load_image( "roadOrange.bmp" );
	settlementTile[0] = load_image( "settlementRed.bmp" );
	settlementTile[1] = load_image( "settlementBlue.bmp" );
	settlementTile[2] = load_image( "settlementWhite.bmp" );
	settlementTile[3] = load_image( "settlementOrange.bmp" );
	cityTile[0] = load_image( "cityRed.bmp" );
	cityTile[1] = load_image( "cityBlue.bmp" );
	cityTile[2] = load_image( "cityWhite.bmp" );
	cityTile[3] = load_image( "cityOrange.bmp" );
	testSelect = load_image( "testSelector.bmp" );
	hexTile = load_image( "Hex_One.bmp" );
	woodTile = load_image( "WoodHex.bmp" );
	wheatTile = load_image( "WheatHex.bmp" );
	stoneTile = load_image( "StoneHex.bmp" );
	sheepTile = load_image( "SheepHex.bmp" );
	brickTile = load_image( "BrickHex.bmp" );
	chitTile[0] = load_image( "chit2.bmp" );
	chitTile[1] = load_image( "chit3.bmp" );
	chitTile[2] = load_image( "chit4.bmp" );
	chitTile[3] = load_image( "chit5.bmp" );
	chitTile[4] = load_image( "chit6.bmp" );
	chitTile[5] = load_image( "chit8.bmp" );
	chitTile[6] = load_image( "chit9.bmp" );
	chitTile[7] = load_image( "chit10.bmp" );
	chitTile[8] = load_image( "chit11.bmp" );
	chitTile[9] = load_image( "chit12.bmp" );
}
void map::drawNodeSelectron(SDL_Surface * screen)
{
	if (nodeSelectron >= 0 && nodeSelectron <= 53)
	{
		apply_surface(	myNodes[nodeSelectron].pixelX,
						myNodes[nodeSelectron].pixelY,
						testSelect,
						screen,
						NULL );
	}
}

void map::drawRoadSelectron(SDL_Surface * screen)
{
	if (roadSelectron >= 0 && roadSelectron <= 143)
	{
		apply_surface(	myEdges[roadSelectron].pixelX,
						myEdges[roadSelectron].pixelY,
						testSelect,
						screen,
						NULL );
	}
}


void map::drawBoard(SDL_Surface * screen)
{
	int x = 0;
	for (int i = 0; i < 19; ++i)
	{
		if(i == 0 || i == 4 || i == 9 || i == 14 || i == 18)
		{
			x = 64;
		}
		else if(i == 1 || i == 6 || i == 11 || i == 16)
		{
			x = 32;
		}
		else if(i == 2 || i == 7 || i == 12 || i == 17)
		{
			x = 96;
		}
		else if(i == 3 || i == 8 || i == 13)
		{
			x = 0;
		}
		else if(i == 5 || i == 10 || i == 15)
		{
			x = 128;
		}
		switch(myCenters[i].resource)
		{
		case WOOD:		apply_surface(	myCenters[i].x * (400 / 9) - x,
										myCenters[i].y * 50 - 55,
										woodTile,
										screen,
										NULL); break;
		case WHEAT:		apply_surface(	myCenters[i].x * (400 / 9) - x,
										myCenters[i].y * 50 - 55,
										wheatTile,
										screen,
										NULL); break;
		case STONE:		apply_surface(	myCenters[i].x * (400 / 9) - x,
										myCenters[i].y * 50 - 55,
										stoneTile,
										screen,
										NULL); break;
		case SHEEP:		apply_surface(	myCenters[i].x * (400 / 9) - x,
										myCenters[i].y * 50 - 55,
										sheepTile,
										screen,
										NULL); break;
		case BRICK:		apply_surface(	myCenters[i].x * (400 / 9) - x,
										myCenters[i].y * 50 - 55,
										brickTile,
										screen,
										NULL); break;
		case 'D':		apply_surface(	myCenters[i].x * (400 / 9) - x,
										myCenters[i].y * 50 - 55,
										hexTile,
										screen,
										NULL); break;
		}
	}
	x = 0;
	for (int i = 0; i < 19; ++i)
	{
		if(i == 0 || i == 4 || i == 9 || i == 14 || i == 18)
		{
			x = 0;
		}
		else if(i == 1 || i == 6 || i == 11 || i == 16)
		{
			x = -32;
		}
		else if(i == 2 || i == 7 || i == 12 || i == 17)
		{
			x = 32;
		}
		else if(i == 3 || i == 8 || i == 13)
		{
			x = -64;
		}
		else if(i == 5 || i == 10 || i == 15)
		{
			x = 64;
		}
		int y = 2;
		if(myCenters[i].chitWorth >= 8){ ++y; }
		if(myCenters[i].chitWorth != 0)
		{
			apply_surface(	myCenters[i].x * (400 / 9) - x - 19,
							myCenters[i].y * 50 - 19,
							chitTile[myCenters[i].chitWorth - y],
							screen,
							NULL);
		}
	}

	for (int i = 0; i < 54; ++i)
	{
		if (myNodes[i].owner != 4)
		{
			if (myNodes[i].cityType == 1)
			{
				apply_surface(	myNodes[i].pixelX,
								myNodes[i].pixelY,
								settlementTile[myNodes[i].owner],
								screen,
								NULL);
			}
			else if (myNodes[i].cityType == 2)
			{
				apply_surface(	myNodes[i].pixelX,
								myNodes[i].pixelY,
								cityTile[myNodes[i].owner],
								screen,
								NULL);
			}
		}
	}
	for (int i = 0; i < 144; ++i)
	{
		if (myEdges[i].owner != 4)
		{
			apply_surface(	myEdges[i].pixelX,
							myEdges[i].pixelY,
							roadTile[myEdges[i].owner],
							screen,
							NULL);
		}
	}
}


void map::drawBuildCard(SDL_Surface * screen)
{
	apply_surface( 0, 0, buildCard, screen, NULL );
}

void map::drawResourceList(SDL_Surface * screen, player * p)
{
	apply_surface( 0, 0, resourceCard, screen, NULL );
}

void map::drawDevHand(SDL_Surface * screen)
{

}

void map::drawTradeScreen(SDL_Surface * screen)
{

}

void map::draw(SDL_Surface * screen, player * p)
{
	switch(mapState)
	{
		case map::MAP:				drawBoard(screen);				break; 
		case map::BUILDCARD:		drawBuildCard(screen);			break;
		case map::RESOURCELIST:		drawResourceList(screen, p);	break;
		case map::DEVHAND:			drawDevHand(screen);			break;
		case map::TRADE:			drawTradeScreen(screen);		break;
		case map::BUILDROAD:		drawBoard(screen);
									drawRoadSelectron(screen);		break;
		case map::BUILDSETTLEMENT:	drawBoard(screen);
									drawNodeSelectron(screen);		break;
		case map::BUILDCITY:		drawBoard(screen);
									drawNodeSelectron(screen);		break;
		case map::TURNONESETTLEMENT:		drawBoard(screen);
									drawNodeSelectron(screen);		break;
		case map::TURNONEROAD:		drawBoard(screen);
									drawRoadSelectron(screen);		break;
		case map::TURNTWOSETTLEMENT:		drawBoard(screen);
									drawNodeSelectron(screen);		break;
		case map::TURNTWOROAD:		drawBoard(screen);
									drawRoadSelectron(screen);		break;
	}
}

void map::shutdownImages()
{
	SDL_FreeSurface(testSelect);
	SDL_FreeSurface(hexTile);
	SDL_FreeSurface(woodTile);
	SDL_FreeSurface(wheatTile);
	SDL_FreeSurface(stoneTile);
	SDL_FreeSurface(sheepTile);
	SDL_FreeSurface(brickTile);
	for (int i = 0; i < 10; ++i)
	{
		SDL_FreeSurface(chitTile[i]);
	}
	for (int i = 0; i < 4; ++i)
	{
		SDL_FreeSurface(settlementTile[i]);
		SDL_FreeSurface(cityTile[i]);
		SDL_FreeSurface(roadTile[i]);
	}
}

//function to load images
SDL_Surface* map::load_image( std::string filename ) 
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

void map::apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect* clip = NULL) 
{ 
	//Make a temporary rectangle to hold the offsets
	SDL_Rect offset;

	//Give the offsets to the rectangle
	offset.x = x;
	offset.y = y;

	//Blit the surface
	SDL_BlitSurface( source, clip, destination, &offset ); 
}


void map::handleInput(SDL_Event e, player * p)
{
		switch(mapState)
		{
		case map::MAP:
			switch(e.type)
			{
				case SDL_KEYDOWN:
					switch(e.key.keysym.sym)
					{
					case SDLK_2:	mapState= map::BUILDCARD;		break;
					case SDLK_3:	mapState= map::RESOURCELIST;	break;
					case SDLK_4:	mapState= map::DEVHAND;			break;
					case SDLK_5:	mapState= map::TRADE;			break;
					case SDLK_0:	mapState= map::ENDTURN;			break;
					}
			}
			break;
		case map::BUILDCARD:
			switch(e.type)
			{
				case SDL_KEYDOWN:
					switch(e.key.keysym.sym)
					{
					case SDLK_1:	mapState= map::MAP;				break;
					case SDLK_3:	mapState= map::RESOURCELIST;	break;
					case SDLK_4:	mapState= map::DEVHAND;			break;
					case SDLK_5:	mapState= map::TRADE;			break;
					case SDLK_0:	mapState= map::ENDTURN;			break;
					case SDLK_r:	if (overallTurn == 1 || overallTurn == 2 || p->checkBuildSomething('R', &dvc) == true)
									{
										p->actuallyBuildSomething('R', &rsc, &dvc);
										mapState = map::BUILDROAD;	break;
									}
					case SDLK_s:	if (overallTurn == 1 || overallTurn == 2 || p->checkBuildSomething('S', &dvc) == true)
									{
										p->actuallyBuildSomething('S', &rsc, &dvc);
										mapState = map::BUILDSETTLEMENT;	break;
									}
					case SDLK_c:	if (overallTurn != 1 || overallTurn != 2 || p->checkBuildSomething('C', &dvc) == true)
									{
										p->actuallyBuildSomething('C', &rsc, &dvc);
										mapState = map::BUILDCITY;	break;
									}
					case SDLK_d:	if (overallTurn != 1 || overallTurn != 2 || p->checkBuildSomething('D', &dvc) == true)
									{
										p->actuallyBuildSomething('D', &rsc, &dvc);
										mapState = map::MAP;	break;
									}
					}
			}
			break;
		case map::RESOURCELIST:
			switch(e.type)
			{
				case SDL_KEYDOWN:
					switch(e.key.keysym.sym)
					{
					case SDLK_1:	mapState= map::MAP;				break;
					case SDLK_2:	mapState= map::BUILDCARD;		break;
					case SDLK_4:	mapState= map::DEVHAND;			break;
					case SDLK_5:	mapState= map::TRADE;			break;
					}
			}
			break;
		case map::DEVHAND:
			switch(e.type)
			{
				case SDL_KEYDOWN:
					switch(e.key.keysym.sym)
					{
					case SDLK_1:	mapState= map::MAP;				break;
					case SDLK_2:	mapState= map::BUILDCARD;		break;
					case SDLK_3:	mapState= map::RESOURCELIST;	break;
					case SDLK_5:	mapState= map::TRADE;			break;
					case SDLK_m:	p->playDevCard('M');			break;
									//MONOPOLY FUNCTIONALITY GO!
					case SDLK_s:	p->playDevCard('S');
									//SOLDIER FUNCTIONALITY GO!
					case SDLK_y:	p->playDevCard('Y');
									//YEAR OF PLENTY FUNCTIONALITY GO!
					case SDLK_t:	p->playDevCard('T');
									//TWO ROADS FUNCTIONALITY GO!
					case SDLK_v:	p->playDevCard('V');
									//VICTORY POINT FUNCTIONALITY GO!
					}
			}
			break;
		case map::TRADE:
			switch(e.type)
			{
				case SDL_KEYDOWN:
					switch(e.key.keysym.sym)
					{
					case SDLK_1:	mapState= map::MAP;				break;
					case SDLK_2:	mapState= map::BUILDCARD;		break;
					case SDLK_4:	mapState= map::DEVHAND;			break;
					case SDLK_5:	mapState= map::TRADE;			break;
					//ADD TRADE FUNCTIONALITY. DON'T KNOW HOW.
					}
			}
			break;
		case map::BUILDROAD:
			switch(e.type)
			{
				case SDL_MOUSEMOTION:	whichRoadIsWithin(e.motion.x, e.motion.y, 100); break;

				case SDL_MOUSEBUTTONDOWN:
					switch(e.button.button)
					{
						case SDL_BUTTON_LEFT:	constructRoadOnMap(p); mapState = map::MAP;	break;
					}
					break;
			}
			break;
		case map::BUILDSETTLEMENT:
			switch(e.type)
			{
				case SDL_MOUSEMOTION:	whichNodeIsWithin(e.motion.x, e.motion.y, 100); break;

				case SDL_MOUSEBUTTONDOWN:
					switch(e.button.button)
					{
						case SDL_BUTTON_LEFT:	constructSettlementOnMap(p); mapState = map::MAP;	break;
					}
					break;
			}
			break;
		case map::BUILDCITY:
			switch(e.type)
			{
				case SDL_MOUSEMOTION:	whichNodeIsWithin(e.motion.x, e.motion.y, 100); break;
			}
			break;
		case map::TURNONESETTLEMENT:
			switch(e.type)
			{
				case SDL_MOUSEMOTION:	whichNodeIsWithin(e.motion.x, e.motion.y, 100); break;
				case SDL_MOUSEBUTTONDOWN:
					switch(e.button.button)
					{
						case SDL_BUTTON_LEFT:	constructSettlementOnMap(p); mapState = map::TURNONEROAD;	break;
					}
					break;
			}
			break;
		case map::TURNONEROAD:
			switch(e.type)
			{
				case SDL_MOUSEMOTION:	whichRoadIsWithin(e.motion.x, e.motion.y, 100); break;
				case SDL_MOUSEBUTTONDOWN:
					switch(e.button.button)
					{
						case SDL_BUTTON_LEFT:	constructRoadOnMap(p); mapState = map::ENDTURN;	cout << "MADE IT THIS FAR" << endl; break;
					}
					break;
			}
			break;
		case map::TURNTWOSETTLEMENT:
			switch(e.type)
			{
				case SDL_MOUSEMOTION:			whichNodeIsWithin(e.motion.x, e.motion.y, 100); break;
				case SDL_MOUSEBUTTONDOWN:
					switch(e.button.button)
					{
						case SDL_BUTTON_LEFT:	constructSettlementOnMap(p); mapState = map::TURNTWOROAD;	break;
					}
					break;
			}
			break;
		case map::TURNTWOROAD:
			switch(e.type)
			{
				case SDL_MOUSEMOTION:	whichRoadIsWithin(e.motion.x, e.motion.y, 100); break;
				case SDL_MOUSEBUTTONDOWN:
					switch(e.button.button)
					{
						case SDL_BUTTON_LEFT:	constructRoadOnMap(p); mapState = map::ENDTURN;	break;
					}
					break;
			}
			break;
		case map::ENDTURN:
			break;
		}
}

void map::whichNodeIsWithin(int const & x, int const & y, int radius)
{
	float minDistance, distance, dx, dy, maxRadius = radius*radius;
	minDistance = 2500;
	Node * closest = NULL;
	for(int i = 0; i < 54; ++i)
	{
		dx = myNodes[i].pixelX + 16- x;
		dy = myNodes[i].pixelY + 16 - y;
		distance = dx*dx + dy*dy;
		if(distance < maxRadius 
		&& (closest != NULL || distance < minDistance))
		{
			minDistance = distance;
			nodeSelectron = myNodes[i].ID - 1;
		}
	}
}

void map::whichRoadIsWithin(int const & x, int const & y, int radius)
{
	float minDistance, distance, dx, dy, maxRadius = radius*radius;
	minDistance = 2500;
	Edge * closest = NULL;
	for(int i = 0; i < 144; ++i)
	{
		dx = myEdges[i].pixelX + 16 - x;
		dy = myEdges[i].pixelY + 16 - y;
		distance = dx*dx + dy*dy;
		if(distance < maxRadius 
		&& (closest != NULL || distance < minDistance))
		{
			minDistance = distance;
			roadSelectron = myEdges[i].ID;
		}
	}
}

void map::constructRoadOnMap(player * p)
{
	if (myEdges[roadSelectron].owner == 4)
	{
		myEdges[roadSelectron].owner = p->ID;
	}
}
void map::constructSettlementOnMap(player * p)
{
	//THIS FUNCTION IS MILDLY BAD. IT LOOKS FOR BUILDABILITY BY DRAW PIXEL COUNTS, NOT BY ACTUALLY LOOKING AT EDGES THAT CONNECT TO NODES.
	bool buildable = true;
	for (int i = 0; i < 54; ++i)
	{
		if (nodeSelectron != i)
		{
			if (myNodes[i].owner != 4)
			{
				if (((myNodes[i].x + 1 == myNodes[nodeSelectron].x ||
					myNodes[i].x - 1 == myNodes[nodeSelectron].x) &&
					(myNodes[i].y + 1 == myNodes[nodeSelectron].y ||
					myNodes[i].y - 1 == myNodes[nodeSelectron].y)) ||
					(myNodes[i].x + 2 == myNodes[nodeSelectron].x ||
					myNodes[i].x - 2 == myNodes[nodeSelectron].x))
				{
					buildable = false;
				}
			}
		}
	}
	// RIGHT AROUND HERE, THIS FUNCTION WOULD NEED TO CHECK FOR ROADS AND SET BUILDABILITY TO FALSE IF IT FINDS NONE.
	if (buildable == true && myNodes[nodeSelectron].owner == 4)
	{
		myNodes[nodeSelectron].owner = p->ID;
		myNodes[nodeSelectron].cityType = 1;
	}
}