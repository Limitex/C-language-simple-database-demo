#ifndef _COMMANDS_H_
#define _COMMANDS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../str_read/str_read.h"
#include "../database/database.h"
#include "extract/extract.h"

#define COMMAND_ROOT_EXIT "exit"
#define COMMAND_ROOT_SELECT "select"
#define COMMAND_ROOT_INFO "info"
#define COMMAND_ROOT_UPDATE "update"
#define COMMAND_ROOT_INSERT "insert"

#define COMMAND_ALL_CLAUSE "*"
#define COMMAND_ORDER_BY_CLAUSE "order_by"
#define COMMAND_WHERE_CLAUSE "where"

#define COMMAND_UPDATE_SUBS_CLAUSE "="

#define COMMAND_INFO_COLUMN_CLAUSE "column"
#define COMMAND_INFO_COUNT_CLAUSE "count"
#define COMMAND_INFO_HELP_CLAUSE "help"

#define COMMAND_ORDER_BY_DESC_SIGN "DESC"

// select コマンド実行時に引数と共に実行
int COMMAND_SELECT(LINE* db, char** commands);

// info コマンド実行時に引数と共に実行
int COMMAND_INFO(LINE* db, char** commands);

// update コマンド実行時に引数と共に実行
int COMMNAD_UPDATE(LINE* db, char** commands);

// isnert コマンド実行時に引数と共に実行
int COMMNAD_INSERT(LINE* db, char** commands);

#endif // _COMMANDS_H_