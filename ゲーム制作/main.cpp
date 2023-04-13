#include  "DxLib.h"
#define    _USE_MATH_DEFINES
#include  <math.h>

/*****************************************
*  �ϐ��̐錾�i�O���[�o���ϐ��j
*****************************************/

int gOldKey;				//�@�O��̓��̓L�[
int gNowKey;				//�@����̓��̓L�[
int gKeyFlg;				//�@���̓L�[���

int gGameState = 0;			//�@�Q�[�����[�h

/*****************************************
*  �֐��̃v���g�^�C�v�錾
*****************************************/



/*****************************************
* �v���O�����J�n
*****************************************/

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR IpCmdLine, _In_ int nCmdShow)
{
	// �^�C�g����ݒ�
	SetMainWindowText("��񂲂����");

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

		// �e�X�g�\��
		DrawString(250, 200, "���", 0xffffff, 0x000000);

		// ����ʂ̓��e��\��ʂɔ��f����
		ScreenFlip();
	}

	// DX ���C�u�����g�p�̏I������
	DxLib_End();

	// �v���O�����̏I��
	return 0;
}