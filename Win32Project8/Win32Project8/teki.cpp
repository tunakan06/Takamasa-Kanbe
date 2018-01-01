#include "teki.h"

void TekiControl::loadFiles() throw(int) {
	int scgh = LoadGraph("enemy1.png");
	if (scgh == -1) throw(-2);
	int gh = DerivationGraph(0,0,30,40,scgh);
	tekianim.setImage(0, gh);
	gh = DerivationGraph(0,40,30,30,scgh);
	tekianim.setImage(1, gh);
	gh = DerivationGraph(30, 40, 30, 30, scgh);
	tekianim.setImage(0, gh);
	gh = DerivationGraph(60, 40, 30, 30, scgh);
	tekianim.setImage(0, gh);
	gh = DerivationGraph(90, 40, 30, 30, scgh);
	tamaanim.setImage(0, gh);
	tamaanim.setGap(0,8);
}

void TekiControl::init() {
	tekilist.clear();
	CharaData teki;
	teki.x = 400; teki.y = 156; teki.anim = &tekianim;
	teki.life = 15;
	teki.image_w = 40; teki.image_h = 30;
	teki.bounds_w = 30; teki.bounds_h = 20;
	teki.amode = A_HARD;
	tekilist.push_back(teki);
	tamalist.clear();
}

void TekiControl::move() {
	list<CharaData>::iterator it;
	it = tekilist.begin();
	(*it).anim->draw(0, (*it).x, (*it).y);
}