#include "jiki.h"

void JikiControl::loadFiles() throw(int) {
	int gh[6];
	if (LoadDivGraph("jiki01.png", 6, 3, 2, 64, 64, gh) == -1)
		throw(-1);
	for(int i=0; i<6 ; ++i ){
		jikianim.setImage(0, gh[i]);
	}
	jikianim.setGap(0, 6);
	gh[0] = LoadGraph("tama.png");
	if (gh[0] == -1) throw(-1);
	tamaanim.setImage(0, gh[0]);
}

void JikiControl::init() {
	jikilist.clear();	//自キャラのリストを空にする
	CharaData jiki;
	jiki.x = 0; jiki.y = 200; jiki.anim = &jikianim;
	jiki.life = 1;
	jiki.image_w = 64; jiki.image_h = 64;
	jiki.bounds_w = 20; jiki.image_h = 20;
	jiki.amode = A_NORMAL;
	jikilist.push_back(jiki);	//自キャラデータをlistに追加
	trigger = 0;
}

void JikiControl::move() {
	list<CharaData>::iterator it;
	it = jikilist.begin();
	//自キャラ移動
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	float df = GameFrame::IdouHosei(4);
	if (key & PAD_INPUT_UP)	(*it).y = (*it).y - df;
	if (key & PAD_INPUT_DOWN)	(*it).y = (*it).y + df;
	if (key & PAD_INPUT_LEFT)	(*it).x = (*it).x - df;
	if (key & PAD_INPUT_RIGHT)	(*it).x = (*it).x + df;
	if ((*it).x<0)	(*it).x = 0;
	if ((*it).x>608)	(*it).x = 608;
	if ((*it).y<0)	(*it).y = 0;
	if ((*it).y>448)	(*it).y = 448;
	(*it).anim->draw(0, (*it).x, (*it).y);
	//自機弾の発射
	if (key & PAD_INPUT_A && (trigger == 0)) {
		CharaData newtama;
		newtama.x = (*it).x + 24; newtama.y = (*it).y + 8;
		newtama.anim = &tamaanim;
		newtama.life = 1;
		newtama.image_w = 48; newtama.image_h = 16;
		newtama.bounds_w = 24; newtama.bounds_h = 8;
		newtama.amode = A_NORMAL;
		tamalist.push_back(newtama);	//弾データセット
		trigger = 20;
	}
	if (trigger > 0) trigger = trigger - 1;
	//弾の移動と表示
	it = tamalist.begin();
	while (it != tamalist.end()) {
		if ((*it).x < 640 && (*it).life>0) {
			(*it).x = (*it).x + GameFrame::IdouHosei(10);//直進
			(*it).anim->draw(0, (*it).x, (*it).y);
			++it;
		}
		else {
			it = tamalist.erase(it);	//画面外に出たorライフ0なら消滅
		}
	}
}