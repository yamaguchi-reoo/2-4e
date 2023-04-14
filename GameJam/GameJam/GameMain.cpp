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

	//プレイヤーの描画
	player->Draw();

	//スコアの描画
	DrawBox(1000, 0,1280, 720, 0xffffff, TRUE);
	DrawFormatString(SCREEN_WIDTH-SCORE_UI_SIZE, 100, 0x000000, "%d", TotalScore);
}

