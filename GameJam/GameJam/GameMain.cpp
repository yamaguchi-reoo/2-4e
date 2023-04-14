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

	//�v���C���[�̕`��
	player->Draw();

	//�X�R�A�̕`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBox(1000, 0,1280, 720, 0xffffff, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	
}

