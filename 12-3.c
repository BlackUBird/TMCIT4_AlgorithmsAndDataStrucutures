/*
	リスト構造によりスタックを表現するプログラム
	最終更新	:2021/10/22
*/
/*
	関数「Push_12_3(struct cell *NewData)」について
	宣言	void Push_12_3(struct cell *NewData);
	概略	データをスタック領域に格納する
	引数	struct cell *NewData
					:登録用データ
	戻り値	なし
	解説	　リスト構造により表現されたスタック領域にデータを登録します。
	
	関数「Pop_12_3(void)」について
	宣言	struct cell *Pop_12_3(void);
	概略	データをスタック領域から取り出す
	引数	なし
	戻り値	return NULL
				:スタック領域にデータがなかった
	解説	　リスト構造により表現されたスタック領域からデータ取り出します。
	
	関数「Draw_List(void)」について
	宣言	void Draw_List(void);
	概略	スタック領域内にあるデータを、先頭から順に表示する
	引数	なし
	戻り値	なし
	解説	　リスト構造により表現されたスタック領域ないのデータを表示します。
	
	関数「Task_12_3(void)」について
	宣言	void Task_12_3(void);
	概略	リスト構造によるスタックの表現の確認
	引数	なし
	戻り値	なし
	解説	　リスト構造によるスタックに関する動作を確認します。
	
	メイン関数について
	概略	Task_12_3()の呼び出し
	解説	　プログラムを動作させます。
*/
/*
	関数の実態
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//データ
#define DATA_NAME_MAX (10)

//データの情報
struct cell
{
	char	Data[DATA_NAME_MAX];	//データ
	struct cell *Next;	//このデータの1つ下にあるデータへのポインタ
};

//スタックの先頭へのポインタ(次取り出されるデータへのポインタ)
struct cell *StackHead = NULL;

//*** push ***//
//登録用
void Push_12_3(struct cell *NewData)
{
	//登録するデータの1つ下にあるデータを
	//さっきまでの先頭データにする
	NewData->Next = StackHead;
	//スタックの先頭を登録用データにする
	StackHead = NewData;
}

//*** pop ***//
//取り出し用
struct cell *Pop_12_3(void)
{
	//作業用
	struct cell *tmp;

	//スタックにデータがあるかどうか
	if( StackHead == NULL )
	{//無かった時
		//NULLを返す
		return NULL;
	}

	//あったとき
	//先頭データへのポインタを退避
	tmp = StackHead;
	//先頭データを、「現在の先頭データの次のデータ」にする
	StackHead = tmp->Next;

	//さっきまで先頭だったデータへのポインタを返す
	return tmp;
}

//リストを表示
void Draw_List(void)
{
	struct cell *tmp;	//作業用

	if( StackHead == NULL )
	{//先頭要素が無かった時
		printf("Data dosen't exist.\n");
	}
	else
	{//先頭要素があったとき
		tmp = StackHead;	//現在の先頭要素へのアドレスを退避

		int i = 1;	//カウント用

		//すべて表示
		while( tmp != NULL )
		{
			//表示
			printf("[No%2d]Data:%s\n",i,tmp->Data);
			
			i++;	//カウントを1進める
			
			tmp = tmp->Next;	//作業中要素を次の要素に更新
		}

		//データ総数を表示
		printf("Number of data:%d\n",i-1);
	}
}

void Task_12_3(void)
{
	while(1)
	{
	//分岐用入力受付用
		char s;
		//分岐用入力受付
		printf("Please input U(pUsh) or O(pOp) or L(List) or Q(Quit):");
		scanf("%c%*c",&s);

		//分岐
		if( s == 'U' )
		{//入力はU
			//新しい要素用のメモリを確保
			struct cell *NewData;
			NewData = (struct cell*)malloc(sizeof(struct cell));

			//各要素を入力
			//データ
			printf("Please input data:");
			scanf("%s%*c",NewData->Data);

			//登録
			Push_12_3(NewData);
		}
		else if( s == 'O' )
		{//入力はO
			//作業用
			struct cell *tmp;

			//取り出し
			tmp = Pop_12_3();

			//NULL判別
			if( tmp != NULL )
			{//NULL出なかったら
				//表示する
				printf("Data=%s\n",tmp->Data);
			}
			else
			{//NULLだったら
				//NULLだったことを表示する
				puts("Data couldn't be found.");
			}
		}
		else if( s == 'Q' )
		{//入力はQ
			break;
		}
		else if( s == 'L' )
		{//入力はL
			Draw_List();
		}
		else
		{//その他入力
			scanf("%*c");
		}

		printf("\n");
	}
}

int main(void)
{
	Task_12_3();

	system("pause");

	return 0;
}


