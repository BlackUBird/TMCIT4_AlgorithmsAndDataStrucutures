/*
	学生用構造体のメモリを動的確保するプログラム
	最終更新	:2021/09/14
*/
/*
	malloc関数を使ってみるプログラムです。
*/

/*
	関数の実態
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student
{
	int num;
	char name[20];
	int score;
};

int main(void)
{
	//学生用構造体
	struct student* nowStudent;

	//学生用構造体のメモリを確保する
	if((nowStudent = (struct student*)malloc(sizeof(struct student))) == NULL)
	{
		//終了
		puts("Memory allocation error");
		exit(1);
	}
	else
	{
		//各メンバを入力・代入
		int num;
		char name[20];
		int score;
		printf("番号:");	scanf("%d",&num);
		printf("名前:");	scanf("%s",name);
		printf("点数:");	scanf("%d",&score);
		nowStudent->num = num;
		strcpy(nowStudent->name,name);
		nowStudent->score = score;

		//表示
		printf("番号\t名前\t点数\n");
		printf("%d\t%s\t%d\n",nowStudent->num,nowStudent->name,nowStudent->score);

	}

	//表示



	system("pause");

	return 0;
}

