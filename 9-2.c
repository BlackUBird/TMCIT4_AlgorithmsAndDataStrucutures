/*
	逆ポーランド法で計算するプログラム
	最終更新	:2021/07/11
*/
/*
	関数「CAL_ReversePolish」について
	宣言	int CAL_ReversePolish(int s);
	概略	逆ポーランド法で計算をします。
	引数	int s	:演算記号を受けます。
	戻り値	return 1	:sが演算記号であり、その計算が有限な値をもつときに返されます。
			return -1	:sが演算記号でないとき、又はゼロ除算を行ったときに返されます。
	解説	sの値による分岐を行い、演算をします。演算結果はスタックにプッシュされます。
			直接値を返すわけではないので、計算結果を得るにはこの関数を呼び出した後にポップをする必要があります。
	
	関数「MNG_ReversePolish」について
	宣言	int MNG_ReversePolish(char X);
	概略	CAL_ReversePolish用のマネージャーです。
	引数	char X	:一桁の数字、演算記号、=を受けます。
	戻り値	return push((int)(X - '0'))
					:Xが数字だった場合、その数字が指す値をプッシュし、その成否を返します。
			return CAL_ReversePolish((int)X)
					:Xが演算記号だった場合、CAL_ReversePolishを呼び出し、その成否を返します。
			return pop()
					:Xが=だったとき、ポップをし、その成否を返します。					
			return -1
					:一桁の数字、演算記号、=以外の時は、失敗の意味を込めて-1を返します。
	解説	Xによって、返り値の分岐をします。逆ポーランド法による計算をしやすくするための、CAL_ReversePolishの補助用関数です。
	
	メイン関数について
	概略	各関数の動作確認
	解説	while内で文字入力、関数呼び出しを行い、逆ポーランド法による計算を行います。
*/
/*
	関数の実態
*/
#include <stdio.h>

#define MAX 10

int stack[MAX];
int top=0;

//push
int push(int x)
{
	if(top==MAX)
	{
		return -1;
	}
	else
	{
		stack[top]=x;
		++top;
		return 1;
	}
}

//pop
int pop(void)
{
	if(top==0)
	{
		return -1;
	}
	else
	{
		--top;
	}
	return (stack[top]);
}

//逆ポーランド
int CAL_ReversePolish(int s)
{
	int b = pop();
	int a = pop();
	switch(s)
	{
	case '+':
		push(a+b);	break;
	case '-':
		push(a-b);	break;
	case '*':
		push(a*b);	break;
	case '/':
		if( b != 0 )
		{
			push(a/b);
		}
		else
		{
			push(a);
			push(b);
			return -1;
		}
		break;
	default:
		push(a);
		push(b);
		return -1;
		break;
	}
	return 1;
}

//逆ポーランド計算用マネージャー
int MNG_ReversePolish(char X)
{
	if( X >= '0' && X <= '9' )
	{
		return push((int)(X - '0'));
	}
	else if( X == '+' || X == '-' || X == '*' || X == '/' )
	{
		return CAL_ReversePolish((int)X);
	}
	else if( X == '=' )
	{
		return pop();
	}
	else
	{
		return -1;
	}
	
}

int main(void)
{
	char s;	//入力された1文字を記憶
	printf("Data\t:");
	while(scanf("%c%*c",&s))
	{
		if(s == '=')
		{
			printf("Answer\t=%d\n",MNG_ReversePolish(s));
		}
		else
		{
			MNG_ReversePolish(s);
			printf("Data\t:");
		}
	}

	return 0;
}


