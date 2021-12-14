#include "utils.h"
#include <inttypes.h>
#include <stdint.h>

I32 part1(I8 **lines);
I32 part2(I8 **lines);

void run(bool real)
{
    I8 **lines = get_lines_from_file(real ? "input.txt" : "example.txt");

    printf("Part 1\n");
    printf("= %u\n", part1(lines));

    printf("Part 2\n");
    printf("= %u\n", part2(lines));
}

I32 main(I32 argc, I8 **argv)
{
    printf("%s", argv[0]);
    printf("\nTEST:\n");
    run(false);
    printf("\nREAL:\n");
    run(true);
}

I32 part1(I8 **lines)
{
    I32 total_value = 0;
    for (I32 i = 0; lines[i] != NULL; i++)
    {
        I8 *line = lines[i];
        I8 chunks[1024];
        I32 chunk_idx = 0;
        for (I32 j = 0; line[j] != '\0'; j++)
        {
            I8 ch = line[j];
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
                I8 other = chunks[--chunk_idx];
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

I32 part2(I8 **lines)
{
    U64 values[1024];
    I32 value_idx = 0;
    for (I32 i = 0; lines[i] != NULL; i++)
    {
        I8 *line = lines[i];
        I8 chunks[1024];
        I32 chunk_idx = 0;

        bool success = true;
        for (I32 j = 0; line[j] != '\0'; j++)
        {
            I8 ch = line[j];
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
                I8 other = chunks[--chunk_idx];
                if (other != ch)
                {
                    success = false;
                    break;
                }
            }
        }

        if (success)
        {
            U64 value = 0;
            for (I32 i = chunk_idx - 1; i >= 0; i--)
            {
                value *= 5;
                I8 ch = chunks[i];
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
    
    I32 i = value_idx / 2;
    
    return values[i];
}