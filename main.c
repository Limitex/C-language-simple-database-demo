#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "str_read/str_read.h"
#include "database/database.h"
#include "commands/commands.h"

#define COMMAND_DELIMITER " "

LINE* DB_DATA = NULL;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {   
        printf("Enter the csv file path > ");
        char *read = read_line();
        DB_DATA = read_csv_data(read);
    }
    else
    {
        DB_DATA = read_csv_data(argv[1]);
    }

    if (DB_DATA == NULL)
    {
        printf("\x1b[31mFile is not found.\x1b[0m\n");
        return -1;
    }

    while (1)
    {
        printf("\n>>> ");
        char** commands = split(read_line(), COMMAND_DELIMITER);
        int cmd_find_flug = 1;

        if (cmpcmp(*commands, COMMAND_ROOT_EXIT)) break;
        if (cmpcmp(*commands, COMMAND_ROOT_SELECT)) cmd_find_flug = COMMAND_SELECT(DB_DATA, commands + 1);
        if (cmpcmp(*commands, COMMAND_ROOT_INFO)) cmd_find_flug = COMMAND_INFO(DB_DATA, commands + 1);
        if (cmpcmp(*commands, COMMAND_ROOT_UPDATE)) cmd_find_flug = COMMNAD_UPDATE(DB_DATA, commands + 1);
        if (cmpcmp(*commands, COMMAND_ROOT_INSERT)) cmd_find_flug = COMMNAD_INSERT(DB_DATA, commands + 1);

        if(cmd_find_flug == 1) printf("The command entered was not found.\nThe command can be found in \"info help\"");
        if(cmd_find_flug == -1) printf("The command entered failed.\n");
    }
    printf("\nbye.\n");
    return 0;
}