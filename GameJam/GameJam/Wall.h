#pragma once
#include "Element.h"

#define BLOCK_NUM 23
#define BLOCK_SIZE 40
#define BASE_SPEED 4 
#define START_TIME 30

enum class BLOCK_COLOR
{
    BLACK = 0,
    BLUE,
    GREEN,
    YELLOW,
    ORANGE,
    RED
};

class Wall :
    public Element
{
private:
    int Level; //レベル
    int Block[BLOCK_NUM]; //ブロック
    int StartPoint; //スタート地点
    int EndPoint; //エンド地点
    int WaitTime; //移動開始するまでの時間
    int PointFont;  //スコア表示用のフォント
    const int POINT[6]{ 10,20,30,40,50,100 };   //得点
    const float MOVE_POINT[4][2] = { {1000,0,},{1000,-200},{1200,0}, {1200,-200} }; //目的地([0]=x座標,[1]=y座標)
public:
    //コンストラクタ
    Wall();

    //デストラクタ
    ~Wall();

    //描画以外の更新を実行
    void UpDate() override;

    //移動処理
    void Move();

    //描画に関することを実装
    void Draw() const override;

    //ポイントの取得
    int GetPoint(float player_y);

    //レベルの設定
    void NextStage(int level);
};

