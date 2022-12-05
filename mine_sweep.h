#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "variable.h"
using namespace std;

void minemap(void)
{
    int num = (int)(rand_ratio * size * size / 100);
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
void showmark(void)
{
    for (int i = 1; i <= size; i++)
    {
        for (int j = 1; j <= size; j++)
            putchar(mark[i][j]);
        putchar('\n');
    }
}
bool test(void)
{
    int count = 0;
    for (int i = 1; i <= size; i++)
    {
        for (int j = 1; j <= size; j++)
        {
            if (map[i][j] == '*')
                count++;
        }
    }
    int marked = 0;
    int revealed = 0;
    for (int i = 1; i <= size; i++)
    {
        for (int j = 1; j <= size; j++)
        {
            if (mark[i][j] == '#' && map[i][j] == '*')
            {
                marked++;
            }
            if (map[i][j] != '*' && (mark[i][j] == '-' || mark[i][j] == map[i][j]))
            {
                revealed++;
            }
        }
    }
    if (marked == count || revealed == size * size - count)
    {
        return 1;
    }
    else
        return 0;
}
void expand(int x, int y)
{
    mark[x][y] = '-';
    for (int i = x - 1; i <= x + 1; i++)
    {
        for (int j = y - 1; j <= y + 1; j++)
        {
            if (map[i][j] >= '1' && map[i][j] <= '8' && (mark[i][j] == ' ' || mark[i][j] == '#'))
            {
                mark[i][j] = map[i][j];
            }
            else if (map[i][j] == '0' && (mark[i][j] == ' ' || mark[i][j] == '#'))
            {
                expand(i, j);
            }
        }
    }
}
void coverall(void)
{
    for (int i = 1; i <= size; i++)
    {
        for (int j = 1; j <= size; j++)
        {
            if (map[i][j] == '*')
                mark[i][j] == '#';
            else if (map[i][j] == '0')
                mark[i][j] == '-';
            else
                mark[i][j] == map[i][j];
        }
    }
}
void play(void)
{
    for (int i = 1; i <= size; i++)
    {
        for (int j = 1; j <= size; j++)
        {
            mark[i][j] = ' ';
        }
    }
    showmark();
    char temp[100];
    cin.getline(temp, 100);
    stringstream s(temp);
    int x, y;
    s >> x; 
    if (x == '#')
    {
        while (!s.str().empty())
        {
            s >> x >> y;
            if (mark[x][y] == ' ')
            {
                mark[x][y] = '#';
            }
        }
        showmark();
        if (test())
        {
            cout << "You Win!" << endl;
            coverall();
            showmark();
        }
    }
    else
    {
        s >> y;
        if (map[x][y] == '*')
        {
            cout << "Game Over!" << endl;
        }
        else if (map[x][y] == '0')
        {
            expand(x, y);
            showmark();
            if (test())
            {
                cout << "You Win!" << endl;
                coverall();
                showmark();
            }
        }
        else
        {
            mark[x][y] = map[x][y];
            showmark();
            if (test())
            {
                cout << "You Win!" << endl;
                coverall();
                showmark();
            }
        }
        while (!s.str().empty())
        {
            s >> x >> y;
            if (map[x][y] == '*')
            {
                cout << "Game Over!" << endl;
            }
            else if (map[x][y] == '0')
            {
                expand(x, y);
                showmark();
                if (test())
                {
                    cout << "You Win!" << endl;
                    coverall();
                    showmark();
                }
            }
            else
            {
                mark[x][y] = map[x][y];
                showmark();
                if (test())
                {
                    cout << "You Win!" << endl;
                    coverall();
                    showmark();
                }
            }
        }
    }
}