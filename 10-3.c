/*
	学生ファイルの作成するプログラム
	最終更新	:2021/09/11
*/
/*
	関数「Student_Make_File()」について
	宣言	void Student_Make_File(void);
	概略	学生データファイルを作成します。
	引数	ありません。
	戻り値	ありません。
	解説	学生データをテキストファイルとして保存します。
	
	関数「Student_Read_File(STUDENT StudentData[])」について
	宣言	void Student_Read_File(STUDENT StudentData[]);
	概略	学生データファイルから読み取りを行います。
	引数	読み取ったデータを受け取るための変数へのポインタです。
	戻り値	ありません。
	解説	テキストファイルから学生データを読み取ります。学生用データ用構造体を型とするポインタが必要です
	
	関数「Student_Draw_Average(STUDENT StudentData[])」について
	宣言	void Student_Draw_Average(STUDENT StudentData[]);
	概略	学生データと平均を表示します。
	引数	表示するデータを格納した変数へのポインタ(配列)です。
	戻り値	ありません。
	解説	学生データと平均を標準ストリームへ出力します。
	
	関数「Student_QuickSort_Score(STUDENT st[],int left,int right)」について
	宣言	void Student_QuickSort_Score(STUDENT st[],int left,int right);
	概略	学生データを点数を基準にクイックソートでソートします。
	引数	st[]	:ソートするデータを格納した変数へのポインタ(配列)です。
			left,right :左右の初期位置となるインデックス番号です。
	戻り値	ありません。
	解説	学生データを点数をもとにソートします。
	
	
	メイン関数について
	概略	学生データを読み取り、成績上位者から順に表示をします。また、平均も表示します。
*/
/*
	関数の実態
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX (7)	//学生数

//学生用の構造体
typedef struct
{
	char number[10];
	char name[20];
	int score;
} STUDENT;

//学生データファイルを生成
void Student_Make_File(void)
{
	FILE* fp;	//ファイルポインタ用変数

	char fname[] = "student.txt";	//ファイル名

	//各学生のデータ
	STUDENT st[MAX] =
	{
		{"TL0070","吉田光子",80},
		{"TL0060","佐藤次郎",90},
		{"TL0070","鈴木三郎",78},
		{"TL0070","後藤司郎",95},
		{"TL0070","島田次子",88},
		{"TL0070","田中一子",75},
		{"TL0070","山田太郎",68},
	};

	if( (fp = fopen(fname,"w")) == NULL )
	{//開けなかった時
		printf("%s cannot be opened.",fname);
		exit(1);
	}
	else
	{//ファイルを作成できた、または開けた時
		//データの書き込み
		for(int i = 0 ; i < MAX ; i++)
		{
			fprintf(fp,"%s %s %d\n",st[i].number,st[i].number,st[i].score);
		}
	}

	//ファイルクローズ
	fclose(fp);
}

//学生データファイルから読み取り
void Student_Read_File(STUDENT StudentData[])
{
	FILE* fp;	//ファイルポインタ用変数

	char fname[] = "student.txt";	//ファイル名

	if( (fp = fopen(fname,"r")) == NULL )
	{//開けなかった時
		printf("%s cannot be opened.",fname);
		exit(1);
	}
	else
	{//ファイルを作成できた、または開けた時
		//仮置き変数
		char in_number[10];
		char in_name[20];
		int in_score;
		//雑用
		int i = 0;
		//読み取り
		while( fscanf(fp,"%s %s %d",in_number,in_name,&in_score) != EOF )
		{
			strcpy(StudentData[i].number,in_number);
			strcpy(StudentData[i].name,in_name);
			StudentData[i].score = in_score;
			i++;
		}
	}

	//ファイルクローズ
	fclose(fp);
}

//学生データの表示
void Student_Draw_Average(STUDENT StudentData[])
{
	//表示
	float ave = 0;	//平均算出用
	puts("------------------------------------");
	for(int i = MAX-1 ; i >= 0 ; i--)
	{
		//各学生の情報
		printf("%s %s %d\n",StudentData[i].number,StudentData[i].name,StudentData[i].score);
		ave += (float)StudentData[i].score;
	}
	puts("------------------------------------");
	printf("    平均点\t%.1f\n",ave/(float)MAX);
}

//点数を参照してクイックソート
void Student_QuickSort_Score(STUDENT st[],int left,int right)
{
	if( left >= right )
	{//left>=rightであれば終了
		return;
	}

	int i,j;	//雑用
	int somewhere;	//境界値の場所
	int pivot;	//境界値

	somewhere=(left+right)/2;	//境界値の場所
	pivot = st[somewhere].score;	//境界値の初期設定

	i = left;
	j = right;

	//ソート
	while(i<=j)
	{
		while( st[i].score < pivot )
		{
			i++;
		}

		while( st[j].score > pivot )
		{
			j--;
		}

		if( i <= j )
		{
			STUDENT tmp = st[i];
			st[i] = st[j];
			st[j] = tmp;
			i++;
			j--;
		}
	}

	//再帰呼び出し
	Student_QuickSort_Score(st,left,j);	//left-jをソート
	Student_QuickSort_Score(st,i,right);	//i-rightをソート
}

int main(void)
{
	//学生データを記憶
	STUDENT St[MAX];

	//ファイルを生成
	Student_Make_File();
	
	//ファイルから読み取り
	Student_Read_File(St);

	//ソート
	Student_QuickSort_Score(St,0,MAX-1);

	//表示
	Student_Draw_Average(St);

	system("pause");

	return 0;
}

