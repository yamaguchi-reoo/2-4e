#pragma once
#include "BoxCollider.h"

#define MAX_APPLE	 10	//リンゴスポーン上限
#define APPLE_SIZE	100//リンゴの大きさ

class Apple :public BoxCollider
{
private:
	
	int A_Count;	//同時にスポーンしているりんごの数

	int frame;	//フレーム
	int Count;	//一度にスポーンしたリンゴの計測

	struct AppleData {
		int flg;			//使用フラグ
		int type;			//タイプ
		int img;			//画像
		float x, y;		//座標、幅、高さ
		float speed;		//移動速度
		int point;			//スコア加算ポイント
	};

	//ランキングデータの変数宣言
	struct AppleData	g_Apple[MAX_APPLE] = { FALSE };

	//imgに仮で色データをいれている
	struct AppleData	g_AppleRd = { TRUE,0,0xff0000,0	 ,0, 1.0,  100 };
	struct AppleData	g_AppleBr = { TRUE,0,0x0000ff,100,0, 2.0,  200 };
	struct AppleData	g_AppleGr = { TRUE,0,0x00ff00,0  ,0, 3.5,  500 };
	struct AppleData	g_AppleTx = { TRUE,1,0xff00ff,0  ,0, 0.5, -750 };

public:
	//コンストラクタ
	Apple();

	//デストラクタ
	~Apple();

	//更新
	void UpDate();

	//描画
	void Draw() const;

	void Spawn();

};



