#pragma once
#include "Element.h"

#define BLOCK_NUM 23
#define BLOCK_SIZE 40
#define BASE_SPEED 4 
#define START_TIME 30

enum class BLOCK_COLOR
{
    BLACK = 0,
    BLUE,
    GREEN,
    YELLOW,
    ORANGE,
    RED
};

class Wall :
    public Element
{
private:
    int Level; //���x��
    int Block[BLOCK_NUM]; //�u���b�N
    int StartPoint; //�X�^�[�g�n�_
    int EndPoint; //�G���h�n�_
    int WaitTime; //�ړ��J�n����܂ł̎���
    int PointFont;  //�X�R�A�\���p�̃t�H���g
    const int POINT[6]{ 10,20,30,40,50,100 };   //���_
    const float MOVE_POINT[4][2] = { {1000,0,},{1000,-200},{1200,0}, {1200,-200} }; //�ړI�n([0]=x���W,[1]=y���W)
public:
    //�R���X�g���N�^
    Wall();

    //�f�X�g���N�^
    ~Wall();

    //�`��ȊO�̍X�V�����s
    void UpDate() override;

    //�ړ�����
    void Move();

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;

    //�|�C���g�̎擾
    int GetPoint(float player_y);

    //���x���̐ݒ�
    void NextStage(int level);
};

