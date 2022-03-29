/*
	関数「enqueue()」関数「dequeue()」の動作確認をするプログラム
	最終更新	:2021/10/09
*/
/*
	関数「enqueue()」について
	宣言	void enqueue(struct student *r);
	概略	データの登録を行う
	引数	struct student *r	:登録したいデータ
	戻り値	なし
	解説	　受けたデータを待ち行列の最後尾につなげます。
			　行列はアドレスを介して紐づけれれています。
	
	関数「dequeue()」について
	宣言	struct student *dequeue(void);
	概略	データの取り出しを行う
	引数	なし
	戻り値	NULL	:データがなかった
			p		:待ち行列内の先頭のデータのアドレス
	解説	　待ち行列の先頭にあるデータを取り出します。
			　今まで先頭にあったデータが取り出されるため、データは先頭へ向けてひとつズレます。
			　
	関数「QueueManager()」について
	宣言	void QueueManager();
	概略	データの登録・取り出しを行う
	引数	なし
	戻り値	なし
	解説	　「enqueue()」「dequeue()」の動作確認をします。

*/
/*
	関数の実態
*/
#include <stdio.h>
#include <stdlib.h>

struct student
{
	int num;
	char name[20];
	struct student *next;
};

//待ち行列の先頭のアドレスを記憶
struct student *root;

//登録用
void enqueue(struct student *r)
{
	//作業用
	struct student *p;
	
	//要素がなかった時
	if(root == NULL)
	{
		//受けた要素のアドレスを、先頭として登録
		root = r;
	}
	//あったとき
	else
	{
		//先頭の要素のアドレスを記憶
		p = root;
		
		//最後尾の要素まで移動
		while( p->next != NULL )
		{
			p = p->next;
		}
		//最後尾の要素の後ろに、受けた要素をつなげる
		p->next = r;
	}
	//最後尾の後ろにはなにも繋げない
	r->next = NULL;
}

//取出し用
struct student *dequeue(void)
{
	//作業用
	struct student *p;
	
	//要素がなかった時
	if( root == NULL )
	{
		//なかったことを返す
		return NULL;
	}
	//あったとき
	else
	{
		//先頭要素のアドレスを記憶
		p = root;
		//先頭要素のアドレスを、前から2番目に要素のアドレスに変更
		root = p->next;
		//先頭の要素のアドレスを返す
		return p;
	}
}

//待ち行列管理用
void QueueManager()
{
	while( 1 )
	{
		//分岐入力受付用
		char s;
		//分岐入力受付
		printf("Please input ENQ(E) or DEQ(D) or QUIT(Q):");
		scanf("%c%*c",&s);
		
		//E(dequeue)
		if( s == 'E' )
		{
			//作業用
			struct student *p;
			//新しくメモリを確保
			p = (struct student *)malloc(sizeof(struct student));
			
			//各要素の入力
			printf("Input number and name:");
			scanf("%d %s%*c",&p->num,p->name);
			
			//登録作業
			enqueue(p);
		}
		//D(dequeue)
		else if( s == 'D' )
		{
			//作業用
			struct student *p;
			//取り出し
			p = dequeue();
			
			//NULLでなかったら
			if( p != NULL )
			{
				//各要素を表示（次のデータのアドレスを除く）
				printf("Number=%d Name=%s\n",p->num,p->name);
			}
			//NULLだったら
			else
			{
				//なかったことを知らせる
				puts("No data!");
			}
		}
		//Q(quit)
		else if( s == 'Q' )
		{
			//ループを抜ける
			break;
		}
	}
}

int main(void)
{
	QueueManager();	

	system("pause");
	
	return 0;
}


