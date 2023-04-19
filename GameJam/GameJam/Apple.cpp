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
			Count++;	//��x�ɃX�|�[����������񂲂��v������
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
			default:	//�z�肵�Ă��Ȃ����l������Ɣ��F��
				g_Apple[i] = g_AppleRd;
				g_Apple[i].img = 0xffffff;
				g_Apple[i].x = GetRand(6) * 150;
				break;
			}
		}
	}
	a_Count += Count;	//���ŏo���������S�̌������v�ɑ���
}

int Apple::Rand()
{
	int rand = GetRand(19);
	//rand��0�`11�Ȃ�ԐF�i�U�O���j
	if (rand >= 0 && rand <= 11)
	{
		return 0;
	}
	//rand��12�`16�Ȃ�F�i�Q�T���j
	else if (rand > 11 && rand <= 16)
	{
		return 1;
	}
	//rand��17�`18�Ȃ���F�i�P�O���j
	else if (rand > 16 && rand <= 18)
	{
		return 2;
	}
	//rand��19�Ȃ率�F�i�Łj�i�T���j
	else if (rand == 19)
	{
		return 3;
	}
	//rand��0�`19�ȊO�̐��l�Ȃ甒�F�i�z��O�j
	else
	{
		return 4;
	}
}