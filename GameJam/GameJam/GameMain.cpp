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
	apple = new Apple();
	fps = new FpsController();

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
	apple->UpDate();
	fps->All();

	return this;
}

void GameMain::Draw()const
{
	// 背景の描画
	DrawGraph(0, 0, mori_img, TRUE);

	//プレイヤーの描画
	player->Draw();

	//リンゴの描画
	apple->Draw();

	fps->Disp();

	//スコアの描画
	DrawBox(1000, 0,1280, 720, 0xffffff, TRUE);
	DrawFormatString(SCREEN_WIDTH-SCORE_UI_SIZE, 100, 0x000000, "%d", TotalScore);
}

