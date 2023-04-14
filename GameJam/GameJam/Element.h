#pragma once
#include "BoxCollider.h"



class Element:public BoxCollider
{
protected:
	int Speed;	//�X�s�[�h

public:
	//�R���X�g���N�^
	Element()
	{
		Speed = 0;
	}

	//�f�X�g���N�^
	~Element()
	{

	}

	//�`��ȊO�̍X�V�����s
	virtual void UpDate() = 0;
	 
	//�`��Ɋւ��邱�Ƃ�����
	virtual void Draw() const = 0;
};
