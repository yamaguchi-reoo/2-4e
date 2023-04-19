#include "DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include "Apple.h"
#include "define.h"

Apple::Apple() 
{
	a_Count = 0;
	frame = 0;
}
Apple::~Apple()
{

}
void Apple::UpDate()
{
	Count = 0;
	for (int i = 0; i < MAX_APPLE; i++)
	{
		if (g_Apple[i].flg == TRUE)
		{
			g_Apple[i].y += g_Apple[i].speed;
			g_Apple[i].span += 1;
			Count++;
		}
		if (g_Apple[i].y >= 500)
		{
			g_Apple[i] = g_AppleNl;
			a_Count--;
		}
	}
	if (++frame >= 25)
	{
		Spawn();
		frame = 0;
	}
}
void Apple::Draw() const
{
	for (int i = 0; i < MAX_APPLE; i++)
	{
		if (g_Apple[i].flg == TRUE)
		{
			DrawCircle(g_Apple[i].x+APPLE_SIZE/2, g_Apple[i].y+APPLE_SIZE/2, APPLE_SIZE/2, g_Apple[i].img, TRUE);
			DrawBox(g_Apple[i].x, g_Apple[i].y, g_Apple[i].x + APPLE_SIZE, g_Apple[i].y + APPLE_SIZE, 0x000000, FALSE);
			DrawFormatString(10,30,0x000000,"%d",a_Count);
		}
	}
}

void Apple::Spawn()
{
	Count = 0;

	for (int i = 0; i < MAX_APPLE; i++)
	{
		if (g_Apple[i].flg == FALSE && Count < ceil(MAX_APPLE - a_Count) / 2)
		{
			int SpawnPos;
			Count++;	//一度にスポーンさせたりんごを計測する
			switch(Rand())
			{
			case 0:
				g_Apple[i] = g_AppleRd;
				g_Apple[i].x = GetRand(6)*150;
				break;
			case 1:
				g_Apple[i] = g_AppleBr;
				g_Apple[i].x = GetRand(6) * 150;
				break;
			case 2:
				g_Apple[i] = g_AppleGr;
				g_Apple[i].x = GetRand(6) * 150;
				break;
			case 3:
				g_Apple[i] = g_AppleTx;
				g_Apple[i].x = GetRand(6) * 150;
				break;
			default:	//想定していない数値が入ると白色に
				g_Apple[i] = g_AppleRd;
				g_Apple[i].img = 0xffffff;
				g_Apple[i].x = GetRand(6) * 150;
				break;
			}
		}
	}
	a_Count += Count;	//一回で出したリンゴの個数を合計に足す
}

int Apple::Rand()
{
	int rand = GetRand(19);
	//randが0～11なら赤色（６０％）
	if (rand >= 0 && rand <= 11)
	{
		return 0;
	}
	//randが12～16なら青色（２５％）
	else if (rand > 11 && rand <= 16)
	{
		return 1;
	}
	//randが17～18なら金色（１０％）
	else if (rand > 16 && rand <= 18)
	{
		return 2;
	}
	//randが19なら紫色（毒）（５％）
	else if (rand == 19)
	{
		return 3;
	}
	//randが0～19以外の数値なら白色（想定外）
	else
	{
		return 4;
	}
}