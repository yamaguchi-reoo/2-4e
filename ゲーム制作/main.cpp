#include  "DxLib.h"
#define    _USE_MATH_DEFINES
#include  <math.h>

/*****************************************
*�񋓌^�̐錾
******************************************/

typedef enum GAME {
	GAME_TITLE,
	GAME_MAIN,
	GAME_INIT,
	GAME_PAUSE,
	GAME_HELP,
	GAME_RESULT,
	GAME_NAME,
	GAME_RANKING
}GAME_MODE;

/***********************************
*�@�萔�̐錾
************************************/

/*****************************************
*  �ϐ��̐錾�i�O���[�o���ϐ��j
*****************************************/

int gOldKey;				//�@�O��̓��̓L�[
int gNowKey;				//�@����̓��̓L�[
int gKeyFlg;				//�@���̓L�[���

int gGameState = 0;			//�@�Q�[�����[�h

GAME_MODE gGameMode = GAME_TITLE;	//�Q�[�����[�h

int gPlayerX = 100;		//�v���C���[��X���W
int gPlayerY = 100;		//�v���C���[��Y���W

/*****************************************
*  �֐��̃v���g�^�C�v�錾
*****************************************/

void GameInit(void);		//�Q�[������������
void GameMain(void);		//�Q�[�����C������
void DrawTitle(void);		//�Q�[���^�C�g������
void PlayerControl(void);	//�v���C���[�ړ�����
void AppleControl(void);	//�����S�ړ�����

/*****************************************
* �v���O�����J�n
*****************************************/

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR IpCmdLine, _In_ int nCmdShow)
{
	// �^�C�g����ݒ�
	SetMainWindowText("���");

	// �E�B���h�E���[�h�ŋN��
	ChangeWindowMode(TRUE);

	// �E�B���h�E�T�C�Y�ύX
	SetWindowSizeChangeEnableFlag(TRUE, FALSE);

	// �E�B���h�E�T�C�Y��1280x720�ɕύX
	SetGraphMode(1280, 720, 32);

	// DX ���C�u�����̏���������
	if (DxLib_Init() == -1)return -1;

	// �`����ʂ𗠂ɂ���i�_�u���o�b�t�@�����O�j
	SetDrawScreen(DX_SCREEN_BACK);

	// �Q�[�����[�v
	while (ProcessMessage() == 0 && gGameState != 99 && !(gKeyFlg & PAD_INPUT_START))
	{
		// ���̓L�[�擾
		gOldKey = gNowKey;
		gNowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		gKeyFlg = gNowKey & ~gOldKey;

		// ��ʂ̏�����
		ClearDrawScreen();

		switch (gGameMode) {
		case GAME_TITLE:
			DrawTitle();
			break;
		case GAME_INIT:
			GameInit();
			break;
		case GAME_MAIN:
			GameMain();
			break;

		}

		// ����ʂ̓��e��\��ʂɔ��f����
		ScreenFlip();
	}

	// DX ���C�u�����g�p�̏I������
	DxLib_End();

	// �v���O�����̏I��
	return 0;
}

/***********************************
*�@�^�C�g�����
************************************/
void DrawTitle(void)
{
	// �e�X�g�\��
	DrawString(250, 200, "�^�C�g�� A�{�^���ŃQ�[�����C��", 0xffffff, 0x000000);
	//�Q�[�����[�h��؂�ւ���
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_A) == 0) {
			
	}else{
		gGameMode = GAME_INIT;
	}
}

/***********************************
*�@�Q�[��������
************************************/
void GameInit(void)
{
	
	gGameMode = GAME_MAIN;
}

/***********************************
*�@�Q�[�����C��������
************************************/
void GameMain(void)
{
	// �e�X�g�\��
	DrawString(250, 200, "�Q�[�����", 0xffffff, 0x000000);

	//�v���C���[�ړ�
	PlayerControl();

}
/***********************************
*�@�Q�[�����C��������
************************************/
void PlayerControl(void)
{
	if (gNowKey & PAD_INPUT_LEFT)	gPlayerX -= 1;
	if (gNowKey & PAD_INPUT_RIGHT)	gPlayerX += 1;
	DrawBox(gPlayerX, gPlayerY, gPlayerX + 100, gPlayerY + 100, 0x00ff00, true);
}