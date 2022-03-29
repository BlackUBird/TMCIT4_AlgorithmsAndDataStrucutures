/*
	各ソートの安定性を比較するプログラム
	最終更新	:2021/09/12
*/
/*
	各関数について
	「Sort_Simple」「Sort_Bubble」「Sort_Selection」「Sort_Insertion」「Sort_Shell」「Sort_Quick」「Sort_Merge」
	　ソート関数です。
	
	「Product_Merge_Sort」
	　関数「Sort_Merge」を扱うためのマネージャーです。受けたデータを細分化し、それらをSort_Mergeに渡してソートしていきます。
	　
	「Product_Draw」
	　データの表示用です。
	
	「main」
	　各ソートの結果を確認します。ソートするたびにデータの初期化を行うため、データ用構造体配列を2つ用意して、
	作業用と初期化用としています。
*/
/*
	関数の実態
*/
/*
	各ソートの安定性を比較する
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRODUCT_MAX	(10)	//商品の数
#define PRODUCT_MAX_NAME (20)	//商品名の最長

//商品用構造体
typedef struct
{
	int Number;	//商品番号
	char Name[PRODUCT_MAX_NAME];	//商品名
	int Price;	//価格
} PRODUCT;

//単純なソート
void Sort_Simple(PRODUCT Data[],int DataMax)
{
	for(int i = 0 ; i < DataMax ; i++)
	{
		for(int j = i+1 ; j < DataMax ; j++)
		{
			if( Data[i].Price > Data[j].Price )
			{
				PRODUCT tmp = Data[i];
				Data[i] = Data[j];
				Data[j] = tmp;
			}
		}
	}
}

//バブルソート
void Sort_Bubble(PRODUCT Data[],int DataMax)
{
	for(int i = 0 ; i < DataMax ; i++)
	{
		for(int j = 1 ; j < DataMax-i ; j++)
		{
			if( Data[j-1].Price > Data[j].Price )
			{
				PRODUCT tmp = Data[j-1];
				Data[j-1] = Data[j];
				Data[j] = tmp;
			}
		}
	}
}

//選択ソート
void Sort_Selection(PRODUCT Data[],int DataMax)
{
	for(int i = 0 ; i < DataMax ; i++)
	{
		int MinIndex = i;
		PRODUCT MinData = Data[i];
		for(int j = i+1 ; j < DataMax ; j++)
		{
			if( Data[j].Price < MinData.Price )
			{
				MinIndex = j;
				MinData = Data[j];
			}
		}
		Data[MinIndex] = Data[i];
		Data[i] = MinData;
	}
}

//挿入ソート
void Sort_Insertion(PRODUCT Data[],int DataMax)
{
	int j;	//雑用
	//ソートする系列を変化させるループ
	for(int i = 1 ; i < DataMax ; i++)
	{
		PRODUCT MinData = Data[i];	//最初の値を今のところの最小値として保持
		//系列内のデータを比較、保持していくループ
		for(j = i-1 ; j >= 0 && Data[j].Price > MinData.Price ; j--)
		{
			Data[j+1] = Data[j];
		}
		Data[j+1] = MinData;
	}
}

//シェルソート
void Sort_Shell(PRODUCT Data[],int DataMax)
{
	int j;	//雑用
	//ソートする系列を変化させるループ
	for(int h = DataMax/2 ; h > 0 ; h = h/2)
	{
		//各系列ごとにソートするループ
		for(int i = h ; i < DataMax ; i++)
		{
			PRODUCT MinData = Data[i];	//最初の値を今のところの最小値として保持
			//各系列内のデータを比較、保持していくループ
			for(j = i-h ; j >= h-1 && Data[j].Price > MinData.Price ; j-=h)
			{
				Data[j+h] = Data[j];	//データをずらす
			}
			Data[j+h] = MinData;	//挿入
		}
	}
}

//クイックソート
void Sort_Quick(PRODUCT Data[],int StartOfData,int EndOfData)
{
	if( StartOfData >= EndOfData )
	{
		return;
	}

	int i,j;	//雑用
	int PlaceOfPivot;	//ピボットの位置を記憶
	PRODUCT Pivot;	//ピボットの値を記憶

	PlaceOfPivot = (StartOfData+EndOfData)/2;	//ピボットの位置をソート範囲の中間にする

	Pivot = Data[PlaceOfPivot];	//

	//走査用の数値を設定
	i = StartOfData;
	j = EndOfData;

	//ソート
	while( i <= j )
	{
		//ピボットより小さい値が見つかるまで
		//データの始点から終点に向けて走査していく
		while( Data[i].Price < Pivot.Price )
		{
			i++;
		}
		//ピボットより大きい値が見つかるまで
		//データの終点から支店に向けて走査していく
		while( Data[j].Price > Pivot.Price )
		{
			j--;
		}
		//もし、上2つの走査線が交差していたら
		//入れ替え・走査線の移動を行う
		if( i <= j )
		{
			//入れ替え
			PRODUCT tmp = Data[i];
			Data[i] = Data[j];
			Data[j] = tmp;

			//移動(両方1進める)
			i++;
			j--;
		}
	}

	Sort_Quick(Data,StartOfData,j);	//データの始点側を再ソート
	Sort_Quick(Data,i,EndOfData);	//データの終点側を再ソート
}

void Product_Draw(PRODUCT Data[])
{
	printf("商品番号 %s\t\t価格\n","商品名");
	for(int i = 0 ; i < PRODUCT_MAX ; i++)
	{
		printf("%04d\t%-10s\t%4d\n",Data[i].Number,Data[i].Name,Data[i].Price);
	}
}

void Product_Draw_Inverse(PRODUCT Data[])
{
	printf("商品番号 %s\t\t価格\n","商品名");
	for(int i = PRODUCT_MAX-1 ; i >=0  ; i--)
	{
		printf("%04d\t%-10s\t%4d\n",Data[i].Number,Data[i].Name,Data[i].Price);
	}
}

//マージソート
int Sort_Merge(PRODUCT Data1[],int Data1Max,
			   PRODUCT Data2[],int Data2Max,
			   PRODUCT ResultData[])
{
	int i,j,k;	//雑用
	i = j = k = 0;

	//両データを比較・ソートしつつ併合していく
	while( i < Data1Max && j < Data2Max )
	{
		if(Data1[i].Price <= Data2[j].Price)
		{
			ResultData[k++] = Data1[i++];
		}
		else
		{
			ResultData[k++] = Data2[j++];
		}
	}

	//余ったデータを併合していく
	while(i < Data1Max)
	{
		ResultData[k++] = Data1[i++];
	}
	while(j < Data2Max)
	{
		ResultData[k++] = Data2[j++];
	}

	return (Data1Max+Data2Max);
}

//商品データをマージソートする
void Product_Merge_Sort(PRODUCT Data[],int DataMax)
{
	int i,j,k;	//雑用

	//作業用配列を作成
	PRODUCT* tmp = (PRODUCT*)malloc(sizeof(PRODUCT)*DataMax);
	PRODUCT* tmp2 = (PRODUCT*)malloc(sizeof(PRODUCT)*DataMax);
	//更新用
	PRODUCT* tmptmp;

	//ソート・マージを行う
	i = 2;
	while(i<DataMax)
	{
		//作業用配列を設定
		tmptmp = (PRODUCT*)realloc(tmp,sizeof(PRODUCT)*(i/2));
		if(tmptmp == NULL)
		{
			free(tmp);
			return;
		}
		else
		{
			tmp = tmptmp;
		}
		tmptmp = (PRODUCT*)realloc(tmp2,sizeof(PRODUCT)*(i/2));
		if(tmptmp == NULL)
		{
			free(tmp);
			free(tmp2);
			return;
		}
		else
		{
			tmp2 = tmptmp;
		}

		//ソート
		for(j = 0 ; j + i/2 < DataMax ; j+=i)
		{
			//作業用配列にソートすべきデータの前半・後半部分を代入
			for(k = 0 ; k < i/2 ; k++)
			{
				tmp[k] = Data[j+k];
				tmp2[k] = Data[j+k+i/2];
			}

			//マージソート
			Sort_Merge(tmp,i/2,tmp2,i/2,&Data[j]);
		}

		i *= 2;
	}

	//余った部分をマージソート
	i /= 2;	//ソートし終わった部分
	////作業用配列を作成
	//PRODUCT* tmp;
	//ソート済み配列と余った1個でマージソート
	//データ数-1=ソート済みが入る配列を用意
	tmptmp = (PRODUCT*)realloc(tmp,sizeof(PRODUCT)*i);
	if(tmptmp == NULL)
	{
		free(tmp);
		free(tmp2);
		free(tmptmp);
		return;
	}
	else 
	{
		tmp = tmptmp;
	}
	//ソート済み部分を記憶
	for(k = 0 ; k < i ; k++)
	{
		tmp[k] = Data[k];
	}
	//余りが入る配列を用意
	tmptmp = (PRODUCT*)realloc(tmp2,sizeof(PRODUCT)*(DataMax-i));
	if(tmptmp == NULL)
	{
		free(tmp);
		free(tmp2);
		free(tmptmp);
		return;
	}
	else 
	{
		tmp2 = tmptmp;
	}
	for(k = 0 ; k < DataMax-i ; k++)
	{
		tmp2[k] = Data[i+k];
	}
	//ソート
	Sort_Merge(tmp,i,tmp2,DataMax-i,Data);

	//メモリ解放
	free(tmp);
}

int main(void)
{
	//商品データ
	PRODUCT nowProduct[PRODUCT_MAX] =
	{
		{1,"G牛乳",120},
		{2,"Pプリン",80},
		{3,"JEゼリー",60},
		{4,"JUジュース",80},
		{5,"Cコーヒー",90},
		{6,"A",60},
		{7,"B",70},
		{8,"C",110},
		{9,"D",95},
		{10,"E",80},
	};

	//商品データ(初期化用)
	PRODUCT initProduct[PRODUCT_MAX];
	for(int i = 0 ; i < PRODUCT_MAX ; i++)
	{
		initProduct[i] = nowProduct[i];
	}

	//そのままを表示
	puts("そのまま");
	Product_Draw(nowProduct);

	//SimpleSort
	puts("シンプルソート");
	Sort_Simple(nowProduct,PRODUCT_MAX);	//ソート
	Product_Draw(nowProduct);	//表示
	//初期化
	for(int i = 0 ; i < PRODUCT_MAX ; i++)
	{
		nowProduct[i] = initProduct[i];
	}

	//BubbleSort
	puts("バブルソート");
	Sort_Bubble(nowProduct,PRODUCT_MAX);	//ソート
	Product_Draw(nowProduct);	//表示
	//初期化
	for(int i = 0 ; i < PRODUCT_MAX ; i++)
	{
		nowProduct[i] = initProduct[i];
	}

	//SelectionSort
	puts("選択ソート");
	Sort_Selection(nowProduct,PRODUCT_MAX);	//ソート
	Product_Draw(nowProduct);	//表示
	//初期化
	for(int i = 0 ; i < PRODUCT_MAX ; i++)
	{
		nowProduct[i] = initProduct[i];
	}

	//InsertionSort
	puts("挿入ソート");
	Sort_Insertion(nowProduct,PRODUCT_MAX);	//ソート
	Product_Draw(nowProduct);	//表示
	//初期化
	for(int i = 0 ; i < PRODUCT_MAX ; i++)
	{
		nowProduct[i] = initProduct[i];
	}

	//ShellSort
	puts("シェルソート");
	Sort_Shell(nowProduct,PRODUCT_MAX);		//ソート
	Product_Draw(nowProduct);	//表示
	//初期化
	for(int i = 0 ; i < PRODUCT_MAX ; i++)
	{
		nowProduct[i] = initProduct[i];
	}

	//QuickSort
	puts("クイックソート");
	Sort_Quick(nowProduct,0,PRODUCT_MAX);	//ソート
	Product_Draw(nowProduct);	//表示
	//初期化
	for(int i = 0 ; i < PRODUCT_MAX ; i++)
	{
		nowProduct[i] = initProduct[i];
	}

	//MergeSort
	puts("マージソート");
	Product_Merge_Sort(nowProduct,PRODUCT_MAX);	//ソート
	Product_Draw(nowProduct);	//表示
	//初期化
	for(int i = 0 ; i < PRODUCT_MAX ; i++)
	{
		nowProduct[i] = initProduct[i];
	}

	system("pause");

	return 0;
}


