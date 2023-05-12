#include "commands.h"

// NODEを入れ替える
void _swap(NODE** node1, NODE** node2)
{
    NODE *tmp = *node1;
    *node1 = *node2;
    *node2 = tmp;
}

// 大きさを比べる <- 数字を考慮せず、全てstrcmpのみで実行すると、10万行のデータでも高速に実行できる
int strcmp_i(NODE* node1, NODE* node2)
{
    if (node1->data_i != NULL && node2->data_i != NULL)
        return *(node1->data_i) - *(node2->data_i);
    else
        return strcmp(node1->data, node2->data);
}

// クイックソートする
void quick_sort(NODE** array, int left, int right, int colmun_index)
{
    int i = left, j = right, pivot = left;
    while (1)
    {
        while (strcmp_i(reference_from_index(array[i], colmun_index), 
                    reference_from_index(array[pivot], colmun_index)) < 0) i++;
        while (strcmp_i(reference_from_index(array[j], colmun_index), 
                    reference_from_index(array[pivot], colmun_index)) > 0) j--;
        if (i >= j) break;
        _swap(&array[i++], &array[j--]);
    }
    if (left < i - 1) quick_sort(array, left, i - 1, colmun_index);
    if (j + 1 < right) quick_sort(array, j + 1, right, colmun_index);
}

// 列名リストから一致した列を抽出
LINE* extract_by_column(LINE* db, char** columns)
{
    // 指定コマンドの抽出と確認
    if (strstrlen(columns) == 1 && cmpcmp(*columns, COMMAND_ALL_CLAUSE)) return db;
    int* indexs = get_column_indexs(db->data, columns), length = strstrlen(columns);
    int max_column = node_count(db->data);
    if (indexs == NULL)
    {
        printf("The column name was not found.\n");
        return NULL;
    }
    for(int i = 0; i < length; i++) if(indexs[i] > max_column) return NULL;
    
    // 抽出処理
    LINE* extracted_db = NULL;
    LINE* db_p = db;
    while (db_p != NULL)
    {
        NODE* extracted_node = NULL;
        for(int i = 0; i < length; i++)
        {
            NODE* find_node = reference_from_index(db_p->data, indexs[i]);
            extracted_node = add_node(extracted_node, find_node->data);
        }
        extracted_db = add_line(extracted_db, extracted_node);
        db_p = db_p->next;
    }
    return extracted_db;
}

// order_by句が入力された場合に実行 DESC無しで昇順、DESCありで降順
LINE* extract_by_order_by(LINE* db, char** order_by)
{
    // 指定コマンドの確認
    int desc_flug = 0;
    int cmd_len = strstrlen(order_by);
    if(cmd_len != 1 && cmd_len != 2)
    {
        printf("The condition of the Order by clause is incorrect.\n");
        return NULL;
    }
    if (get_column_index(db->data, *order_by) == -1)
    {
        printf("The specified column name was not found.\n");
        return NULL;
    }
    if (cmd_len == 2)
    {
        if (cmpcmp(*(order_by + 1), COMMAND_ORDER_BY_DESC_SIGN))
        {
            desc_flug = 1;
        }
        else
        {
            printf("The condition of the Order by clause is incorrect.\n");
            return NULL;
        }
    }

    // ソートのためにデータをLINE*型からNODE**型に変換
    int count = 0;
    LINE* db_p = db;
    NODE** array = (NODE**)calloc(line_count(db), sizeof(NODE*));
    while (db_p != NULL)
    {
        array[count] = (NODE*)calloc(1, sizeof(NODE));
        array[count] = db_p->data;
        db_p = db_p->next;
        count++;
    }

    quick_sort(array, 1, count - 1, get_column_index(db->data, *order_by));

    // クイックソートは昇順のみでするため、
    // NODE**型からLINE*型に変換するときに昇順か降順かでそのまま戻すか、逆から戻すかでわける
    LINE* result = NULL;
    if (desc_flug == 0)
    {
        for(int i = 0; i < count; i++) result = add_line(result, array[i]);
    }
    else
    {
        result = add_line(result, array[0]);
        for(int i = count - 1; i > 0; i--) result = add_line(result, array[i]);
    }

    return result;
}

int COMMAND_SELECT(LINE* db, char** commands)
{
    // 指定コマンドの確認と抽出
    char** column_name = (char**)calloc(0, 0);
    char** order_by = (char**)calloc(0, 0);
    char** where = (char**)calloc(0, 0);

    int read_state = 0;
    char** cmds_p = commands;
    while (*cmds_p != NULL)
    {
        if (cmpcmp(*cmds_p, COMMAND_ORDER_BY_CLAUSE) || cmpcmp(*cmds_p, COMMAND_WHERE_CLAUSE))
        {
            if(cmpcmp(*cmds_p, COMMAND_ORDER_BY_CLAUSE)) read_state = 1;
            if(cmpcmp(*cmds_p, COMMAND_WHERE_CLAUSE)) read_state = 2;
            cmds_p++;
            continue;
        }
        switch (read_state)
        {
            case 0:
                column_name = add_strstr(column_name, *cmds_p);
                break;
            case 1:
                order_by = add_strstr(order_by, *cmds_p);
                break;
            case 2:
                where = add_strstr(where, *cmds_p);
                break;
        }
        cmds_p++;
    }
    
    // 処理
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

    if (strstrlen(order_by) != 0)
    {
        data = extract_by_order_by(data, order_by);
        if (data == NULL) return -1;
    }

    if (strstrlen(column_name) != 0)
    {
        data = extract_by_column(data, column_name);
        if (data == NULL) return -1;
    }
    else
    {
        printf("Please specify a column.\n");
        return -1;
    }

    print_list(data);
    return 0;
}