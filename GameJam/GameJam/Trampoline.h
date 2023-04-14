#pragma once
#include "Element.h"

#define EXTEND_TIME 20

enum class TRAMPOLINE_STATE
{
    IDOL = 0,   //�ʏ���
    PRESS,      //���܂�Ă�����
    EXTEND      //�L�тĂ�����
};

class Trampoline :
    public Element
{
private:
    int Images[3]; //�摜
    TRAMPOLINE_STATE state; //���
    int ExtendTime; //�L�тĂ��鎞��
public:
    //�R���X�g���N�^
    Trampoline();

    //�f�X�g���N�^
    ~Trampoline();

    //�`��ȊO�̍X�V�����s
    void UpDate() override;

    //�v���C���[�Ƃ̓����蔻��
    void GetPoint();

    //�L�тĂ��u�Ԃ̏���
    void Extend();

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;

    //�X�e�[�g�̎擾
    TRAMPOLINE_STATE GetState() { return state; }
};

