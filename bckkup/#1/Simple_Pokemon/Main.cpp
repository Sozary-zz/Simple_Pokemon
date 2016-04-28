#include "Game.h"
#include <iostream>

int main()
{
	Game game("data/maps.ini", 1);
	game.run();

	return 0;
}