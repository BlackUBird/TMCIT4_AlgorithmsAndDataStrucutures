/*
	学生番号から学生を検索するプログラム
	最終更新	:2021/06/15
*/
/*
	関数「search」について
	宣言	int search(int target);
	概略	学生用構造体配列から、targetと同じ出席番号の学生をさがします。
	引数	int target  :探索する学生の番号
	戻り値	i :target番の学生のインデックス番号
	        -1:探索失敗
	解説	検索したい番号を受け、一致するものがあればその配列のインデックス番号を、
	　　　　一致するモノがなければ-1を返します。
	　　　　構造体を返すのではなく、あくまで値のみを返します。
	
	メイン関数について
	概略	学生番号から、その学生のステータスの検索
	解説	while内で学生番号を読み込み、関数「search」で検索を行います。
*/
/*
	関数の実態
*/
#include <stdio.h>
#include <stdlib.h>

#define MAX 10 //Structure Max

//Structure of student
struct student {
	int num;
	char name[10];
};

//Student structure array
struct student St[MAX] = {
	{8,"Hanada"},{5,"Goto"},{24,"Nishida"},
	{10,"Toh"},{3,"Sasaki"}
};

int num = 5;  //Number of student

//Search function
int search(int target)
{
	int i = 0;
	while( i < num && target != St[i].num )
	{
		i++;
	}
	if( i < num )
	{
		return i;
	}
	else
	{
		return -1;
	}
}

int main(void)
{
	int i;
	int tgt_key;

	while(1)
	{
		printf("Please input a key.\n");
		if(scanf("%d",&tgt_key) == EOF)
		{
			break;
		}
		if( (i = search(tgt_key)) != -1 )
		{
			printf("Found! Num=%d,Name=%s \n",St[i].num,St[i].name);
		}
		else
		{
			puts("Not found.");
		}
	}

	system("pause");

    return 0;
}

