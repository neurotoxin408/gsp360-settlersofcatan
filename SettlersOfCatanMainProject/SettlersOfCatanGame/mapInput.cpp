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
			case map::BUILDROAD:			handleInput_BUILDROAD(e, g);			break;
			case map::BUILDSETTLEMENT:		handleInput_BUILDSETTLEMENT(e, g);		break;
			case map::BUILDCITY:			handleInput_BUILDCITY(e, g);			break;
			case map::TURNONESETTLEMENT:	handleInput_TURNONESETTLEMENT(e, g);	break;
			case map::TURNONEROAD:			handleInput_TURNONEROAD(e, g);			break;
			case map::TURNTWOSETTLEMENT:	handleInput_TURNTWOSETTLEMENT(e, g);	break;
			case map::TURNTWOROAD:			handleInput_TURNTWOROAD(e, g);			break;
			case map::FREETWORESOURCES:		handleInput_FREETWORESOURCES(e, g);		break;
			case map::FREETWOROADS:			handleInput_FREETWOROADS(e, g);			break;
			case map::SETTHETHIEF:			handleInput_SETTHETHIEF(e, g);			break;
			case map::TRADEBANKHARBORSCREEN:	handleInput_TRADEBANKHARBORSCREEN(e, g);	break;
			case map::TRADETARGET:			handleInput_TRADETARGET(e, g);			break;
			case map::TRADEPLAYERSCREEN:	handleInput_TRADEPLAYERSCREEN(e, g);	break;
			case map::PICKMONOPOLY:			handleInput_PICKMONOPOLY(e, g);	break;
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
			if (myCenters[i].chitWorth == dice1+dice2 && myCenters[i].thiefHere == false)
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
		calculateVictoryPoints(g);
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
	placeholderFREE = 2; // POOR PLACEMENT, BUT IT MUST BE DONE!
	soundQueue = 20;
	switch(e.type)
	{
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym)
			{
			case SDLK_2:	mapState= map::BUILDCARD;		break;
			case SDLK_3:	mapState= map::RESOURCELIST;	break;
			case SDLK_4:	mapState= map::DEVHAND;			break;
			case SDLK_5:	mapState= map::TRADETARGET;			break;
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
			case SDLK_5:	mapState= map::TRADETARGET;			break;
			case SDLK_0:	mapState= map::ENDTURN;			break;
			case SDLK_r:	if (g->p[g->activePlayer].checkBuildSomething('R', &dvc) == true)
							{
								mapState = map::BUILDROAD;	break;
							}
							else{break;}
			case SDLK_s:	if (g->p[g->activePlayer].checkBuildSomething('S', &dvc) == true)
							{
								mapState = map::BUILDSETTLEMENT;	break;
							}
							else{break;}
			case SDLK_c:	if (g->p[g->activePlayer].checkBuildSomething('C', &dvc) == true)
							{
								mapState = map::BUILDCITY;	break;
							}
							else{break;}
			case SDLK_d:	if (g->p[g->activePlayer].checkBuildSomething('D', &dvc) == true)
							{
								g->p[g->activePlayer].actuallyBuildSomething('D', &rsc, &dvc);
								mapState = map::MAP;	break;
							}
							else{break;}
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
			case SDLK_5:	mapState= map::TRADETARGET;			break;
				//DONT BE CHEATING DAWG
				
			case SDLK_j:	g->p[g->activePlayer].changeResource(WOOD, 99);	
				g->p[g->activePlayer].changeResource(BRICK, 99);
				g->p[g->activePlayer].changeResource(STONE, 99);
				g->p[g->activePlayer].changeResource(SHEEP, 99);	
				g->p[g->activePlayer].changeResource(WHEAT, 99);	break;
				

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
			case SDLK_5:	mapState= map::TRADETARGET;			break;
			case SDLK_m:	if (g->p[g->activePlayer].playDevCard('M'))
							{
								mapState = map::PICKMONOPOLY;
							}
							break;
			case SDLK_s:	if (g->p[g->activePlayer].playDevCard('S'))
							{
								calcLargestArmy(g);
								calculateVictoryPoints(g);
								mapState = map::SETTHETHIEF;
							}
							break;
			case SDLK_y:	if (g->p[g->activePlayer].playDevCard('Y'))
							{	
								mapState = map::FREETWORESOURCES;
							}
							break;
			case SDLK_r:	if (g->p[g->activePlayer].playDevCard('T'))
							{
								mapState = map::FREETWOROADS;
							}
							break;
			case SDLK_v:	if (g->p[g->activePlayer].playDevCard('V'))
							{
								if (calculateVictoryPoints(g))
								{
									mapState= map::SOMEONEWON;
								}
								else {mapState= map::MAP;}
							}
							break;
							
			}
	}
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void map::handleInput_TRADETARGET(SDL_Event e, Game * g)
{
	switch(e.type)
	{
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym)
			{
			case SDLK_1:					
				if (g->activePlayer != 0)
				{	
					tradebank->playerNumber = 0;
					mapState= map::TRADEPLAYERSCREEN;			
				}
				break;
			case SDLK_2:				
				if (g->activePlayer != 1)
				{	
					tradebank->playerNumber = 1;
					mapState= map::TRADEPLAYERSCREEN;			
				}
				break;
			case SDLK_3:				
				if (g->activePlayer != 2)
				{	
					tradebank->playerNumber = 2;
					mapState= map::TRADEPLAYERSCREEN;			
				}
				break;
			case SDLK_4:
				if (g->activePlayer != 3)
				{	
					if (g->numPlayers == 4)
					{
						tradebank->playerNumber = 3;
						mapState= map::TRADEPLAYERSCREEN;			
					}
				}
				break;

			case SDLK_i:
				if(g->p[g->activePlayer].ownsThreeForOneHarbor)
					tradebank->harbor_type = THREE_TO_ONE;
				else
					tradebank->harbor_type = BANK;
				mapState = map::TRADEBANKHARBORSCREEN;			
				break;
			
			case SDLK_b:
				if(g->p[g->activePlayer].ownsBrickHarbor)
				{
					tradebank->harbor_type = BRICK;
					mapState = map::TRADEBANKHARBORSCREEN;	
				}
				else
					cout << "You dont own this harbor type: brick" << endl;
				break;
			
			case SDLK_l:
				if(g->p[g->activePlayer].ownsWoodHarbor)
				{
					tradebank->harbor_type = WOOD;
					mapState = map::TRADEBANKHARBORSCREEN;			
				}
				else
					cout << "You dont own this harbor type: wood" << endl;
				break;
			
			case SDLK_s:	
				if(g->p[g->activePlayer].ownsStoneHarbor)
				{
					tradebank->harbor_type = STONE;
					mapState = map::TRADEBANKHARBORSCREEN;	
				}
				else
					cout << "You dont own this harbor type: stone" << endl;
				break;
			
			case SDLK_e:	
				if(g->p[g->activePlayer].ownsSheepHarbor)
				{
					tradebank->harbor_type = SHEEP;
					mapState = map::TRADEBANKHARBORSCREEN;	
				}
				else
					cout << "You dont own this harbor type: sheep" << endl;
				break;
			
			case SDLK_w:	
				if(g->p[g->activePlayer].ownsWheatHarbor)
				{
					tradebank->harbor_type = WHEAT;
					mapState = map::TRADEBANKHARBORSCREEN;		
				}
				else
					cout << "You dont own this harbor type: wheat" << endl;
				break;
			
			case SDLK_0:	mapState = map::MAP;	break;
			}
	}
}

void map::handleInput_TRADEPLAYERSCREEN(SDL_Event e, Game * g)
{
	switch(e.type)
	{
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym)
			{
			case SDLK_0:	mapState= map::MAP;				break;
			case SDLK_1:	mapState= map::MAP;				break;
			case SDLK_2:	mapState= map::BUILDCARD;		break;
			case SDLK_3:	mapState= map::RESOURCELIST;	break;
			case SDLK_4:	mapState= map::DEVHAND;			break;
			
			//i think we could do something like this, it seems to add to the numbers, then when its traded, just set them back to 0
			case SDLK_q:	if (g->p[g->activePlayer].brick > 0 + tradebank->temp_brick_give){tradebank->temp_brick_give++; cout << "+1 Temp Brick Give" << endl;} break;
			case SDLK_w:	if (g->p[g->activePlayer].wood > 0 + tradebank->temp_wood_give){tradebank->temp_wood_give++; cout << "+1 Temp Wood Give" << endl;} break;
			case SDLK_e:	if (g->p[g->activePlayer].stone > 0 + tradebank->temp_stone_give){tradebank->temp_stone_give++; cout << "+1 Temp Stone Give" << endl;} break;
			case SDLK_r:	if (g->p[g->activePlayer].sheep > 0 + tradebank->temp_sheep_give){tradebank->temp_sheep_give++; cout << "+1 Temp Sheep Give" << endl;} break;
			case SDLK_t:	if (g->p[g->activePlayer].wheat > 0 + tradebank->temp_wheat_give){tradebank->temp_wheat_give++; cout << "+1 Temp Wheat Give" << endl;} break;

			case SDLK_a:	if (g->p[tradebank->playerNumber].brick > 0 + tradebank->temp_brick_recieve){tradebank->temp_brick_recieve++; cout << "+1 Temp Brick Recieve" << endl;} break;
			case SDLK_s:	if (g->p[tradebank->playerNumber].wood > 0 + tradebank->temp_wood_recieve){tradebank->temp_wood_recieve++; cout << "+1 Temp Wood Recieve" << endl;} break;
			case SDLK_d:	if (g->p[tradebank->playerNumber].stone > 0 + tradebank->temp_stone_recieve){tradebank->temp_stone_recieve++; cout << "+1 Temp Stone Recieve" << endl;} break;
			case SDLK_f:	if (g->p[tradebank->playerNumber].sheep > 0 + tradebank->temp_sheep_recieve){tradebank->temp_sheep_recieve++; cout << "+1 Temp Sheep Recieve" << endl;} break;
			case SDLK_g:	if (g->p[tradebank->playerNumber].wheat > 0 + tradebank->temp_wheat_recieve){tradebank->temp_wheat_recieve++; cout << "+1 Temp Wheat Recieve" << endl;} break;

			case SDLK_RETURN: 
				if(tradebank->setGiveResources(g) && tradebank->setRecieveResources(g))
				{
					if(tradebank->trade(g))
						cout << "Trade with Player Successful!!" << endl;
					else
						cout << "IT DIDNT WORK!" << endl;
				}
				break;
			case SDLK_BACKSPACE:
				tradebank->ResetBank();
				break;
			}
	}
}

void map::handleInput_TRADEBANKHARBORSCREEN(SDL_Event e, Game * g)
{
	switch(e.type)
	{
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym)
			{
			case SDLK_0:	mapState= map::MAP;				break;
			case SDLK_1:	mapState= map::MAP;				break;
			case SDLK_2:	mapState= map::BUILDCARD;		break;
			case SDLK_3:	mapState= map::RESOURCELIST;	break;
			case SDLK_4:	mapState= map::DEVHAND;			break;

			case SDLK_q:	
				if(tradebank->harbor_type == BANK || tradebank->harbor_type == BRICK || tradebank->harbor_type == THREE_TO_ONE)
				{
					if(g->p[g->activePlayer].brick > 0 + tradebank->temp_brick_give)
					{
						tradebank->temp_brick_give++; 
						cout << "+1 Temp Brick Give" << endl;
					} 
				}
				break;
			case SDLK_w:	
				if(tradebank->harbor_type == BANK || tradebank->harbor_type == WOOD || tradebank->harbor_type == THREE_TO_ONE)
				{
					if(g->p[g->activePlayer].wood > 0 + tradebank->temp_wood_give)
					{
						tradebank->temp_wood_give++; 
						cout << "+1 Temp Wood Give" << endl;
					} 
				}
				break;
			case SDLK_e:
				if(tradebank->harbor_type == BANK || tradebank->harbor_type == STONE || tradebank->harbor_type == THREE_TO_ONE)
				{
					if(g->p[g->activePlayer].stone > 0 + tradebank->temp_stone_give)
					{
						tradebank->temp_stone_give++;
						cout << "+1 Temp Stone Give" << endl;
					}
				}
				break;
			case SDLK_r:	
				if(tradebank->harbor_type == BANK || tradebank->harbor_type == SHEEP || tradebank->harbor_type == THREE_TO_ONE)
				{
					if(g->p[g->activePlayer].sheep > 0 + tradebank->temp_sheep_give)
					{
						tradebank->temp_sheep_give++; cout << "+1 Temp Sheep Give" << endl;
					} 
				}
				break;
			case SDLK_t:
				if(tradebank->harbor_type == BANK || tradebank->harbor_type == WHEAT || tradebank->harbor_type == THREE_TO_ONE)
				{
					if(g->p[g->activePlayer].wheat > 0 + tradebank->temp_wheat_give)
					{
						tradebank->temp_wheat_give++; cout << "+1 Temp Wheat Give" << endl;
					}
				}
				break;

			case SDLK_a:	tradebank->temp_brick_recieve++; cout << "+1 Temp Brick Recieve" << endl; break;
			case SDLK_s:	tradebank->temp_wood_recieve++; cout << "+1 Temp Wood Receive" << endl; break;
			case SDLK_d:	tradebank->temp_stone_recieve++; cout << "+1 Temp Stone Recieve" << endl; break;
			case SDLK_f:	tradebank->temp_sheep_recieve++; cout << "+1 Temp Sheep Recieve" << endl; break;
			case SDLK_g:	tradebank->temp_wheat_recieve++; cout << "+1 Temp Wheat Recieve" << endl; break;
			case SDLK_BACKSPACE: 
				tradebank->ResetBank();
				break;
			case SDLK_RETURN:
				//trading with the bank or harbor
				//player sets the resource they are going to give to something other than 0
				//and sets the number of the amount to recieve to the number they want
				char tgive = ' ';
				char trecieve = ' ';
				int numget = 0;

				if(tradebank->temp_wood_give != 0)
					tgive = WOOD;
				else if(tradebank->temp_wheat_give != 0)
					tgive = WHEAT;
				else if(tradebank->temp_stone_give != 0)
					tgive = STONE;
				else if(tradebank->temp_sheep_give !=0)
					tgive = SHEEP;
				else if(tradebank->temp_brick_give != 0)
					tgive = BRICK;

				if(tradebank->temp_wood_recieve != 0)
				{
					trecieve = WOOD;
					numget = tradebank->temp_wood_recieve;
				}					
				else if(tradebank->temp_wheat_recieve != 0)
				{
					trecieve = WHEAT;
					numget = tradebank->temp_wheat_recieve;
				}
				else if(tradebank->temp_stone_recieve != 0)
				{
					trecieve = STONE;
					numget = tradebank->temp_stone_recieve;
				}
				else if(tradebank->temp_sheep_recieve != 0)
				{
					trecieve = SHEEP;
					numget = tradebank->temp_sheep_recieve;
				}
				else if(tradebank->temp_brick_recieve != 0)
				{
					trecieve = BRICK;
					numget = tradebank->temp_brick_recieve;
				}

				if(tradebank->tradeWithBank(g, trecieve, tgive, numget))
					cout << "Trade with Bank/Harbor Successful!" << endl;
				else
					cout << "Trade with Bank/Harbor Failed!" << endl;

				tradebank->ResetBank();

				break;
			}
	}
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

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
					if (calculateVictoryPoints(g))
					{
						mapState = map::SOMEONEWON;
					}
					else
					{
						mapState = map::MAP;
					}
				}	
				break;
			}
			break;

		case SDL_KEYDOWN:
			switch(e.key.keysym.sym)
			{
				case SDLK_0:	mapState= map::MAP;				break;
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
					if (calculateVictoryPoints(g))
					{
						mapState = map::SOMEONEWON;
					}
					else
					{
						mapState = map::MAP;
					}
				}	
				break;
			}
			break;
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym)
			{
				case SDLK_0:	mapState= map::MAP;				break;
			}
			break;
	}
}

void map::handleInput_BUILDCITY(SDL_Event e, Game * g)
{
	switch(e.type)
	{
		case SDL_MOUSEMOTION:	whichNodeIsWithin(e.motion.x, e.motion.y, 100); break;

		case SDL_MOUSEBUTTONDOWN:
			switch(e.button.button)
			{
			case SDL_BUTTON_LEFT:	
				if(constructCityOnMap(g) == true)
				{ 
					g->p[g->activePlayer].actuallyBuildSomething('C', &rsc, &dvc);
					if (calculateVictoryPoints(g))
					{
						mapState = map::SOMEONEWON;
					}
					else
					{
						mapState = map::MAP;
					}
				}	
				break;
			}
			break;

		case SDL_KEYDOWN:
			switch(e.key.keysym.sym)
			{
				case SDLK_0:	mapState= map::MAP;				break;
			}
			break;
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
				case SDL_BUTTON_LEFT:	
					if(constructSettlementOnMapAnywhere(g) == true)
					{ 
						g->p[g->activePlayer].freeBuildSomething('S', &rsc, &dvc);
						mapState = map::TURNONEROAD;
					}	
					break;
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
			case SDL_BUTTON_LEFT:	
				if (constructRoadOnMap(g) == true)
				{ 
					g->p[g->activePlayer].freeBuildSomething('R', &rsc, &dvc);
					mapState = map::ENDTURN;
				} 
				break;
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
				case SDL_BUTTON_LEFT:	
					if(constructSettlementOnMapAnywhere(g) == true)
					{ 
						g->p[g->activePlayer].freeBuildSomething('S', &rsc, &dvc);
						mapState = map::TURNTWOROAD;
					}	
					break;
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
				case SDL_BUTTON_LEFT:	
					if (constructRoadOnMap(g) == true)
					{ 
						g->p[g->activePlayer].freeBuildSomething('R', &rsc, &dvc);
						if (calculateVictoryPoints(g)){}
						mapState = map::ENDTURN;
					} 
					break;
			}
			break;
	}
}

void map::handleInput_FREETWOROADS(SDL_Event e, Game * g)
{
	switch(e.type)
	{
		case SDL_MOUSEMOTION:	whichRoadIsWithin(e.motion.x, e.motion.y, 100); break;
		case SDL_MOUSEBUTTONDOWN:
			switch(e.button.button)
			{
				case SDL_BUTTON_LEFT:	
					if (constructRoadOnMap(g) == true)
					{ 
						g->p[g->activePlayer].freeBuildSomething('R', &rsc, &dvc);
						placeholderFREE--;
						if (calculateVictoryPoints(g))
						{
							mapState= map::SOMEONEWON;
						}
						else {}
					} 
					break;
			}
			break;
	}
	if (placeholderFREE == 0)
	{
		mapState = map::MAP;
	}
}

void map::handleInput_FREETWORESOURCES(SDL_Event e, Game * g)
{
	switch(e.type)
	{
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym)
			{
			case SDLK_b:	g->p[g->activePlayer].drawResource(&rsc, BRICK, 1);	placeholderFREE--;			break;		
			case SDLK_l:	g->p[g->activePlayer].drawResource(&rsc, WOOD, 1);	placeholderFREE--;			break;	
			case SDLK_s:	g->p[g->activePlayer].drawResource(&rsc, STONE, 1); placeholderFREE--;			break;	
			case SDLK_e:	g->p[g->activePlayer].drawResource(&rsc, SHEEP, 1);	placeholderFREE--;			break;	
			case SDLK_w:	g->p[g->activePlayer].drawResource(&rsc, WHEAT, 1);	placeholderFREE--;			break;	
			}
		break;
	}
	if (placeholderFREE == 0)
	{
		mapState = map::MAP;
	}
}

void map::handleInput_PICKMONOPOLY(SDL_Event e, Game * g)
{
	switch(e.type)
	{
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym)
			{
			case SDLK_b:	playMonopolyCard(BRICK, g);	mapState = map::MAP;	break;
			case SDLK_l:	playMonopolyCard(WOOD, g);	mapState = map::MAP;	break;
			case SDLK_s:	playMonopolyCard(STONE, g);	mapState = map::MAP;	break;
			case SDLK_e:	playMonopolyCard(SHEEP, g);	mapState = map::MAP;	break;
			case SDLK_w:	playMonopolyCard(WHEAT, g);	mapState = map::MAP;	break;	
			}
		break;
	}
}

void map::handleInput_SETTHETHIEF(SDL_Event e, Game * g)
{
	switch(e.type)
	{
		case SDL_MOUSEMOTION:	whichCenterIsWithin(e.motion.x, e.motion.y, 100); break;
		case SDL_MOUSEBUTTONDOWN:
			switch(e.button.button)
			{
				case SDL_BUTTON_LEFT:	
					if (constructThiefOnMap(g) == true)
					{ 
						thiefIsRolled(g);
						mapState = map::MAP;
					} 
					break;
			}
			break;
	}
}
