#include "extract.h"

int* get_column_indexs(NODE* node, char** columns)
{
    int* indexs = (int*)calloc(strstrlen(columns), sizeof(int)), count = 0;
    char** colms_p = columns;
    while (*colms_p != NULL)
    {
        int find_flug = 0;
        int locate_count = 0;
        NODE *find_node_p = node;
        while (find_node_p != NULL)
        {
            if (cmpcmp(*colms_p, find_node_p->data)) { find_flug = 1; break; }
            locate_count++;
            find_node_p = find_node_p->next;
        }
        if (find_flug == 0) return NULL;
        indexs[count++] = locate_count;
        colms_p++;
    }
    return indexs;
}

int get_column_index(NODE* node, char* column)
{
    char** column_name = (char**)calloc(0, 0);
    column_name = add_strstr(column_name, column);
    int* indexs = get_column_indexs(node, column_name);
    if (indexs == NULL) return -1;
    return *indexs;
}