/*
	算術式を読み込み、トークンごとにスペースを入れるプログラム
	最終更新	:2022/02/11
*/
/*
	関数「Get_Token」について
	宣言	char Get_Token();
	概略	入力された文字列をトークンごとに解析します。
	引数	ありません。
	戻り値	トークンの属性を返します。
			return EOF	:ファイルの終端であること
			return NUM	:トークンが数字であったこと(小数含む)
			return token:トークンが数字意外であったこと
	解説	入力された文字列を1文字ずつ読み取り、演算子であるか数字であるかを判別します。
			対応する演算子は次の通りです。
			・加算:+
			・減算:-
			・乗算:*
			・除算:/
			・左かっこ:(
			・右かっこ:)
			演算子でも数字でもない場合は「'E'」が、数字の場合は「'N'」が返されます。
			
	
	メイン関数について
	概略	入力された算術式に対しトークンごとにスペースを入れていきます。
	解説	Get_Tokenによりトークンの属性を取得し、トークンごとにスペースを入れた文字列を生成します。
*/
/*
	関数の実態
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//字句の種別
#define	NUM	('N')	//数字
#define	LPAR ('(')	//左かっこ
#define RPAR (')')	//右かっこ
#define PLUS ('+')	//たす
#define MINUS ('-')	//ひく
#define MUL ('*')	//かける
#define DIV ('/')	//わる
#define ERR	('E')	//エラー

//文字列の長さ
#define STRING_LENGTH (256)

//バッファ
#define BUFF_LENGTH (16)


//標準入力から読み込んだ文字を記憶
char C = ' ';
#define cget()	(C = getchar())
//読み込んだ文字が数字だった時のその値
float C_Value;
//読み込んだ文字による文字列
char C_String[STRING_LENGTH];


//字句を取得
char Get_Token()
{
	//雑用
	int i;

	//今記憶している文字が「スペース」「タブ」「改行」のいずれかの時
	while( C == ' ' || C == '\t' || C == '\n' )
	{
		//文字を取得しなおす
		cget();
	}
	
	//printf("C:%c\n",C);

	//もしファイルの最後であったら
	if( C == EOF )
	{
		//ファイルの最後であることを返す
		return (EOF);
	}

	//もし今記憶している文字が数字であったら
	if( C >= '0' && C <= '9' )
	{
		//その値を記憶
		C_Value = (float)(C - '0');
		//次の入力を取得
		cget();
		//取得した文字が数字のとき
		while( C >= '0' && C <= '9' )
		{
			//値を加えていく
			C_Value = 10.0 * C_Value + C - '0';

			//printf("C:%c\n",C);

			//次の入力を取得
			cget();
		}

		//もし小数点が入力されたら
		if( C == '.' )
		{
			//printf("C:%c\n",C);
			//次の入力を取得
			cget();
			//小数点以下を値に加えていく
			i = 10;	//初期値は小数第一位(/10)
			while( C >= '0' && C <= '9' )
			{
				//値を加えていく
				C_Value = C_Value + (float)(C - '0')/i;
				//次の位
				i *= 10;
				
				//printf("C:%c\n",C);

				//次の入力を取得
				cget();
			}
		}

		//数字であったことを返す
		return (NUM);
	}

	//かっこや演算記号であったとき
	char token;
	switch(C)
	{
	case '(' :
		token = LPAR;	break;
	case ')' :
		token = RPAR;	break;
	case '+' :
		token = PLUS;	break;
	case '-' :
		token = MINUS;	break;
	case '*' :
		token = MUL;	break;
	case '/' :
		token = DIV;	break;
	default :
		token = ERR;	break;
	}

	//次の入力を取得
	cget();

	//かっこや演算記号であったことを返す
	return (token);
}



int main(void)
{
	char tmp_Get_Token;
	while((tmp_Get_Token = Get_Token()) != EOF)
	{
		char tmp_buf[BUFF_LENGTH];
		
		printf("Get_Token:%c\n",tmp_Get_Token);
		if( tmp_Get_Token == NUM )
		{
			sprintf_s(tmp_buf,BUFF_LENGTH,"%f",C_Value);
			strcat(C_String,tmp_buf);
			printf("C_Value:%f\n",C_Value);
		}
		else
		{
			sprintf_s(tmp_buf,BUFF_LENGTH,"%c",tmp_Get_Token);
			strcat(C_String,tmp_buf);
		}
		sprintf_s(tmp_buf,BUFF_LENGTH,"%c",' ');
		strcat(C_String,tmp_buf);
	}

	printf("Input:%s\n",C_String);

	system("pause");
	return 0;
}

