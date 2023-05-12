#ifndef _STR_READ_H_
#define _STR_READ_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// 文字列最後尾に文字を追加
// 引数strは初期化済みか、文字列が入っている必要がある
// str      : 追加先文字列
// c        : 追加する文字
// return   : 結果文字列へのポインタ
char* add_char(char* str, char c);

// 標準入力から可変長文字列入力を受け付ける
// return : 結果ポインタ
char* read_line();

// 文字列配列の行の数を取得
// str : 対象文字列
// return : 文字列の個数
int strstrlen(char** strstr);

// 文字列配列を表示
// strs : 対象文字列配列
void print_strs(char** strs);

// 文字列配列の末尾に文字列を追加する
// soruce : 追加先文字列配列
// str    : 追加する文字列
// return : 追加された後のポインタ
char** add_strstr(char** source, char* str);

// 区切り文字ごとに区切って配列にする
// str : 対象文字列
// c   : 区切り文字
char** split(char* str, char* c);

// 文字列同士を比較する
// str1, str2 : 比較対象文字列
// return : str1, str2 が同じ場合は１、違う場合は０
int cmpcmp(char* str1, char *str2);

// str1からstr2を削除する（最初にマッチしたものだけ）
// str1 : 被削除側文字列
// str2 : 削除、検索対象文字列
void delstr(char *str1, char *str2);

// 文字列が数字かどうかを調べる
// str : 対象
// return : 数字列の場合は１、文字列の場合は０
int isdigit_str(char* str);

// 高速に階乗の計算をする
// x : 底
// n : 指数
int fast_pow(int x, int n);

// 文字列をint型にキャストする
// str : 対象　文字列が全て数字である必要がある
int toInt(char* str);

#endif // _STR_READ_H_