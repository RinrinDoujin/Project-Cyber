//=============================================================================
//
// �X���[�G�t�F�N�g [slow.h]
// Author : GP11B132 33 ���D
//
//=============================================================================
#pragma once

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define			SLOW_FRAME_NUM_DEFAULT		40		// �f�t�H���g���s�t���[����

// �X���[���x��
enum {
	SLOW_PLAYER_DIE,
	SLOW_BOSS_DIE,

	SLOW_MAX,
};

//*****************************************************************************
// �\���̒�`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSlow(void);
void UninitSlow(void);
void UpdateSlow(void);

void SetSlow(int label, int frameNum);

BOOL IsSlowApplied(void);