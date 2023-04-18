#include "Stage.h"
#include <Dxlib.h>

Stage::Stage()
{
	//観客席画像の読み込み
	if ((StageImage = LoadGraph("Resource/Images/BackGround.png")) == -1)
	{
		throw "Resource/Images/BackGround.png";
	}
	//レーン画像の読み込み
	if ((StageLane = LoadGraph("Resource/Images/StageLane.png")) == -1)
	{
		throw "Resource/Images/StageLane.png";
	}
}
Stage::~Stage()
{

}

void Stage::UpDate()
{

}

void Stage::Draw() const
{
	for (int i = 0; i < 2; i++)
	{
		DrawRotaGraph(350 + (702 * i), 243, 0.2, 0, StageImage, TRUE);		//観客席の描画
	}
	
	DrawRotaGraph(640, 653, 0.7, 0, StageLane, TRUE);				//ステージレーンの描画

}
