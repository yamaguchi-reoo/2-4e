#include "DxLib.h"
#include "Trampoline.h"

Trampoline::Trampoline()
{
	//画像の読み込み
	if (LoadDivGraph("Resource/Images/Element/Trampoline.png", 3, 3, 1, 80, 80, Images) == -1)
	{
		throw "Resource/Images/Element/Trampoline";
	}

	//初期化
	state = TRAMPOLINE_STATE::IDOL;
	ExtendTime = 0;

	//初期座標の設定
	location.x = 750;
	location.y = 550;

	//当たり判定の設定
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
		if (--ExtendTime < 0) //伸びている時間が0秒以下になったら//通常状態に変更
		{
			//通常状態に変更
			state = TRAMPOLINE_STATE::IDOL;
		}
	}
}

void Trampoline::GetPoint()
{
	//踏まれた状態に変更
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