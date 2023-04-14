#pragma once
#include "define.h"
#include "AbstractScene.h"
#include "Player.h"
#include "Trampoline.h"
#include "Wall.h"
#include "Stage.h"


class GameMain :
    public AbstractScene
{
private:

    int Level; //レベル
    int Score[MAX_LEVEL]; //各ステージのスコア
    int TotalScore;
    Trampoline* trampoline; //トランポリン
    Player* player; //プレイヤー
    Wall* wall; //壁
    Stage* stage; //ステージ

    int GameBGM;    //BGM
    int ScoreFont[2]; //スコア用のフォント
    int ClimbingTimer;      //時間停止用
    int MissTimer;
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

