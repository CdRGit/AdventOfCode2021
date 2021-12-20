#include "utils.h"

I32 part1(I32 *ints);
I32 part2(I32 *ints);

void run(bool real)
{
    I32 *ints = get_ints_from_file(real ? "input.txt" : "example.txt");

    printf("Part 1\n");
    printf("= %u\n", part1(ints));

    printf("Part 2\n");
    printf("= %u\n", part2(ints));
}

I32 main(I32 argc, I8 **argv)
{
    printf("%s", argv[0]);
    printf("\nTEST:\n");
    run(false);
    printf("\nREAL:\n");
    run(true);
}

I32 part1(I32 *ints)
{
    I32 count = 0;
    I32 previous = 0x7FFFFFFF;

    for (I32 i = 0; ints[i] != -1; i++)
    {
        if (ints[i] > previous)
        {
            count++;
        }
        previous = ints[i];
    }

    return count;
}

I32 part2(I32 *ints)
{
    I32 count = 0;
    I32 prev[3] = {0};

    for (I32 i = 0; ints[i] != -1; i++)
    {
        if (i >= 3)
        {
            I32 prev_sum = prev[0] + prev[1] + prev[2];
            I32 sum = prev[1] + prev[2] + ints[i];

            if (sum > prev_sum)
            {
                count++;
            }
        }

        for (I32 j = 1; j < 3; j++)
        {
            prev[j - 1] = prev[j];
        }
        prev[2] = ints[i];
    }

    return count;
}