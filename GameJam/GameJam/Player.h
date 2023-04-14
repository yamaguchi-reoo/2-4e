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
	PLAYER_STATE PlayerState;	// プレイヤーの現在の状態を制御
	int JumpPower;

	int ImageStand;				// 画像用変数
	int ImageMiss;				// 画像用変数
	int ImagesDash[6];			// 画像用配列
	int ImagesWalk[8];			// 画像用配列
	int ImagesJump[11];			// 画像用配列
	int Image;
	int AnimTimer;				// 画像切り替え用タイマー
	int AnimInterval;
	int AnimType;
	int JumpImageTimer;				// 画像切り替え用タイマー

	int JumpChage;		// トランポリンのゲージ用

	float Speed;

	
	int ClimbingTimer;	//文字点滅用タイマー

	

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
	//コンストラクタ
	Player();

	//デストラクタ
	~Player();

	//更新
	void UpDate();

	//描画
	void Draw() const;

	void Reset();

	//トランポリンに触れた
	void HitTrampoline();
	void LeaveTrampoline();

	void HitWall();

	void MissJump();
};

