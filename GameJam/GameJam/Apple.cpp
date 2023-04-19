#include "DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include "Apple.h"
#include "define.h"

Apple::Apple() 
{
	A_Count = 0;
	frame = 0;
}
Apple::~Apple()
{

}
void Apple::UpDate()
{
	for (int i = 0; i <= MAX_APPLE; i++)
	{
		if (g_Apple[i].flg == TRUE)
		{
			g_Apple[i].y += g_Apple[i].speed;
		}
	}
	if (++frame % 25 == 0)
	{
		Spawn();
	}
}
void Apple::Draw() const
{
	for (int i = 0; i <= MAX_APPLE; i++)
	{
		if (g_Apple[i].flg == TRUE)
		{
			DrawBox(g_Apple[i].x, g_Apple[i].y, g_Apple[i].x + APPLE_SIZE, g_Apple[i].y + APPLE_SIZE, g_Apple[i].img, TRUE);
			DrawBox(g_Apple[i].x, g_Apple[i].y, g_Apple[i].x + APPLE_SIZE, g_Apple[i].y + APPLE_SIZE, 0x000000, FALSE);
		}
	}
}

void Apple::Spawn()
{
	for (int i = 0; i <= MAX_APPLE; i++)
	{
		if (g_Apple[i].flg == FALSE && Count <= ceil((MAX_APPLE - A_Count) / 2))
		{
			int rand = GetRand(4);
			Count++;
			switch(rand)
			{
			case 0:
				g_Apple[i] = g_AppleRd;
				g_Apple[i].x = GetRand(700);
				break;
			case 1:
				g_Apple[i] = g_AppleBr;
				g_Apple[i].x = GetRand(700);
				break;
			case 2:
				g_Apple[i] = g_AppleGr;
				g_Apple[i].x = GetRand(700);
				break;
			case 3:
				g_Apple[i] = g_AppleTx;
				g_Apple[i].x = GetRand(700);
				break;
			default:
				break;
			}
		}
	}
	A_Count += Count;
}

