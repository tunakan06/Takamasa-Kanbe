#include "Player.h"

#include "Monster.h"

#define PLAYER_MOVE_SPEED			30.0f*3.0f*3.0f		// 移動速度
#define PLAYER_MAX_HITCOLL			2048		// 処理するコリジョンポリゴンの最大数
#define PLAYER_ENUM_DEFAULT_SIZE		800.0f		// 周囲のポリゴン検出に使用する球の初期サイズ
#define PLAYER_HIT_WIDTH			200.0f		// 当たり判定カプセルの半径
#define PLAYER_HIT_HEIGHT			700.0f		// 当たり判定カプセルの高さ
#define PLAYER_HIT_TRYNUM			16		// 壁押し出し処理の最大試行回数
#define PLAYER_HIT_SLIDE_LENGTH			5.0f		// 一度の壁押し出し処理でスライドさせる距離

Player::Player(){

	//走行フラグ。最初は偽
	running = false;

	//アクションフラグ。最初は偽
	action = false;

	playtime = 0.0f;

	//テキストパラメータ生成
	mTextParam = new TextParam();

	//サウンド生成
	mSound = new Sound();

	//武器生成
	//mWeapon = new Weapon();

	//アニメーション生成
	mAnimation = new Animation();

	//プレイヤーデータロード
	playerInfo.data = MV1LoadModel("Data\\Character\\Player\\PC.mv1");

	//ニュートラルアニメーションロード
	anim_nutral = MV1LoadModel("Data\\Character\\Player\\Anim_Neutral.mv1");

	//走行アニメーション
	anim_run = MV1LoadModel("Data\\Character\\Player\\Anim_Run.mv1");
	
	//if(MV1SetScale(playerInfo.data, VGet( 10,10, 10)) == -1) printfDx("モデルの読み込みに失敗");

	//攻撃アニメーション1
	anim_attack_1 = MV1LoadModel("Data\\Character\\Player\\Anim_Attack1.mv1");

	//攻撃アニメーション2
	anim_attack_2 = MV1LoadModel("Data\\Character\\Player\\Anim_Attack2.mv1");

	//攻撃アニメーション3
	anim_attack_3 = MV1LoadModel("Data\\Character\\Player\\Anim_Attack3.mv1");

	//ブロウアニメーション
	anim_blow_in = MV1LoadModel("Data\\Character\\Player\\Anim_Blow_In.mv1");

	//アタッチ（取り付け）
	attachidx = MV1AttachAnim(playerInfo.data, 0, anim_nutral);

	//アニメーション合計時間
	anim_totaltime = MV1GetAttachAnimTotalTime(playerInfo.data, attachidx);

	//
	rootflm = MV1SearchFrame(playerInfo.data, "root");

	//
	MV1SetFrameUserLocalMatrix(playerInfo.data, rootflm, MGetIdent());

	weapondata = MV1LoadModel("Data\\Character\\Player\\Sabel.mv1");

	sayadata = MV1LoadModel("Data\\Character\\Player\\Saya.mv1");

	righthandframeNo = MV1SearchFrame(playerInfo.data, "wp");

	actionnumber = NO_ATTACK;

	playerInfo.Angle = 0.0f;

	playerInfo.TargetMoveDirection = VGet( 1.0f, 0.0f, 0.0f );

	countAnim = 0;

	monsterKill = false;

}

Player::~Player(){

	delete& playerInfo.data;
	playerInfo.data = 0;

	delete& anim_nutral;
	anim_nutral = 0;

	delete& anim_run;
	anim_run = 0;

}

//キャラクター出力
void	Player::Draw( float arg, float camX, float camZ, int stg) {

	if (countAnim > 3 * 60) {
		countAnim = 0;
	}

	//アニメーション進行
	playtime += 0.5f;
	if (playtime > anim_totaltime) playtime = 0.0f;
	MV1SetAttachAnimTime(playerInfo.data, attachidx, playtime);

	//キー操作
	key = GetJoypadInputState(DX_INPUT_KEY);


	//アニメーション毎の変数遷移
	if (key & PAD_INPUT_A) { actionnumber = ATTACK_1; }
	if (key & PAD_INPUT_B) { actionnumber = BLOW; }

	//アニメーション	
	if (key == 0) {
		if (running == true) {
			moveAnimation(false, anim_nutral);
		}
		else if (action == true) {
			actionAnimation(false, anim_nutral);
		}
	}
	else {
		if (((key & PAD_INPUT_DOWN) || (key & PAD_INPUT_UP) || (key & PAD_INPUT_LEFT) || (key & PAD_INPUT_RIGHT)) && (running == false)) {
			moveAnimation(true, anim_run);
		}
		else if (((key & PAD_INPUT_A) || (key & PAD_INPUT_B)) && (action == false)) {
			actionAnimation(true, anim_attack_1);
			if ( VSize( VSub(pos,Monster().pos)) < 30.0f ) {
				// 敵を消す
				kill();

			}
			actionnumber = ATTACK_1;
			countAnim++;
			//WaitTimer(120);
			if ((key & PAD_INPUT_A)&&(actionnumber == ATTACK_1) && (action == true)) {
			actionAnimation(true, anim_attack_2);
			actionnumber = ATTACK_2;
			countAnim++;
			//WaitTimer(120);
				if ((key & PAD_INPUT_A) && (actionnumber == ATTACK_2) && (action == true)) {
					actionAnimation(true, anim_attack_3);
					actionnumber = ATTACK_3;
					countAnim++;
					//WaitTimer(120);
				}
			}
			if (countAnim > 60*2*5*100 ) {
				actionnumber = NO_ATTACK;
			}
		}
	}
	//方向毎の変数遷移
	directFunction(arg, camX, camZ, stg);

	//ClearDrawScreen();
	
	//キャラクター回転行列演算
	MV1SetRotationXYZ(playerInfo.data, VGet(0.f, playerInfo.Angle + DX_PI_F, 0.f));
	// 画面に映る位置に３Ｄモデルを移動
	MV1SetPosition(playerInfo.data, pos);
	//mat1 = MGetRotY( playerInfo.Angle + DX_PI_F );
	//mat2 = MGetTranslate(pos);
	//MV1SetMatrix(playerInfo.data, MMult(mat1, mat2));

	//キャラクター出力
	MV1DrawModel(playerInfo.data);

	//武器設定
	wd = weapondata;

	//キャラクターモデルの右手フレームの行列を取得
	righthandmatrix = MV1GetFrameLocalWorldMatrix(playerInfo.data, righthandframeNo);
	// キャラクターモデルの右手フレームの行列をアクセサリモデルの行列としてセットしてから描画
	MV1SetMatrix(wd, righthandmatrix);
	//武器３Ｄモデルを描画
	MV1DrawModel(wd);


}

//移動アニメーション処理関数
void	Player::moveAnimation(bool flg, int anim_state) {

	running = flg;
	if (attachidx >= 0) {
		MV1DetachAnim(playerInfo.data, attachidx);
	}
	attachidx = MV1AttachAnim(playerInfo.data, 0, anim_state);
	anim_totaltime = MV1GetAttachAnimTotalTime(playerInfo.data, attachidx);

}

//行動アニメーション処理関数
void	Player::actionAnimation(bool act, int anim_state) {

	action = act;
	if ( attachidx >= 0 ) {
		MV1DetachAnim(playerInfo.data, attachidx);
	}
	attachidx = MV1AttachAnim(playerInfo.data, 0, anim_state);
	anim_totaltime = MV1GetAttachAnimTotalTime(playerInfo.data, attachidx);
}

//キャラクターポジションx座標を返す関数
float	Player::charaPositionX() {

	return pos.x;

}

//キャラクターポジションz座標を返す関数
float	Player::charaPositionZ() {

	return pos.z;

}

//方向毎の変数遷移の関数
void	Player::directFunction(float movedir, float camX, float camZ, int stg) {

	VECTOR CamVec = VGet(camX, 0, camZ);

	VECTOR UpMoveVec;
	VECTOR LeftMoveVec;
	VECTOR MoveVec;

	UpMoveVec = VSub( pos , CamVec );
	UpMoveVec.y = 0.0f;

	LeftMoveVec = VCross(UpMoveVec, VGet(0.0f, 1.0f, 0.0f));

	UpMoveVec = VNorm(UpMoveVec);
	LeftMoveVec = VNorm(LeftMoveVec);

	// このフレームでの移動ベクトルを初期化
	MoveVec = VGet(0.0f, 0.0f, 0.0f);

	if (key & PAD_INPUT_DOWN) {
		MoveVec = VAdd(MoveVec, VScale(UpMoveVec, -1.0f)); //direction = 0.0 + di;
		MVmem = MoveVec;
	}
	else 
	if (key & PAD_INPUT_UP) {
		MoveVec = VAdd(MoveVec, UpMoveVec); //direction = 2.0 + di;
		MVmem = MoveVec;
	}
	if (key & PAD_INPUT_LEFT) {
		MoveVec = VAdd(MoveVec, LeftMoveVec); //direction = 1.0 + di;
		MVmem = MoveVec;
	}
	else
	if (key & PAD_INPUT_RIGHT) {
		MoveVec = VAdd(MoveVec, VScale(LeftMoveVec, -1.0f)); //direction = -1.0 + di;
		MVmem = MoveVec;
	}

	playerInfo.TargetMoveDirection = VNorm(MVmem);

	// プレイヤーの向きを変える
	AngleProcess();

	// 移動ベクトルを元にコリジョンを考慮しつつプレイヤーを移動
	Move(MoveVec, stg);

	// プレイヤーが向くべき方向ベクトルをプレイヤーのスピード倍したものを移動ベクトルとする
	MoveVec = VScale(playerInfo.TargetMoveDirection, 6000.0f * PLAYER_MOVE_SPEED);

}

//方向ベクトル計算
VECTOR	Player::directVector() {

	return	VGet(pos.x, pos.y, pos.z);

}

//キャラクターとカメラの角度計算
float Player::ctArg(float camX, float camZ) {

	return (float)atan((pos.z - camZ) / (pos.x - camX));

}

// プレイヤーの向きを変える
void Player::AngleProcess(){
	float TargetAngle;			// 目標角度
	float SaAngle;				// 目標角度と現在の角度との差

								// 目標の方向ベクトルから角度値を算出する
	TargetAngle = atan2(playerInfo.TargetMoveDirection.x, playerInfo.TargetMoveDirection.z);

	// 目標の角度と現在の角度との差を割り出す
	{
		// 最初は単純に引き算
		SaAngle = TargetAngle - playerInfo.Angle;

		// ある方向からある方向の差が１８０度以上になることは無いので
		// 差の値が１８０度以上になっていたら修正する
		if (SaAngle < -DX_PI_F)
		{
			SaAngle += DX_TWO_PI_F;
		}
		else
			if (SaAngle > DX_PI_F)
			{
				SaAngle -= DX_TWO_PI_F;
			}
	}

	// 角度の差が０に近づける
	if (SaAngle > 0.0f)
	{
		// 差がプラスの場合は引く
		SaAngle -= 0.2f;
		if (SaAngle < 0.0f)
		{
			SaAngle = 0.0f;
		}
	}
	else
	{
		// 差がマイナスの場合は足す
		SaAngle += 0.2f;
		if (SaAngle > 0.0f)
		{
			SaAngle = 0.0f;
		}
	}

	// モデルの角度を更新
	playerInfo.Angle = TargetAngle - SaAngle;
}


// プレイヤーの移動処理
void Player::Move(VECTOR MoveVector, int stg) {

	int i, j, k;						// 汎用カウンタ変数
	int MoveFlag;						// 水平方向に移動したかどうかのフラグ( ０:移動していない  １:移動した )
	int HitFlag;						// ポリゴンに当たったかどうかを記憶しておくのに使う変数( ０:当たっていない  １:当たった )
	MV1_COLL_RESULT_POLY_DIM HitDim;			// プレイヤーの周囲にあるポリゴンを検出した結果が代入される当たり判定結果構造体
	int KabeNum;						// 壁ポリゴンと判断されたポリゴンの数
	int YukaNum;						// 床ポリゴンと判断されたポリゴンの数
	MV1_COLL_RESULT_POLY *Kabe[PLAYER_MAX_HITCOLL];	// 壁ポリゴンと判断されたポリゴンの構造体のアドレスを保存しておくためのポインタ配列
	MV1_COLL_RESULT_POLY *Yuka[PLAYER_MAX_HITCOLL];	// 床ポリゴンと判断されたポリゴンの構造体のアドレスを保存しておくためのポインタ配列
	MV1_COLL_RESULT_POLY *Poly;				// ポリゴンの構造体にアクセスするために使用するポインタ( 使わなくても済ませられますがプログラムが長くなるので・・・ )
	HITRESULT_LINE LineRes;				// 線分とポリゴンとの当たり判定の結果を代入する構造体
	VECTOR OldPos;						// 移動前の座標	
	VECTOR NowPos;						// 移動後の座標

										// 移動前の座標を保存
	OldPos = pos;

	// 移動後の座標を算出
	NowPos = VAdd(pos, MoveVector);

	// プレイヤーの周囲にあるステージポリゴンを取得する
	// ( 検出する範囲は移動距離も考慮する )
	HitDim = MV1CollCheck_Sphere(stg, -1, pos, PLAYER_ENUM_DEFAULT_SIZE + VSize(MoveVector));

	// x軸かy軸方向に 0.01f 以上移動した場合は「移動した」フラグを１にする
	if (fabs(MoveVector.x) > 0.01f || fabs(MoveVector.z) > 0.01f)
	{
		MoveFlag = 1;
	}
	else
	{
		MoveFlag = 0;
	}

	// 検出されたポリゴンが壁ポリゴン( ＸＺ平面に垂直なポリゴン )か床ポリゴン( ＸＺ平面に垂直ではないポリゴン )かを判断する
	{
		// 壁ポリゴンと床ポリゴンの数を初期化する
		KabeNum = 0;
		YukaNum = 0;

		// 検出されたポリゴンの数だけ繰り返し
		for (i = 0; i < HitDim.HitNum; i++)
		{
			// ＸＺ平面に垂直かどうかはポリゴンの法線のＹ成分が０に限りなく近いかどうかで判断する
			if (HitDim.Dim[i].Normal.y < 0.000001f && HitDim.Dim[i].Normal.y > -0.000001f)
			{
				// 壁ポリゴンと判断された場合でも、プレイヤーのＹ座標＋１．０ｆより高いポリゴンのみ当たり判定を行う
				if (HitDim.Dim[i].Position[0].y > pos.y + 1.0f ||
					HitDim.Dim[i].Position[1].y > pos.y + 1.0f ||
					HitDim.Dim[i].Position[2].y > pos.y + 1.0f)
				{
					// ポリゴンの数が列挙できる限界数に達していなかったらポリゴンを配列に追加
					if (KabeNum < PLAYER_MAX_HITCOLL)
					{
						// ポリゴンの構造体のアドレスを壁ポリゴンポインタ配列に保存する
						Kabe[KabeNum] = &HitDim.Dim[i];

						// 壁ポリゴンの数を加算する
						KabeNum++;
					}
				}
			}
			else
			{
				// ポリゴンの数が列挙できる限界数に達していなかったらポリゴンを配列に追加
				if (YukaNum < PLAYER_MAX_HITCOLL)
				{
					// ポリゴンの構造体のアドレスを床ポリゴンポインタ配列に保存する
					Yuka[YukaNum] = &HitDim.Dim[i];

					// 床ポリゴンの数を加算する
					YukaNum++;
				}
			}
		}
	}

	// 壁ポリゴンとの当たり判定処理
	if (KabeNum != 0)
	{
		// 壁に当たったかどうかのフラグは初期状態では「当たっていない」にしておく
		HitFlag = 0;

		// 移動したかどうかで処理を分岐
		if (MoveFlag == 1)
		{
			// 壁ポリゴンの数だけ繰り返し
			for (i = 0; i < KabeNum; i++)
			{
				// i番目の壁ポリゴンのアドレスを壁ポリゴンポインタ配列から取得
				Poly = Kabe[i];

				// ポリゴンとプレイヤーが当たっていなかったら次のカウントへ
				if (HitCheck_Capsule_Triangle(NowPos, VAdd(NowPos, VGet(0.0f, PLAYER_HIT_HEIGHT, 0.0f)), PLAYER_HIT_WIDTH, Poly->Position[0], Poly->Position[1], Poly->Position[2]) == FALSE) continue;

				// ここにきたらポリゴンとプレイヤーが当たっているということなので、ポリゴンに当たったフラグを立てる
				HitFlag = 1;

				// 壁に当たったら壁に遮られない移動成分分だけ移動する
				{
					VECTOR SlideVec;	// プレイヤーをスライドさせるベクトル

										// 進行方向ベクトルと壁ポリゴンの法線ベクトルに垂直なベクトルを算出
					SlideVec = VCross(MoveVector, Poly->Normal);

					// 算出したベクトルと壁ポリゴンの法線ベクトルに垂直なベクトルを算出、これが
					// 元の移動成分から壁方向の移動成分を抜いたベクトル
					SlideVec = VCross(Poly->Normal, SlideVec);

					// それを移動前の座標に足したものを新たな座標とする
					NowPos = VAdd(OldPos, SlideVec);
				}

				// 新たな移動座標で壁ポリゴンと当たっていないかどうかを判定する
				for (j = 0; j < KabeNum; j++)
				{
					// j番目の壁ポリゴンのアドレスを壁ポリゴンポインタ配列から取得
					Poly = Kabe[j];

					// 当たっていたらループから抜ける
					if (HitCheck_Capsule_Triangle(NowPos, VAdd(NowPos, VGet(0.0f, PLAYER_HIT_HEIGHT, 0.0f)), PLAYER_HIT_WIDTH, Poly->Position[0], Poly->Position[1], Poly->Position[2]) == TRUE) break;
				}

				// j が KabeNum だった場合はどのポリゴンとも当たらなかったということなので
				// 壁に当たったフラグを倒した上でループから抜ける
				if (j == KabeNum)
				{
					HitFlag = 0;
					break;
				}
			}
		}
		else
		{
			// 移動していない場合の処理

			// 壁ポリゴンの数だけ繰り返し
			for (i = 0; i < KabeNum; i++)
			{
				// i番目の壁ポリゴンのアドレスを壁ポリゴンポインタ配列から取得
				Poly = Kabe[i];

				// ポリゴンに当たっていたら当たったフラグを立てた上でループから抜ける
				if (HitCheck_Capsule_Triangle(NowPos, VAdd(NowPos, VGet(0.0f, PLAYER_HIT_HEIGHT, 0.0f)), PLAYER_HIT_WIDTH, Poly->Position[0], Poly->Position[1], Poly->Position[2]) == TRUE)
				{
					HitFlag = 1;
					break;
				}
			}
		}

		// 壁に当たっていたら壁から押し出す処理を行う
		if (HitFlag == 1)
		{
			// 壁からの押し出し処理を試みる最大数だけ繰り返し
			for (k = 0; k < PLAYER_HIT_TRYNUM; k++)
			{
				// 壁ポリゴンの数だけ繰り返し
				for (i = 0; i < KabeNum; i++)
				{
					// i番目の壁ポリゴンのアドレスを壁ポリゴンポインタ配列から取得
					Poly = Kabe[i];

					// プレイヤーと当たっているかを判定
					if (HitCheck_Capsule_Triangle(NowPos, VAdd(NowPos, VGet(0.0f, PLAYER_HIT_HEIGHT, 0.0f)), PLAYER_HIT_WIDTH, Poly->Position[0], Poly->Position[1], Poly->Position[2]) == FALSE) continue;

					// 当たっていたら規定距離分プレイヤーを壁の法線方向に移動させる
					NowPos = VAdd(NowPos, VScale(Poly->Normal, PLAYER_HIT_SLIDE_LENGTH));

					// 移動した上で壁ポリゴンと接触しているかどうかを判定
					for (j = 0; j < KabeNum; j++)
					{
						// 当たっていたらループを抜ける
						Poly = Kabe[j];
						if (HitCheck_Capsule_Triangle(NowPos, VAdd(NowPos, VGet(0.0f, PLAYER_HIT_HEIGHT, 0.0f)), PLAYER_HIT_WIDTH, Poly->Position[0], Poly->Position[1], Poly->Position[2]) == TRUE) break;
					}

					// 全てのポリゴンと当たっていなかったらここでループ終了
					if (j == KabeNum) break;
				}

				// i が KabeNum ではない場合は全部のポリゴンで押し出しを試みる前に全ての壁ポリゴンと接触しなくなったということなのでループから抜ける
				if (i != KabeNum) break;
			}
		}
	}

	// 床ポリゴンとの当たり判定
	if (YukaNum != 0)
	{
		// ジャンプ中且つ上昇中の場合は処理を分岐
		//if (pl.State == 2 && pl.JumpPower > 0.0f)
		/*{
			float MinY;

			// 天井に頭をぶつける処理を行う

			// 一番低い天井にぶつける為の判定用変数を初期化
			MinY = 0.0f;

			// 当たったかどうかのフラグを当たっていないを意味する０にしておく
			HitFlag = 0;

			// 床ポリゴンの数だけ繰り返し
			for (i = 0; i < YukaNum; i++)
			{
				// i番目の床ポリゴンのアドレスを床ポリゴンポインタ配列から取得
				Poly = Yuka[i];

				// 足先から頭の高さまでの間でポリゴンと接触しているかどうかを判定
				LineRes = HitCheck_Line_Triangle(NowPos, VAdd(NowPos, VGet(0.0f, PLAYER_HIT_HEIGHT, 0.0f)), Poly->Position[0], Poly->Position[1], Poly->Position[2]);

				// 接触していなかったら何もしない
				if (LineRes.HitFlag == FALSE) continue;

				// 既にポリゴンに当たっていて、且つ今まで検出した天井ポリゴンより高い場合は何もしない
				if (HitFlag == 1 && MinY < LineRes.Position.y) continue;

				// ポリゴンに当たったフラグを立てる
				HitFlag = 1;

				// 接触したＹ座標を保存する
				MinY = LineRes.Position.y;
			}

			// 接触したポリゴンがあったかどうかで処理を分岐
			if (HitFlag == 1)
			{
				// 接触した場合はプレイヤーのＹ座標を接触座標を元に更新
				NowPos.y = MinY - PLAYER_HIT_HEIGHT;

				// Ｙ軸方向の速度は反転
				//pl.JumpPower = -pl.JumpPower;
			}
		}*/
		//else
		{
			float MaxY;

			// 下降中かジャンプ中ではない場合の処理

			// 床ポリゴンに当たったかどうかのフラグを倒しておく
			HitFlag = 0;

			// 一番高い床ポリゴンにぶつける為の判定用変数を初期化
			MaxY = 0.0f;

			// 床ポリゴンの数だけ繰り返し
			for (i = 0; i < YukaNum; i++)
			{
				// i番目の床ポリゴンのアドレスを床ポリゴンポインタ配列から取得
				Poly = Yuka[i];

				// ジャンプ中かどうかで処理を分岐
				/*if (pl.State == 2)
				{
					// ジャンプ中の場合は頭の先から足先より少し低い位置の間で当たっているかを判定
					LineRes = HitCheck_Line_Triangle(VAdd(NowPos, VGet(0.0f, PLAYER_HIT_HEIGHT, 0.0f)), VAdd(NowPos, VGet(0.0f, -1.0f, 0.0f)), Poly->Position[0], Poly->Position[1], Poly->Position[2]);
				}*/
				//else
				{
					// 走っている場合は頭の先からそこそこ低い位置の間で当たっているかを判定( 傾斜で落下状態に移行してしまわない為 )
					LineRes = HitCheck_Line_Triangle(VAdd(NowPos, VGet(0.0f, PLAYER_HIT_HEIGHT, 0.0f)), VAdd(NowPos, VGet(0.0f, -40.0f, 0.0f)), Poly->Position[0], Poly->Position[1], Poly->Position[2]);
				}

				// 当たっていなかったら何もしない
				if (LineRes.HitFlag == FALSE) continue;

				// 既に当たったポリゴンがあり、且つ今まで検出した床ポリゴンより低い場合は何もしない
				if (HitFlag == 1 && MaxY > LineRes.Position.y) continue;

				// ポリゴンに当たったフラグを立てる
				HitFlag = 1;

				// 接触したＹ座標を保存する
				MaxY = LineRes.Position.y;
			}

			// 床ポリゴンに当たったかどうかで処理を分岐
			if (HitFlag == 1)
			{
				// 当たった場合

				// 接触したポリゴンで一番高いＹ座標をプレイヤーのＹ座標にする
				NowPos.y = MaxY;

				// Ｙ軸方向の移動速度は０に
				//pl.JumpPower = 0.0f;

				// もしジャンプ中だった場合は着地状態にする
				/*if (pl.State == 2)
				{
					// 移動していたかどうかで着地後の状態と再生するアニメーションを分岐する
					if (MoveFlag)
					{
						// 移動している場合は走り状態に
						Player_PlayAnim(1);
						pl.State = 1;
					}
					else
					{
						// 移動していない場合は立ち止り状態に
						Player_PlayAnim(4);
						pl.State = 0;
					}

					// 着地時はアニメーションのブレンドは行わない
					pl.AnimBlendRate = 1.0f;
				}*/
			}
			else
			{
				// 床コリジョンに当たっていなくて且つジャンプ状態ではなかった場合は
				//if (pl.State != 2)
				{
					// ジャンプ中にする
					//pl.State = 2;

					// ちょっとだけジャンプする
					//pl.JumpPower = PLAYER_FALL_UP_POWER;

					// アニメーションは落下中のものにする
					//Player_PlayAnim(3);
				}
			}
		}
	}

	// 新しい座標を保存する
	pos = NowPos;

	// プレイヤーのモデルの座標を更新する
	MV1SetPosition(playerInfo.data, pos);

	// 検出したプレイヤーの周囲のポリゴン情報を開放する
	MV1CollResultPolyDimTerminate(HitDim);

}

void Player::kill() {

	monsterKill = true;

}