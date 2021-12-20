#include "utils.h"

typedef enum SnailfishType SnailfishType;
enum SnailfishType
{
    NUM,
    PAIR,
};

typedef struct SnailfishPair SnailfishPair;
typedef struct SnailfishNumber SnailfishNumber;
typedef union SnailfishNumberAs SnailfishNumberAs;

union SnailfishNumberAs
{
    U64 num;
    SnailfishPair *pair;
};

struct SnailfishNumber
{
    SnailfishType type;
    SnailfishNumberAs as;
};

struct SnailfishPair
{
    SnailfishNumber left;
    SnailfishNumber right;
};

U64 part1(I8 **lines);
U64 part2(I8 **lines);

void run(bool real)
{
    I8 **lines = get_lines_from_file(real ? "input.txt" : "example.txt");

    printf("Part 1\n");
    printf("= %llu           \n", part1(lines));

    printf("Part 2\n");
    printf("= %llu           \n", part2(lines));
}

I32 main(I32 argc, I8 **argv)
{
    printf("%s", argv[0]);
    printf("\nTEST:\n");
    run(false);
    printf("\nREAL:\n");
    run(true);
}

SnailfishNumber parse_snailfish(I8 *line, I32 *length)
{
    SnailfishNumber number;

    I8 *start = line;

    if (line[0] == '[')
    {
        line++;
        number.type = PAIR;
        SnailfishPair *pair = malloc(sizeof(SnailfishPair));
        pair->left = parse_snailfish(line, length);
        line += *length + 1;
        pair->right = parse_snailfish(line, length);
        line += *length;
        if (line[0] == ']')
        {
            line++;
            number.as.pair = pair;

            *length = line - start;
        }
        else
        {
            fprintf(stderr, "no ]\n");
            exit(1);
        }
    }
    else
    {
        U64 value = to_int(line, length);
        number.type = NUM;
        number.as.num = value;
    }

    return number;
}

void print_snailfish(SnailfishNumber number)
{
    if (number.type == NUM)
    {
        printf("%d", number.as.num);
    }
    else
    {
        printf("[");
        print_snailfish(number.as.pair->left);
        printf(",");
        print_snailfish(number.as.pair->right);
        printf("]");
    }
}

bool needs_split(SnailfishNumber number)
{
    if (number.type == NUM)
        return number.as.num >= 10;

    return needs_split(number.as.pair->left) || needs_split(number.as.pair->right);
}

bool needs_explosion(SnailfishNumber number, U64 depth)
{
    if (number.type == NUM)
        return false;

    if (depth == 4)
        return true;

    return needs_explosion(number.as.pair->left, depth + 1) || needs_explosion(number.as.pair->right, depth + 1);
}

SnailfishNumber copy_snailfish(SnailfishNumber number)
{
    if (number.type == NUM)
    {
        return number;
    }

    SnailfishNumber new_num;
    SnailfishPair *pair = malloc(sizeof(SnailfishPair));
    pair->left = copy_snailfish(number.as.pair->left);
    pair->right = copy_snailfish(number.as.pair->right);
    new_num.type = PAIR;
    new_num.as.pair = pair;
    return new_num;
}

SnailfishNumber *flattened[1024];
U64 flattened_count = 0;

void snailfish_partial_flatten(SnailfishNumber *number, U64 depth)
{
    if (depth == 4 || number->type == NUM)
    {
        flattened[flattened_count++] = number;
        return;
    }

    snailfish_partial_flatten(&number->as.pair->left, depth + 1);
    snailfish_partial_flatten(&number->as.pair->right, depth + 1);
}

SnailfishNumber split_snailfish(SnailfishNumber number)
{
    flattened_count = 0;
    snailfish_partial_flatten(&number, 0);
    for (U64 i = 0; i < flattened_count; i++)
    {
        SnailfishNumber *current = flattened[i];
        if (current->type == NUM && current->as.num >= 10)
        {
            current->type = PAIR;
            SnailfishPair *pair = malloc(sizeof(SnailfishPair));
            pair->left.as.num = current->as.num / 2;
            pair->right.as.num = current->as.num - (current->as.num / 2);
            pair->left.type = NUM;
            pair->right.type = NUM;
            current->as.pair = pair;
            break;
        }
    }
    return number;
}

SnailfishNumber explode_snailfish(SnailfishNumber number)
{
    flattened_count = 0;
    snailfish_partial_flatten(&number, 0);
    SnailfishNumber *left = NULL;
    SnailfishNumber *right = flattened[0];
    for (U64 i = 0; i < flattened_count; i++)
    {
        SnailfishNumber *current = flattened[i];
        right = i + 1 < flattened_count ? flattened[i + 1] : NULL;
        if (current->type == PAIR)
        {
            // EXPLODE!
            if (left && left->type == NUM)
                left->as.num += current->as.pair->left.as.num;
            if (right)
            {
                while (right->type != NUM)
                    right = &right->as.pair->left;
                right->as.num += current->as.pair->right.as.num;
            }

            SnailfishNumber zero = {.type = NUM, .as.num = 0};
            *current = zero;
            break;
        }
        left = current;
    }
    return number;
}

SnailfishNumber simplify_snailfish(SnailfishNumber number)
{
    bool changed = true;
    while (changed)
    {
        changed = false;

        bool explode = needs_explosion(number, 0);

        if (explode)
        {
            // explode
            number = explode_snailfish(number);
            changed = true;
            continue;
        }

        bool split = needs_split(number);

        if (split)
        {
            // split
            number = split_snailfish(number);
            changed = true;
            continue;
        }
    }

    return number;
}

SnailfishNumber add_snailfish(SnailfishNumber left, SnailfishNumber right)
{
    SnailfishNumber number;
    SnailfishPair *pair = malloc(sizeof(SnailfishPair));
    pair->left = left;
    pair->right = right;
    number.as.pair = pair;
    number.type = PAIR;
    return simplify_snailfish(number);
}

SnailfishNumber eval_snailfish(SnailfishNumber *numbers, U64 count)
{
    I32 idx = 0;
    SnailfishNumber left = numbers[idx];
    for (idx = 1; idx < count; idx++)
    {
        left = add_snailfish(left, numbers[idx]);
    }
    return left;
}

U64 mag_snailfish(SnailfishNumber number)
{
    if (number.type == NUM)
        return number.as.num;
    else
        return mag_snailfish(number.as.pair->left) * 3 + mag_snailfish(number.as.pair->right) * 2;
}

U64 part1(I8 **lines)
{
    I32 length;
    SnailfishNumber numbers[100];

    U64 count;
    for (count = 0; lines[count] != NULL; count++)
    {
        numbers[count] = parse_snailfish(lines[count], &length);
    }

    SnailfishNumber evaled = eval_snailfish(numbers, count);
    print_snailfish(evaled);
    printf("\n");
    return mag_snailfish(evaled);
}

U64 part2(I8 **lines)
{
    I32 length;
    SnailfishNumber numbers[100];

    U64 count;
    for (count = 0; lines[count] != NULL; count++)
    {
        numbers[count] = parse_snailfish(lines[count], &length);
    }

    U64 max = 0;
    I32 highest_i = 0;
    I32 highest_j = 0;

    for (I32 i = 0; i < count; i++)
    {
        for (I32 j = 0; j < count; j++)
        {
            if (i == j)
                continue;
            SnailfishNumber sum = add_snailfish(copy_snailfish(numbers[i]), copy_snailfish(numbers[j]));
            U64 value = mag_snailfish(sum);
            if (value > max) {
                max = value;
                highest_i = i;
                highest_j = j;
            }
        }
    }

    print_snailfish(numbers[highest_i]);
    printf("\n");
    print_snailfish(numbers[highest_j]);
    printf("\n");
    print_snailfish(add_snailfish(numbers[highest_i], numbers[highest_j]));
    printf("\n");

    return max;
}