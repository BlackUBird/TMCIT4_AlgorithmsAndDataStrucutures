/*
	配列を用いたスタック表現
	最終更新	:2021/07/03
*/
/*
	関数「push」について
	宣言	push(int x);
	概略	スタック用配列stackに対しプッシュ動作を行います
	引数	int X  :プッシュする値を受けます
	戻り値	-1  :スタックが満杯のときのプッシュ失敗を表します。
	        1   :プッシュに成功したことを表します。
	解説	スタック用配列stackにデータXをプッシュをします。
	        使用するにはスタック用配列「stack」をグローバル変数として宣言する必要があります。
	        スタック用配列は0が下になるようにします。
	
	関数「pop」について
	宣言	pop(void);
	概略	スタック用配列stackに対しポップ動作を行います。
	引数	ありません
	戻り値	-1  :スタック内に何も入っていない(ポップに失敗した)ことを表します。
	        stack[top]
	            :ポップに成功したことを表します。スタックの一番最後に格納されたものを返します。
	解説	スタック用配列stackからデータをポップします。
	        使用するにはスタック用配列「stack」をグローバル変数として宣言する必要があります。
	        スタック用配列は0が下になるようにします。
	
	メイン関数について
	概略	関数「push」「pop」の動作確認
	解説	まずキーボードから文字列を読み込み。
	       「push」と入力されたらpushするデータを読み込み、関数pushを呼び出します。
	       「pop」と入力されたら関数popを呼び出し、データを取得します。
*/
/*
	関数の実態
*/
#include <stdio.h>
#include <stdlib.h>

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

int main(void)
{
	int	X;
	char OPE[5];
	int a;
	
	while(1)
	{
		//Input operation
		printf("Input operation: push/pop :");
		scanf("%s",OPE);
		
		if( OPE[0] == 'p' && OPE[1] == 'u' &&
		    OPE[2] == 's' && OPE[3] == 'h' && OPE[4] == '\0' )
		{
			//Input data
			printf("Input data:");
			scanf("%d",&X);
			if(push(X) == -1 )
			{
				printf("Stack is full!\n");
			}
			else
			{
				printf("Success.\n");
			}
		}
		else if( OPE[0] == 'p' && OPE[1] == 'o' &&
		         OPE[2] == 'p' && OPE[3] == '\0' )
		{
			//Poped data
			if( (a = pop()) == -1 )
			{
				printf("Stack is empty!\n");
			}
			else
			{
				printf("Poped data=%d\n",a);
			}
		}
	}

	system("pause");

    return 0;
}

