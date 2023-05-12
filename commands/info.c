#include "commands.h"

int COMMAND_INFO(LINE* db, char** commands)
{
    if (strstrlen(commands) != 1)
    {
        printf("The format is incorrect.\n");
        return -1;
    }

    char* cmd = *commands;
    if (cmpcmp(cmd, COMMAND_INFO_COLUMN_CLAUSE))
    {
        print_node(db->data);
    }
    else if (cmpcmp(cmd, COMMAND_INFO_COUNT_CLAUSE))
    {
        printf("%d lines\n", line_count(db) - 1);
    }
    else if(cmpcmp(cmd, COMMAND_INFO_HELP_CLAUSE))
    {
        printf(
            "%s\n"
                "\t[Column name or \"%s\"]...\n"
                    "\t\t(%s [Column name] [%s,%s,%s,%s,%s] [Target character])\n"
                    "\t\t(%s [Column name] [%s or nothing])\n"
            "%s\n"
                "\t[Column name] = [Set string]\n"
                "\t\t(%s [Column name] [%s,%s,%s,%s,%s] [Target character])\n"
            "%s\n"
                "\t[Column data]...\n"
            "%s\n"
                "\t%s\n"
                "\t%s\n"
                "\t%s\n"
            "%s",
            COMMAND_ROOT_SELECT,
                COMMAND_ALL_CLAUSE,
                    COMMAND_WHERE_CLAUSE,
                    COMMAND_WHERE_GREATER_SIGN,
                    COMMAND_WHERE_LESSER_SIGN,
                    COMMAND_WHERE_EQUALS_SIGN,
                    COMMAND_WHERE_GREATER_EQUALS_SIGN,
                    COMMAND_WHERE_LESSER_EQUALS_SIGN,
                    COMMAND_ORDER_BY_CLAUSE,
                    COMMAND_ORDER_BY_DESC_SIGN,
            COMMAND_ROOT_UPDATE,
                    COMMAND_WHERE_CLAUSE,
                    COMMAND_WHERE_GREATER_SIGN,
                    COMMAND_WHERE_LESSER_SIGN,
                    COMMAND_WHERE_EQUALS_SIGN,
                    COMMAND_WHERE_GREATER_EQUALS_SIGN,
                    COMMAND_WHERE_LESSER_EQUALS_SIGN,
            COMMAND_ROOT_INSERT,
            COMMAND_ROOT_INFO,
                COMMAND_INFO_COLUMN_CLAUSE,
                COMMAND_INFO_COUNT_CLAUSE,
                COMMAND_INFO_HELP_CLAUSE,
                COMMAND_ROOT_EXIT
        );
    }
    else return -1;
    return 0;
}