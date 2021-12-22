#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>
#include <assert.h>

#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

typedef uint8_t  U8;
typedef int8_t   I8;
typedef uint16_t U16;
typedef int16_t  I16;
typedef uint32_t U32;
typedef int32_t  I32;
typedef uint64_t U64;
typedef int64_t  I64;

I32 ptr_arr_len(void **arr)
{
    I32 len = 0;
    for (len = 0; arr[len] != NULL; len++);
    return len;
}

I32 bin_str_to_int(I8* string)
{
    I32 value = 0;
    for (I32 i = 0; string[i] == '1' || string[i] == '0'; i++) {
        value <<= 1;
        value |= string[i] == '1';
    }
    return value;
}

I32 to_int(I8* string, I32* length)
{
    bool is_neg = string[0] == '-';
    I32 temp = 0;
    I32 j = is_neg;
    for (; string[j] != '\0'; j++)
    {
        I32 chr_val = string[j] - '0';
        if (chr_val < 0 || chr_val > 9)
            break;
        temp = temp * 10 + chr_val;
    }
    if (length != NULL)
        *length = j;
    return is_neg ? -temp : temp;
}

I8 *get_file_content(I8 *filename)
{
    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        fprintf(stderr, "FILE NOT OPENED\n");
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    I32 lengthOfFile = ftell(file);
    rewind(file);

    I8 *str = malloc(lengthOfFile + 1);

    if (str == NULL) {
        fprintf(stderr, "MALLOC FAILED\n");
        exit(1);
    }

    memset(str, 0, lengthOfFile + 1);

    I8 c;
    I32 i = 0;
    while ((c = fgetc(file)) != EOF)
    {
        // fuck you windows for giving me carriage return
        if (c != '\r')
            str[i++] = c;
    }

    fclose(file);

    return str;
}

I8 *comma_buffer[32 * 1024];

I8 **split_by_comma(I8 *text)
{
    I8 *temp = malloc(strlen(text));

    I32 i = 0;
    I32 j = 0;

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

I8 *space_buffer[32 * 1024];

I8 **split_by_spaces(I8 *text)
{
    I8 *temp = malloc(strlen(text));

    I32 i = 0;
    I32 j = 0;

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

I8 *newline_buffer[32 * 1024];

I8 **split_by_newlines(I8 *text)
{
    I8 *temp = malloc(strlen(text));

    I32 i = 0;
    I32 j = 0;

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

I32 I32_buffer[32 * 1024];

I32 *convert_to_int(I8 **lines)
{
    I32 i = 0;
    for (i = 0; lines[i] != NULL; i++)
    {
        I8 *line = lines[i];
        I32_buffer[i] = to_int(line, NULL);
    }
    I32_buffer[i] = -1;
    return I32_buffer;
}

I8 **get_lines_from_file(I8 *filename)
{
    I8 *content = get_file_content(filename);
    return split_by_newlines(content);
}

I32 *get_ints_from_file(I8 *filename)
{
    I8 **split = get_lines_from_file(filename);
    return convert_to_int(split);
}

void sort_in_place(U64 *array, I32 length) {
    if (length == 1)
        return;

    I32 max_idx = 0;
    U64 max = 0;
    for (I32 i = 0; i < length; i++) {
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