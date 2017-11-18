#include "Stage.h"

Stage::Stage(){

	BinaryFile::SBinaryFileData		BinFileData;

	mBinaryFile = new BinaryFile();

	//カメラ設置
	//mCamera = new Camera();



	//ステージデータ生成
	stagedata = MV1LoadModel("Data\\Stage\\Stage00.mv1");
	stagedata_sky = MV1LoadModel("Data\\Stage\\Stage00_sky.mv1");

	//ステージのコリジョンモデルハンドル
	CollisionModelHandle = MV1LoadModel("Data\\Stage\\Stage00_c.mv1");

	//ステージのバイナリファイルを開く
	mBinaryFile->ReadBinFile_Open(&BinFileData, "Data\\Stage\\Stage00.dat");

	//オブジェクトの数を読み込む
	mBinaryFile->ReadBinFile_Int(&BinFileData, &ObjectInfoNum);

	//ロードフラグ
	Load = false;

}

Stage::~Stage(){



	delete	mBinaryFile;
	mBinaryFile = 0;


	//delete	mCamera;
	//mCamera = 0;


}

//ステージセットアップ
void	Stage::Setup() {



}

//ステージデータ出力
int	Stage::Draw() {

	//ステージ描写
	MV1DrawModel( stagedata );
	MV1DrawModel(stagedata_sky);

	return stagedata;

}

//ステージのコリジョン用３Ｄモデルハンドルを取得する
//    戻り値 : ステージのコリジョン用３Ｄモデルハンドル
int Stage::GetCollisionModelHandle(){
	return	CollisionModelHandle;
}

//ステージオブジェクトの数を取得する
int Stage::GetObjectNum() {
	return	ObjectInfoNum;
}

//オブジェクトが使用するコリジョン用３Ｄモデルハンドルを取得する
int Stage::GetObjectCollisionModelHandle(
	int	Index
) {
	return ObjectCollisionModelHandle[ Index ];
}

//オブジェクトモデル読み込み
void Stage::ObjectModel_Load( int Index ) {

	char	FilePath[ MAX_PATH ];

	//ロードのフラグが経っていたら処理終了
	if (Load) {
		return;
	}
	//3Dモデルの読み込み
	sprintf_s( FilePath, "Data\\Stage\\Stage_Obj%3d.mv1", Index );
	ModelHandle = MV1LoadModel( FilePath );
	//ファイルがなかったら失敗終了
	if(ModelHandle < 0){
		return;
	}
	//コリジョン用の3Dモデルの読み込み


}