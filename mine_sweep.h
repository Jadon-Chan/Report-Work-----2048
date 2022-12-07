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
void mapline(void)
{
    for (int i = 0; i < size; i++)
    {
        cout << "+-";
    }
    cout << '+' << endl;
}
void show_mark_box(void)
{
    for (int i = 1; i <= size; i++)
    {
        mapline();
        for (int j = 1; j <= size; j++)
        {
            cout << '|' << mark[i][j];
        }
        cout << '|' << endl;
    }
    mapline();
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
    //int count is set to the number of mines in the map
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
    //int marked is to indicate the number of mines marked by player
    //int revealed is to indicate the number of pitches that player has revealed
    if (marked == count || revealed == size * size - count)
    {
        return 1;
    }
    else
        return 0;
    // if all the mines have been marked, return true
    // or if all the pitches have been uncovered, return false
}
void expand(int x, int y)
{
    mark[x][y] = '-';
    //the found 0 is assigned to '-'
    for (int i = x - 1; i <= x + 1; i++)
    {
        for (int j = y - 1; j <= y + 1; j++)
        {
            if (map[i][j] >= '1' && map[i][j] <= '8' && (mark[i][j] == ' ' || mark[i][j] == '#'))
            {
                mark[i][j] = map[i][j];
                //when the around elements are not 0's, reveal them.
            }
            else if (map[i][j] == '0' && (mark[i][j] == ' ' || mark[i][j] == '#'))
            {
                expand(i, j);
                //recursion is used to 'expand' the newly-found 0's
            }
        }
    }
}
void show_map_box(void)
{
    for (int i = 1; i <= size; i++)
    {
        mapline();
        for (int j = 1; j <= size; j++)
        {
            cout << '|' << map[i][j];
        }
        cout << '|' << endl;
    }
    mapline();
}

void coverall(void)
{
    for (int i = 1; i <= size; i++)
    {
        for (int j = 1; j <= size; j++)
        {
            if (map[i][j] == '*')
                mark[i][j] = '#';
            else if (map[i][j] == '0')
                mark[i][j] == '-';
            else
                mark[i][j] = map[i][j];
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
    if (box)
        show_mark_box();
    else
        showmark();
    char temp[100];
    while (1)
    {
        cin.getline(temp, 100);
        stringstream s(temp);
        char x, y;
        s >> x;
        if (x == '#')
        {
            s >> x >> y;
            x -= '0';
            y -= '0';
            while (!s.tellp())
            {
                if (mark[x][y] == ' ')
                {
                    mark[x][y] = '#';
                }
                s >> x >> y;
                x -= '0';
                y -= '0';
            }
            if (box)
                show_mark_box();
            else
                showmark();
            if (test())
            {
                cout << "You Win!" << endl;
                coverall();
                if (box)
                    show_mark_box();
                else
                    showmark();
                return;
            }
        }
        else
        {
            s >> y;
            x -= '0';
            y -= '0';
            if (map[x][y] == '*')
            {
                cout << "Game Over!" << endl;
                coverall();
                if (box)
                    show_mark_box();
                else
                    showmark();
                return;
            }
            else if (map[x][y] == '0')
            {
                expand(x, y);
                if (box)
                    show_mark_box();
                else
                    showmark();
            }
            else
            {
                mark[x][y] = map[x][y];
                if (box)
                    show_mark_box();
                else
                    showmark();
            }
            if (test())
            {
                cout << "You Win!" << endl;
                coverall();
                if (box)
                    show_mark_box();
                else
                    showmark();
                return;
            }
            s >> x >> y;
            x -= '0';
            y -= '0';
            while (!s.tellp())
            {
                if (map[x][y] == '*')
                {
                    cout << "Game Over!" << endl;
                    coverall();
                    if (box)
                        show_mark_box();
                    else
                        showmark();
                    return;
                }
                else if (map[x][y] == '0')
                {
                    expand(x, y);
                    if (box)
                        show_mark_box();
                    else
                        showmark();
                }
                else
                {
                    mark[x][y] = map[x][y];
                    if (box)
                        show_mark_box();
                    else
                        showmark();
                }
                if (test())
                {
                    cout << "You Win!" << endl;
                    coverall();
                    if (box)
                        show_mark_box();
                    else
                        showmark();
                    return;
                }
                s >> x >> y;
                x -= '0';
                y -= '0';
            }
        }
    }
}