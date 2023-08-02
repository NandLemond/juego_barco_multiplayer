#include "Game.h"

//using namespace sf;

int main()
{
	
	srand(static_cast<unsigned>(time(0)));

	
	Game game;

	
	while (game.running())
	{
		
		game.update();
		game.render();
	}

	
	return 0;
}
