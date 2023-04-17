#pragma once
#include "define.h"
#include "AbstractScene.h"
#include "Player.h"
#include "Stage.h"


class GameMain :
    public AbstractScene
{
private:

    int TotalScore;
    Player* player; //�v���C���[

    int mori_img;

public:
    //�R���X�g���N�^
    GameMain();

    //�f�X�g���N�^
    ~GameMain();

    //�`��ȊO�̍X�V�����s
    AbstractScene* Update() override;

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;
};
