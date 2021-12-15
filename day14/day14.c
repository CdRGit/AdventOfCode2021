#include "utils.h"

#include <stdint.h>

typedef U64 Pair;

typedef struct Operation Operation;

struct Operation
{
    I8 left;
    I8 right;
    I8 insert;
};

Pair part1(I8 **lines);
Pair part2(I8 **lines);

#define PAIR_COUNT 128 * 128
Pair *apply_operation(Pair *pairs, Operation *operations, I32 op_count);

void run(bool real)
{
    I8 **lines = get_lines_from_file(real ? "input.txt" : "example.txt");

    printf("Part 1\n");
    printf("= %llu\n", part1(lines));

    printf("Part 2\n");
    printf("= %llu\n", part2(lines));
}

I32 main(I32 argc, I8 **argv)
{
    printf("%s", argv[0]);
    printf("\nTEST:\n");
    run(false);
    printf("\nREAL:\n");
    run(true);
}

#define SIZE 128
Pair run_iters(I8 **lines, I32 iteration_count)
{
    Pair *pairs = malloc(sizeof(Pair) * PAIR_COUNT);
    memset(pairs, 0, sizeof(Pair) * PAIR_COUNT);
    for (I32 i = 0; i < PAIR_COUNT; i++)
    {
        if (pairs[i] > 0)
        {
            printf("AAAAAAAAAAAAAAAAAAAAAA %llu\n", i);
            exit(1);
        }
    }
    Operation operations[SIZE] = {0};
    I32 op_count = 0;
    memset(operations, '-', sizeof(operations));

    I8 left = lines[0][0];
    for (I32 i = 1; lines[0][i] != '\0'; i++)
    {
        I8 right = lines[0][i];
        pairs[(left << 7) | right]++;
        left = right;
    }

    for (I32 i = 0; i < PAIR_COUNT; i++)
    {
        Pair pair = pairs[i];

        I8 right = i & 0x7F;
        I8 left = i >> 7;

        if (pairs[i] > 2)
            pairs[i] = 0;
    }

    I8 start = lines[0][0];
    I8 end = left;

    for (I32 i = 2; lines[i] != NULL; i++)
    {
        I8 *line = lines[i];
        Operation operation = {.left = line[0], .right = line[1], .insert = line[6]};
        operations[op_count++] = operation;
    }

    for (I32 i = 0; i < iteration_count; i++)
    {
        apply_operation(pairs, operations, op_count);
    }

    Pair count[128] = {0};
    count[start]++;
    count[end]++;
    I32 highest_pair = 0;
    I8 highest_right = 0;
    I8 highest_left = 0;
    for (I32 i = 0; i < PAIR_COUNT; i++)
    {
        Pair pair = pairs[i];

        I8 right = i & 0x7F;
        I8 left = i >> 7;

        if (right > 'Z' || right < 'A' || left > 'Z' || right < 'A')
        {
            if (pair > 0)
            {
                printf("AAAAAAAAAAAAAAAAAAAAA %llu\n", i);
                exit(1);
            }
        }

        if (pair > highest_pair)
        {
            highest_pair = pair;
            highest_left = left;
            highest_right = right;
        }

        count[right] += pair;
        count[left] += pair;
    }

    Pair max = 0;
    I8 max_c;
    Pair min = 0x7FFFFFFFFFFFFFFF;
    I8 min_c;
    for (I32 i = 0; i < 128; i++)
    {
        if (count[i] == 0)
            continue;
        if (count[i] > max)
        {
            max = count[i];
            max_c = i;
        }
        if (count[i] < min)
        {
            min = count[i];
            min_c = i;
        }
    }

    min /= 2;
    max /= 2;


    return max - min;
}

Pair *apply_operation(Pair *pairs, Operation *operations, I32 op_count)
{
    Pair new_pairs[PAIR_COUNT] = {0};
    memset(new_pairs, 0, sizeof(new_pairs));
    for (I32 i = 0; i < PAIR_COUNT; i++)
    {
        Pair pair = pairs[i];

        I8 right = i & 0x7F;
        I8 left = i >> 7;

        for (I32 j = 0; j < op_count; j++)
        {
            if (operations[j].left == left && operations[j].right == right)
            {
                I32 replace1 = (left << 7) | operations[j].insert;
                I32 replace2 = (operations[j].insert << 7) | right;
                new_pairs[replace1] += pair;
                new_pairs[replace2] += pair;
                break;
            }
        }
    }
    memcpy(pairs, new_pairs, PAIR_COUNT * sizeof(Pair));
    return pairs;
}

Pair part1(I8 **lines)
{
    return run_iters(lines, 10);
}

Pair part2(I8 **lines)
{
    return run_iters(lines, 40);
}