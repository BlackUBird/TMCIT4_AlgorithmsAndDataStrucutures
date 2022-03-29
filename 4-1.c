/*
	四則演算をするプログラム
	最終更新	:2021/05/11
*/
/*
関数「calc」について
	宣言	float calc(char op,float,a,float b);
	概略	演算子をopから読み取り、a(op)bの計算結果を返します。
	引数	char op		:演算子(+,-,*,/)を受けます。
			float a,b	:演算に使われる値を受けます。
	戻り値	各計算結果を返します。opに演算子以外が代入された場合、エラー文を表示して、0を返します。
	解説	簡易的な電卓となります。できるのは四則演算のみです
	
	メイン関数について
	概略	関数calcによる算術演算
	解説	キーボードから値2つと演算子1つを入力し、それを関数calcに渡して表示します。
*/
/*
	関数の実態
*/
/*
	算術演算を行う
*/
#include <stdio.h>

//算術演算を行う関数
float calc(char op,float a,float b)
{
	switch( op )
	{
	case '+':
		return a+b;
	case '-':
		return a-b;
	case '*':
		return a*b;
	case '/':
		return a/b;
	default:
		printf("ERROR:Operator\n");
		return 0.0f;
	}
}

//メイン関数
int main(void)
{
	float	x[2];	//演算する値を記憶
	char	op;		//演算子を記憶

	int i;	//ループ用

	//値の入力
	printf("演算する値を入力\n");
	for( i = 0 ; i < 2 ; i++ )
	{
		scanf("%f",&x[i]);
	}

	//演算子の入力
	printf("演算子を入力(+,-,*,/)\n");
	scanf("%*c%c",&op);

	//結果を表示
	printf("answer=%f\n",calc(op,x[0],x[1]));

	return 0;
}

