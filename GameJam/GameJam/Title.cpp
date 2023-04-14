#include "DxLib.h"
#include "Title.h"
#include "GameMain.h"
#include "DrawRanking.h"
#include"PadInput.h"
#include"Help.h"
#include"Credit.h"
#include"End.h"

//タイトルメニュー
enum class TITLE_MENU 
{
	GAME_START = 0,
	GAME_RANKING,
    GAME_HELP,
	GAME_CREDIT,
	GAME_END
};

Title::Title()
{
	//初期化
	Select = 0;

	MenuFont = CreateFontToHandle("HeadLine", 80, 8, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);

	//画像の読み込み
	if ((TitleImage = LoadGraph("Resource/Images/Title.png")) == -1)
	{
		throw "Resource/Images/Title.png";
	}

	//BGMの読み込み
	if ((TitleBGM = LoadSoundMem("Resource/sounds/BGM/Sick_Red_Girl.wav")) == -1)
	{
		throw "Resource/sounds/BGM/Sick_Red_Girl.wav";
	}
	//BGMの音量変更
	ChangeVolumeSoundMem(125, TitleBGM);

	//SEの読み込み
	if ((MenuSE = LoadSoundMem("Resource/sounds/SE/Select.wav")) == -1) //選択SE
	{
		throw "Resource/sounds/SE/Select.wav";
	}
	if ((DecisionSE = LoadSoundMem("Resource/sounds/SE/Decision.wav")) == -1) //決定ボタン
	{
		throw "Resource/sounds/SE/Decision.wav";
	}
	//SEの音量変更
	ChangeVolumeSoundMem(200, MenuSE);
	ChangeVolumeSoundMem(200, DecisionSE);

	//タイトルBGMをスタート
	if (CheckSoundMem(TitleBGM) == 0) {
		PlaySoundMem(TitleBGM, DX_PLAYTYPE_BACK, TRUE);
	}
}

Title::~Title()
{
	//フォントの削除
	DeleteFontToHandle(MenuFont);

	//サウンドの削除
	DeleteSoundMem(TitleBGM);
	DeleteSoundMem(MenuSE);
	DeleteSoundMem(DecisionSE);
}

//更新
AbstractScene* Title::Update()
{
	

	//十字キー↑入力
	if(PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP))
	{
		PlaySoundMem(MenuSE, DX_PLAYTYPE_BACK);
		Select--;
		if (Select < 0)Select = 4;
	}
	//十字キー↓入力
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN))
	{
		PlaySoundMem(MenuSE, DX_PLAYTYPE_BACK);
		Select++;
		if (Select > 4)Select = 0;

	}

	{
		//入力キー情報
		OldKey = NowKey;
		NowKey = PAD_INPUT::GetLStick().ThumbY;
		KeyFlg = NowKey & ~OldKey;

		//Lスティック上入力
		if (KeyFlg & NowKey/(-20923) < 0)
		{
			PlaySoundMem(MenuSE, DX_PLAYTYPE_BACK);
			Select--;
			if (Select < 0)Select = 4;
		}

		//Lスティック下入力
		if (KeyFlg & NowKey/ 20923 < 0)
		{
			PlaySoundMem(MenuSE, DX_PLAYTYPE_BACK);
			Select++;
			if (Select > 4)Select = 0;
		}

	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
	{
		PlaySoundMem(DecisionSE, DX_PLAYTYPE_BACK);
		switch(static_cast<TITLE_MENU>(Select))
		{
			//ゲーム画面へ
		case TITLE_MENU::GAME_START:
			StopSoundMem(TitleBGM);
			return new GameMain();
			break;
			//ランキング画面へ
		case TITLE_MENU::GAME_RANKING:
			StopSoundMem(TitleBGM);
			return new DrawRanking();
			break;
			//ヘルプ画面へ
		case TITLE_MENU::GAME_HELP:
			StopSoundMem(TitleBGM);
			return new Help();
			break;
			//クレジット画面へ
		case TITLE_MENU::GAME_CREDIT:
			StopSoundMem(TitleBGM);
			return new Credit();
			break;
			//エンド画面へ
		case TITLE_MENU::GAME_END:
			StopSoundMem(TitleBGM);
			return new End();
			break;
		default:
			break;
		}
	}
	
	return this;
}

//画像描画
void Title::Draw()const
{
	DrawGraph(0, 0, TitleImage, TRUE);

	// ステージの描画
	SetFontSize(64);                             //サイズを64に変更
	SetFontThickness(8);                         //太さを8に変更

	//メニューの描画
	DrawStringToHandle(730, 240, "GameStart",0xff00ff,MenuFont);
	DrawStringToHandle(730, 320, "GameRanking", 0xff00ff, MenuFont);
	DrawStringToHandle(730, 400, "GameHelp", 0xff00ff, MenuFont);
	DrawStringToHandle(730, 480, "GameCredit", 0xff00ff, MenuFont);
	DrawStringToHandle(730, 560, "GameEnd", 0xff00ff, MenuFont);

	//カーソルの描画
	int select_y = 280 + Select * 80;
	DrawTriangle(700, select_y, 670, select_y - 30, 670, select_y + 30, 0xffd700, TRUE);
	DrawTriangle(700, select_y, 670, select_y - 30, 670, select_y + 30, 0x000000, FALSE);
}