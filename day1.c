#include "utils.h"

int part1(int *ints);
int part2(int *ints);

void run(bool real)
{
    int *ints = get_ints_from_file(real ? "day1.txt" : "day1_test.txt");

    printf("Part 1\n");
    printf("= %u\n", part1(ints));

    printf("Part 2\n");
    printf("= %u\n", part2(ints));
}

int main(int argc, char **argv)
{
    printf("%s", argv[0]);
    printf("\nTEST:\n");
    run(false);
    printf("\nREAL:\n");
    run(true);
}

int part1(int *ints)
{
    int count = 0;
    int previous = 0x7FFFFFFF;

    for (int i = 0; ints[i] != -1; i++)
    {
        if (ints[i] > previous)
        {
            count++;
        }
        previous = ints[i];
    }

    return count;
}

int part2(int *ints)
{
    int count = 0;
    int prev[3] = {0};

    for (int i = 0; ints[i] != -1; i++)
    {
        if (i >= 3)
        {
            int prev_sum = prev[0] + prev[1] + prev[2];
            int sum = prev[1] + prev[2] + ints[i];

            if (sum > prev_sum)
            {
                count++;
            }
        }

        for (int j = 1; j < 3; j++)
        {
            prev[j - 1] = prev[j];
        }
        prev[2] = ints[i];
    }

    return count;
}