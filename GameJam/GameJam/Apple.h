#pragma once
#include "BoxCollider.h"

class Apple :public BoxCollider
{
private:
	
	int A_Count;	//同時にスポーンしているりんごの数

	struct AppleData {
		int flg;			//使用フラグ
		int type;			//タイプ
		int img;			//画像
		float x, y, w, h;		//座標、幅、高さ
		float speed;		//移動速度
		int point;			//スコア加算ポイント
	};

	//ランキングデータの変数宣言
	struct AppleData	g_Apple[10];
	struct AppleData	g_AppleRd = { TRUE,0,0,0,-50,63,120,1,100 };
	struct AppleData	g_AppleBr = { TRUE,1,0,100,-50,63,120,2,200 };
	struct AppleData	g_AppleGr = { TRUE,2,0,0,-50,63,120,3.5,500 };
	struct AppleData	g_AppleTx = { TRUE,3,0,0,-50,63,120,0.5,-750 };
public:
	//コンストラクタ
	Apple();

	//デストラクタ
	~Apple();

	//更新
	void UpDate();

	//描画
	void Draw() const;

	int Spawn();
	int Delete();
};



