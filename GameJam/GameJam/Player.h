#pragma once
#include "BoxCollider.h"

#define WALK_SPEED 3
#define DASH_SPEED 7
#define JUMP_POWER 22
#define ANIMATION_INTERVAL 10
#define MAX_CHARGE 100

enum class PLAYER_STATE {
	IDOL = 0,
	WALK,
	DASH,
	JUMP_START,
	JUMP,
	JUMP_END,
	JUMP_CHARGE,
	JUMP_MISS,
	CLIMBING
};

class Player :public BoxCollider
{
private:
	bool TrunFlag;
	bool ChageFlag;
	bool StickRollFlag;
	PLAYER_STATE PlayerState;	// �v���C���[�̌��݂̏�Ԃ𐧌�
	int JumpPower;

	int ImageStand;				// �摜�p�ϐ�
	int ImageMiss;				// �摜�p�ϐ�
	int ImagesDash[6];			// �摜�p�z��
	int ImagesWalk[8];			// �摜�p�z��
	int ImagesJump[11];			// �摜�p�z��
	int Image;
	int AnimTimer;				// �摜�؂�ւ��p�^�C�}�[
	int AnimInterval;
	int AnimType;
	int JumpImageTimer;				// �摜�؂�ւ��p�^�C�}�[

	int JumpChage;		// �g�����|�����̃Q�[�W�p

	float Speed;

	
	int ClimbingTimer;	//�����_�ŗp�^�C�}�[

	

	int GuideFont;
	int JumpSE;
	int WalkSE;
	int DashSE;
	int MissSE;
	int JumpEndSE;

private:
	bool NotJump();

	void DashAnimation();
	void WalkAnimation();
	bool JumpStartAnimation();
	void JumpAnimaiton();
	bool JumpEndAnimation();

public:
	//�R���X�g���N�^
	Player();

	//�f�X�g���N�^
	~Player();

	//�X�V
	void UpDate();

	//�`��
	void Draw() const;

	void Reset();

	//�g�����|�����ɐG�ꂽ
	void HitTrampoline();
	void LeaveTrampoline();

	void HitWall();

	void MissJump();
};

