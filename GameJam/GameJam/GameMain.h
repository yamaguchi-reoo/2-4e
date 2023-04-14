#pragma once
#include "define.h"
#include "AbstractScene.h"
#include "Player.h"
#include "Trampoline.h"
#include "Wall.h"
#include "Stage.h"


class GameMain :
    public AbstractScene
{
private:

    int Level; //���x��
    int Score[MAX_LEVEL]; //�e�X�e�[�W�̃X�R�A
    int TotalScore;
    Trampoline* trampoline; //�g�����|����
    Player* player; //�v���C���[
    Wall* wall; //��
    Stage* stage; //�X�e�[�W

    int GameBGM;    //BGM
    int ScoreFont[2]; //�X�R�A�p�̃t�H���g
    int ClimbingTimer;      //���Ԓ�~�p
    int MissTimer;
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

