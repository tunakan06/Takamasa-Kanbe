#include "Monster.h"
#include <math.h>

#define CHARA_MOVE_SPEED			30.0f		// 移動速度
#define CHARA_ANGLE_SPEED			0.2f		// 角度変化速度

// プレイヤーキャラ以外キャラの情報
#define NOTPLAYER_NUM				4			// プレイヤー以外のキャラの数
#define NOTPLAYER_MOVETIME			120			// 一つの方向に移動する時間
#define NOTPLAYER_JUMPRATIO			250			// プレイヤー以外のキャラがジャンプする確率

Monster::Monster(){

	mPlayer = new Player();
	mStage	= new Stage();

	noticedistance	= 300.0f;

	//モンスター（蜂）データロード
	monsterdata		=	MV1LoadModel("Data\\Character\\Bee\\Bee.mv1");

	//モンスターニュートラルロード
	monster_anim_neutral = MV1LoadModel("Data\\Character\\Bee\\Anim_Neutral.mv1");

	//初期位置
	pos = VGet( 0.0f, 200.0f, 500.0f);

	//プレイヤーに気づく距離
	PlayerNoticeDistanceCounter = 0.0f;
	PlayerNoticeDistanceCounter_XZ = 0.0f;

	//視界の範囲
	SeeAngleRange = 120.0f * DX_PI_F / 180.0f;

	int	i;

	for (i = 0; i < ENEMY_ATTACK_MAX_NUM; i++)
	{
		AttackNum++;
	}

	np.State = 0;

}

Monster::~Monster(){
}

//モンスター描写
int Monster::born( float steptime, VECTOR playerpos) {

	int i;
	int j;
	VECTOR MoveVec;
	//int JumpFlag;

	// キャラクタの数だけ繰り返し
	for (i = 0; i < NOTPLAYER_NUM; i++)
	{
		// ジャンプフラグを倒しておく
		//JumpFlag = 0;

		// 一定時間が経過したら移動する方向を変更する
		np.MoveTime++;
		if (np.MoveTime >= NOTPLAYER_MOVETIME)
		{
			np.MoveTime = 0;

			// 新しい方向の決定
			np.MoveAngle = GetRand(1000) * DX_PI_F * 2.0f / 1000.0f;

			// 一定確率でジャンプ　　　する
			if (GetRand(1000) < NOTPLAYER_JUMPRATIO)
			{
				//JumpFlag = 1;
			}
		}

		// 新しい方向の角度からベクトルを算出
		MoveVec.x = cos(np.MoveAngle) * CHARA_MOVE_SPEED/60.0f;
		MoveVec.y = 0.0f;
		MoveVec.z = sin(np.MoveAngle) * CHARA_MOVE_SPEED/60.0f;

		// プレイヤーとの当たり判定を行う
		//Chara_Collision(&npl[i].CharaInfo, &MoveVec, &pl.CharaInfo);

		// 自分以外のプレイヤーキャラとの当たり判定を行う
		for (j = 0; j < NOTPLAYER_NUM; j++)
		{
			// 自分との当たり判定はしない
			if (i == j) continue;

			//Chara_Collision(&npl[i].CharaInfo, &MoveVec, &npl[j].CharaInfo);
		}

		// 移動処理を行う
		//Chara_Process(&npl[i].CharaInfo, MoveVec, JumpFlag);
		{
			int MoveFlag;			// 移動したかどうかのフラグ( 1:移動した  0:移動していない )

			// 移動したかどうかのフラグをセット、少しでも移動していたら「移動している」を表す１にする
			MoveFlag = 0;
			if (MoveVec.x < -0.001f || MoveVec.x > 0.001f ||
				MoveVec.y < -0.001f || MoveVec.y > 0.001f ||
				MoveVec.z < -0.001f || MoveVec.z > 0.001f)
			{
				MoveFlag = 1;
			}

			// 移動ボタンが押されたかどうかで処理を分岐
			if (MoveFlag)
			{
				// 移動ベクトルを正規化したものをキャラクターが向くべき方向として保存
				np.TargetMoveDirection = VNorm(MoveVec);

				// もし今まで「立ち止まり」状態だったら
				if (np.State == 0)
				{
					// 走りアニメーションを再生する
					//Chara_PlayAnim(ch, 1);

					// 状態を「走り」にする
					np.State = 1;
				}
			}
			else
			{
				// このフレームで移動していなくて、且つ状態が「走り」だったら
				if (np.State == 1)
				{
					// 立ち止りアニメーションを再生する
					//Chara_PlayAnim(ch, 4);

					// 状態を「立ち止り」にする
					np.State = 0;
				}
			}

			// キャラクターの移動方向にモデルの方向を近づける
			//Chara_AngleProcess(ch);
			{
				float TargetAngle;			// 目標角度
				float SaAngle;				// 目標角度と現在の角度との差

											// 目標の方向ベクトルから角度値を算出する
				TargetAngle = atan2(np.TargetMoveDirection.x, np.TargetMoveDirection.z);

				// 目標の角度と現在の角度との差を割り出す
				{
					// 最初は単純に引き算
					SaAngle = TargetAngle - np.Angle;

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
					SaAngle -= CHARA_ANGLE_SPEED;
					if (SaAngle < 0.0f)
					{
						SaAngle = 0.0f;
					}
				}
				else
				{
					// 差がマイナスの場合は足す
					SaAngle += CHARA_ANGLE_SPEED;
					if (SaAngle > 0.0f)
					{
						SaAngle = 0.0f;
					}
				}

				// モデルの角度を更新
				np.Angle = TargetAngle - SaAngle;
				MV1SetRotationXYZ(monsterdata, VGet(0.0f, np.Angle + DX_PI_F, 0.0f));
			}

			// 移動ベクトルを元にコリジョンを考慮しつつキャラクターを移動
			//Chara_Move(ch, MoveVec);
			{
				int i, j, k;						// 汎用カウンタ変数
				int MoveFlag;						// 水平方向に移動したかどうかのフラグ( ０:移動していない  １:移動した )
				int HitFlag;						// ポリゴンに当たったかどうかを記憶しておくのに使う変数( ０:当たっていない  １:当たった )
				MV1_COLL_RESULT_POLY_DIM HitDim;			// キャラクターの周囲にあるポリゴンを検出した結果が代入される当たり判定結果構造体
				int KabeNum;						// 壁ポリゴンと判断されたポリゴンの数
				int YukaNum;						// 床ポリゴンと判断されたポリゴンの数
			//	MV1_COLL_RESULT_POLY *Kabe[CHARA_MAX_HITCOLL];	// 壁ポリゴンと判断されたポリゴンの構造体のアドレスを保存しておくためのポインタ配列
			//	MV1_COLL_RESULT_POLY *Yuka[CHARA_MAX_HITCOLL];	// 床ポリゴンと判断されたポリゴンの構造体のアドレスを保存しておくためのポインタ配列
				MV1_COLL_RESULT_POLY *Poly;				// ポリゴンの構造体にアクセスするために使用するポインタ( 使わなくても済ませられますがプログラムが長くなるので・・・ )
				HITRESULT_LINE LineRes;				// 線分とポリゴンとの当たり判定の結果を代入する構造体
				VECTOR OldPos;						// 移動前の座標	
				VECTOR NowPos;						// 移動後の座標

													// 移動前の座標を保存
				OldPos = pos;

				// 移動後の座標を算出
				NowPos = VAdd(pos, MoveVec);

				// キャラクターの周囲にあるステージポリゴンを取得する
				// ( 検出する範囲は移動距離も考慮する )
				/*HitDim = MV1CollCheck_Sphere(stg.ModelHandle, -1, ch->Position, CHARA_ENUM_DEFAULT_SIZE + VSize(MoveVector));

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
							// 壁ポリゴンと判断された場合でも、キャラクターのＹ座標＋１．０ｆより高いポリゴンのみ当たり判定を行う
							if (HitDim.Dim[i].Position[0].y > ch->Position.y + 1.0f ||
								HitDim.Dim[i].Position[1].y > ch->Position.y + 1.0f ||
								HitDim.Dim[i].Position[2].y > ch->Position.y + 1.0f)
							{
								// ポリゴンの数が列挙できる限界数に達していなかったらポリゴンを配列に追加
								if (KabeNum < CHARA_MAX_HITCOLL)
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
							if (YukaNum < CHARA_MAX_HITCOLL)
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

							// ポリゴンとキャラクターが当たっていなかったら次のカウントへ
							if (HitCheck_Capsule_Triangle(NowPos, VAdd(NowPos, VGet(0.0f, CHARA_HIT_HEIGHT, 0.0f)), CHARA_HIT_WIDTH, Poly->Position[0], Poly->Position[1], Poly->Position[2]) == FALSE) continue;

							// ここにきたらポリゴンとキャラクターが当たっているということなので、ポリゴンに当たったフラグを立てる
							HitFlag = 1;

							// 壁に当たったら壁に遮られない移動成分分だけ移動する
							{
								VECTOR SlideVec;	// キャラクターをスライドさせるベクトル

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
								if (HitCheck_Capsule_Triangle(NowPos, VAdd(NowPos, VGet(0.0f, CHARA_HIT_HEIGHT, 0.0f)), CHARA_HIT_WIDTH, Poly->Position[0], Poly->Position[1], Poly->Position[2]) == TRUE) break;
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
							if (HitCheck_Capsule_Triangle(NowPos, VAdd(NowPos, VGet(0.0f, CHARA_HIT_HEIGHT, 0.0f)), CHARA_HIT_WIDTH, Poly->Position[0], Poly->Position[1], Poly->Position[2]) == TRUE)
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
						for (k = 0; k < CHARA_HIT_TRYNUM; k++)
						{
							// 壁ポリゴンの数だけ繰り返し
							for (i = 0; i < KabeNum; i++)
							{
								// i番目の壁ポリゴンのアドレスを壁ポリゴンポインタ配列から取得
								Poly = Kabe[i];

								// キャラクターと当たっているかを判定
								if (HitCheck_Capsule_Triangle(NowPos, VAdd(NowPos, VGet(0.0f, CHARA_HIT_HEIGHT, 0.0f)), CHARA_HIT_WIDTH, Poly->Position[0], Poly->Position[1], Poly->Position[2]) == FALSE) continue;

								// 当たっていたら規定距離分キャラクターを壁の法線方向に移動させる
								NowPos = VAdd(NowPos, VScale(Poly->Normal, CHARA_HIT_SLIDE_LENGTH));

								// 移動した上で壁ポリゴンと接触しているかどうかを判定
								for (j = 0; j < KabeNum; j++)
								{
									// 当たっていたらループを抜ける
									Poly = Kabe[j];
									if (HitCheck_Capsule_Triangle(NowPos, VAdd(NowPos, VGet(0.0f, CHARA_HIT_HEIGHT, 0.0f)), CHARA_HIT_WIDTH, Poly->Position[0], Poly->Position[1], Poly->Position[2]) == TRUE) break;
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
					if (ch->State == 2 && ch->JumpPower > 0.0f)
					{
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
							LineRes = HitCheck_Line_Triangle(NowPos, VAdd(NowPos, VGet(0.0f, CHARA_HIT_HEIGHT, 0.0f)), Poly->Position[0], Poly->Position[1], Poly->Position[2]);

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
							// 接触した場合はキャラクターのＹ座標を接触座標を元に更新
							NowPos.y = MinY - CHARA_HIT_HEIGHT;

							// Ｙ軸方向の速度は反転
							ch->JumpPower = -ch->JumpPower;
						}
					}
					else
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
							if (ch->State == 2)
							{
								// ジャンプ中の場合は頭の先から足先より少し低い位置の間で当たっているかを判定
								LineRes = HitCheck_Line_Triangle(VAdd(NowPos, VGet(0.0f, CHARA_HIT_HEIGHT, 0.0f)), VAdd(NowPos, VGet(0.0f, -1.0f, 0.0f)), Poly->Position[0], Poly->Position[1], Poly->Position[2]);
							}
							else
							{
								// 走っている場合は頭の先からそこそこ低い位置の間で当たっているかを判定( 傾斜で落下状態に移行してしまわない為 )
								LineRes = HitCheck_Line_Triangle(VAdd(NowPos, VGet(0.0f, CHARA_HIT_HEIGHT, 0.0f)), VAdd(NowPos, VGet(0.0f, -40.0f, 0.0f)), Poly->Position[0], Poly->Position[1], Poly->Position[2]);
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

							// 接触したポリゴンで一番高いＹ座標をキャラクターのＹ座標にする
							NowPos.y = MaxY;

							// Ｙ軸方向の移動速度は０に
							ch->JumpPower = 0.0f;

							// もしジャンプ中だった場合は着地状態にする
							if (ch->State == 2)
							{
								// 移動していたかどうかで着地後の状態と再生するアニメーションを分岐する
								if (MoveFlag)
								{
									// 移動している場合は走り状態に
									Chara_PlayAnim(ch, 1);
									ch->State = 1;
								}
								else
								{
									// 移動していない場合は立ち止り状態に
									Chara_PlayAnim(ch, 4);
									ch->State = 0;
								}

								// 着地時はアニメーションのブレンドは行わない
								ch->AnimBlendRate = 1.0f;
							}
						}
						else
						{
							// 床コリジョンに当たっていなくて且つジャンプ状態ではなかった場合は
							if (ch->State != 2)
							{
								// ジャンプ中にする
								ch->State = 2;

								// ちょっとだけジャンプする
								ch->JumpPower = CHARA_FALL_UP_POWER;

								// アニメーションは落下中のものにする
								Chara_PlayAnim(ch, 3);
							}
						}
					}
				}*/

				// 新しい座標を保存する
				pos = NowPos;

				// キャラクターのモデルの座標を更新する
				MV1SetPosition(monsterdata, pos);

				// 検出したキャラクターの周囲のポリゴン情報を開放する
				//MV1CollResultPolyDimTerminate(HitDim);
			}

			// アニメーション処理
			//Chara_AnimProcess(ch);
		}

	}

	//敵の処理に必要な情報のセットアップ
	infoSetup( steptime , playerpos);

	//モンスター位置設定
	MV1SetPosition( monsterdata, pos );

	//モンスターニュートラルアニメーション
	MV1AttachAnim( monsterdata,0,monster_anim_neutral );

	//モンスター描写
	MV1DrawModel( monsterdata );

	//モンスターがプレイヤーを見つけたら、プレイヤーを追跡
	//tracking(playerpos);

	return monsterdata;

}

//プレイヤーを追跡
void Monster::tracking(	VECTOR playerpos ) {

	char *a;

	//プレイヤーの位置を格納
	//ppos = mPlayer->pos;

	//デバッグ
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	DrawFormatString(1280 - 84, 720 - 20, GetColor(255, 255, 255), "pos.x : %d", pos.x);
	
	//モンスターがプレイヤーを見つけたら、プレイヤーを追跡
	if ( ( pos.x - playerpos.x <= 100 )
		&& ( pos.z - playerpos.z <= 100 ) ) {




		//プレイヤーに、追跡。
		//敵は、1.5	倍早く追跡してくる。
		pos.x = pos.x - 1.5 * (playerpos.x)/fabs(playerpos.x);
		pos.z = pos.z - 1.5 * (playerpos.z) / fabs(playerpos.z);
	}

}

//情報のセットアップ
void Monster::infoSetup(float steptime, VECTOR playerpos ) {

	int		i;

	//ステージ用コリジョン３Ｄモデルのハンドルを取得
	StageCollModel = mStage->GetCollisionModelHandle();

	//ステージオブジェクトの数を取得する
	StageObjectNum = mStage->GetObjectNum();

	// プレイヤーが居るかどうかで処理を分岐
	if ( mPlayer == NULL)
	{
		// プレイヤーが居ない場合は『プレイヤーを見つけたかどうか』などの情報を初期化する
		PlayerNoticeDistanceCounter = 0.0f;
		PlayerNoticeDistanceCounter_XZ = 0.0f;
		SeePlayer = false;
		SeePlayerCounter = 0.0f;
		NoticePlayer = false;
		NoticePlayer_AttackMode = false;
	}
	else {
		//敵からプレイヤーへのベクトルを算出
		EnemyToPlayerVec = VSub(playerpos, pos);
		EnemyToPlayerVec_XZ = VSub(VGet(playerpos.x, 0.0f, mPlayer->pos.z),
			VGet(pos.x, 0.0f, pos.z));

		//敵からプレイヤーへの正規化ベクトルを算出
		PlayerDirection = VNorm(EnemyToPlayerVec);
		PlayerDirection_XZ = VNorm(EnemyToPlayerVec_XZ);

		//敵からプレイヤーまでの距離を算出
		PlayerDistance = VSize(EnemyToPlayerVec);
		PlayerDistance_XZ = VSize(EnemyToPlayerVec_XZ);



		//プレイヤーに気付く距離に居る場合はプレイヤーに
		//気づく距離になってからの時間を進める
		if (PlayerDistance < noticedistance) {
			PlayerNoticeDistanceCounter += steptime;
		}
		else {
			PlayerNoticeDistanceCounter = 0.0f;
		}

		//プレイヤーに気付く距離に居る場合はプレイヤーに
		//気付く距離になってからの時間を進める( 水平方向のみ考慮 )
		if (PlayerDistance_XZ < noticedistance) {
			PlayerNoticeDistanceCounter_XZ += steptime;
		}
		else {
			PlayerNoticeDistanceCounter_XZ = 0.0f;
		}

		//敵の視界の範囲にプレイヤーがいるかを調べる
		if (cos(SeeAngleRange) <
			VDot(FrontDirection, PlayerDirection_XZ)) {

			//敵の視界の範囲にプレイヤーが居る場合は間に遮蔽物が無いかを調べる

			//プレイヤーと敵の頭の位置を取得
			PlayerHeadPosition = MV1GetFramePosition(mPlayer->playerInfo.data,
				MV1SearchFrame(mPlayer->playerInfo.data, "head"));
			HeadPosition = MV1GetFramePosition(monsterdata,
				MV1SearchFrame(monsterdata, "head"));

			//お互いの頭部の間に遮るものがあるかどうかを調べる
			CollPoly = MV1CollCheck_Line(StageCollModel, -1, HeadPosition,
				PlayerHeadPosition);
			if (CollPoly.HitFlag == FALSE) {

				/*for (i = 0; i < StageObjectNum; i++)
				{
					ObjectCollModel = mStage->GetObjectCollisionModelHandle(i);

					if (ObjectCollModel == -1)
					{
						continue;
					}

					CollPoly = MV1CollCheck_Line(ObjectCollModel, -1, HeadPosition,
						PlayerHeadPosition);

					if (CollPoly.HitFlag)
					{
						break;
					}
				}*/
			}

			//無い場合は敵からプレイヤーが見えるということ
			SeePlayer = CollPoly.HitFlag == FALSE;
		}
		else
		{
			SeePlayer = false;
		}
		//敵からプレイヤーが見えている場合は見えるようになってからの時間を進める
		if (SeePlayer)
		{
			SeePlayerCounter += steptime;
		}
		else
		{
			SeePlayerCounter = 0.0f;
		}

		//攻撃モードではない場合にプレイヤーの存在に気付く条件が揃っているかをチェック
		if ((SeePlayerCounter > NoticeTime_See &&
			PlayerDistance_XZ < NoticeDistance_See) ||
			PlayerNoticeDistanceCounter > NoticeTime_Distance ||
			PlayerNoticeDistanceCounter_XZ > NoticeTime_Distance)
		{
			// 揃っている場合はプレイヤーに気付いているかどうかのフラグを立てる
			NoticePlayer = true;
		}
		else
		{
			NoticePlayer = false;
		}

		// 戦闘モードでプレイヤーの存在に気付く条件が揃っているかをチェック
		if (SeePlayer ||
			PlayerDistance < NoticeDistance_AttackMode ||
			PlayerDistance_XZ < NoticeDistance_AttackMode) {

			// 揃っている場合はプレイヤーに気付いているかどうかのフラグを立てる
			NoticePlayer_AttackMode = true;
		}
		else
		{
			NoticePlayer_AttackMode = false;
		}

		// プレイヤーが周囲に居るというメッセージが届いていたら無条件で
		// プレイヤーに気付いていることにする
		if (PlayerNearDistanceMessage) {
			NoticePlayer = true;
			NoticePlayer_AttackMode = true;

			// メッセージが届いたことを示すフラグを倒す
			PlayerNearDistanceMessage = false;
		}

		// 各攻撃タイプの「攻撃を行う距離に居るかどうか」のフラグを更新
		for (i = 0; i < AttackNum; i++)
		{
			AttackDistancebool =
				PlayerDistance < AttackDistance;

			AttackDistance_XZbool =
				PlayerDistance_XZ < AttackDistance;
		}
	}
}

//モンスターの情報推移
/*bool Monster::step( float steptime ) {

	//処理の情報に必要な情報のセットアップ
	infoSetup( steptime );



}*/

// モンスター死亡
void Monster::dead() {

	live = false;

}
