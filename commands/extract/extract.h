#ifndef _EXTRACT_H_
#define _EXTRACT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../str_read/str_read.h"
#include "../../database/database.h"

#define COMMAND_WHERE_GREATER_SIGN ">"
#define COMMAND_WHERE_LESSER_SIGN "<"
#define COMMAND_WHERE_EQUALS_SIGN "="
#define COMMAND_WHERE_GREATER_EQUALS_SIGN ">="
#define COMMAND_WHERE_LESSER_EQUALS_SIGN "<="

// 列名から一致した列の場所をINTで返す
int get_column_index(NODE* node, char* column);

// 列名リストから一致した列の場所をINTリストで返す
int* get_column_indexs(NODE* node, char** columns);

// SELECT_ROOT where句が入力された場合に実行　入力された条件に一致するものを抽出
LINE* extract_by_where(LINE* db, char** where);

#endif // _EXTRACT_H_