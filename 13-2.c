/*
	チェイン法でデータを記憶するプログラム(削除用関数付き)
	最終更新	:2021/11/09
*/
/*
	関数「Hash_Get」について
	宣言	int Hash_Get(char Key[]);
	概略	キー値からハッシュ値を計算し、その値を返します。
	引数	char Key[]	:ハッシュ値を生成する際に参照するキー値
	戻り値	h	:生成したハッシュ値
	解説	受けたキー値を用いてint型でハッシュ値を生成します。
	
	関数「Chain_Initialize」について
	宣言	void Chain_Initialize(void);
	概略	チェイン法によるデータの記憶のための下準備をします。
	引数	ありません。
	戻り値	ありません。
	解説	ハッシュテーブルの各先頭を初期化（NULLに）します。
	
	関数「Chain_SetData」について
	宣言	int Chain_SetData(char *Key,char *Data);
	概略	キー値とデータを受け新しいデータを作成・記憶をします。
	引数	char *Key	:新たなデータのキー値
			char *Data	:新たなデータのデータ値
	戻り値	-1	:キー値の重複があった。
			h	:登録したデータのハッシュ値
	解説	データの登録を行います。
	
	関数「Chain_GetData」について
	宣言	S_Cell *Chain_GetData(char Key[]);
	概略	データの取得を行います。
	引数	char Key[]	:取り出すデータのキー値
	戻り値	p	:取り出したデータへのポインタ
			NULL	:見つからなかった
	解説	データの探索・取り出しを行います。データはリスト中に残ったままとなります。
	
	関数「Chain_DeleteData」について
	宣言	int Chain_DeleteData(char Key[]);
	概略	データの削除を行います
	引数	Key[]	:削除したいデータのキー値を受けます。
	戻り値	-1	:削除に失敗
			h	:削除したデータのハッシュ値
	解説	登録されているデータを削除します。そのデータの前後は連結されます。
	
	関数「Chain_Finalize」について
	宣言	void Chain_Finalize();
	概略	チェイン法によるデータの記憶の終了処理をします。
	引数	ありません。
	戻り値	ありません。
	解説	登録されているデータが占有しているメモリを開放していきます
	
	関数「Task_13_2」について
	宣言	void Task_13_2(void);
	概略	チェイン法でのデータの取り扱いを確認します。
	引数	ありません。
	戻り値	ありません。
	解説	数字キーの入力により、データの登録、データの取得、データの削除、ハッシュ値の取得、終了に分岐し、動作を確認します。
	
	メイン関数について
	概略	Task関数のよびだし
	解説	Task関数を実際に動かします。
*/
/*
	関数の実態
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//ハッシュテーブルのエントリ数(系列の数)
#define HASH_MAX (1)
//定数(ハッシュ値生成用)
#define HASH_CNST (3)

//キーの最大長さ
#define MAX_KEY (4)
//データの最大長さ
#define MAX_DATA (10)

//データを格納する構造体
typedef struct S_cell
{
	char Key[MAX_KEY];	//キー値
	char Data[MAX_DATA];	//データ値
	struct S_cell *Next;	//次につながっているデータへのポインタ
} S_Cell;

//ハッシュテーブル
S_Cell *Chain_HashTable[HASH_MAX];

//ハッシュ値を返す
int Hash_Get(char Key[])
{
	int i;	//雑用
	int h = 0;	//ハッシュ値を記憶
	//生成
	for(i = 0 ; Key[i] != '\0' ; i++)
	{
		h = (h * HASH_CNST + Key[i]) % HASH_MAX;
	}

	//返却
	return h;
}

//初期化用
void Chain_Initialize(void)
{
	int i;	//雑用
	//ハッシュテーブルにNULLを代入
	for(i = 0 ; i < HASH_MAX ; i++)
	{
		Chain_HashTable[i] = NULL;
	}
}

//データ挿入用
int Chain_SetData(char *Key,char *Data)
{
	//新しいデータを格納する
	S_Cell *r;
	r = (S_Cell*)calloc(1,sizeof(S_Cell));
	//登録
	strcpy(r->Key,Key);
	strcpy(r->Data,Data);
	
	//作業用
	S_Cell *p;

	//登録するデータのキー値から
	//ハッシュ値を計算し、格納
	int h;
	h = Hash_Get(r->Key);
	
	//ハッシュ値を参照して特定のハッシュテーブルに登録
	if(Chain_HashTable[h] == NULL)
	{//特定のハッシュテーブルにデータが無かったら
		//特定のハッシュテーブルに新しいデータを登録
		Chain_HashTable[h] = r;
		//その次には何もつながっていない
		r->Next = NULL;
		//登録したデータのハッシュ値を返す
		return h;
	}
	else
	{//特定のハッシュテーブルにデータがあったら
		//作業用変数に特定のハッシュテーブルのポインタを格納
		p = Chain_HashTable[h];

		//同じキーを持つデータがあるかを探索
		while(1)
		{
			if(strcmp(r->Key,p->Key) == 0)
			{//もし同じキーを持つデータがあれば
				//中断
				return -1;	//2重登録
			}

			if(p->Next == NULL)
			{//末尾まで来たら
				//探索完了
				break;
			}
			else
			{//末尾でなければ
				//探索続行
				p = p->Next;
			}
		}

		//末尾にデータにつなげる
		p->Next = r;
		//つなげたデータは末尾なので次には何もつながっていない
		r->Next = NULL;

		//登録したデータのハッシュ値を返す
		return h;
	}
}

//取り出し用
S_Cell *Chain_GetData(char Key[])
{
	//ハッシュ値を記憶
	int h;
	h = Hash_Get(Key);

	//キーを参照した、特定のハッシュテーブルへのポインタを記憶
	S_Cell *p;	//作業用
	p = Chain_HashTable[h];

	//探索
	while(p != NULL)
	{//最後尾になるまで続ける
		//分岐
		if(strcmp(Key,p->Key) == 0)
		{//指定されたキーを持つデータが見つかったら
			return p;	//そのデータへのポインタを返す
		}
		else
		{//まだ見つかっていないのなら
			p = p->Next;	//データの探索を続ける
		}
	}

	//見つからなかったら
	return NULL;	//NULLを返す
}

//削除用
int Chain_DeleteData(char Key[])
{
	//ハッシュ値を記憶
	int h;
	h = Hash_Get(Key);

	//キーを参照した、特定のハッシュテーブルへのポインタを記憶
	S_Cell *p;	//作業用
	p = Chain_HashTable[h];

	//指定されたキー値のデータを探索
	while(p != NULL && p->Next != NULL)
	{//最後尾になるまで続ける
		//分岐
		if(strcmp(Key,p->Next->Key) == 0)
		{//指定されたキーを持つデータが見つかったら
			break;	//ループを抜ける
		}
		else
		{//まだ見つかっていないのなら
			p = p->Next;	//データの探索を続ける
		}
	}
	
	//見つからなかったら
	if( p == NULL )
	{//見つからなかったら
		return -1;	//-1を返す
	}
	
	//指定されたキー値のデータを取り除く
	p->Next = p->Next->Next;
	
	//削除したデータのハッシュ値を返す
	return h;
}

//終了処理用
void Chain_Finalize()
{
	S_Cell *a,*b;	//作業用
	int i;	//雑用
	for(i = 0 ; i < HASH_MAX ; i++)
	{
		a = Chain_HashTable[i];
		while( a != NULL )
		{
			b = a->Next;
			free(a);
			a = b;
		}
	}
}

//チェイン法でのデータの取り扱いを観察する
void Task_13_2(void)
{
	//初期化
	Chain_Initialize();

	while(1)
	{//無限ループ
		//入力の受け付け
		char s;	//入力を記憶
		printf("Please input number.\n");
		printf("1:Set 2:Get 3:Delete 4:GetHash 0:Quit\n->");
		scanf("%c%*c",&s);
		
		char Key[MAX_KEY];	//キー値
		char Data[MAX_DATA];//データ

		//入力による分岐
		if( s == '1' )
		{//Set
			//キー値とデータを入力
			printf("Please input key and data.\n");
			printf("Key (MaxLength=3):");	scanf("%s%*c",Key);
			printf("Data(MaxLength=9):");	scanf("%s%*c",Data);

			//登録
			if( Chain_SetData(Key,Data) == -1 )
			{//キーの重複があったら
				printf("This key is already used.\n");
			}
			else
			{//無かったら
				printf("Success\n");
			}
		}
		else if( s == '2' )
		{//Get
			//キー値を入力
			printf("Please input key.\n");
			printf("Key :");	scanf("%s%*c",Key);

			//取り出し
			S_Cell* p;	//作業用
			if( (p = Chain_GetData(Key)) == NULL )
			{//データが見つからなかったら
				printf("Data couldn't be found;\n");
			}
			else
			{//見つかったら
				printf("Data:%s\n",p->Data);	//データを表示
			}
		}
		else if( s == '3' )
		{//Delete
			//キー値を入力
			printf("Please input key.\n");
			printf("Key :");	scanf("%s%*c",Key);
			
			//削除
			if( Chain_DeleteData(Key) == -1 )
			{//失敗したら
				printf("Data couldn't be deleted.\n");
			}
			else
			{//できたら
				printf("Data is deleted.\n");
			}
		}
		else if( s == '4' )
		{//GetHash
			//キー値を入力
			printf("Please input key.\n");
			printf("Key :");	scanf("%s%*c",Key);
			
			printf("Hash of \"%s\" = %d\n",Key,Hash_Get(Key));
		}
		else if( s == '0' )
		{
			break;	//ループを抜ける
		}
		else
		{
			;
		}

		puts("");
	}

	//終了用
	Chain_Finalize();
}

int main(void)
{
	Task_13_2();

	system("pause");
	return 0;
}

