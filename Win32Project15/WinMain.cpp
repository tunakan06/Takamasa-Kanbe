#include "Game.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {


	GameFrame* game = new Game();

	//ゲームのメイン処理
	game->Main( );

	delete game;
	return	0;
}