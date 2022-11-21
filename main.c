#include <stdio.h>
#include <string.h>
#include "configure.h"
#include "mine_sweep.h"
#include "operation.h"
#include "command.h"
int size;
double rand_ratio;
int mat[100][100] = {0};
char map[100][100] = {'\0'};
char logg[200] = {};
int box = 0;
FILE * duplicate;
int main(void)
{
    configure();
    FILE * cmd = fopen("D:\\Users\\JadonChan\\AppData\\Local\\Programs\\C\\2048\\cmd.txt", "r");
    if (!cmd)
    {
        minemap();
        fill();
        showmap();
    }
    else
    {
        cope(cmd);
    }
    return 0;
}
