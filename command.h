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
int instant(char ch)
{
    char ins[5] = "klij";
    int t = strchr(ins, ch)-ins;
    int isfull = 1;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if(mat[i][j] == 0)
                isfull = 0;
        } 
    }
    int temp[100][100];
    memcpy(temp, mat, sizeof(mat));
    for (int i = 0; i < t; i++)
    {
        rotate();
    }
    combine();
    for (int i = 0; i < 4-t; i++)
    {
        rotate();
    }
    int flag = 1;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (mat[i][j] != temp[i][j])
                flag = 0;
        }
    }
    if (flag&&isfull)
    {
        printf("Game Over!\n");
        return 1;
    }
    produce();
    show();
    return 0;
}