/*
	２分探索（降順対応版）をするプログラム
	最終更新	:2021/06/22
*/
/*
	関数「BinarySearch2」について
	宣言	int BinarySearch2(int target,int a[]);
	概略	targetと一致する値を2分探索で探索します。
	引数	int target  :探索する値です。
	        int a[]     :探索の対象となる配列です。
	戻り値	M    :探索に成功したらその値のインデックス番号を返します。
	        -1   :探索失敗したら-1を返します。
	解説	2分探索で対象を探索します。通常の「BinarySearch」と異なり降順にも対応しています。
	        関数内で降順か昇順かを判別するために新たに変数Sを宣言しています。降順なら+1が昇順なら-1が入ります。
	        また、その値をMの値の更新の際にも用いています。
	        　　「降順の時」
	        　　a[M] < target のとき、H=M-1
	        　　a[M] > target のとき、H=M+1
	        　　「昇順の時」
	        　　a[M] < target のとき、H=M+1
	        　　a[M] > target のとき、H=M-1
	        このように、Mに加算される値は1か-1のどちらかになり、降順と昇順では真逆になる関係があるからです。
	        また、継続条件で出てくるEには更新される前のMの値が入ります。これは、更新手続きが行われる前と行われたあとの値が
	        一致した時に探索失敗となることを利用しています。
	
	メイン関数について
	概略	BinarySearch2の動作確認
	解説	昇順の配列と降順の配列を用意して、2通りの動作を確認しています。
*/
/*
	関数の実態
*/
#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM 10

int A1[MAX_NUM] = {0,1,2,3,4,5,6,7,8,9};
int A2[MAX_NUM] = {9,8,7,6,5,4,3,2,1,0};

//BinarySearch Function
int BinarySearch2(int target,int a[])
{
	int H = a[MAX_NUM-1];
	int	L = a[0];
	int M = (L+H)/2;
	int S = (L-H)/(L+H);
	int E = -1;

	while(E != M)
	{
		E = M;
		if( a[M] == target )
		{
			return M;	//Mとtargetが一致したら終了
		}
		else if( a[M] < target )
		{
			L = M - S;	//M<targetだったら最小値を中央よりHに1個寄った場所にする
		}
		else
		{
			H = M + S;	//M>targetだったら最大値を中央よりLに1個寄った場所にする
		}
		M = (L+H)/2;
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
		if( (i = BinarySearch2(tgt_key,A1)) != -1 )
		{
			printf("Found! A1 Number=%d \n",A1[i]);
			i=0;
		}
		else
		{
			puts("Not found.");
		}
		if( (i = BinarySearch2(tgt_key,A2)) != -1 )
		{
			printf("Found! A2 Number=%d \n",A2[i]);
			i=0;
		}
		else
		{
			puts("Not found.");
		}
	}

	system("pause");

    return 0;
}

