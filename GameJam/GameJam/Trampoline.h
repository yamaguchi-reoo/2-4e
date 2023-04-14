#pragma once
#include "Element.h"

#define EXTEND_TIME 20

enum class TRAMPOLINE_STATE
{
    IDOL = 0,   //通常状態
    PRESS,      //踏まれている状態
    EXTEND      //伸びている状態
};

class Trampoline :
    public Element
{
private:
    int Images[3]; //画像
    TRAMPOLINE_STATE state; //状態
    int ExtendTime; //伸びている時間
public:
    //コンストラクタ
    Trampoline();

    //デストラクタ
    ~Trampoline();

    //描画以外の更新を実行
    void UpDate() override;

    //プレイヤーとの当たり判定
    void GetPoint();

    //伸びてた瞬間の処理
    void Extend();

    //描画に関することを実装
    void Draw() const override;

    //ステートの取得
    TRAMPOLINE_STATE GetState() { return state; }
};

