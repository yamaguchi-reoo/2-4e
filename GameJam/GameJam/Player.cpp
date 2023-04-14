#include "Player.h"
#include"PadInput.h"
#include"math.h"

Player::Player()
{

	//ここでプレイヤー画像とSE読込

	

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
}

Player::~Player()
{
	
}

void Player::UpDate()
{
	//移動

	if (PAD_INPUT::GetLStick().ThumbX < -10000 || PAD_INPUT::GetLStick().ThumbX > 10000)
	{
		PlayerState = PLAYER_STATE::WALK;
		Speed = WALK_SPEED;
		location.x += PAD_INPUT::GetLStick().ThumbX / 1000;
	}
	else {}	
	
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


void Player::WalkAnimation()
{

}


void Player::Draw() const
{	
	DrawBox(location.x, location.y, location.x+100,location.y+100,0x00ff00,TRUE);
}

void Player::Reset()
{

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
