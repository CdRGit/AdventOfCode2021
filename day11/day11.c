#include "utils.h"
#include <inttypes.h>
#include <stdint.h>

int part1(I8 **lines);
int part2(I8 **lines);

void run(bool real)
{
    I8 **lines = get_lines_from_file(real ? "input.txt" : "example.txt");

    printf("Part 1\n");
    printf("= %u\n", part1(lines));

    printf("Part 2\n");
    printf("= %u\n", part2(lines));
}

int main(int argc, I8 **argv)
{
    printf("%s", argv[0]);
    printf("\nTEST:\n");
    run(false);
    printf("\nREAL:\n");
    run(true);
}

int iteration(I8 octopi[100])
{
    bool flashed[100] = {false};
    for (int y = 0; y < 10; y++)
    {
        for (int x = 0; x < 10; x++)
        {
            int index = x + y * 10;
            octopi[index]++;
        }
    }

    bool any_flashed = true;
    while (any_flashed)
    {
        any_flashed = false;
        for (int y = 0; y < 10; y++)
        {
            for (int x = 0; x < 10; x++)
            {
                int index = x + y * 10;

                bool high_energy = octopi[index] > 9;
                if (high_energy && !flashed[index])
                {
                    any_flashed = true;
                    for (int dx = -1; dx <= 1; dx++)
                    {
                        int x_other = x + dx;
                        if (x_other < 0 || x_other >= 10)
                            continue;
                        for (int dy = -1; dy <= 1; dy++)
                        {
                            int y_other = y + dy;
                            if (y_other < 0 || y_other >= 10)
                                continue;
                            if (x_other == x && y_other == y)
                                continue;
                            int index_other = x_other + y_other * 10;
                            octopi[index_other]++;
                        }
                    }
                }

                flashed[index] |= high_energy;
            }
        }
    }

    int total = 0;

    for (int y = 0; y < 10; y++)
    {
        for (int x = 0; x < 10; x++)
        {
            int index = x + y * 10;
            if (flashed[index])
            {
                octopi[index] = 0;
                total++;
            }
        }
    }
    return total;
}

int part1(I8 **lines)
{
    I8 octopi[100] = {0};
    for (int y = 0; y < 10; y++)
    {
        I8 *line = lines[y];
        for (int x = 0; x < 10; x++)
        {
            int index = x + y * 10;
            octopi[index] = line[x] - '0';
        }
    }

    int total = 0;
    for (int iter = 0; iter < 100; iter++)
    {
        total += iteration(octopi);
    }

    return total;
}

int part2(I8 **lines)
{
    I8 octopi[100] = {0};
    for (int y = 0; y < 10; y++)
    {
        I8 *line = lines[y];
        for (int x = 0; x < 10; x++)
        {
            int index = x + y * 10;
            octopi[index] = line[x] - '0';
        }
    }

    int step = 1;
    while (iteration(octopi) != 100)
    {
        step++;
    }

    return step;
}