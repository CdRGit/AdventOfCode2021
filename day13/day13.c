#include "utils.h"
#include <inttypes.h>
#include <stdint.h>

typedef unsigned char byte;

typedef struct Cave Cave;

struct Cave
{
    char *name;
    int *neighbours;
    bool is_big;
    int neighbour_count;
};

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

#define SIZE 2048
int part1(char **lines)
{
    static bool paper[SIZE * SIZE] = {false};
    memset(paper, 0, sizeof(paper));
    int i = 0;
    for (i = 0; lines[i] != NULL; i++)
    {
        char *line = lines[i];
        if (strlen(line) == 0)
            break;
        int len = 0;
        int x = to_int(line, &len);
        line += len + 1;
        int y = to_int(line, &len);
        paper[x + y * SIZE] = true;
    }
    i++;
    for (; lines[i] != NULL; i++)
    {
        char *line = lines[i];

        char axis = line[11];
        int val = to_int(line + 13, NULL);

        for (int j = 0; j <= val; j++)
        {
            int dest = val - j;
            int source = val + j;
            for (int k = 0; k < SIZE; k++)
            {
                if (axis == 'x')
                {
                    int dest_i = dest + k * SIZE;
                    int source_i = source + k * SIZE;
                    paper[dest_i] |= paper[source_i];
                    paper[source_i] = false;
                }
                else
                {
                    int dest_i = k + dest * SIZE;
                    int source_i = k + source * SIZE;
                    paper[dest_i] |= paper[source_i];
                    paper[source_i] = false;
                }
            }
        }
        break;
    }

    int total = 0;
    for (i = 0; i < SIZE * SIZE; i++)
    {
        total += paper[i] ? 1 : 0;
    }
    return total;
}

int part2(char **lines)
{
    static bool paper[SIZE * SIZE] = {false};
    memset(paper, 0, sizeof(paper));
    int width = 0, height = 0;
    int i = 0;
    for (i = 0; lines[i] != NULL; i++)
    {
        char *line = lines[i];
        if (strlen(line) == 0)
            break;
        int len = 0;
        int x = to_int(line, &len);
        line += len + 1;
        int y = to_int(line, &len);
        paper[x + y * SIZE] = true;
        if (x > width)
            width = x + 2;
        if (y > height)
            height = y + 2;
    }
    i++;

    int count = 0;

    for (; lines[i] != NULL; i++)
    {
        char *line = lines[i];

        char axis = line[11];
        int val = to_int(line + 13, NULL);

        for (int j = 1; j <= val; j++)
        {
            int dest = val - j;
            int source = val + j;
            for (int k = 0; k < SIZE; k++)
            {
                if (axis == 'x')
                {
                    int dest_i = dest + k * SIZE;
                    int source_i = source + k * SIZE;
                    paper[dest_i] |= paper[source_i];
                    paper[source_i] = false;
                    width = val;
                }
                else
                {
                    int dest_i = k + dest * SIZE;
                    int source_i = k + source * SIZE;
                    paper[dest_i] |= paper[source_i];
                    paper[source_i] = false;
                    height = val;
                }
            }
        }
    }

    int total = 0;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            printf("%c", paper[x + y * SIZE] ? '|' : ' ');
            total += paper[x + y * SIZE] ? 1 : 0;
        }
        printf("\n");
    }
    return total;
}