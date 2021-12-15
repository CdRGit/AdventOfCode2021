#include "utils.h"

#include <stdint.h>

typedef struct Cave Cave;

struct Cave
{
    I8 *name;
    I32 *neighbours;
    bool is_big;
    I32 neighbour_count;
};

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

#define SIZE 2048
I32 part1(I8 **lines)
{
    static bool paper[SIZE * SIZE] = {false};
    memset(paper, 0, sizeof(paper));
    I32 i = 0;
    for (i = 0; lines[i] != NULL; i++)
    {
        I8 *line = lines[i];
        if (strlen(line) == 0)
            break;
        I32 len = 0;
        I32 x = to_int(line, &len);
        line += len + 1;
        I32 y = to_int(line, &len);
        paper[x + y * SIZE] = true;
    }
    i++;
    for (; lines[i] != NULL; i++)
    {
        I8 *line = lines[i];

        I8 axis = line[11];
        I32 val = to_int(line + 13, NULL);

        for (I32 j = 0; j <= val; j++)
        {
            I32 dest = val - j;
            I32 source = val + j;
            for (I32 k = 0; k < SIZE; k++)
            {
                if (axis == 'x')
                {
                    I32 dest_i = dest + k * SIZE;
                    I32 source_i = source + k * SIZE;
                    paper[dest_i] |= paper[source_i];
                    paper[source_i] = false;
                }
                else
                {
                    I32 dest_i = k + dest * SIZE;
                    I32 source_i = k + source * SIZE;
                    paper[dest_i] |= paper[source_i];
                    paper[source_i] = false;
                }
            }
        }
        break;
    }

    I32 total = 0;
    for (i = 0; i < SIZE * SIZE; i++)
    {
        total += paper[i] ? 1 : 0;
    }
    return total;
}

I32 part2(I8 **lines)
{
    static bool paper[SIZE * SIZE] = {false};
    memset(paper, 0, sizeof(paper));
    I32 width = 0, height = 0;
    I32 i = 0;
    for (i = 0; lines[i] != NULL; i++)
    {
        I8 *line = lines[i];
        if (strlen(line) == 0)
            break;
        I32 len = 0;
        I32 x = to_int(line, &len);
        line += len + 1;
        I32 y = to_int(line, &len);
        paper[x + y * SIZE] = true;
        if (x > width)
            width = x + 2;
        if (y > height)
            height = y + 2;
    }
    i++;

    I32 count = 0;

    for (; lines[i] != NULL; i++)
    {
        I8 *line = lines[i];

        I8 axis = line[11];
        I32 val = to_int(line + 13, NULL);

        for (I32 j = 1; j <= val; j++)
        {
            I32 dest = val - j;
            I32 source = val + j;
            for (I32 k = 0; k < SIZE; k++)
            {
                if (axis == 'x')
                {
                    I32 dest_i = dest + k * SIZE;
                    I32 source_i = source + k * SIZE;
                    paper[dest_i] |= paper[source_i];
                    paper[source_i] = false;
                    width = val;
                }
                else
                {
                    I32 dest_i = k + dest * SIZE;
                    I32 source_i = k + source * SIZE;
                    paper[dest_i] |= paper[source_i];
                    paper[source_i] = false;
                    height = val;
                }
            }
        }
    }

    I32 total = 0;
    for (I32 y = 0; y < height; y++)
    {
        for (I32 x = 0; x < width; x++)
        {
            printf("%c", paper[x + y * SIZE] ? '|' : ' ');
            total += paper[x + y * SIZE] ? 1 : 0;
        }
        printf("\n");
    }
    return total;
}