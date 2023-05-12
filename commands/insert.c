#include "commands.h"

int COMMNAD_INSERT(LINE* db, char** commands)
{
    // 確認処理
    if (node_count(db->data) != strstrlen(commands))
    {
        printf("The number of data entered is different from the number of columns.\n");
        return -1;
    }
    char** d = commands;
    while (*d != NULL) 
    {
        if (strlen(*d++) > STR_LEN)
        {
            printf("The entered string exceeds the maximum value that can be saved.\n");
            return -1;
        }
    }

    // 処理
    char** data = commands;
    NODE* add_data = NULL;
    while (*data != NULL) add_data = add_node(add_data, *data++);
    db = add_line(db, add_data);
    printf("\nThe operation was successful.\n");
    return 0;
}