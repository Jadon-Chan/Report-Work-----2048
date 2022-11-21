#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "variable.h"

void minemap(void)
{
    int num = rand_ratio == -1 ? 1 : (int)(rand_ratio * size * size / 100);
    int count = 0;
    srand(time(0));
    while (1)
    {
        int pose = rand() % (size * size);
        int x = pose / size + 1, y = pose % size + 1;
        if (map[x][y] == '\0')
        {
            map[x][y] = '*';
            count++;
        }
        if (count == num)
            break;
    }
}
void sweep(int x, int y)
{
    int count = 0;
    for (int i = x - 1; i <= x + 1; i++)
        for (int j = y - 1; j <= y + 1; j++)
            if (map[i][j] == '*')
                count++;
    map[x][y] = '0' + count;
}
void fill(void)
{
    for (int i = 1; i <= size; i++)
        for (int j = 1; j <= size; j++)
            if (map[i][j] != '*')
                sweep(i, j);
}
void showmap(void)
{
    for (int i = 1; i <= size; i++)
    {
        for (int j = 1; j <= size; j++)
            putchar(map[i][j]);
        putchar('\n');
    }
    if (duplicate)
    {
        for (int i = 1; i <= size; i++)
        {
            for (int j = 1; j <= size; j++)
                putc(map[i][j], duplicate);
            putc('\n', duplicate);
        }
    }
}