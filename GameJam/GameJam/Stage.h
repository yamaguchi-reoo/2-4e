#pragma once
class Stage
{
private:

	int StageImage;		//�X�e�[�W�摜�p�ϐ�
	int StageLane;		//���[���摜�p�ϐ�

public:
	Stage();
	~Stage();

	void UpDate();			//�X�V

	void Draw() const;		//�`��
};

