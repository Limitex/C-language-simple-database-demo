#include "str_read.h"

char* add_char(char* str, char c)
{
    int length = strlen(str) + 1;
    char* new_str = (char*)calloc(length + 1, sizeof(char));
    strcpy(new_str, str);
    *(new_str + length - 1) = c;
    *(new_str + length) = '\0';
    return new_str;
}

char* read_line()
{
    int count = 0;
    char* str = (char*)calloc(0, 0), input_char;
    while ((input_char = getchar()) != '\n') str = add_char(str, input_char);
    return str;
}

int strstrlen(char** strstr)
{
    if (strstr == NULL) return -1;
    int count = 0;
    while(*(strstr++) != NULL) count++;
    return count;
}

void print_strs(char** strs)
{
    if (strs == NULL) { printf("(null)\n"); return; }
    printf("[\n");
    while(*strs != NULL)
        printf("\t\"%s\"\n", *strs++);
    printf("]\n");
}

char** add_strstr(char** source, char* str)
{
    char** direction = (char**)calloc(strstrlen(source) + 2, sizeof(char*));
    char** source_p = source;
    char** direction_p = direction;
    while(*source_p != NULL)
    {
        *direction_p = (char*)calloc(strlen(*source_p) + 1, sizeof(char));
        strcpy(*direction_p, *source_p);
        direction_p++;
        source_p++;
    } 
    *direction_p = (char*)calloc(strlen(str) + 1, sizeof(char));
    strcpy(*direction_p, str);
    *(direction + strstrlen(direction)) = NULL;
    return direction;
}

char** split(char* str, char* c)
{
    char** strstr = (char**)calloc(0, 0);
    char* token = strtok(str, c);
    while (token != NULL) 
    {
        strstr = add_strstr(strstr, token);
        token = strtok(NULL, c);
    }
    return strstr;
}

int cmpcmp(char* str1, char *str2) 
{ 
    if (str1 == NULL || str2 == NULL) return 0;
    return strcmp(str1, str2) == 0; 
}

void delstr(char *str1, char *str2)
{
    str1 = strstr(str1, str2);
    int len = strlen(str2);
    for (int i = 0; i < strlen(str1); i++)
    {
        *(str1 + i) = *(str1 + len + i);
    }
}

int isdigit_str(char* str)
{
    for (char* s = str; *s != '\0'; s++) if (isdigit(*s) == 0) return 0;
    return 1;
}

int fast_pow(int x, int n) 
{
    int ret = 1;
    while (n > 0) {
        if (n & 1) ret *= x;
        x *= x;
        n >>= 1;
    }
    return ret;
}

int toInt(char* str)
{
    int result = 0;
    int len = strlen(str) - 1;
    for(char *p = str; *p != '\0'; p++)
    {
        result += fast_pow(10, len--) * (*p - '0');
    }
    return result;
}