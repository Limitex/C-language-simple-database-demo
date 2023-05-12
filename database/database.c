#include "database.h"

NODE* add_node(NODE* node, char data[STR_LEN])
{
    NODE* newNode = (NODE*)calloc(1, sizeof(NODE));
    strcpy(newNode->data, data);
    newNode->next = NULL;
    if (isdigit_str(data))
    {
        newNode->data_i = (int*)calloc(1, sizeof(int));
        *(newNode->data_i) = toInt(data);
    }
    else
    {
        newNode->data_i = NULL;
    }

    if (node == NULL)
    {
        newNode->last = newNode;
        newNode->prev = NULL;
        return newNode;
    }
    else
    {
        newNode->last = NULL;
        newNode->prev = node->last;
        node->last->next = newNode;
        node->last = newNode;
        return node;
    }
}

LINE* add_line(LINE* line, NODE* data)
{
    LINE* newLine = (LINE*)calloc(1, sizeof(LINE));
    newLine->data = data;
    newLine->next = NULL;
    if (line == NULL)
    {
        newLine->last = newLine;
        newLine->prev = NULL;
        return newLine;
    }
    else
    {
        newLine->last = NULL;
        newLine->prev = line->last;
        line->last->next = newLine;
        line->last = newLine;
        return line;
    }
}

LINE* read_csv_data(char* filepath)
{
    FILE* fp = fopen(filepath, "r");
    if (fp == NULL) return NULL;

    LINE* data = NULL;
    char contents[STR_LINE_BUFFER_SIZE];
    while (fscanf(fp, "%[^\n] ", contents) != EOF) {
        if (strstr(contents, BOM) != NULL) delstr(contents, BOM);
        if (strstr(contents, RETURN) != NULL) delstr(contents, RETURN);
        char* token = strtok(contents, DELIMITER);
        NODE* node = NULL;
        while (token != NULL) 
        {
            node = add_node(node, token);
            token = strtok(NULL, DELIMITER);
        }
        data = add_line(data, node);
    }
    fclose(fp);
    return data;
}

NODE* reference_from_index(NODE* node, int index)
{
    NODE* node_p = node;
    for(int i = 0; i < index; i++) node_p = node_p->next;
    return node_p;
}

int line_count(LINE* line)
{
    int count = 0;
    LINE* line_p = line;
    while (line_p != NULL)
    {
        count++;
        line_p = line_p->next;
    }
    return count;
}

int node_count(NODE* node)
{
    int count = 0;
    NODE* node_p = node;
    while (node_p != NULL)
    {
        count++;
        node_p = node_p->next;
    }
    return count;
}

void print_list(LINE* data)
{
    printf("\x1b[36m");
    print_node(data->data);
    printf("\x1b[39m");
    LINE* p = data->next;
    while (p != NULL)
    {
        print_node(p->data);
        p = p->next;
    }
}

void print_node(NODE* data)
{
    NODE* pp = data;
    while (pp != NULL)
    {
        printf("[%s] ", pp->data);
        pp = pp->next;
    }
    printf("\n");
}