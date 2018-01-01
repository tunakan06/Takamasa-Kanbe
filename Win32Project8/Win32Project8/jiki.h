#ifndef _JIKICONTROL_H
#define _JIKICONTROL_H
#include "animdraw.h"
#include "charadata.h"
#include <list>
using namespace std;

class JikiControl {
	list<CharaData> jikilist;
	list<CharaData> tamalist;
	AnimDraw jikianim;
	AnimDraw tamaanim;
	int trigger;
public:
	void loadFiles() throw(int);
	void init();
	void move();
};


#endif
