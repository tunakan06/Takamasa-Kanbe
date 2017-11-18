//
//このクラスは、ゲームのジャンルごとの処理を行うものです。
//（例：アクションゲーム、ロールプレイングゲーム、ＦＰＳ（ＴＰＳ）等）
//シナリオパートなどとブレンドして作る場合もあります。
//

#ifndef _GAME_H
#define _GAME_H


#include "GameFrame.h"


class Game : public GameFrame {

public:

	Game();

	~Game();
};

#endif
