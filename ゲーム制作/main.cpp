#include  "DxLib.h"
#define    _USE_MATH_DEFINES
#include  <math.h>

/*****************************************
*列挙型の宣言
******************************************/

typedef enum GAME {
	GAME_TITLE,
	GAME_MAIN,
	GAME_INIT,
	GAME_PAUSE,
	GAME_HELP,
	GAME_RESULT,
	GAME_NAME,
	GAME_RANKING
}GAME_MODE;

/***********************************
*　定数の宣言
************************************/

/*****************************************
*  変数の宣言（グローバル変数）
*****************************************/

int gOldKey;				//　前回の入力キー
int gNowKey;				//　今回の入力キー
int gKeyFlg;				//　入力キー情報

int gGameState = 0;			//　ゲームモード

GAME_MODE gGameMode = GAME_TITLE;	//ゲームモード

int gPlayerX = 100;		//プレイヤーのX座標
int gPlayerY = 100;		//プレイヤーのY座標

/*****************************************
*  関数のプロトタイプ宣言
*****************************************/

void GameInit(void);		//ゲーム初期化処理
void GameMain(void);		//ゲームメイン処理
void DrawTitle(void);		//ゲームタイトル処理
void PlayerControl(void);	//プレイヤー移動処理
void AppleControl(void);	//リンゴ移動処理

/*****************************************
* プログラム開始
*****************************************/

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR IpCmdLine, _In_ int nCmdShow)
{
	// タイトルを設定
	SetMainWindowText("りんご");

	// ウィンドウモードで起動
	ChangeWindowMode(TRUE);

	// ウィンドウサイズ変更
	SetWindowSizeChangeEnableFlag(TRUE, FALSE);

	// ウィンドウサイズを1280x720に変更
	SetGraphMode(1280, 720, 32);

	// DX ライブラリの初期化処理
	if (DxLib_Init() == -1)return -1;

	// 描画先画面を裏にする（ダブルバッファリング）
	SetDrawScreen(DX_SCREEN_BACK);

	// ゲームループ
	while (ProcessMessage() == 0 && gGameState != 99 && !(gKeyFlg & PAD_INPUT_START))
	{
		// 入力キー取得
		gOldKey = gNowKey;
		gNowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		gKeyFlg = gNowKey & ~gOldKey;

		// 画面の初期化
		ClearDrawScreen();

		switch (gGameMode) {
		case GAME_TITLE:
			DrawTitle();
			break;
		case GAME_INIT:
			GameInit();
			break;
		case GAME_MAIN:
			GameMain();
			break;

		}

		// 裏画面の内容を表画面に反映する
		ScreenFlip();
	}

	// DX ライブラリ使用の終了処理
	DxLib_End();

	// プログラムの終了
	return 0;
}

/***********************************
*　タイトル画面
************************************/
void DrawTitle(void)
{
	// テスト表示
	DrawString(250, 200, "タイトル Aボタンでゲームメイン", 0xffffff, 0x000000);
	//ゲームモードを切り替える
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_A) == 0) {
			
	}else{
		gGameMode = GAME_INIT;
	}
}

/***********************************
*　ゲーム初期化
************************************/
void GameInit(void)
{
	
	gGameMode = GAME_MAIN;
}

/***********************************
*　ゲームメイン化処理
************************************/
void GameMain(void)
{
	// テスト表示
	DrawString(250, 200, "ゲーム画面", 0xffffff, 0x000000);

	//プレイヤー移動
	PlayerControl();

}
/***********************************
*　ゲームメイン化処理
************************************/
void PlayerControl(void)
{
	if (gNowKey & PAD_INPUT_LEFT)	gPlayerX -= 1;
	if (gNowKey & PAD_INPUT_RIGHT)	gPlayerX += 1;
	DrawBox(gPlayerX, gPlayerY, gPlayerX + 100, gPlayerY + 100, 0x00ff00, true);
}