#include "Stage.h"
#include <Dxlib.h>

Stage::Stage()
{
	//�ϋq�ȉ摜�̓ǂݍ���
	if ((StageImage = LoadGraph("Resource/Images/BackGround.png")) == -1)
	{
		throw "Resource/Images/BackGround.png";
	}
	//���[���摜�̓ǂݍ���
	if ((StageLane = LoadGraph("Resource/Images/StageLane.png")) == -1)
	{
		throw "Resource/Images/StageLane.png";
	}
}
Stage::~Stage()
{

}

void Stage::UpDate()
{

}

void Stage::Draw() const
{
	for (int i = 0; i < 2; i++)
	{
		DrawRotaGraph(350 + (702 * i), 243, 0.2, 0, StageImage, TRUE);		//�ϋq�Ȃ̕`��
	}
	
	DrawRotaGraph(640, 653, 0.7, 0, StageLane, TRUE);				//�X�e�[�W���[���̕`��

}
