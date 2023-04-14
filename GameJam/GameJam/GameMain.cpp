#include "DxLib.h"
#include "GameMain.h"
#include "Result.h"

#define TIMER 180

GameMain::GameMain()
{
	//������
	TotalScore = 0;
	//�I�u�W�F�N�g��
	player = new Player();

	//�摜�̓ǂݍ���
	if ((mori_img = LoadGraph("Resource/Images/mori.png")) == -1)
	{
		throw "Resource/Images/mori.png";
	}
	
}

GameMain::~GameMain()
{
	//�I�u�W�F�N�g�̍폜
	delete player;

}

AbstractScene* GameMain::Update()
{
	//�����̍X�V
	player->UpDate();

	return this;
}

void GameMain::Draw()const
{
	// �w�i�̕`��
	DrawGraph(0, 0, mori_img, TRUE);


	//�v���C���[�̕`��
	player->Draw();

	
	//�X�R�A�̕`��
	DrawBox(1000, 0,1280, 720, 0xff00ff, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	
}

