#include"DxLib.h"
#include"Score.h"
#include"Apple.h"

Score::Score()
{
	gAppleCount[0] = 0;
	gAppleCount[1] = 0;
	gAppleCount[2] = 0;


	if ((gAppleImg[0] = LoadGraph("Resource/Images/apple.png")) == -1)
	{
		throw "Resource/Images/apple.png";
	}
	if ((gAppleImg[1] = LoadGraph("Resource/Images/apple.png")) == -1)
	{
		throw "Resource/Images/apple.png";
	}
	if ((gAppleImg[2] = LoadGraph("Resource/Images/apple.png")) == -1)
	{
		throw "Resource/Images/apple.png";
	}
}
Score::~Score()
{

}
void Score::UpDate()
{
	for (int i = 0; i < MAX_APPLE; i++)
	{

	}
	return;
}
void Score::Draw() const
{
	DrawFormatString(1070, 390, 0xffffff, "%d", gAppleCount[0]);
	DrawFormatString(1130, 390, 0xffffff, "%d", gAppleCount[1]);
	DrawFormatString(1190, 390, 0xffffff, "%d", gAppleCount[2]);


	DrawBox(1000, 0, 1280, 720, 0xffffff, TRUE);
	DrawRotaGraph(1080, 370, 0.5f, 0, gAppleImg[0], TRUE, FALSE);
	DrawRotaGraph(1140, 370, 0.5f, 0, gAppleImg[1], TRUE, FALSE);
	DrawRotaGraph(1200, 370, 0.5f, 0, gAppleImg[2], TRUE, FALSE);
}
