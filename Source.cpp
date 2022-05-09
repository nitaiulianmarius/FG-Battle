#include<iostream>
#include "Game.h"

using namespace std;

int main()
{
	Game *game;
	game = new Game;
	
	game->init(720, 520);
	game->globalTime = GetTickCount();

	while (game->window->isOpen())
	{
		game->handleEvent();
		game->update();
		game->render();
	}
	
	return 0;
}