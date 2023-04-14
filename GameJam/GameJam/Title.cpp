#include "DxLib.h"
#include "Title.h"
#include "GameMain.h"
#include "DrawRanking.h"
#include"PadInput.h"
#include"Help.h"
#include"Credit.h"
#include"End.h"

//�^�C�g�����j���[
enum class TITLE_MENU 
{
	GAME_START = 0,
	GAME_RANKING,
    GAME_HELP,
	GAME_CREDIT,
	GAME_END
};

Title::Title()
{
	//������
	Select = 0;

	MenuFont = CreateFontToHandle("HeadLine", 80, 8, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);

	//�摜�̓ǂݍ���
	if ((TitleImage = LoadGraph("Resource/Images/Title.png")) == -1)
	{
		throw "Resource/Images/Title.png";
	}

	//BGM�̓ǂݍ���
	if ((TitleBGM = LoadSoundMem("Resource/sounds/BGM/Sick_Red_Girl.wav")) == -1)
	{
		throw "Resource/sounds/BGM/Sick_Red_Girl.wav";
	}
	//BGM�̉��ʕύX
	ChangeVolumeSoundMem(125, TitleBGM);

	//SE�̓ǂݍ���
	if ((MenuSE = LoadSoundMem("Resource/sounds/SE/Select.wav")) == -1) //�I��SE
	{
		throw "Resource/sounds/SE/Select.wav";
	}
	if ((DecisionSE = LoadSoundMem("Resource/sounds/SE/Decision.wav")) == -1) //����{�^��
	{
		throw "Resource/sounds/SE/Decision.wav";
	}
	//SE�̉��ʕύX
	ChangeVolumeSoundMem(200, MenuSE);
	ChangeVolumeSoundMem(200, DecisionSE);

	//�^�C�g��BGM���X�^�[�g
	if (CheckSoundMem(TitleBGM) == 0) {
		PlaySoundMem(TitleBGM, DX_PLAYTYPE_BACK, TRUE);
	}
}

Title::~Title()
{
	//�t�H���g�̍폜
	DeleteFontToHandle(MenuFont);

	//�T�E���h�̍폜
	DeleteSoundMem(TitleBGM);
	DeleteSoundMem(MenuSE);
	DeleteSoundMem(DecisionSE);
}

//�X�V
AbstractScene* Title::Update()
{
	

	//�\���L�[������
	if(PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP))
	{
		PlaySoundMem(MenuSE, DX_PLAYTYPE_BACK);
		Select--;
		if (Select < 0)Select = 4;
	}
	//�\���L�[������
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN))
	{
		PlaySoundMem(MenuSE, DX_PLAYTYPE_BACK);
		Select++;
		if (Select > 4)Select = 0;

	}

	{
		//���̓L�[���
		OldKey = NowKey;
		NowKey = PAD_INPUT::GetLStick().ThumbY;
		KeyFlg = NowKey & ~OldKey;

		//L�X�e�B�b�N�����
		if (KeyFlg & NowKey/(-20923) < 0)
		{
			PlaySoundMem(MenuSE, DX_PLAYTYPE_BACK);
			Select--;
			if (Select < 0)Select = 4;
		}

		//L�X�e�B�b�N������
		if (KeyFlg & NowKey/ 20923 < 0)
		{
			PlaySoundMem(MenuSE, DX_PLAYTYPE_BACK);
			Select++;
			if (Select > 4)Select = 0;
		}

	}
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
	{
		PlaySoundMem(DecisionSE, DX_PLAYTYPE_BACK);
		switch(static_cast<TITLE_MENU>(Select))
		{
			//�Q�[����ʂ�
		case TITLE_MENU::GAME_START:
			StopSoundMem(TitleBGM);
			return new GameMain();
			break;
			//�����L���O��ʂ�
		case TITLE_MENU::GAME_RANKING:
			StopSoundMem(TitleBGM);
			return new DrawRanking();
			break;
			//�w���v��ʂ�
		case TITLE_MENU::GAME_HELP:
			StopSoundMem(TitleBGM);
			return new Help();
			break;
			//�N���W�b�g��ʂ�
		case TITLE_MENU::GAME_CREDIT:
			StopSoundMem(TitleBGM);
			return new Credit();
			break;
			//�G���h��ʂ�
		case TITLE_MENU::GAME_END:
			StopSoundMem(TitleBGM);
			return new End();
			break;
		default:
			break;
		}
	}
	
	return this;
}

//�摜�`��
void Title::Draw()const
{
	DrawGraph(0, 0, TitleImage, TRUE);

	// �X�e�[�W�̕`��
	SetFontSize(64);                             //�T�C�Y��64�ɕύX
	SetFontThickness(8);                         //������8�ɕύX

	//���j���[�̕`��
	DrawStringToHandle(730, 240, "GameStart",0xff00ff,MenuFont);
	DrawStringToHandle(730, 320, "GameRanking", 0xff00ff, MenuFont);
	DrawStringToHandle(730, 400, "GameHelp", 0xff00ff, MenuFont);
	DrawStringToHandle(730, 480, "GameCredit", 0xff00ff, MenuFont);
	DrawStringToHandle(730, 560, "GameEnd", 0xff00ff, MenuFont);

	//�J�[�\���̕`��
	int select_y = 280 + Select * 80;
	DrawTriangle(700, select_y, 670, select_y - 30, 670, select_y + 30, 0xffd700, TRUE);
	DrawTriangle(700, select_y, 670, select_y - 30, 670, select_y + 30, 0x000000, FALSE);
}