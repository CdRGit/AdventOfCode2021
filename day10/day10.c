#include "utils.h"
#include <inttypes.h>
#include <stdint.h>

typedef unsigned char byte;

int part1(char **lines);
int part2(char **lines);

void run(bool real)
{
    char **lines = get_lines_from_file(real ? "input.txt" : "example.txt");

    printf("Part 1\n");
    printf("= %u\n", part1(lines));

    printf("Part 2\n");
    printf("= %u\n", part2(lines));
}

int main(int argc, char **argv)
{
    printf("%s", argv[0]);
    printf("\nTEST:\n");
    run(false);
    printf("\nREAL:\n");
    run(true);
}

int part1(char **lines)
{
    int total_value = 0;
    for (int i = 0; lines[i] != NULL; i++)
    {
        char *line = lines[i];
        char chunks[1024];
        int chunk_idx = 0;
        for (int j = 0; line[j] != '\0'; j++)
        {
            char ch = line[j];
            if (ch == '(' || ch == '[' || ch == '{' || ch == '<')
            {
                chunks[chunk_idx++] = ch;
            }
            else
            {
                if (ch == ')')
                {
                    ch--;
                }
                else
                {
                    ch -= 2;
                }
                char other = chunks[--chunk_idx];
                if (other != ch)
                {
                    if (ch == '(')
                    {
                        total_value += 3;
                    }
                    else if (ch == '[')
                    {
                        total_value += 57;
                    }
                    else if (ch == '{')
                    {
                        total_value += 1197;
                    }
                    else if (ch == '<')
                    {
                        total_value += 25137;
                    }
                    break;
                }
            }
        }
    }
    return total_value;
}

int part2(char **lines)
{
    unsigned long long values[1024];
    int value_idx = 0;
    for (int i = 0; lines[i] != NULL; i++)
    {
        char *line = lines[i];
        char chunks[1024];
        int chunk_idx = 0;

        bool success = true;
        for (int j = 0; line[j] != '\0'; j++)
        {
            char ch = line[j];
            if (ch == '(' || ch == '[' || ch == '{' || ch == '<')
            {
                chunks[chunk_idx++] = ch;
            }
            else
            {
                if (ch == ')')
                {
                    ch--;
                }
                else
                {
                    ch -= 2;
                }
                char other = chunks[--chunk_idx];
                if (other != ch)
                {
                    success = false;
                    break;
                }
            }
        }

        if (success)
        {
            unsigned long long value = 0;
            for (int i = chunk_idx - 1; i >= 0; i--)
            {
                value *= 5;
                char ch = chunks[i];
                if (ch == '(')
                {
                    value += 1;
                }
                else if (ch == '[')
                {
                    value += 2;
                }
                else if (ch == '{')
                {
                    value += 3;
                }
                else if (ch == '<')
                {
                    value += 4;
                }
            }
            if (value != 0)
            {
                values[value_idx++] = value;
            }
        }
    }
    sort_in_place(values, value_idx);
    
    int i = value_idx / 2;
    
    return values[i];
}