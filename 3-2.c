/*
	本の構造体を表示するプログラム
	最終更新	:2021/04/27
*/
/*	
	メイン関数について
	概略	本の構造体配列を6個宣言し、初期化。その後表示。
	解説	特にありません。
*/
/*
	関数の実態
*/
/*
	本の構造体を表示
*/
#include <stdio.h>
#include <stdlib.h>

#define	TITLE_LENGTH	51
#define	AUTHOR_LENGTH	21

typedef struct{
	char	title[TITLE_LENGTH];
	char	author[AUTHOR_LENGTH];
	int		price;
} book;

int main(void)
{
	book	B[6]={
		{"調合書①入門編","辻本良三",1000},
		{"調合書②初級編","辻本良三",2000},
		{"調合書③中級編","辻本良三",5000},
		{"調合書④上級編","辻本良三",10000},
		{"調合書⑤達人編","辻本良三",15000},
		{"調合書G・錬金編","辻本良三",0},
	};

	int		i;	//ループ用

	//表示
	for( i = 0 ; i < 6 ; i++ )
	{
		printf("書名:%s\n",B[i].title);
		printf("著者:%s\n",B[i].author);
		printf("値段:%d\n",B[i].price);
	}


	system("pause");
	return 0;
}

