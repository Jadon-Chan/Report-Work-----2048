#include <sstream>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "configure.h"
#include "mine_sweep.h"
#include "operation.h"
#include "command.h"
char mark[100][100] = {};
int size = -1;
double rand_ratio = -1;
int mat[100][100] = {0};
char map[100][100] = {'\0'};
char logg[200] = {};
int box = 0;
FILE *duplicate;
int main(void)
{
    configure();
    FILE *cmd = fopen("hahaD:\\Users\\JadonChan\\AppData\\Local\\Programs\\C\\2048\\cmd.txt", "r");
    if (cmd)
    {
        char temp[30];
        if (fgets(temp, 30, cmd) == 0)
        {
            produce();
            show();
            int count = 0;
            while (1)
            {
                char ch = getch();
                if (ch != 'q')
                {
                    count++;
                    printf("Move %d: %c\n", count, ch);
                    if (instant(ch))
                    {
                        return 0;
                    }
                }
                else
                {
                    break;
                }
            }
        }
        else
        {
            fseek(cmd, 0L, SEEK_SET);
            cope(cmd);
        }
    }
    else
    {
        configure();
        minemap();
        fill();
        showmap();
        
        play();
    }
    system("pause");
    return 0;
}
