#include "DxLib.h"
#include "Trampoline.h"

Trampoline::Trampoline()
{
	//�摜�̓ǂݍ���
	if (LoadDivGraph("Resource/Images/Element/Trampoline.png", 3, 3, 1, 80, 80, Images) == -1)
	{
		throw "Resource/Images/Element/Trampoline";
	}

	//������
	state = TRAMPOLINE_STATE::IDOL;
	ExtendTime = 0;

	//�������W�̐ݒ�
	location.x = 750;
	location.y = 550;

	//�����蔻��̐ݒ�
	erea.width = 65;
	erea.height = 55;
	erea.height_rate = 0.25;
	erea.width_rate = 0.5;
}

Trampoline::~Trampoline()
{

}

void Trampoline::UpDate()
{
	if (state == TRAMPOLINE_STATE::EXTEND)
	{
		if (--ExtendTime < 0) //�L�тĂ��鎞�Ԃ�0�b�ȉ��ɂȂ�����//�ʏ��ԂɕύX
		{
			//�ʏ��ԂɕύX
			state = TRAMPOLINE_STATE::IDOL;
		}
	}
}

void Trampoline::GetPoint()
{
	//���܂ꂽ��ԂɕύX
	state = TRAMPOLINE_STATE::PRESS;
}

void Trampoline::Extend()
{
	state = TRAMPOLINE_STATE::EXTEND;
	ExtendTime = EXTEND_TIME;
}

void Trampoline::Draw() const
{
	DrawRotaGraph(location.x, location.y, 1.5, 0, Images[static_cast<int>(state)], TRUE);
}