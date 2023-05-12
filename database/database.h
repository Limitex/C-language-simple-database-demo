#ifndef _DATABASE_H_
#define _DATABASE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../str_read/str_read.h"

#define STR_LEN 256
#define STR_LINE_BUFFER_SIZE 2048

#define DELIMITER ","
#define BOM "\xef\xbb\xbf"
#define RETURN "\r"

typedef struct node {
    int* data_i;
    char data[STR_LEN];
    struct node *last;
    struct node *next;
    struct node *prev;
} NODE;
typedef struct line {
    struct node* data;
    struct line *last;
    struct line *next;
    struct line *prev;
} LINE;

// 行リストにデータを追加する
NODE* add_node(NODE* node, char data[STR_LEN]);

// 列リストにデータを追加する
LINE* add_line(LINE* line, NODE* data);

// csvからデータを読み込む
LINE* read_csv_data(char* filepath);

// 列の場所をindexから取得する
NODE* reference_from_index(NODE* node, int index);

// 行の数をカウントする。
int line_count(LINE* line);

// 列の数をカウントする
int node_count(NODE* node);

// 表を表示する
void print_list(LINE* data);

// 行を表示する
void print_node(NODE* data);

#endif // _DATABASE_H_