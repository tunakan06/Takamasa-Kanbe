#include "animdraw.h"

int AnimDraw::setImage(int apid, int ghandle){
	if (apid >= aplist.size()) {
		aplist.push_back(animpat());	//新しいアニメパターンの追加
		//apidが追加したアニメパターンを指すように調整
		apid = aplist.size() - 1;
	}
	aplist.at(apid).ghlist.push_back(ghandle);
	return (apid);
}

int AnimDraw::setGap(int apid,int gap){
	if (apid >= aplist.size()) {
		aplist.push_back( animpat() );
		apid = aplist.size() - 1;
	}
	aplist.at(apid).anigap = gap;
	return(apid);
}

void AnimDraw::draw(int apid, int x, int y) {
	if (aplist.at(apid).ghlist.size() > 1) {
		int curpat = GameFrame::getAnimCnt()
			/ aplist.at(apid).anigap % aplist.at(apid).ghlist.size();
		DrawGraph(x, y, aplist.at(apid).ghlist.at(curpat), true);
	}
	else {
		DrawGraph(x, y, aplist.at(apid).ghlist.at(0), true);
	}
}

void AnimDraw::draw(int apid, int x, int y, float rad) {
	if (aplist.at(apid).ghlist.size() > 1) {
		int curpat = GameFrame::getAnimCnt()
			/ aplist.at(apid).anigap % aplist.at(apid).ghlist.size();
		DrawRotaGraph(x, y, 1.0, rad, aplist.at(apid).ghlist.at(curpat), TRUE, FALSE);
	}
	else {
		DrawRotaGraph(x, y, 1.0, rad, aplist.at(apid).ghlist.at(0), TRUE, FALSE);
	}
}

vector<int> SoundBox::sounds;
int SoundBox::bgm = -1;

int SoundBox::set(int shandle) {
	sounds.push_back(shandle);
	return(sounds.size()-1);
}

void SoundBox::play(int snum) {
	PlaySoundMem(sounds.at(snum), DX_PLAYTYPE_BACK);
}

void SoundBox::stop(int snum) {
	StopSoundMem(sounds.at(snum));
}

void SoundBox::playbgm(int snum) {
	int newbgm = sounds.at(snum);
	if (bgm == newbgm) return;
	StopSoundMem(bgm);
	bgm = newbgm;
	PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);
}