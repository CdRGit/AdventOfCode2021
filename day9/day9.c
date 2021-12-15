#include "utils.h"

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
    I32 width = strlen(lines[0]);
    I32 height = 0;

    for (I32 y = 0; lines[y] != NULL; y++)
    {
        height++;
    }

    I8 *grid = malloc(width * height);
    memset(grid, 0, width * height);

    for (I32 y = 0; y < height; y++)
    {
        I8 *line = lines[y];
        for (I32 x = 0; x < width; x++)
        {
            I8 ch = line[x];
            grid[x + y * width] = ch - '0';
        }
    }

    I32 count = 0;
    for (I32 y = 0; y < height; y++)
    {
        I8 *line = lines[y];
        for (I32 x = 0; x < width; x++)
        {
            I32 min = 0x7FFFFFFF;
            I32 curr = grid[x + y * width];
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

I32 find_size_of_basin(I8 **grid, I32 width, I32 height, I32 x, I32 y);

I32 part2(I8 **lines)
{
    I32 width = strlen(lines[0]);
    I32 height = 0;

    for (I32 y = 0; lines[y] != NULL; y++)
    {
        height++;
    }

    I8 *grid = malloc(width * height);
    memset(grid, 0, width * height);

    for (I32 y = 0; y < height; y++)
    {
        I8 *line = lines[y];
        for (I32 x = 0; x < width; x++)
        {
            I8 ch = line[x];
            grid[x + y * width] = ch - '0';
        }
    }

    I32 highest[3] = {0, 0, 0};

    for (I32 x = 0; x < width; x++)
    {
        for (I32 y = 0; y < height; y++)
        {
            I32 size = find_size_of_basin(&grid, width, height, x, y);
            I32 lowest_of_highest_index = 0;
            I32 lowest_of_highest = 0x7FFFFFFF;

            for (I32 i = 0; i < 3; i++) {
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

I32 find_size_of_basin(I8 **grid, I32 width, I32 height, I32 x, I32 y)
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
    I32 size = 1;
    size += find_size_of_basin(grid, width, height, x - 1, y);
    size += find_size_of_basin(grid, width, height, x + 1, y);
    size += find_size_of_basin(grid, width, height, x, y - 1);
    size += find_size_of_basin(grid, width, height, x, y + 1);
    return size;
}