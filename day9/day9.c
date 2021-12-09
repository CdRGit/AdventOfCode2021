#include "utils.h"
#include <inttypes.h>
#include <stdint.h>

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
    int width = strlen(lines[0]);
    int height = 0;

    for (int y = 0; lines[y] != NULL; y++)
    {
        height++;
    }

    unsigned char *grid = malloc(width * height);
    memset(grid, 0, width * height);

    for (int y = 0; y < height; y++)
    {
        char *line = lines[y];
        for (int x = 0; x < width; x++)
        {
            char ch = line[x];
            grid[x + y * width] = ch - '0';
        }
    }

    int count = 0;
    for (int y = 0; y < height; y++)
    {
        char *line = lines[y];
        for (int x = 0; x < width; x++)
        {
            int min = 0x7FFFFFFF;
            int curr = grid[x + y * width];
            if (x > 0 && grid[x - 1 + y * width] < min)
            {
                min = grid[x - 1 + y * width];
            }
            if (x < width - 1 && grid[x + 1 + y * width] < min)
            {
                min = grid[x + 1 + y * width];
            }
            if (y > 0 && grid[x + (y - 1) * width] < min)
            {
                min = grid[x + (y - 1) * width];
            }
            if (y < height - 1 && grid[x + (y + 1) * width] < min)
            {
                min = grid[x + (y + 1) * width];
            }
            if (curr < min)
            {
                count += curr + 1;
            }
        }
    }

    return count;
}

int find_size_of_basin(unsigned char **grid, int width, int height, int x, int y);

int part2(char **lines)
{
    int width = strlen(lines[0]);
    int height = 0;

    for (int y = 0; lines[y] != NULL; y++)
    {
        height++;
    }

    unsigned char *grid = malloc(width * height);
    memset(grid, 0, width * height);

    for (int y = 0; y < height; y++)
    {
        char *line = lines[y];
        for (int x = 0; x < width; x++)
        {
            char ch = line[x];
            grid[x + y * width] = ch - '0';
        }
    }

    int highest[3] = {0, 0, 0};

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            int size = find_size_of_basin(&grid, width, height, x, y);
            int lowest_of_highest_index = 0;
            int lowest_of_highest = 0x7FFFFFFF;

            for (int i = 0; i < 3; i++) {
                if (highest[i] < lowest_of_highest) {
                    lowest_of_highest = highest[i];
                    lowest_of_highest_index = i;
                }
            }

            if (size > lowest_of_highest) {
                highest[lowest_of_highest_index] = size;
            }
        }
    }

    return highest[0] * highest[1] * highest[2];
}

int find_size_of_basin(unsigned char **grid, int width, int height, int x, int y)
{
    if (x < 0 || y < 0 || x > width - 1 || y > height - 1)
    {
        return 0;
    }
    if ((*grid)[x + y * width] == 9)
    {
        return 0;
    }
    (*grid)[x + y * width] = 9;
    int size = 1;
    size += find_size_of_basin(grid, width, height, x - 1, y);
    size += find_size_of_basin(grid, width, height, x + 1, y);
    size += find_size_of_basin(grid, width, height, x, y - 1);
    size += find_size_of_basin(grid, width, height, x, y + 1);
    return size;
}