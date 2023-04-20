#pragma once
#include "BoxCollider.h"



class Element:public BoxCollider
{
protected:
	int Speed;	//スピード

public:
	//コンストラクタ
	Element()
	{
		Speed = 0;
	}

	//デストラクタ
	~Element()
	{

	}

	//描画以外の更新を実行
	virtual void UpDate() = 0;
	 
	//描画に関することを実装
	virtual void Draw() const = 0;
};
