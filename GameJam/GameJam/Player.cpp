#include "Player.h"
#include"PadInput.h"
#include"math.h"

Player::Player()
{

	if (LoadDivGraph("Resource/Images/Player/Dash.png", 6, 6, 1, 160, 160, ImagesDash) == -1)
	{
		throw "Resource/Images/Player/Dash.png";
	}
	if (LoadDivGraph("Resource/Images/Player/Walk.png", 8, 8, 1, 160, 160, ImagesWalk) == -1)
	{
		throw "Resource/Images/Player/Walk.png";
	}
	if (LoadDivGraph("Resource/Images/Player/Jump.png", 11, 11, 1, 160, 160, ImagesJump) == -1)
	{
		throw "Resource/Images/Player/Jump.png";
	}
	if ((ImageStand = LoadGraph("Resource/Images/Player/characterStand.png")) == -1)
	{
		throw "Resource/Images/Player/characterStand.png";
	}
	if ((ImageMiss = LoadGraph("Resource/Images/Player/JumpMiss01.png")) == -1)
	{
		throw "Resource/Images/Player/JumpMiss01.png";
	}

	//SEの読み込み
	if ((WalkSE = LoadSoundMem("Resource/sounds/SE/Player/Walk.wav")) == -1)
	{
		throw "Resource/sounds/SE/Player/Walk.wav";
	}
	if ((DashSE = LoadSoundMem("Resource/sounds/SE/Player/Run.wav")) == -1)
	{
		throw "Resource/sounds/SE/Player/Run.wav";
	}
	if ((JumpSE = LoadSoundMem("Resource/sounds/SE/Player/Jump.wav")) == -1)
	{
		throw "Resource/sounds/SE/Player/Jump.wav";
	}
	if ((JumpEndSE = LoadSoundMem("Resource/sounds/SE/Player/Landing.wav")) == -1)
	{
		throw "Resource/sounds/SE/Player/Landing.wav";
	}
	if ((MissSE = LoadSoundMem("Resource/sounds/SE/Player/Miss.wav")) == -1)
	{
		throw "Resource/sounds/SE/Player/Miss.wav";
	}

	//初期化
	TrunFlag = false;
	ChageFlag = false;
	StickRollFlag = false;
	location.x = 100;
	location.y = 500;
	erea.width = 50;
	erea.height = 100;
	erea.width_rate = 0.6;
	erea.height_rate = 0.5;
	PlayerState = PLAYER_STATE::IDOL;
	Speed = 0;
	JumpPower = 0;
	JumpChage = 0;
	AnimTimer = 0;
	AnimInterval = 0;
	AnimType = 0;
	ClimbingTimer = 0;
	Image = ImageStand;

	

	//フォントの追加
	GuideFont = CreateFontToHandle("Guide", 20, 8, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
}

Player::~Player()
{
	//SEの削除
	DeleteSoundMem(WalkSE);
	DeleteSoundMem(DashSE);
	DeleteSoundMem(JumpSE);
	DeleteSoundMem(JumpEndSE);
	DeleteSoundMem(MissSE);

	//フォントの削除
	DeleteFontToHandle(GuideFont);
}

void Player::UpDate()
{
	//移動
	if (PlayerState != PLAYER_STATE::JUMP_MISS)
	{
		if (NotJump() && (PlayerState != PLAYER_STATE::JUMP_CHARGE))
		{
			if (PAD_INPUT::GetLStick().ThumbX < -10000 || PAD_INPUT::GetLStick().ThumbX > 10000)
			{
				if (PlayerState == PLAYER_STATE::CLIMBING)
				{
					if (!StickRollFlag)
					{
						Speed = 1;
						StickRollFlag = true;
					}
				}
				else
				{
					if (PAD_INPUT::OnPressed(XINPUT_BUTTON_X) || PAD_INPUT::OnPressed(XINPUT_BUTTON_Y))
					{
						if (PlayerState != PLAYER_STATE::DASH)
						{
							PlayerState = PLAYER_STATE::DASH;
							AnimInterval = ANIMATION_INTERVAL;
							AnimTimer = 0;
							AnimType = 0;
							if (PAD_INPUT::GetLStick().ThumbX < -10000)
							{
								Speed = -DASH_SPEED;
								TrunFlag = true;
							}
							else
							{
								Speed = DASH_SPEED;
								TrunFlag = false;
							}
						}
					}
					else if ((PlayerState != PLAYER_STATE::WALK))
					{
						PlayerState = PLAYER_STATE::WALK;
						AnimInterval = ANIMATION_INTERVAL;
						AnimTimer = 0;
						AnimType = 0;
						if (PAD_INPUT::GetLStick().ThumbX < -10000)
						{
							Speed = -WALK_SPEED;
							TrunFlag = true;
						}
						else
						{
							Speed = WALK_SPEED;
							TrunFlag = false;
						}
					}
					else {}
				}
			}
			else if (PlayerState == PLAYER_STATE::CLIMBING)
			{
				Speed = 0;
				StickRollFlag = false;
			}
			else if ((PlayerState != PLAYER_STATE::IDOL) && NotJump())
			{
				AnimTimer = 0;
				AnimType = 0;
				PlayerState = PLAYER_STATE::IDOL;
				Image = ImageStand;
				Speed = 0;
			}
			else {}
		}

		//ジャンプ
		if ((PAD_INPUT::OnButton(XINPUT_BUTTON_A) || PAD_INPUT::OnButton(XINPUT_BUTTON_B)) && 
			NotJump() && PlayerState != PLAYER_STATE::CLIMBING)
		{
			PlayerState = PLAYER_STATE::JUMP_START;
			JumpPower = JUMP_POWER * (1 + (static_cast<float>(JumpChage) / MAX_CHARGE));
			if (ChageFlag)
			{
				Speed = Speed * (2 + (static_cast<float>(JumpChage) / MAX_CHARGE));
			}
			AnimInterval = ANIMATION_INTERVAL;
			AnimTimer = 0;
			AnimType = 0;
		}
	}
	switch (PlayerState)
	{
	case PLAYER_STATE::IDOL:
		if (CheckSoundMem(WalkSE) == 1)
		{
			StopSoundMem(WalkSE);
		}
		if (CheckSoundMem(DashSE) == 1)
		{
			StopSoundMem(DashSE);
		}
		break;
	case PLAYER_STATE::WALK:
		if (CheckSoundMem(DashSE) == 1)
		{
			StopSoundMem(DashSE);
		}
		if (CheckSoundMem(WalkSE) == 0)
		{
			PlaySoundMem(WalkSE, DX_PLAYTYPE_BACK, TRUE);
		}
		WalkAnimation();
		location.x += Speed;
		break;
	case PLAYER_STATE::DASH:
		if (CheckSoundMem(WalkSE) == 1)
		{
			StopSoundMem(WalkSE);
		}
		if (CheckSoundMem(DashSE) == 0)
		{
			PlaySoundMem(DashSE, DX_PLAYTYPE_BACK, TRUE);
		}
		DashAnimation();
		location.x += Speed;
		break;
	case PLAYER_STATE::JUMP_START:
		if (CheckSoundMem(WalkSE) == 1)
		{
			StopSoundMem(WalkSE);
		}
		if (CheckSoundMem(DashSE) == 1)
		{
			StopSoundMem(DashSE);
		}
		if (JumpStartAnimation())
		{
			if (CheckSoundMem(JumpSE) == 0)
			{
				PlaySoundMem(JumpSE, DX_PLAYTYPE_BACK, TRUE);
			}
			PlayerState = PLAYER_STATE::JUMP;
			JumpChage = 0;
			AnimTimer = 0;
			AnimType = 0;
		}
		break;
	case PLAYER_STATE::JUMP:
		JumpPower -= 2;
		JumpAnimaiton();
		if (500 < location.y)
		{
			PlayerState = PLAYER_STATE::JUMP_END;
			AnimTimer = 0;
			AnimType = 0;
			JumpPower = 0;
			location.y = 500;
		}
		location.x += Speed;
		location.y -= JumpPower;
		break;
	case PLAYER_STATE::JUMP_END:
		if (CheckSoundMem(JumpSE) == 1)
		{
			StopSoundMem(JumpSE);
		}
		if (CheckSoundMem(JumpEndSE) == 0)
		{
			PlaySoundMem(JumpEndSE, DX_PLAYTYPE_BACK, TRUE);
		}
		if (JumpEndAnimation())
		{
			PlayerState = PLAYER_STATE::IDOL;
			AnimTimer = 0;
			AnimType = 0;
		}
		break;
	case PLAYER_STATE::JUMP_CHARGE:
		if (CheckSoundMem(WalkSE) == 1)
		{
			StopSoundMem(WalkSE);
		}
		if (CheckSoundMem(DashSE) == 1)
		{
			StopSoundMem(DashSE);
		}
		JumpChage = (++JumpChage % MAX_CHARGE) + 1;
		break;
	case PLAYER_STATE::JUMP_MISS:
		if (CheckSoundMem(MissSE) == 0)
		{
			PlaySoundMem(MissSE, DX_PLAYTYPE_BACK, TRUE);
		}
		break;
	case PLAYER_STATE::CLIMBING:
		location.y -= Speed;
		Speed = 0;
		break;
	default:
		break;
	}

	if (location.x < erea.width * erea.width_rate)
	{
		location.x = erea.width * erea.width_rate;
	}
	if (location.y < erea.height * erea.height_rate)
	{
		location.y = erea.height * erea.height_rate;
	}
}



bool Player::NotJump()
{
	bool ret = true;
	if ((PlayerState == PLAYER_STATE::JUMP) || (PlayerState == PLAYER_STATE::JUMP_START) || (PlayerState == PLAYER_STATE::JUMP_END))
	{
		ret = false;
	}
	return ret;
}

void Player::DashAnimation()
{
	if (AnimTimer++ % AnimInterval == 0)
	{
		Image = ImagesDash[AnimType++ % 6];
	}
}
void Player::WalkAnimation()
{
	if (AnimTimer++ % AnimInterval == 0)
	{
		Image = ImagesWalk[AnimType++ % 8];
	}
}
bool Player::JumpStartAnimation()
{
	bool ret = false;
	if (AnimTimer++ % AnimInterval == 0)
	{
		Image = ImagesJump[AnimType++];
	}
	if (AnimType > 3)
	{
		ret = true;
	}
	return ret;
}

void Player::JumpAnimaiton()
{
	if (AnimTimer++ % AnimInterval == 0)
	{
		Image = ImagesJump[3 + (AnimType++ % 8)];
	}
}
bool Player::JumpEndAnimation()
{
	bool ret = false;
	if (AnimTimer++ % AnimInterval == 0)
	{
		AnimType++;
		if (AnimType == 0)
		{
			Image = ImagesJump[0];
		}
		else if (AnimType == 1)
		{
			Image = ImagesWalk[2];
		}
		else
		{
			Image = ImageStand;
			ret = true;
		}
	}
	return ret;
}

void Player::Draw() const
{	
	DrawRotaGraphF(location.x, location.y, 1.0, 0, Image, TRUE,TrunFlag);
	if (PlayerState == PLAYER_STATE::JUMP_CHARGE)
	{
		DrawBox(location.x + 100, location.y - 50, location.x + 150, location.y + 50, 0x000000, TRUE);
		DrawBox(location.x + 105, location.y + 50 - JumpChage, location.x + 145, location.y + 50, 0xFFFFFF, TRUE);

		DrawStringToHandle(location.x + 70, location.y + 50, "Press A or B", 0x659ad2,GuideFont);
	}

	int box_color;
	int string_color;
	if (PlayerState == PLAYER_STATE::CLIMBING)
	{
		DrawStringToHandle(location.x - 80, location.y + 80, "LeftStick←→", 0xf8a7a0, GuideFont);
	}
}

void Player::Reset()
{
	TrunFlag = false;
	ChageFlag = false;
	location.x = 100;
	location.y = 500;
	Speed = 0;
	JumpPower = 0;
	JumpChage = 0;
	AnimTimer = 0;
	AnimInterval = 0;
	AnimType = 0;
	ClimbingTimer = 0;
	PlayerState = PLAYER_STATE::IDOL;
	Image = ImageStand;

}

//トランポリンに触れたら実行される
void Player::HitTrampoline()
{
	if (!ChageFlag)
	{
		PlayerState = PLAYER_STATE::JUMP_CHARGE;
		Image = ImagesJump[0];
		ChageFlag = true;
	}
	
}

void Player::LeaveTrampoline()
{
	if (ChageFlag)
	{
		ChageFlag = false;
	}
}

void Player::HitWall()
{
	PlayerState = PLAYER_STATE::CLIMBING;
	Image = ImagesJump[10];
}

void Player::MissJump()
{
	Image = ImageMiss;
	PlayerState = PLAYER_STATE::JUMP_MISS;
}
