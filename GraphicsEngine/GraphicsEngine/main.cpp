#include "Game.h"

int main()
{
	Game* game = new Game();
	if (game->Startup() == 1)
	{
		while (game->Update() == true)
		{
			game->Draw();
		}

		game->Shutdown();
	}
	
	delete game;
	return 0;
}
