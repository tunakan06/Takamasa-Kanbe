#include "Stage.h"

Stage::Stage(){

	BinaryFile::SBinaryFileData		BinFileData;

	mBinaryFile = new BinaryFile();

	//�J�����ݒu
	//mCamera = new Camera();



	//�X�e�[�W�f�[�^����
	stagedata = MV1LoadModel("Data\\Stage\\Stage00.mv1");
	stagedata_sky = MV1LoadModel("Data\\Stage\\Stage00_sky.mv1");

	//�X�e�[�W�̃R���W�������f���n���h��
	CollisionModelHandle = MV1LoadModel("Data\\Stage\\Stage00_c.mv1");

	//�X�e�[�W�̃o�C�i���t�@�C�����J��
	mBinaryFile->ReadBinFile_Open(&BinFileData, "Data\\Stage\\Stage00.dat");

	//�I�u�W�F�N�g�̐���ǂݍ���
	mBinaryFile->ReadBinFile_Int(&BinFileData, &ObjectInfoNum);

	//���[�h�t���O
	Load = false;

}

Stage::~Stage(){



	delete	mBinaryFile;
	mBinaryFile = 0;


	//delete	mCamera;
	//mCamera = 0;


}

//�X�e�[�W�Z�b�g�A�b�v
void	Stage::Setup() {



}

//�X�e�[�W�f�[�^�o��
int	Stage::Draw() {

	//�X�e�[�W�`��
	MV1DrawModel( stagedata );
	MV1DrawModel(stagedata_sky);

	return stagedata;

}

//�X�e�[�W�̃R���W�����p�R�c���f���n���h�����擾����
//    �߂�l : �X�e�[�W�̃R���W�����p�R�c���f���n���h��
int Stage::GetCollisionModelHandle(){
	return	CollisionModelHandle;
}

//�X�e�[�W�I�u�W�F�N�g�̐����擾����
int Stage::GetObjectNum() {
	return	ObjectInfoNum;
}

//�I�u�W�F�N�g���g�p����R���W�����p�R�c���f���n���h�����擾����
int Stage::GetObjectCollisionModelHandle(
	int	Index
) {
	return ObjectCollisionModelHandle[ Index ];
}

//�I�u�W�F�N�g���f���ǂݍ���
void Stage::ObjectModel_Load( int Index ) {

	char	FilePath[ MAX_PATH ];

	//���[�h�̃t���O���o���Ă����珈���I��
	if (Load) {
		return;
	}
	//3D���f���̓ǂݍ���
	sprintf_s( FilePath, "Data\\Stage\\Stage_Obj%3d.mv1", Index );
	ModelHandle = MV1LoadModel( FilePath );
	//�t�@�C�����Ȃ������玸�s�I��
	if(ModelHandle < 0){
		return;
	}
	//�R���W�����p��3D���f���̓ǂݍ���


}