#include "gameframe.h"
#include "animdraw.h"
#include "jiki.h"
#include "teki.h"

class ShootGame : public GameFrame {
	JikiControl jikicnt;
	TekiControl tekicnt;
	void loadFiles() throw(int);
	void initStage();
	void drawGameMain();
};

void ShootGame::loadFiles() throw(int) {
	jikicnt.loadFiles();
	tekicnt.loadFiles();
}

void ShootGame::initStage() {
	jikicnt.init();
	tekicnt.init();
}

void ShootGame::drawGameMain() {
	jikicnt.move();
	tekicnt.move();
}

int WINAPI WinMain(HINSTANCE hI, HINSTANCE hp, LPSTR lpC, int nC) {
	ShootGame* sg = new ShootGame();
	sg->doMainLoop(TRUE);
	delete sg;
}