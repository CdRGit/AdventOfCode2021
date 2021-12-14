#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

typedef unsigned char           U8;
typedef   signed char           I8;
typedef unsigned short int      U16;
typedef   signed short int      I16;
typedef unsigned int            U32;
typedef   signed int            I32;
typedef unsigned long long int  U64;
typedef   signed long long int  I64;

int bin_str_to_int(char* string)
{
    int value = 0;
    for (int i = 0; string[i] != '\0'; i++) {
        value <<= 1;
        value |= string[i] == '1';
    }
    return value;
}

int to_int(char* string, int* length)
{
    int temp = 0;
    int j = 0;
    for (j = 0; string[j] != '\0'; j++)
    {
        int chr_val = string[j] - '0';
        if (chr_val < 0 || chr_val > 9)
            break;
        temp = temp * 10 + chr_val;
    }
    if (length != NULL)
        *length = j;
    return temp;
}

char *get_file_content(char *filename)
{
    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        fprintf(stderr, "FILE NOT OPENED\n");
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    int lengthOfFile = ftell(file);
    rewind(file);

    char *str = malloc(lengthOfFile + 1);

    if (str == NULL) {
        fprintf(stderr, "MALLOC FAILED\n");
        exit(1);
    }

    memset(str, 0, lengthOfFile + 1);

    char c;
    int i = 0;
    while ((c = fgetc(file)) != EOF)
    {
        str[i++] = c;
    }

    fclose(file);

    return str;
}

char *comma_buffer[32 * 1024];

char **split_by_comma(char *text)
{
    char *temp = malloc(strlen(text));

    int i = 0;
    int j = 0;

    while (*text != '\0')
    {
        if (*text == ',')
        {
            temp[i++] = '\0';
            text++;
            i = 0;
            comma_buffer[j++] = temp;
            temp = malloc(strlen(text));
        }
        else
        {
            temp[i++] = *text++;
        }
    }
    temp[i++] = '\0';
    comma_buffer[j++] = temp;
    comma_buffer[j] = NULL;
    return comma_buffer;
}

char *space_buffer[32 * 1024];

char **split_by_spaces(char *text)
{
    char *temp = malloc(strlen(text));

    int i = 0;
    int j = 0;

    while (*text != '\0')
    {
        if (*text == ' ')
        {
            temp[i++] = '\0';
            text++;
            i = 0;
            space_buffer[j++] = temp;
            temp = malloc(strlen(text));
        }
        else
        {
            temp[i++] = *text++;
        }
    }
    temp[i++] = '\0';
    space_buffer[j++] = temp;
    space_buffer[j] = NULL;
    return space_buffer;
}

char *newline_buffer[32 * 1024];

char **split_by_newlines(char *text)
{
    char *temp = malloc(strlen(text));

    int i = 0;
    int j = 0;

    while (*text != '\0')
    {
        if (*text == '\n')
        {
            temp[i++] = '\0';
            text++;
            i = 0;
            newline_buffer[j++] = temp;
            temp = malloc(strlen(text));
        }
        else
        {
            temp[i++] = *text++;
        }
    }
    temp[i++] = '\0';
    newline_buffer[j++] = temp;
    newline_buffer[j] = NULL;
    return newline_buffer;
}

int int_buffer[32 * 1024];

int *convert_to_int(char **lines)
{
    int i = 0;
    for (i = 0; lines[i] != NULL; i++)
    {
        char *line = lines[i];
        int_buffer[i] = to_int(line, NULL);
    }
    int_buffer[i] = -1;
    return int_buffer;
}

char **get_lines_from_file(char *filename)
{
    char *content = get_file_content(filename);
    return split_by_newlines(content);
}

int *get_ints_from_file(char *filename)
{
    char **split = get_lines_from_file(filename);
    return convert_to_int(split);
}

void sort_in_place(unsigned long long *array, int length) {
    if (length == 1)
        return;

    int max_idx = 0;
    unsigned long long max = 0;
    for (int i = 0; i < length; i++) {
        if (array[i] > max)
        {
            max = array[i];
            max_idx = i;
        }
    }
    array[max_idx] = array[length - 1];
    array[length - 1] = max;
    sort_in_place(array, length - 1);
}