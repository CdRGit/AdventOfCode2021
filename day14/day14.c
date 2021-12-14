#include "utils.h"
#include <inttypes.h>
#include <stdint.h>

typedef unsigned char byte;

typedef unsigned long long int Pair;

typedef struct Operation Operation;

struct Operation
{
    char left;
    char right;
    char insert;
};

Pair part1(char **lines);
Pair part2(char **lines);

#define PAIR_COUNT 128 * 128
Pair *apply_operation(Pair *pairs, Operation *operations, int op_count);

void run(bool real)
{
    char **lines = get_lines_from_file(real ? "input.txt" : "example.txt");

    printf("Part 1\n");
    printf("= %llu\n", part1(lines));

    printf("Part 2\n");
    printf("= %llu\n", part2(lines));
}

int main(int argc, char **argv)
{
    printf("%s", argv[0]);
    printf("\nTEST:\n");
    run(false);
    printf("\nREAL:\n");
    run(true);
}

#define SIZE 128
Pair run_iters(char **lines, int iteration_count)
{
    Pair *pairs = malloc(sizeof(Pair) * PAIR_COUNT);
    memset(pairs, 0, sizeof(Pair) * PAIR_COUNT);
    for (int i = 0; i < PAIR_COUNT; i++)
    {
        if (pairs[i] > 0)
        {
            printf("AAAAAAAAAAAAAAAAAAAAAA %llu\n", i);
            exit(1);
        }
    }
    Operation operations[SIZE] = {0};
    int op_count = 0;
    memset(operations, '-', sizeof(operations));

    char left = lines[0][0];
    for (int i = 1; lines[0][i] != '\0'; i++)
    {
        char right = lines[0][i];
        pairs[(left << 7) | right]++;
        left = right;
    }

    for (int i = 0; i < PAIR_COUNT; i++)
    {
        Pair pair = pairs[i];

        char right = i & 0x7F;
        char left = i >> 7;

        if (pairs[i] > 2)
            pairs[i] = 0;
    }

    char start = lines[0][0];
    char end = left;

    for (int i = 2; lines[i] != NULL; i++)
    {
        char *line = lines[i];
        Operation operation = {.left = line[0], .right = line[1], .insert = line[6]};
        operations[op_count++] = operation;
    }

    for (int i = 0; i < iteration_count; i++)
    {
        apply_operation(pairs, operations, op_count);
    }

    Pair count[128] = {0};
    count[start]++;
    count[end]++;
    int highest_pair = 0;
    char highest_right = 0;
    char highest_left = 0;
    for (int i = 0; i < PAIR_COUNT; i++)
    {
        Pair pair = pairs[i];

        char right = i & 0x7F;
        char left = i >> 7;

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
    char max_c;
    Pair min = 0x7FFFFFFFFFFFFFFF;
    char min_c;
    for (int i = 0; i < 128; i++)
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

Pair *apply_operation(Pair *pairs, Operation *operations, int op_count)
{
    Pair new_pairs[PAIR_COUNT] = {0};
    memset(new_pairs, 0, sizeof(new_pairs));
    for (int i = 0; i < PAIR_COUNT; i++)
    {
        Pair pair = pairs[i];

        char right = i & 0x7F;
        char left = i >> 7;

        for (int j = 0; j < op_count; j++)
        {
            if (operations[j].left == left && operations[j].right == right)
            {
                int replace1 = (left << 7) | operations[j].insert;
                int replace2 = (operations[j].insert << 7) | right;
                new_pairs[replace1] += pair;
                new_pairs[replace2] += pair;
                break;
            }
        }
    }
    memcpy(pairs, new_pairs, PAIR_COUNT * sizeof(Pair));
    return pairs;
}

Pair part1(char **lines)
{
    return run_iters(lines, 10);
}

Pair part2(char **lines)
{
    return run_iters(lines, 40);
}