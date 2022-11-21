#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "variable.h"

void show(void)
{
    for (int i = 0; i < size; i++)
    {
        printf("    ");
        for (int j = 0; j < size; j++)
            printf("%02d ", mat[i][j]);
        putchar('\n');
    }
    if (duplicate)
        for (int i = 0; i < size; i++)
        {
            fprintf(duplicate,"    ");
            for (int j = 0; j < size; j++)
                fprintf(duplicate,"%02d ", mat[i][j]);
            putc('\n', duplicate);
        }    
    putc('\n', duplicate);
}
void line(int width)
{
    for (int i = 0; i < size; i++)
    {
        putchar('+');
        for (int i = 0; i < width; i++)
        {
            putchar('-');
        }
    }
    printf("+\n");
}
void show_in_box(void)
{
    int max = mat[0][0];
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (max < mat[i][j])
                max = mat[i][j];
    int width = 1;
    while (max/(int)(pow(10, width))>9)
        width++;
    for (int i = 0; i < size; i++)
    {
        line(width);
        for (int j = 0; j < size; j++)
            printf("|%*d", width, mat[i][j]);
        printf("|\n");
    }
    line(width);
}
// produce_random() is used to generate a sizebysize matrix with random integer value in
// range[0, 20], and then print it
void produce_a(void)
{
    srand(time(0));
    int count0 = 0; 
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (mat[i][j] == 0)
                count0++;
    int num = (int)(count0 * rand_ratio/100);
    int count = 0;
    while (count != num)
    {
        int target = rand() % (size*size);
        int x = target/size, y = target%size;
        if (mat[x][y] == 0)
        {
            mat[x][y] = rand()%20+1;
                count++;
        }
    }
}
// produce_pow2() is used to generate a sizebysize matrix with selected ratio of power-2
// integers and fill the rest with 0
void produce_b(void)
{
    srand(time(0));
    int flag = 0;
    while(!flag)
    {
        int target = rand() % (size*size);
        int x = target/size, y = target%size;
        if (mat[x][y] == 0)
        {
            mat[x][y] = (rand()%2+1)*2;
            flag = 1;
        }                   
    }
}
void produce(void)
{
    if (rand_ratio == 0)
        produce_b();
    else
        produce_a();
}
// swap(a, b) is used to communicate the value of a with that of b (both of which are int type)
// This is set up for the repose() defined below
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
// compress(mat, direct) is used to compress it.
// The direction is determined by the first character in the direct string.
void compress(char *a)
{
    switch (*a)
    {
    case 'u':
    case 'U':
        for (int i = 0; i < size; i++)
            for (int j = 1; j < size; j++)
                mat[0][i] += mat[j][i];
        for (int j = 1; j < size; j++)
            for (int i = 0; i < size; i++)
                mat[j][i] = 0;
        break;
    case 'd':
    case 'D':
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size-1; j++)
                mat[size-1][i] += mat[j][i];
        for (int j = 0; j < size-1; j++)
            for (int i = 0; i < size; i++)
                mat[j][i] = 0;
        break;
    case 'l':
    case 'L':
        for (int i = 0; i < size; i++)
            for (int j = 1; j < size; j++)
                mat[i][0] += mat[i][j];
        for (int j = 1; j < size; j++)
            for (int i = 0; i < size; i++)
                mat[i][j] = 0;
        break;
    case 'r':
    case 'R':
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size-1; j++)
                mat[i][size-1] += mat[i][j];
        for (int j = 0; j < size-1; j++)
            for (int i = 0; i < size; i++)
                mat[i][j] = 0;
        break;
    default:
        printf("No such options, will compress it downward by default.\n");
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size-1; j++)
                mat[size-1][i] += mat[j][i];
        for (int j = 0; j < size-1; j++)
            for (int i = 0; i < size; i++)
                mat[j][i] = 0;
    }
}
// rotate() is used to rotate the matrix
void rotate(void)
{
    int temp[size][size];
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            temp[i][j] = mat[3 - j][i];
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            mat[i][j] = temp[i][j];
}
// repose() is uesd to set all zeros in every column in the upper part
void repose(void)
{
    for (int j = 0; j < size; j++)
        for (int i = 3; i >= 1; i--)
            if (mat[i][j] == 0)
                for (int m = i - 1; m >= 0; m--)
                    if (mat[m][j] != 0)
                    {
                        swap(&mat[m][j], &mat[i][j]);
                        break;
                    }
}
// combine() is used to combine equal neighbour elements
void combine(void)
{
    repose();
    for (int j = 0; j < size; j++)
    {
        int flag = 0;
        do
        {
            for (int i = 0; i < 3; i++)
                if (mat[i][j] == mat[i + 1][j] && mat[i][j] != 0)
                {
                    mat[i][j] = 0;
                    mat[i + 1][j] *= 2;
                }
            for (int i = 0; i < 3; i++)
                if (mat[i][j] == mat[i + 1][j] && mat[i][j] != 0)
                    flag = 1;
        } while (flag);
    }
    repose();
    int flag = 0;
    for (int j = 0; j < size; j++)
    {
        for (int i = 0; i < 3; i++)
            if (mat[i][j] == mat[i + 1][j] && mat[i][j] != 0)
                flag = 1;
    }
    if (flag)
        combine();
}