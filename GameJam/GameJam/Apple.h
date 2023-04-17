#pragma once
#include "BoxCollider.h"

class Apple :public BoxCollider
{
private:
	
	int A_Count;	//�����ɃX�|�[�����Ă����񂲂̐�

	struct AppleData {
		int flg;			//�g�p�t���O
		int type;			//�^�C�v
		int img;			//�摜
		float x, y, w, h;		//���W�A���A����
		float speed;		//�ړ����x
		int point;			//�X�R�A���Z�|�C���g
	};

	//�����L���O�f�[�^�̕ϐ��錾
	struct AppleData	g_Apple[10];
	struct AppleData	g_AppleRd = { TRUE,0,0,0,-50,63,120,1,100 };
	struct AppleData	g_AppleBr = { TRUE,1,0,100,-50,63,120,2,200 };
	struct AppleData	g_AppleGr = { TRUE,2,0,0,-50,63,120,3.5,500 };
	struct AppleData	g_AppleTx = { TRUE,3,0,0,-50,63,120,0.5,-750 };
public:
	//�R���X�g���N�^
	Apple();

	//�f�X�g���N�^
	~Apple();

	//�X�V
	void UpDate();

	//�`��
	void Draw() const;

	int Spawn();
	int Delete();
};



