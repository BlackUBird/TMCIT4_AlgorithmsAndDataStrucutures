/*
	学生用構造体配列を点数を参照してソートするプログラム
	最終更新	:2021/07/18
*/
/*
	関数「Student_Sort」について
	宣言	void Student_Sort(struct student st[],int num);
	概略	学生用構造体配列を点数を参照してソートする
	引数	struct student st[]	:ソートされる配列
			int num				:配列の要素数
	戻り値	ありません。
	解説	学生用構造体配列を点数を参照してソートします。
			ソートには挿入ソートを用いています。
	
	メイン関数について
	概略	ソートの動作確認
	解説	学生用構造体配列を宣言し、ソート前後の状態をそれぞれ表示しています。
*/
/*
	関数の実態
*/
#include <stdio.h>

#define MAX_STUDENT 7

struct student{
	int num;
	char name[10];
	int score;
};

//挿入ソートによるソート
void Student_Sort(struct student st[],int num)
{
	int i,j;	//雑用
	struct student tmp;
	for( i=0 ; i<num ; i++ )
	{
		tmp = st[i];
		for( j=i-1 ; j>=0 && st[j].score < tmp.score ; j--)
		{
			st[j+1] = st[j];
		}
		st[j+1] = tmp;
	}
}

int main(void)
{
	struct student St[] = 
	{ 
		{1,"Ichiko",90},
		{2,"Niko",70},
		{3,"Sanko",80},
		{4,"Yonko",88},
		{5,"Goko",55},
		{6,"Rokuko",80},
		{0,"Zeroko",100}
	};
	int i;
	
	for(i=0 ; i < MAX_STUDENT ; i++)
	{
		printf("num:%d\tname:%10s\tscore:%3d\n",St[i].num,St[i].name,St[i].score);
	}
	
	printf("\n");
	Student_Sort(St,MAX_STUDENT);
	for(i=0 ; i < MAX_STUDENT ; i++)
	{
		printf("num:%d\tname:%10s\tscore:%3d\n",St[i].num,St[i].name,St[i].score);
	}

	return 0;
}

