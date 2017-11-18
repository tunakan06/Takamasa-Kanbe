#include "Game.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {


	GameFrame* game = new Game();

	//ƒQ[ƒ€‚ÌƒƒCƒ“ˆ—
	game->Main( );

	delete game;
	return	0;
}