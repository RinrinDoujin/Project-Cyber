//=============================================================================
//
// �t�@�C������ [file.cpp]
// Author : GP11B132 33 ���D
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "file.h"
#include "result.h"

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
SAVEDATA	save;		// �Z�[�u�f�[�^�쐬�ꏊ


//=============================================================================
// �f�[�^�o��
//=============================================================================
void SaveData(void)
{
	// SCORE���Z�[�u
	int* record = GetRecord();
	for (int i = 0; i < SCORE_RECORD_MAX; i++) {
		save.score[i] = record[i];
	}


	// �Z�[�u�f�[�^�̃`�F�b�N�T�������߂�
	{
		char *adr = (char *)&save;	// �f�[�u�f�[�^�̐擪�A�h���X��adr�ɓ����
		int  sum = 0;				// �v�Z����`�F�b�N�T��

		save.sum = 0;				// �Z�[�u�f�[�^���̃`�F�b�N�T�����O�ŃN���A���Ă���

		for (int i = 0; i < sizeof(SAVEDATA); i++)
		{
			sum += adr[i];
		}

		save.sum = sum;
	}



	// SAVEDATA�\���̂��ƑS�����t�@�C���ɏo�͂���
	FILE *fp;

	printf("\n�Z�[�u�J�n�E�E�E");
	fp = fopen("savedata.bin", "wb");			// �t�@�C�����o�C�i���������݃��[�h��Open����

	if (fp != NULL)								// �t�@�C��������Ώ������݁A������Ζ���
	{	
		fwrite(&save, 1, sizeof(SAVEDATA), fp);	// �w�肵���A�h���X����w�肵���o�C�g�����t�@�C���֏�������
		fclose(fp);								// Open���Ă����t�@�C�������
		printf("�I���I\n");
	}
	else
	{
		printf("�t�@�C���G���[�I\n");
	}

}


//=============================================================================
// �f�[�^�ǂݎ��
//=============================================================================
void LoadData(void)
{
	// �t�@�C������Z�[�u�f�[�^��ǂݍ���
	FILE* fp;

	printf("\n���[�h�J�n�E�E�E");
	fp = fopen("savedata.bin", "rb");	// �t�@�C�����o�C�i���ǂݍ��݃��[�h��Open����

	if (fp != NULL)						// �t�@�C��������Ώ������݁A������Ζ���
	{
		fread(&save, 1, sizeof(SAVEDATA), fp);	// �w�肵���A�h���X�֎w�肵���o�C�g�����t�@�C������ǂݍ���
		fclose(fp);								// Open���Ă����t�@�C�������
		printf("�I���I\n");
	}
	else
	{
		printf("�t�@�C���G���[�I\n");
	}


	// �Z�[�u�f�[�^�̃`�F�b�N�T���������Ă��邩���ׂ�
	{
		char *adr = (char *)&save;	// �f�[�u�f�[�^�̐擪�A�h���X��adr�ɓ����
		int  sum = 0;				// �v�Z����`�F�b�N�T��
		int  org = save.sum;		// �Z�[�u�f�[�^���̃`�F�b�N�T��

		save.sum = 0;				// �Z�[�u�f�[�^���̃`�F�b�N�T�����O�ŃN���A���Ă���

		for (int i = 0; i < sizeof(SAVEDATA); i++)
		{
			sum += adr[i];
		}

		// ���X�̃`�F�b�N�T���ƍČv�Z�����`�F�b�N�T�������������ׂĂ���
		if (sum != org)
		{
			// �f�[�^�������񂳂�Ă���I
			return;
		}
	}
}

//=============================================================================
// �Z�[�u�f�[�^���擾
//=============================================================================
SAVEDATA* GetData(void) {
	return &save;
}