#pragma once
#include "define.h"
#include "AbstractScene.h"
#include "Player.h"
#include "Stage.h"
#include "Apple.h"


class GameMain :
    public AbstractScene
{
private:

    int TotalScore;
    Player* player; //プレイヤー
    Apple* apple;   //リンゴ 

    int mori_img;

public:
    //コンストラクタ
    GameMain();

    //デストラクタ
    ~GameMain();

    //描画以外の更新を実行
    AbstractScene* Update() override;

    //描画に関することを実装
    void Draw() const override;
};

