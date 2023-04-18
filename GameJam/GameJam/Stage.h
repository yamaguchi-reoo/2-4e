#pragma once
class Stage
{
private:

	int StageImage;		//ステージ画像用変数
	int StageLane;		//レーン画像用変数

public:
	Stage();
	~Stage();

	void UpDate();			//更新

	void Draw() const;		//描画
};

