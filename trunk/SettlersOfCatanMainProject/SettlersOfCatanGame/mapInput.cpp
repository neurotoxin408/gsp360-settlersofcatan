#include "map.h"
#include <ctime>

// DURING THE GAME, THE MAP GOES INTO MANY MAP STATES. 
// THIS IS THE LIST OF ALL THE MAP STATES, AND WHICH 
// INPUT SCRIPT TO CALL WHEN IT IS IN A SPECIFIC MAP STATE.

void map::handleInput(SDL_Event e, Game * g)
{
		switch(mapState)
		{
		case map::BEGINTURN:			handleInput_BEGINTURN(e, g);			break;		
		case map::MAP:					handleInput_MAP(e, g);					break;
		case map::BUILDCARD:			handleInput_BUILDCARD(e, g);			break;
		case map::RESOURCELIST:			handleInput_RESOURCELIST(e, g);			break;
		case map::DEVHAND:				handleInput_DEVHAND(e, g);				break;
		case map::TRADE:				handleInput_TRADE(e, g);				break;
		case map::BUILDROAD:			handleInput_BUILDROAD(e, g);			break;
		case map::BUILDSETTLEMENT:		handleInput_BUILDSETTLEMENT(e, g);		break;
		case map::BUILDCITY:			handleInput_BUILDCITY(e, g);			break;
		case map::TURNONESETTLEMENT:	handleInput_TURNONESETTLEMENT(e, g);	break;
		case map::TURNONEROAD:			handleInput_TURNONEROAD(e, g);			break;
		case map::TURNTWOSETTLEMENT:	handleInput_TURNTWOSETTLEMENT(e, g);	break;
		case map::TURNTWOROAD:			handleInput_TURNTWOROAD(e, g);			break;
		case map::ENDTURN:														break;
		}
}

void map::handleInput_BEGINTURN(SDL_Event e, Game * g)
{
	if (rolledDice == false)
	{
		cout << " ROLLED A " << dice1+dice2 << endl;
		for (int i = 0; i < 19; ++i)
		{
			if (myCenters[i].chitWorth == dice1+dice2)
			{
				for (int j = 0; j < 6; ++j)
				{
					if (myCenters[i].connectedNodes[j]->owner != map::NOT_A_PLAYER)
					{
						int amount = myCenters[i].connectedNodes[j]->cityType;
						char type = myCenters[i].resource;
						g->p[myCenters[i].connectedNodes[j]->owner].drawResource(&rsc, type, amount);
						cout << "AWARDED " << amount << " " << type << " to player " << g->p[myCenters[i].connectedNodes[j]->owner].ID << endl;
					}
				}
			}
		}
		rsc.DisplayResourceBankStatus();
	}
	rolledDice = true;
	


	switch(e.type)
	{
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym)
			{
			case SDLK_SPACE:		rolledDice = false; 
									mapState= map::MAP;		break;	// THIS SWITCH FUNCTION MEANS THAT THIS 
																	// STATE WILL WAIT UNTIL THE PLAYER ACKNOWLEDGES 
																	// THE FACT THAT IT IS HIS OR HER TURN AND HE OR 
																	// SHE HAS ROLLED A #.
			}
	}
}

void map::handleInput_MAP(SDL_Event e, Game * g)
{
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
				//Dice roll can go here <--------------------
				// kyle:: actually I'd recommend putting it in handleInput_BEGINTURN, 
				// that way it only happens once. handleInput_MAP can happen multiple 
				// times per turn (if someone switches in and out of the map screen 
				// and the trade screen, for example).
			}
	}
}

void map::handleInput_BUILDCARD(SDL_Event e, Game * g)
{
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
			case SDLK_r:	if (g->p[g->activePlayer].checkBuildSomething('R', &dvc) == true)
							{
								mapState = map::BUILDROAD;	break;
							}
			case SDLK_s:	if (g->p[g->activePlayer].checkBuildSomething('S', &dvc) == true)
							{
								mapState = map::BUILDSETTLEMENT;	break;
							}
			case SDLK_c:	if (g->p[g->activePlayer].checkBuildSomething('C', &dvc) == true)
							{
								g->p[g->activePlayer].actuallyBuildSomething('C', &rsc, &dvc);
								mapState = map::BUILDCITY;	break;
							}
			case SDLK_d:	if (g->p[g->activePlayer].checkBuildSomething('D', &dvc) == true)
							{
								g->p[g->activePlayer].actuallyBuildSomething('D', &rsc, &dvc);
								mapState = map::MAP;	break;
							}
			}
	}
}

void map::handleInput_RESOURCELIST(SDL_Event e, Game * g)
{
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
}

void map::handleInput_DEVHAND(SDL_Event e, Game * g)
{
	switch(e.type)
	{
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym)
			{
			case SDLK_1:	mapState= map::MAP;				break;
			case SDLK_2:	mapState= map::BUILDCARD;		break;
			case SDLK_3:	mapState= map::RESOURCELIST;	break;
			case SDLK_5:	mapState= map::TRADE;			break;
			case SDLK_m:	g->p[g->activePlayer].playDevCard('M');			break;
							//MONOPOLY FUNCTIONALITY GO!
			case SDLK_s:	g->p[g->activePlayer].playDevCard('S');
							//SOLDIER FUNCTIONALITY GO!
			case SDLK_y:	g->p[g->activePlayer].playDevCard('Y');
							//YEAR OF PLENTY FUNCTIONALITY GO!
			case SDLK_t:	g->p[g->activePlayer].playDevCard('T');
							//TWO ROADS FUNCTIONALITY GO!
			case SDLK_v:	g->p[g->activePlayer].playDevCard('V');
							//VICTORY POINT FUNCTIONALITY GO!
			}
	}
}

void map::handleInput_TRADE(SDL_Event e, Game * g)
{
	switch(e.type)
	{
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym)
			{
			case SDLK_1:	mapState= map::MAP;				break;
			case SDLK_2:	mapState= map::BUILDCARD;		break;
			case SDLK_3:	mapState= map::RESOURCELIST;	break;
			case SDLK_4:	mapState= map::DEVHAND;			break;
			//ADD TRADE FUNCTIONALITY. DON'T KNOW HOW.
			}
	}
}

void map::handleInput_BUILDROAD(SDL_Event e, Game * g)
{
	switch(e.type)
	{
		case SDL_MOUSEMOTION:	whichRoadIsWithin(e.motion.x, e.motion.y, 100); break;

		case SDL_MOUSEBUTTONDOWN:
			switch(e.button.button)
			{
			case SDL_BUTTON_LEFT:	
				if(constructRoadOnMap(g) == true)
				{ 
					g->p[g->activePlayer].actuallyBuildSomething('R', &rsc, &dvc);
					mapState = map::MAP;
				}	
				break;
			}
			break;
	}
}

void map::handleInput_BUILDSETTLEMENT(SDL_Event e, Game * g)
{
	switch(e.type)
	{
		case SDL_MOUSEMOTION:	whichNodeIsWithin(e.motion.x, e.motion.y, 100); break;

		case SDL_MOUSEBUTTONDOWN:
			switch(e.button.button)
			{
			case SDL_BUTTON_LEFT:	
				if(constructSettlementOnMap(g) == true)
				{ 
					g->p[g->activePlayer].actuallyBuildSomething('S', &rsc, &dvc);
					mapState = map::MAP;
				}	
				break;
			}
			break;
	}
}

void map::handleInput_BUILDCITY(SDL_Event e, Game * g)
{
	switch(e.type)
	{
		case SDL_MOUSEMOTION:	whichNodeIsWithin(e.motion.x, e.motion.y, 100); break;
	}
}

void map::handleInput_TURNONESETTLEMENT(SDL_Event e, Game * g)
{
	switch(e.type)
	{
		case SDL_MOUSEMOTION:	whichNodeIsWithin(e.motion.x, e.motion.y, 100); break;
		case SDL_MOUSEBUTTONDOWN:
			switch(e.button.button)
			{
				case SDL_BUTTON_LEFT:	if(constructSettlementOnMapAnywhere(g) == true){ mapState = map::TURNONEROAD;}	break;
			}
			break;
	}
}

void map::handleInput_TURNONEROAD(SDL_Event e, Game * g)
{
	switch(e.type)
	{
		case SDL_MOUSEMOTION:	whichRoadIsWithin(e.motion.x, e.motion.y, 100); break;
		case SDL_MOUSEBUTTONDOWN:
			switch(e.button.button)
			{
			case SDL_BUTTON_LEFT:	if (constructRoadOnMap(g) == true){ mapState = map::ENDTURN;} break;
			}
			break;
	}
}

void map::handleInput_TURNTWOSETTLEMENT(SDL_Event e, Game * g)
{
	switch(e.type)
	{
		case SDL_MOUSEMOTION:			whichNodeIsWithin(e.motion.x, e.motion.y, 100); break;
		case SDL_MOUSEBUTTONDOWN:
			switch(e.button.button)
			{
				case SDL_BUTTON_LEFT:	if(constructSettlementOnMapAnywhere(g) == true){ mapState = map::TURNTWOROAD;}	break;
			}
			break;
	}
}

void map::handleInput_TURNTWOROAD(SDL_Event e, Game * g)
{
	switch(e.type)
	{
		case SDL_MOUSEMOTION:	whichRoadIsWithin(e.motion.x, e.motion.y, 100); break;
		case SDL_MOUSEBUTTONDOWN:
			switch(e.button.button)
			{
				case SDL_BUTTON_LEFT:	if (constructRoadOnMap(g) == true){ mapState = map::ENDTURN;} break;
			}
			break;
	}
}