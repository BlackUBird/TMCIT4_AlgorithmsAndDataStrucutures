/*
	ファイルのデータをファイルへ書き出すプログラム
	最終更新	:2021/06/01
*/
/*	
	メイン関数について
	概略	FILE_Aの各データをFILE_Bに書き出します。
	解説	まず、FILE_Aに元となるデータを書き込みます。この時のみ、"w"モードでファイルオープンします。
			その後FILE_Aを"r"モードで、FILE_Bを"w"モードでファイルオープンし、FILE_Aから各データを読み込みます。
			そして、追加情報の点数scoreを入力、先ほど読み込んだデータとscoreをFILE_Bに書き出します。
*/
/*
	関数の実態
*/
#include <stdio.h>
#include <stdlib.h>

#define IN_DATA_A "FILE_A.txt"	//書き込み先ファイル名A
#define IN_DATA_B "FILE_B.txt"	//書き込み先ファイル名B

#define STUDENT_MAX 3

int main(void)
{
	FILE *fp_A,*fp_B;	//ファイル操作用ポインタ

	//ステータスの構造体
	struct student 
	{
		int  num;
		char name[20];
	};
	struct student St[STUDENT_MAX] = {
		{30,"ののか"},
		{7, "かいと"},
		{37,"ぴの"}
	};

	int  in_num;		//読み込んだ番号
	char in_name[20];	//読み込んだ名前

	int score;	//書き込む点数

	int i;	//ループ用

	//ファイルをオープン
	//FILE_A("w")
	if( (fp_A=fopen(IN_DATA_A,"w")) == NULL )
	{
		printf("FILE_A coudn't be found.\n");	//エラーメッセージを表示
		exit(1);
	}
	else
	{
		//FILE_Aに書き込み
		for( i = 0 ; i < STUDENT_MAX ; i++ )
		{
			if( (fprintf(fp_A,"%d %s\n",St[i].num,St[i].name) ) < 0 )
			{
				fprintf(fp_A,"Failed to write.\n");
			}
		}
	}
	fclose(fp_A);
	//FILE_A("r")
	if( (fp_A=fopen(IN_DATA_A,"r")) == NULL )
	{
		printf("FILE_A coudn't be found.\n");	//エラーメッセージを表示
		exit(1);
	}
	//FILE_B("w")
	if( (fp_B=fopen(IN_DATA_B,"w")) == NULL )
	{
		printf("FILE_B coudn't be found.\n");	//エラーメッセージを表示
		exit(1);
	}

	//オープンできたら
	//FILE_Aの情報を取得
	while( fscanf(fp_A,"%d %s",&in_num,in_name) != EOF )
	{
		printf("No:%3d,NAME:%s\n",in_num,in_name);	//番号、名前表示
		score = 0;	//点数初期化
		//点数入力
		printf("Please input this student's score:");	scanf("%d",&score);
		//FILE_Bに書き込み
		if( (fprintf(fp_B,"%d %s %d\n",in_num,in_name,score) ) < 0 )
		{
			fprintf(fp_B,"Failed to write.\n");
		}
	}

	//ファイルクローズ
	fclose(fp_A);
	fclose(fp_B);

	system("pause");

    return 0;
}

