#include "DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include "Wall.h"


Wall::Wall()
{
	FILE* fp = NULL;

	//ファイルオープン
	if (fopen_s(&fp, "Resource/Block/BlockData.csv", "r") != NULL)
	{
		throw "Resource/Block/BlockData.csv";
	}

	//ブロックデータ配分列データを読み込む
	for (int i = 0; i < BLOCK_NUM; i++) {
		fscanf_s(fp, "%1d", &Block[i]);
	}
	//座標の設定
	location.x = 1000;
	location.y = 0;

	//当たり判定の設定
	erea.height = BLOCK_SIZE * BLOCK_NUM;
	erea.width = BLOCK_SIZE * 2;
	erea.height_rate = 0;
	erea.width_rate = 0;

	//初期化
	Level = 0;
	StartPoint = 0;
	EndPoint = 0;
	WaitTime = START_TIME;
	PointFont = CreateFontToHandle("Point", 32, 8, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);

}

Wall::~Wall()
{
	DeleteFontToHandle(PointFont);
}

void Wall::UpDate()
{

	if (1 < Level)
	{
		if ((floorf(location.x) == MOVE_POINT[EndPoint][0]) && (floorf(location.y) == MOVE_POINT[EndPoint][1]))//目的についた
		{
			if (Level < 4)
			{
				int w = StartPoint;
				StartPoint = EndPoint;
				EndPoint = w;
			}
			else
			{
				StartPoint = ++StartPoint % 4;
				EndPoint = ++EndPoint % 4;
			}
			if (WaitTime < 0)
			{
				WaitTime = START_TIME;
			}
		}
		if (--WaitTime < 0)	
		{
			Move();
		}
	}

}

void Wall::Move()
{
	float rad; //角度
	//スタート地点とゴール地点の角度の計算
	rad = atan2f(MOVE_POINT[EndPoint][1] - MOVE_POINT[StartPoint][1], MOVE_POINT[EndPoint][0] - MOVE_POINT[StartPoint][0]);

	location.x += static_cast<int>(BASE_SPEED * cosf(rad));
	location.y += static_cast<int>(BASE_SPEED * sinf(rad));
}

int Wall::GetPoint(float player_y)
{
	int index = 0;
	//プレイヤーが触った位置の特定
	index = (player_y + fabs(location.y))/ BLOCK_SIZE;

	return POINT[Block[index]];
}

void Wall::NextStage(int level)
{
	if ((0 <= level) && (level < 5))
	{
		Level = level;
	}
	
	if (Level != 1)
	{
		location.x = MOVE_POINT[0][0];
		location.y = MOVE_POINT[0][1];

		if (Level == 2)
		{
			StartPoint = 0;
			EndPoint = 2;
		}
		else if (Level == 3)
		{
			StartPoint = 0;
			EndPoint = 1;

		}
		else if (Level == 4)
		{
			StartPoint = 0;
			EndPoint = 1;
		}
		else {}
	}
	else
	{
		location.x = MOVE_POINT[2][0];
		location.y = MOVE_POINT[2][1];
	}
	WaitTime = START_TIME;


}

void Wall::Draw() const
{
	int block_color = 0x000000;
	for (int i = 0; i < BLOCK_NUM; i++)
	{
		switch (static_cast<BLOCK_COLOR>(Block[i]))
		{
		case BLOCK_COLOR::BLACK:
			block_color = 0x000000;
			break;
		case BLOCK_COLOR::BLUE:
			block_color = 0x0000cc;
			break;
		case BLOCK_COLOR::GREEN:
			block_color = 0x00cc00;
			break;
		case BLOCK_COLOR::YELLOW:
			block_color = 0xcccc00;
			break;
		case BLOCK_COLOR::ORANGE:
			block_color = 0xf36c21;
			break;
		case BLOCK_COLOR::RED:
			block_color = 0xcc0000;
			break;
		default:
			break;
		}
		DrawBox(location.x, location.y + (BLOCK_SIZE * i),
			location.x + BLOCK_SIZE * 2, location.y + (BLOCK_SIZE * (i + 1)), block_color, TRUE);
	}

	//加点数の描画
	

	DrawFormatStringToHandle(location.x + 22, location.y + 600, 0xffffff, PointFont, "%d", POINT[0]);
	DrawFormatStringToHandle(location.x + 22, location.y + 420, 0xffffff, PointFont, "%d", POINT[1]);
	DrawFormatStringToHandle(location.x + 22, location.y + 280, 0xffffff, PointFont, "%d", POINT[2]);
	DrawFormatStringToHandle(location.x + 22, location.y + 165, 0xffffff, PointFont, "%d", POINT[3]);
	DrawFormatStringToHandle(location.x + 22, location.y + 62, 0xffffff, PointFont, "%d", POINT[4]);
	DrawFormatStringToHandle(location.x + 13, location.y, 0xffffff,PointFont, "%d", POINT[5]);

}