#include "tradebank.h"
#include "game.h"

TradeBank::TradeBank()
{
	wood_give = 0;
	wheat_give = 0;
	stone_give = 0;
	sheep_give = 0;
	brick_give = 0;

	wood_recieve = 0;
	wheat_recieve = 0;
	stone_recieve = 0;
	sheep_recieve = 0;
	brick_recieve = 0;

	active_set = false;
	trader_set = false;

	temp_wood_give = 0;
	temp_wheat_give = 0;
	temp_stone_give = 0;
	temp_sheep_give = 0;
	temp_brick_give = 0;
	
	temp_wood_recieve = 0;
	temp_wheat_recieve = 0;
	temp_stone_recieve = 0;
	temp_sheep_recieve = 0;
	temp_brick_recieve = 0;

	playerNumber = 0;
	harbor_type = ' ';
}

bool TradeBank::setGiveResources(Game* g)
{
	if(g->activePlayer != playerNumber)
	{
		if(g->p[g->activePlayer].getResource(WOOD) >= temp_wood_give)
			wood_give = temp_wood_give;
		else
			return false;
		
		if(g->p[g->activePlayer].getResource(WHEAT) >= temp_wheat_give)
			wheat_give = temp_wheat_give;
		else
			return false;
		
		if(g->p[g->activePlayer].getResource(STONE) >= temp_stone_give)
			stone_give = temp_stone_give;
		else
			return false;

		if(g->p[g->activePlayer].getResource(SHEEP) >= temp_sheep_give)
			sheep_give = temp_sheep_give;
		else
			return false;

		if(g->p[g->activePlayer].getResource(BRICK) >= temp_brick_give)
			brick_give = temp_brick_give;
		else
			return false;
			
		active_set = true;
		return true;
	}
	return false;
}

bool TradeBank::setRecieveResources(Game* g)
{
	if(g->activePlayer != playerNumber)
	{
		if(g->p[playerNumber].getResource(WOOD) >= temp_wood_recieve)
			wood_recieve = temp_wood_recieve;
		else
			return false;
	
		if(g->p[playerNumber].getResource(WHEAT) >= temp_wheat_recieve)
			wheat_recieve = temp_wheat_recieve;
		else
			return false;
		
		if(g->p[playerNumber].getResource(STONE) >= temp_stone_recieve)
			stone_recieve = temp_stone_recieve;
		else
			return false;

		if(g->p[playerNumber].getResource(SHEEP) >= temp_sheep_recieve)
			sheep_recieve = temp_sheep_recieve;
		else
			return false;

		if(g->p[playerNumber].getResource(BRICK) >= temp_brick_recieve)
			brick_recieve = temp_brick_recieve;
		else
			return false;
		trader_set = true;
		return true;
	}
	return false;
}

bool TradeBank::trade(Game* g)
{
	if(active_set && trader_set && g->activePlayer != playerNumber)
	{
		//taking away the resources that the g->p[g->activePlayer]   (active)   player is trading
		g->p[g->activePlayer].changeResource(WOOD, -wood_give);
		g->p[g->activePlayer].changeResource(WHEAT, -wheat_give);
		g->p[g->activePlayer].changeResource(STONE, -stone_give);
		g->p[g->activePlayer].changeResource(SHEEP, -sheep_give);
		g->p[g->activePlayer].changeResource(BRICK, -brick_give);

		//adding the resources that the g->p[g->activePlayer]    (active)    player wants
		g->p[g->activePlayer].changeResource(WOOD, wood_recieve);
		g->p[g->activePlayer].changeResource(WHEAT, wheat_recieve);
		g->p[g->activePlayer].changeResource(STONE, stone_recieve);
		g->p[g->activePlayer].changeResource(SHEEP, sheep_recieve);
		g->p[g->activePlayer].changeResource(BRICK, brick_recieve);

		//adding the resources to the g->p[playerNumber] (trader)that the active player gave
		g->p[playerNumber].changeResource(WOOD, wood_give);
		g->p[playerNumber].changeResource(WHEAT, wheat_give);
		g->p[playerNumber].changeResource(STONE, stone_give);
		g->p[playerNumber].changeResource(SHEEP, sheep_give);
		g->p[playerNumber].changeResource(BRICK, brick_give);

		//taking away the resources that the g->p[playerNumber](trader) is giving to the active player
		g->p[playerNumber].changeResource(WOOD, -wood_recieve);
		g->p[playerNumber].changeResource(WHEAT, -wheat_recieve);
		g->p[playerNumber].changeResource(STONE, -stone_recieve);
		g->p[playerNumber].changeResource(SHEEP, -sheep_recieve);
		g->p[playerNumber].changeResource(BRICK, -brick_recieve);

		ResetBank();

		return true;
	}
	return false;
}

bool TradeBank::tradeWithBank(Game* g, char choice_recieve, char choice_give, int num_recieve)
{
	switch(harbor_type)
	{
	case WOOD:
		if(g->p[g->activePlayer].getResource(WOOD) >= 2 * num_recieve)
		{
			g->p[g->activePlayer].drawResource(&g->underlyingBoard->rsc, choice_recieve, num_recieve);
			g->p[g->activePlayer].changeResource(WOOD, -2 * num_recieve);
			g->underlyingBoard->rsc.returnToResourcePool(WOOD, 2 * num_recieve);
			return true;
		}
		break;
	case WHEAT:
		if(g->p[g->activePlayer].getResource(WHEAT) >= 2 * num_recieve)
		{
			g->p[g->activePlayer].drawResource(&g->underlyingBoard->rsc, choice_recieve, num_recieve);
			g->p[g->activePlayer].changeResource(WHEAT, -2 * num_recieve);
			g->underlyingBoard->rsc.returnToResourcePool(WHEAT, 2 * num_recieve);
			return true;
		}
		break;
	case STONE:
		if(g->p[g->activePlayer].getResource(STONE) >= 2 * num_recieve)
		{
			g->p[g->activePlayer].drawResource(&g->underlyingBoard->rsc, choice_recieve, num_recieve);
			g->p[g->activePlayer].changeResource(STONE, -2 * num_recieve);
			g->underlyingBoard->rsc.returnToResourcePool(STONE, 2 * num_recieve);
			return true;
		}
		break;
	case BRICK:
		if(g->p[g->activePlayer].getResource(BRICK) >= 2 * num_recieve)
		{
			g->p[g->activePlayer].drawResource(&g->underlyingBoard->rsc, choice_recieve, num_recieve);
			g->p[g->activePlayer].changeResource(BRICK, -2 * num_recieve);
			g->underlyingBoard->rsc.returnToResourcePool(BRICK, 2 * num_recieve);
			return true;
		}
		break;
	case SHEEP:
		if(g->p[g->activePlayer].getResource(SHEEP) >= 2 * num_recieve)
		{
			g->p[g->activePlayer].drawResource(&g->underlyingBoard->rsc, choice_recieve, num_recieve);
			g->p[g->activePlayer].changeResource(SHEEP, -2 * num_recieve);
			g->underlyingBoard->rsc.returnToResourcePool(SHEEP, 2 * num_recieve);
			return true;
		}
		break;
	case THREE_TO_ONE:
		if(g->p[g->activePlayer].getResource(choice_give) >= 3 * num_recieve)
		{
			g->p[g->activePlayer].drawResource(&g->underlyingBoard->rsc, choice_recieve, num_recieve);
			g->p[g->activePlayer].changeResource(choice_give, -3 * num_recieve);
			g->underlyingBoard->rsc.returnToResourcePool(choice_give, 3 * num_recieve);
			return true;
		}
	case BANK:
		if(g->p[g->activePlayer].getResource(choice_give) >= 4 * num_recieve)
		{
			g->p[g->activePlayer].drawResource(&g->underlyingBoard->rsc, choice_recieve, num_recieve);
			g->p[g->activePlayer].changeResource(choice_give, -4 * num_recieve);
			g->underlyingBoard->rsc.returnToResourcePool(choice_give, 4 * num_recieve);
			return true;
		}
	default:
		break;
	};
	return false;
}

void TradeBank::ResetBank()
{
	//resetting everything so its ready for the next trade
	wood_give = 0;
	wheat_give = 0;
	stone_give = 0;
	sheep_give = 0;
	brick_give = 0;

	wood_recieve = 0;
	wheat_recieve = 0;
	stone_recieve = 0;
	sheep_recieve = 0;
	brick_recieve = 0;

	temp_wood_give = 0;
	temp_wheat_give = 0;
	temp_stone_give = 0;
	temp_sheep_give = 0;
	temp_brick_give = 0;

	temp_wood_recieve = 0;
	temp_wheat_recieve = 0;
	temp_stone_recieve = 0;
	temp_sheep_recieve = 0;
	temp_brick_recieve = 0;

	active_set = false;
	trader_set = false;

	cout << "Trade Bank Reset!" << endl;
}