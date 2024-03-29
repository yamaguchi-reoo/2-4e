#pragma once
#include "BoxCollider.h"

#define PLAYER_SIZE 100
#define WALK_SPEED  5

enum class PLAYER_STATE {
	IDOL = 0,
	WALK_RIGTH,
	WALK_LEFT,

};

class Player :public BoxCollider
{
private:
	
	PLAYER_STATE PlayerState;	// プレイヤーの現在の状態を制御

	float Speed;
	int AccelerationRight;	//加速度（右）
	int AccelerationLeft;	//加速度（左）

private:


public:
	//コンストラクタ
	Player();

	//デストラクタ
	~Player();

	//更新
	void UpDate();

	//描画
	void Draw() const;
};

