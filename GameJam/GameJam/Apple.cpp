#include "DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include "Apple.h"
#include "define.h"

Apple::Apple() 
{
	A_Count = 0;
}
Apple::~Apple()
{

}
void Apple::UpDate()
{
	Spawn();
	for (int i = 0; i <= MAX_APPLE; i++)
	{
		if (g_Apple[i].flg == TRUE)
		{
			g_Apple[i].y += g_Apple[i].speed;
		}
	}

}
void Apple::Draw() const
{
	for (int i = 0; i <= MAX_APPLE; i++)
	{
		if (g_Apple[i].flg == TRUE)
		{
			DrawBox(g_Apple[i].x, g_Apple[i].y, g_Apple[i].x+50,g_Apple[i].y+50, 0x0000ff, TRUE);
		}
	}
}

int Apple::Spawn()
{
	for (int i = 0; i <= MAX_APPLE; i++)
	{
		if (g_Apple[i].flg == FALSE) 
		{
			A_Count++;
			int rand = GetRand(3);

		switch(rand){
			case 0:
				g_Apple[i] = g_AppleRd;
				//g_Apple[i].img = 
				g_Apple[i].x = GetRand(1000);
				break;
			case 1:
					g_Apple[i] = g_AppleBr;
				//g_Apple[i].img = 
				g_Apple[i].x = 300;
				break;
			case 2:
				g_Apple[i] = g_AppleGr;
				//g_Apple[i].img = 
				g_Apple[i].x = 300;
				break;
			case 3:
				g_Apple[i] = g_AppleTx;
				//g_Apple[i].img = 
					g_Apple[i].x = 300;
				break;
			default:
				break;
				}
		return TRUE;
		}
	}
	return FALSE;
}

int Apple::Delete()
{
	return 0;
}

