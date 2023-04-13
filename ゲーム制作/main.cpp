#include  "DxLib.h"
#define    _USE_MATH_DEFINES
#include  <math.h>

/*****************************************
*  変数の宣言（グローバル変数）
*****************************************/

int gOldKey;				//　前回の入力キー
int gNowKey;				//　今回の入力キー
int gKeyFlg;				//　入力キー情報

int gGameState = 0;			//　ゲームモード

/*****************************************
*  関数のプロトタイプ宣言
*****************************************/



/*****************************************
* プログラム開始
*****************************************/

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR IpCmdLine, _In_ int nCmdShow)
{
	// タイトルを設定
	SetMainWindowText("りんごごりら");

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

		// テスト表示
		DrawString(250, 200, "りんご", 0xffffff, 0x000000);

		// 裏画面の内容を表画面に反映する
		ScreenFlip();
	}

	// DX ライブラリ使用の終了処理
	DxLib_End();

	// プログラムの終了
	return 0;
}