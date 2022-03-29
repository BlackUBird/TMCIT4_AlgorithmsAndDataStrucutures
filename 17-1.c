/*
	BM法におけるスキップテーブルを表示するプログラム
	最終更新	:2022/02/01
*/
/*
	関数「Search_BM_GetSkipTable」について
	宣言	int Search_BM_GetSkipTable(int *skipTable,char *pattern);
	概略	スキップテーブルを取得します。
	引数	int *skipTable	:計算したスキップテーブルの各値を格納するための1次元配列
			char *pattern	:探索対象となる文字列
	戻り値	return changed	:変更箇所の数を返します。
	解説	パターンから、JIS8ビットコードに従ったスキップテーブルを作成します。
			取得したテーブルは1次元配列に格納されます。
	
	関数「Search_BM_DrawSkipTable」について
	宣言	int Search_BM_DrawSkipTable(int *skipTable);
	概略	スキップテーブルを表示します。
	引数	int *skipTable	:表示するスキップテーブル
	戻り値	return i	:表示されているスキップテーブルの値の総数
	解説	1次元配列からスキップテーブルを表示します。
	
	関数「Serch_BM」について
	宣言	int Serch_BM(char *text,char *pattern);
	概略	BM法で文字列を探索します。
	引数	char *text		:探索領域となる文字列を受けます。
			char *pattern	:探索対象の文字列を受けます。
	戻り値	return i	:探索に成功した場合に、その位置の開始地点を返します。
			return -1	:探索に失敗した場合-1を返します。
	解説	BM法により、探索領域の文字列から特定の文字列を探索し、その位置を返します。
	
	メイン関数について
	概略	スキップテーブルの表示をします。
	解説	文字列を"television"とした場合のスキップテーブルを表示します。
*/
/*
	関数の実態
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define JIS_8_MAX (256)

//スキップテーブルを取得
int Search_BM_GetSkipTable(int *skipTable,char *pattern)
{
	//パターンの長さ
	int length_pattern;
	length_pattern = strlen(pattern);
	
	//雑用
	int i;

	//過去の状態を記憶
	int* table_old;
	table_old = skipTable;
	
	//スキップテーブルの設定
	//各スキップ値の初期値を設定
	for(i = 0 ; i < JIS_8_MAX ; i++)
	{
		skipTable[i] = length_pattern;
	}

	//パターンに現れる文字について、スキップ値を更新
	for(i = 0 ; i < length_pattern-1 ; i++)
	{
		skipTable[ pattern[i] ] = length_pattern - 1 - i;
	}
	//パターンの最後に現れる文字のスキップ値は1
	skipTable[ pattern[length_pattern-1] ] = length_pattern - 1 - i;
	
	//変更箇所の数を記憶
	int changed = 0;
	for(i = 0 ; i < JIS_8_MAX ; i++)
	{
		if(skipTable[i] != table_old[i])
		{
			changed++;
		}
	}

	//変更箇所の数を返却
	return changed;
}
//スキップテーブルを表示
int Search_BM_DrawSkipTable(int *skipTable)
{
	//雑用
	int i;
	
	//説明を表示
	puts("Number of rows    :Upper 2 bits");
	puts("Number of columns :Lower 2 bits");
	puts("");

	//列番号を表示
	//行番号の位置と合わせるための調整
	printf("   ");
	//表示
	for(i = 0 ; i < 15 ; i++)
	{
		printf("%02d:",i);
	}
	printf("%02d\n",i);

	//表・行番号を表示
	for(i = 0 ; i < JIS_8_MAX ; i++)
	{
		if( i%16 == 0 )
		{//先頭なら行番号を表示
			printf("%02d:",i/16);
		}

		//テーブルの要素を表示
		printf("%2d",skipTable[i]);

		//補助文字を表示
		if( (i+1)%16 == 0 )
		{//表の右端に来た時
			//改行
			printf("\n");
		}
		else
		{//それ以外なら
			//カンマ
			printf(",");
		}
	}

	//iの最終的な値を返す(256のハズ)
	return i;
}


//BM法で文字列探索
int Serch_BM(char *text,char *pattern)
{
	//テキストの長さ、パターンの長さ
	int length_text;
	length_text = strlen(text);
	int length_pattern;
	length_pattern = strlen(pattern);
	
	//スキップテーブル
	int *table_skip;
	table_skip = (int*)calloc(JIS_8_MAX,sizeof(int));
	//スキップテーブルを取得
	Search_BM_GetSkipTable(table_skip,pattern);

	//雑用
	int i,j;
	
	//テキストとパターンを比較
	//テキスト開始位置を設定
	i=0;
	//比較
	while(i <= length_text - length_pattern)
	{
		//パターンの後ろから比較
		for(j = length_pattern-1 ; j >= 0 ; j--)
		{
			if(pattern[j] != text[i+j])
			{//現在地が不一致箇所であったら
				if(j == length_pattern-1)
				{//パターンの最後の文字で不一致ならば
					//テキストを1文字ずらす
					i++;
				}
				else
				{
					//次の位置をスキップ値から不一致が見つかった位置を引いたものにする
					i += table_skip[text[i+j]] - (length_pattern-1-j);
				}

				break;
			}

			if( j == 0)
			{//もし、先頭文字まで一致していたら
				//テキスト開始位置を返却
				return i;
			}
		}
	}

	//失敗(発見できず)
	return -1;
}

int main(void)
{
	int *skip;
	skip = (int *)calloc(JIS_8_MAX,sizeof(int));

	//スキップテーブルを取得
	Search_BM_GetSkipTable(skip,"television");

	//スキップテーブルを表示
	Search_BM_DrawSkipTable(skip);

	system("pause");
	return 0;
}

