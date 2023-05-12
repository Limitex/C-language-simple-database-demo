#include "extract.h"

// 文字列を指定文字と指定量分左詰めする
char* right_justified(char* str, int count, char c)
{
    int len = strlen(str) + 1;
    int newLen = len + count;
    char* result = (char*)calloc(newLen, sizeof(char));
    for(int i = 0; i < newLen; i++)
    {
        if (i < count) *(result + i) = c;
        else *(result + i) = *(str + i - count);
    }
    return result;
}

// 比較記号から比較して返す
int cmp_by_sign(char* str1, char* str2, char* sign)
{
    int leng = strlen(str1) - strlen(str2);
    if (leng != 0)
    {
        if (leng > 0) str2 = right_justified(str2, leng, ' ');
        else str1 = right_justified(str1, -leng, ' ');
    }
    if (cmpcmp(sign, COMMAND_WHERE_GREATER_SIGN)) // ">"
        return strcmp(str1, str2) > 0;
    if (cmpcmp(sign, COMMAND_WHERE_LESSER_SIGN)) // "<"
        return strcmp(str1, str2) < 0;
    if (cmpcmp(sign, COMMAND_WHERE_EQUALS_SIGN)) // "="
        return strcmp(str1, str2) == 0;
    if (cmpcmp(sign, COMMAND_WHERE_GREATER_EQUALS_SIGN)) // ">="
        return strcmp(str1, str2) > 0 || strcmp(str1, str2) == 0;
    if (cmpcmp(sign, COMMAND_WHERE_LESSER_EQUALS_SIGN)) // "<="
        return strcmp(str1, str2) < 0 || strcmp(str1, str2) == 0;
    return -1;
}

LINE* extract_by_where(LINE* db, char** where)
{
    // 指定コマンドの確認
    if (strstrlen(where) != 3)
    {
        printf("The condition of Where is wrong.\n");
        return NULL;
    }
    if (get_column_index(db->data, *where) == -1)
    {
        printf("The specified column name was not found.\n");
        return NULL;
    }
    char* sign = *(where + 1);
    if (!cmpcmp(sign, COMMAND_WHERE_GREATER_SIGN) &&
        !cmpcmp(sign, COMMAND_WHERE_LESSER_SIGN) &&
        !cmpcmp(sign, COMMAND_WHERE_EQUALS_SIGN) &&
        !cmpcmp(sign, COMMAND_WHERE_GREATER_EQUALS_SIGN) &&
        !cmpcmp(sign, COMMAND_WHERE_LESSER_EQUALS_SIGN))
    {
        printf("The comparison specifier is different.\n");
        return NULL;
    }

    // 処理本体
    char* cmd_column_name = *where;
    char* cmd_sign = *(where + 1);
    char* cmd_sign_column = *(where + 2);

    int column_index = get_column_index(db->data, cmd_column_name);

    LINE* result = NULL;
    LINE* db_p = db->next;
    result = add_line(result, db->data);
    while (db_p != NULL)
    {
        char* cmp_data = reference_from_index(db_p->data, column_index)->data;
        if (cmp_by_sign(cmp_data, cmd_sign_column, cmd_sign))
            result = add_line(result, db_p->data);
        db_p = db_p->next;
    }
    return result;
}
