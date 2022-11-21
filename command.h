#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "variable.h"

void lower(char *str)
{
    for (int i = 0; i < strlen(str); i++)
        if (isupper(str[i]))
            str[i] = tolower(str[i]);
}

void cope(FILE *cmd)
{
    char line[30];
    int count = 0;
    produce();
    show();
    while (fgets(line, 30, cmd))
    {
        count++;
        char op1[10], op2[10];
        sscanf(line, "%s %s", op1, op2);
        printf("Line %d:\n    %s", count, line);
        if (duplicate)
            fprintf(duplicate,"Line %d:\n    %s", count, line);
        lower(op1);
        lower(op2);
        if (strcmp(op1, "compress") == 0)
        {
            compress(op2);
            produce();
            show();
        }
        else if (strcmp(op1, "rotate") == 0)
        {
            rotate();
            show();
        }
        else if (strcmp(op1, "combine") == 0)
        {
            combine();
            produce();
            show();
        }
        else
        {
            printf("Line %d in cmd.txt is invalid operation!\n", count);
            if(duplicate)
                fprintf(duplicate, "Line %d in cmd.txt is invalid operation!\n", count);
        }
    }
}