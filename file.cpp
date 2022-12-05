//=============================================================================
//
// ファイル処理 [file.cpp]
// Author : GP11B132 33 呉優
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "file.h"
#include "result.h"

//*****************************************************************************
// 構造体定義
//*****************************************************************************
SAVEDATA	save;		// セーブデータ作成場所


//=============================================================================
// データ出力
//=============================================================================
void SaveData(void)
{
	// SCOREをセーブ
	int* record = GetRecord();
	for (int i = 0; i < SCORE_RECORD_MAX; i++) {
		save.score[i] = record[i];
	}


	// セーブデータのチェックサムを求める
	{
		char *adr = (char *)&save;	// デーブデータの先頭アドレスをadrに入れる
		int  sum = 0;				// 計算するチェックサム

		save.sum = 0;				// セーブデータ側のチェックサムを０でクリアしていく

		for (int i = 0; i < sizeof(SAVEDATA); i++)
		{
			sum += adr[i];
		}

		save.sum = sum;
	}



	// SAVEDATA構造体ごと全部をファイルに出力する
	FILE *fp;

	printf("\nセーブ開始・・・");
	fp = fopen("savedata.bin", "wb");			// ファイルをバイナリ書き込みモードでOpenする

	if (fp != NULL)								// ファイルがあれば書き込み、無ければ無視
	{	
		fwrite(&save, 1, sizeof(SAVEDATA), fp);	// 指定したアドレスから指定したバイト数分ファイルへ書き込む
		fclose(fp);								// Openしていたファイルを閉じる
		printf("終了！\n");
	}
	else
	{
		printf("ファイルエラー！\n");
	}

}


//=============================================================================
// データ読み取り
//=============================================================================
void LoadData(void)
{
	// ファイルからセーブデータを読み込む
	FILE* fp;

	printf("\nロード開始・・・");
	fp = fopen("savedata.bin", "rb");	// ファイルをバイナリ読み込みモードでOpenする

	if (fp != NULL)						// ファイルがあれば書き込み、無ければ無視
	{
		fread(&save, 1, sizeof(SAVEDATA), fp);	// 指定したアドレスへ指定したバイト数分ファイルから読み込む
		fclose(fp);								// Openしていたファイルを閉じる
		printf("終了！\n");
	}
	else
	{
		printf("ファイルエラー！\n");
	}


	// セーブデータのチェックサムが合っているか調べる
	{
		char *adr = (char *)&save;	// デーブデータの先頭アドレスをadrに入れる
		int  sum = 0;				// 計算するチェックサム
		int  org = save.sum;		// セーブデータ内のチェックサム

		save.sum = 0;				// セーブデータ側のチェックサムを０でクリアしていく

		for (int i = 0; i < sizeof(SAVEDATA); i++)
		{
			sum += adr[i];
		}

		// 元々のチェックサムと再計算したチェックサムが同じか調べている
		if (sum != org)
		{
			// データが改ざんされている！
			return;
		}
	}
}

//=============================================================================
// セーブデータを取得
//=============================================================================
SAVEDATA* GetData(void) {
	return &save;
}