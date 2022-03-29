/*
	双方向リストの動作確認をするプログラム
	最終更新	:2021/10/15
*/
/*
	関数「Enqueue_12_2」について
	宣言	void Enqueue_12_2(struct cell *NewData);
	概略	struct cell型構造体データの登録を行います。
	引数	struct cell *NewData
				:追加するデータ
	戻り値	なし
	解説	双方向リストにデータを登録します。
	
	関数「Denqueue_12_2」について
	宣言	struct cell *Dequeue_12_2(char key[]);
	概略	キーを参照して双方向リストからデータを取り出します。
	引数	char key[]
				:取り出したいデータが持つであろうキーです。
	戻り値	NULL:データがなかった時に返します。
			p	:見つかったデータのポインタを返します。
	解説	キー値を参照してデータを取り出します。
	
	関数「Draw_List」について
	宣言	void Draw_List(void);
	概略	リストに登録されているデータを表示します。
	引数	なし
	戻り値	なし
	解説	リストに登録されているデータのキーを、先頭要素から順に表示します。
			表示後はデータ数を返します。
	
	関数「Task_12_2」について
	宣言	void Task_12_2(void);
	概略	データの登録/取り出しを行います。
	引数	なし
	戻り値	なし
	解説	Enqueue_12_2,Denqueue_12_2の応用です。
*/
/*
	関数の実態
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define KEY_MAX 10	//キーの最大文字数
#define DATA_MAX 20	//データの最大数

struct cell {
	char key[KEY_MAX];	//キー値
	int data[DATA_MAX];	//データ
	struct cell *next;	//次の要素のアドレス
	struct cell *prev;	//前の要素のアドレス
};

//先頭要素へのポインタ
struct cell *root = NULL;

//あたしい要素の登録をする
void Enqueue_12_2(struct cell *NewData)
{
	//作業用
	struct cell *p;
	
	//判別／登録
	if( root == NULL )
	{//先頭要素がNULL（存在しない）の時
		//先頭要素を新しい要素とする
		root = NewData;
		//前後の情報を登録
		NewData->next = NULL;	//次は何もない
		NewData->prev = NULL;	//前は何もない
	}
	else
	{//先頭要素がNULL以外（存在する）の時
		//先頭要素を作業用変数に待避
		p = root;
		
		//最後尾へ移動
		while( p->next != NULL )
		{
			p = p->next;
		}
		//現在の最後尾の後ろに新しい要素を連結
		p->next = NewData;
		//新しい要素（現最後尾）の前後を登録
		NewData->next = NULL;	//次は何もない
		NewData->prev = p;	//前はさっきまで最後尾だった要素
	}
}

//要素を取り出す
struct cell *Dequeue_12_2(char key[])
{
	//作業用
	struct cell *p;
	
	//判別／取出し
	if( root == NULL )
	{//先頭要素がNULL（存在しない）の時
		return NULL;	//NULLを返す
	}
	else
	{//先頭要素がNULL以外（存在する）の時
		//先頭要素を作業用変数に待避
		p = root;
		
		//指定されたキーを持つまたは最後尾の要素まで移動
		while( strcmp(p->key,key) != 0 )
		{
			p = p->next;
			if( p == NULL )
			{//指定されたキーを持つ要素がなかった時
				return NULL;	//NULLを返す
			}
		}
		
		//場合分け／処理
		if( p->next == NULL && p->prev == NULL )
		{//リストに指定されたキーを持つ要素だけが登録されていた時
			root = NULL;	//先頭要素は無し
		}
		else if( p->prev == NULL )
		{//先頭で見つかった
			//先頭要素の更新
			root = p->next;	//先頭要素を前から2番目の要素にする
			p->next->prev = NULL;	//先頭であるため、前には何もない
		}
		else if( p->next == NULL )
		{//最後尾で見つかった
			p->prev->next = NULL;	//最後尾を後ろから2番目の要素にする
		}
		else
		{//途中で見つかった
			//取り出す要素をとばすように更新する
			p->next->prev = p->prev;
			p->prev->next = p->next;
		}

		//見つかった要素のポインタを返す
		return p;
		
	}
}

//リストを表示
void Draw_List(void)
{
	struct cell *tmp;	//作業用

	if( root == NULL )
	{//先頭要素がNULLだった時
		printf("Data dosen't exist.\n");
	}
	else
	{//先頭要素がNULL出なかったとき
		tmp = root;	//現在の先頭要素へのアドレスを退避

		int i = 1;	//カウント用

		//すべて表示
		while( tmp != NULL )
		{
			//表示
			printf("[No%2d]Key:%s\n",i,tmp->key);
			
			i++;	//カウントを1進める
			
			tmp = tmp->next;	//作業注要素を次の要素に更新
		}

		//データ総数を表示
		printf("Number of data:%d\n",i-1);
	}
}

void Task_12_2(void)
{
	while(1)
	{
		//分岐用入力受付用
		char s;
		//分岐用入力受付
		printf("Please input E(Enqueue) or D(Dequeue) or L(List) or Q(Quit):");
		scanf("%c%*c",&s);

		//分岐
		if( s == 'E' )
		{//入力はE
			//新しい要素用のメモリを確保
			struct cell *NewData;
			NewData = (struct cell*)malloc(sizeof(struct cell));

			//各要素を入力
			//キー
			printf("Please input key:");
			scanf("%s%*c",NewData->key);
			//データ
			printf("Please input data\n");
			for(int i = 0 ; i < DATA_MAX ; i++)
			{
				printf("Data[%2d]:",i);
				scanf("%d%*c",&NewData->data[i]);
			}

			//登録
			Enqueue_12_2(NewData);
		}
		else if( s == 'D' )
		{//入力はD
			//作業用
			struct cell *tmp;

			//キーの入力
			char Key[KEY_MAX];
			printf("Please input key:");
			scanf("%s%*c",Key);

			//取り出し
			tmp = Dequeue_12_2(Key);

			//NULL判別
			if( tmp != NULL )
			{//NULL出なかったら
				//表示する
				printf("Key=%s Data=[",tmp->key);
				for(int i = 0 ; i < DATA_MAX ; i++)
				{
					printf("%2d ",tmp->data[i]);
				}
				printf("]\n");
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
	Task_12_2();

	system("pause");

	return 0;
}
