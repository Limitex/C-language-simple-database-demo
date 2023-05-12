#include "commands.h"

int COMMNAD_UPDATE(LINE* db, char** commands)
{
    char** set_data = (char**)calloc(0, 0);
    char** where = (char**)calloc(0, 0);

    // 入力されたデータの分解と確認
    int read_state = 0;
    char** cmds_p = commands;
    while (*cmds_p != NULL)
    {
        if (cmpcmp(*cmds_p, COMMAND_WHERE_CLAUSE))
        {
            read_state = 1;
            cmds_p++;
            continue;
        }
        switch (read_state)
        {
            case 0:
                set_data = add_strstr(set_data, *cmds_p);
                break;
            case 1:
                where = add_strstr(where, *cmds_p);
                break;
        }
        cmds_p++;
    }
    int column_index;
    if (strstrlen(set_data) != 3)
    {
        printf("The condition of Where is wrong.\n");
        return -1;
    }
    if ((column_index = get_column_index(db->data, *set_data)) == -1)
    {
        printf("The specified column name was not found.\n");
        return -1;
    }
    if (!cmpcmp(*(set_data + 1), COMMAND_WHERE_EQUALS_SIGN))
    {
        printf("The assignment operator is different\n");
        return -1;
    }
    char* change_str = *(set_data + 2);
    if(strlen(change_str) >= STR_LEN)
    {
        printf("Cannot be changed to more than %d characters.\n", STR_LEN);
        return -1;
    }
    
    LINE* data = db;
    if (strstrlen(where) != 0)
    {
        data = extract_by_where(data, where);
        if (line_count(data) == 1)
        {
            printf("No data was found under the specified conditions.\n");
            return 0;
        }
        if (data == NULL) return -1;
    }

    // Update 処理
    LINE* update_data = data->next;
    while (update_data != NULL)
    {
        NODE* r_data = reference_from_index(update_data->data, column_index);
        strcpy(r_data->data, change_str);
        update_data = update_data->next;
    }
    print_list(data);
    printf("\nThe operation was successful.\n");
    return 0;
}