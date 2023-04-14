#include "DxLib.h"
#include "GameMain.h"
#include "Result.h"

#define TIMER 180

GameMain::GameMain()
{
	//初期化
	Level = 0;
	TotalScore = 0;
	for (int i = 0; i < MAX_LEVEL; i++)
	{
		Score[i] = 0;
	}
	ClimbingTimer = TIMER;
	MissTimer = TIMER;
	//オブジェクト化
	trampoline = new Trampoline();
	player = new Player();
	wall = new Wall();
	stage = new Stage();

	//BGMの読み込み
	if ((GameBGM = LoadSoundMem("Resource/sounds/BGM/Jackpot.wav")) == -1)
	{
		throw "Resource/sounds/BGM/Jackpot.wav";
	}
	//BGMの音量変更
	ChangeVolumeSoundMem(125, GameBGM);

	//フォントの設定
	ScoreFont[0] = CreateFontToHandle("Score1", 20, 0, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	ScoreFont[1] = CreateFontToHandle("Score2", 26, 0, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	//BGMの再生
	if (CheckSoundMem(GameBGM) == 0) {
		PlaySoundMem(GameBGM, DX_PLAYTYPE_LOOP, TRUE);
	}
}

GameMain::~GameMain()
{
	//オブジェクトの削除
	delete trampoline;
	delete player;
	delete wall;
	delete stage;

	//フォントの削除
	for (int i = 0; i < 2; i++)
	{
		DeleteFontToHandle(ScoreFont[i]);
	}

	//BGMの削除
	DeleteSoundMem(GameBGM);
}

AbstractScene* GameMain::Update()
{
	//処理の更新
	player->UpDate();
	trampoline->UpDate();
	if (ClimbingTimer == TIMER)
	{
		wall->UpDate();
	}

	

	//プレイヤーとトランポリンの当たり判定
	if (trampoline->HitBox(player))	//プレイヤーと当たったら
	{
		if (trampoline->GetState() == TRAMPOLINE_STATE::IDOL) //アイドル状態なら
		{
			trampoline->GetPoint();
		}
		player->HitTrampoline();
	}
	else if (trampoline->GetState() == TRAMPOLINE_STATE::PRESS) //踏まれているなら
	{
		trampoline->Extend();
		player->LeaveTrampoline();
	}
	else {}

	//壁と当たらなかった
	if ((trampoline->GetLocation().x + trampoline->GetErea().width / 2 < player->GetLocation().x) && (player->GetLocation().y >= 500))
	{
		if (MissTimer == TIMER)
		{
			player->MissJump();
		}
		if (--MissTimer < 0)
		{
			Score[Level] = 0;
			TotalScore += Score[Level];
			Level++;
			player->Reset();
			wall->NextStage(Level);
			MissTimer = TIMER;
		}
	}

	//プレイヤーと壁との当たり判定
	else if (wall->HitBox(player))
	{
		if (ClimbingTimer == TIMER)
		{
			player->HitWall();
		}
		if (--ClimbingTimer < 0)
		{
			Score[Level] = wall->GetPoint(player->GetLocation().y - 30);
			TotalScore += Score[Level];
			Level++;
			player->Reset();
			wall->NextStage(Level);
			ClimbingTimer = TIMER;
		}
	}

	//ゲーム終了
	if (MAX_LEVEL <= Level)
	{
		StopSoundMem(GameBGM);
		return new Result(TotalScore, Score);
	}

	return this;
}

void GameMain::Draw()const
{
	//ステージの描画
	stage->Draw();
	//トランポリンの描画
	trampoline->Draw();
	//壁の描画
	wall->Draw();

	//プレイヤーの描画
	player->Draw();

	//スコアの描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBox(20, 20,320, 220, 0xffffff, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	for (int i = 0; i < MAX_LEVEL; i++)
	{
		DrawFormatStringToHandle(30, 60 + (30 * i), 0xffffff, ScoreFont[0], "%dステージ：%3dpt", i + 1, Score[i]);
	}
	DrawFormatStringToHandle(30, 30, 0xffffff, ScoreFont[1], "TotalScore :%4dpt", TotalScore);
}

