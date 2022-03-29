/*
	2分探索をするプログラム
	最終更新	:2021/06/22
*/
/*
	関数「BinarySearch」について
	宣言	int BinarySearch(int target);
	概略	numがtargetと一致する学生を２分探索で探索する。
	引数	target  :探索する学生の学生番号を受けます。int型
	戻り値	M       :探索に成功した場合、その学生のインデックス番号を返します。
	        -1      :探索失敗時には-1を返します。
	解説	指定された番号を持つ学生のインデックス番号を探索します。
	        探索には２分探索のアルゴリズムを用いています。
	
	メイン関数について
	概略	2分探索の実演
	解説	2分探索（昇順のみ）の動作を確認します。
*/
/*
	関数の実態
*/
#include <stdio.h>

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

//BinarySearch Function
int BinarySearch(int target)
{
	int H,L,M; //Hi,Low,Mid
	L = 0;
	H = num;
	while(L<=H)
	{
		M = (L+H)/2;
		if( St[M].num == target )
		{
			return M;	//Mとtargetが一致したら終了
		}
		else if( St[M].num < target )
		{
			L = M + 1;	//M<targetだったら最小値を中央よりHに1個寄った場所にする
		}
		else
		{
			H = M - 1;	//M>targetだったら最大値を中央よりLに1個寄った場所にする
		}
	}
	return -1;
}

int main(void)
{
	int i;
	int tgt_key;

	while(1)
	{
		printf("Please input a key: ");
		if(scanf("%d",&tgt_key) == EOF)
		{
			break;
		}
		if( (i = BinarySearch(tgt_key)) != -1 )
		{
			printf("Found! Key=%d,Name=%s \n",St[i].num,St[i].name);
		}
		else
		{
			puts("Not found.");
		}
	}

    return 0;
}

