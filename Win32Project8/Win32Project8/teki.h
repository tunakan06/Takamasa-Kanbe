#ifndef _TEKICONTROL_H
#define _TEKICONTROL_H
#include "animdraw.h"
#include "charadata.h"
#include <list>
using namespace std;

class TekiControl {
	list<CharaData> tekilist;
	list<CharaData> tamalist;
	AnimDraw tekianim;
	AnimDraw tamaanim;
public:
	void loadFiles() throw(int);
	void init();
	void move();
};
#endif
