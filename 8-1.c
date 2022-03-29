/*
	ファイルにデータを書きだすプログラム
	最終更新	:2021/06/01
*/
/*
	メイン関数について
	概略	U89_210601.txtにデータを書き出します。
	解説	ファイルを開きデータを書き出していきます。fprintfの使い方確認という感じです。
*/
/*
	関数の実態
*/
#include <stdio.h>
#include <stdlib.h>

#define IN_DATA "U89_210601.txt"	//書き込み先ファイル名

int main(void)
{
	FILE *fp;	//ファイル操作用ポインタ

	struct student 
	{
		int  num;
		char name[20];
		int  score;
	};
	struct student St[] = {
		{3 ,"鈴木三郎"  ,86},
		{1 ,"山田一郎"  ,75},
		{14,"高橋十四子",93},
		{2, "田中二子"  ,68}
	};

	int i;

	//ファイルをオープン
	//オープンできなかったら
	if( (fp=fopen(IN_DATA,"w")) == NULL )
	{
		printf("file coudn't be found.\n");	//エラーメッセージを表示
		exit(1);
	}
	else
	{
		for(i = 0 ; i < 4 ; i++)
		{
			if( ( fprintf(fp,"%d %s %d\n",St[i].num,St[i].name,St[i].score) ) < 0 )
			{
				fprintf(fp,"書き込みに失敗しました\n");
			}
		}
		fclose(fp);
	}

	system("pause");

    return 0;
}
