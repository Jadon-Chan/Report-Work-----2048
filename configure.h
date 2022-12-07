#include <stdio.h>
#include <string.h>
#include "variable.h"

void configure(void)
{
    FILE * ptr = fopen("D:\\Users\\JadonChan\\AppData\\Local\\Programs\\C\\2048\\config.txt", "r");
    char line[100];
    size = -1;
    rand_ratio = 0;
    if (!ptr)
    {
        size = 9;
        rand_ratio = 30;
        box = 1;
        return;
    }
    while (fgets(line, 100, ptr))
    {
        char temp[100];
        strcpy(temp, line);
        temp[7] = '\0';
        if (strcmp(temp, "SIZE = ") == 0)
        {
            double temp;
            sscanf(line, "SIZE = %lf", &temp);
            if (temp - (int)temp < 0.000001 && (int)temp > 0)
                size = (int)temp;
        }
        else if (strcmp(temp, "RAND = ") == 0)
        {
            double before = rand_ratio;
            sscanf(line, "RAND = %lf", &rand_ratio);
            if (rand_ratio < 0 || rand_ratio >= 100)
                rand_ratio = before;
        }
        else
        {
            temp[6] = '\0';
            if (strcmp(temp, "LOG = ") == 0)
            {
                sscanf(line, "LOG = %s", logg);
                duplicate = fopen(logg, "w");
            }
            else if (strcmp(temp, "BOX = ") == 0)
            {
                line[10] = '\0';
                if (strcmp(line, "BOX = TRUE") == 0)
                    box = 1;
            }
        }
    }
    fclose(ptr);
    if (size == -1)
    {
        printf("Wrong Configuration!\n");
        size = 4;
        return;
    }
}