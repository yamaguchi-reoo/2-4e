#include "DxLib.h"
#include "GameMain.h"
#include "Result.h"

#define TIMER 180

GameMain::GameMain()
{
	//初期化
	TotalScore = 0;
	//オブジェクト化
	player = new Player();

	//画像の読み込み
	if ((mori_img = LoadGraph("Resource/Images/mori.png")) == -1)
	{
		throw "Resource/Images/mori.png";
	}
	
}

GameMain::~GameMain()
{
	//オブジェクトの削除
	delete player;

}

AbstractScene* GameMain::Update()
{
	//処理の更新
	player->UpDate();

	return this;
}

void GameMain::Draw()const
{
	// 背景の描画
	DrawGraph(0, 0, mori_img, TRUE);


	//プレイヤーの描画
	player->Draw();

	
	//スコアの描画
	DrawBox(1000, 0,1280, 720, 0xff00ff, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	
}

