#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

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
    memset(str, 0, lengthOfFile + 1);

    char c;
    int i = 0;
    while ((c = fgetc(file)) != EOF)
    {
        str[i++] = c;
    }
    return str;
}

char *text_buffer[32 * 1024];

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
            text_buffer[j++] = temp;
            temp = malloc(strlen(text));
        }
        else
        {
            temp[i++] = *text++;
        }
    }
    text_buffer[j++] = temp;
    text_buffer[j] = NULL;
    return text_buffer;
}

int int_buffer[32 * 1024];

int *convert_to_int(char **lines)
{
    int i = 0;
    for (i = 0; lines[i] != NULL; i++)
    {
        char *line = lines[i];
        int temp = 0;
        for (int j = 0; line[j] != '\0'; j++)
        {
            int chr_val = line[j] - '0';
            temp = temp * 10 + chr_val;
        }
        int_buffer[i] = temp;
    }
    int_buffer[i] = -1;
    return int_buffer;
}

int *get_ints_from_file(char *filename)
{
    char *content = get_file_content(filename);
    char **split = split_by_newlines(content);
    return convert_to_int(split);
}