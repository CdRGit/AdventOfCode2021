#include "utils.h"

typedef struct
{
    I32 values[25];
    bool found[25];
    bool won;
} Board;

I32 part1(I8 **lines);
I32 part2(I8 **lines);

void run(bool real)
{
    I8 **lines = get_lines_from_file(real ? "input.txt" : "example.txt");

    printf("Part 1\n");
    printf("= %u\n", part1(lines));

    lines = get_lines_from_file(real ? "input.txt" : "example.txt");

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
    I32 len = 0;
    I32 first = to_int(lines[0], &len);
    I32 value_count = 1;
    I32 values[1024] = {first};
    Board boards[256] = {0};
    I32 board_count = 0;
    lines[0] += len;

    while (*lines[0] != '\0')
    {
        lines[0]++;
        I32 amt = to_int(lines[0], &len);
        lines[0] += len;
        values[value_count++] = amt;
    }

    for (I32 i = 0; lines[i] != NULL; i++)
    {
        I8 *line = lines[i];
        if (strlen(line) == 0)
        {
        }
        else
        {
            // board tiem
            Board board = {.found = {false}, .values = {0}};
            for (I32 y = 0; y < 5; y++)
            {
                for (I32 x = 0; x < 5; x++)
                {
                    while (*line == ' ')
                        line++;
                    I32 j = x + y * 5;
                    I32 amt = to_int(line, &len);
                    board.values[j] = amt;
                    line += len;
                }
                i++;
                line = lines[i];
            }
            boards[board_count++] = board;
            i--;
        }
    }

    for (I32 i = 0; i < value_count; i++)
    {
        I32 value = values[i];
        for (I32 j = 0; j < board_count; j++)
        {
            Board *board = &boards[j];
            for (I32 k = 0; k < 25; k++)
            {
                if (board->values[k] == value)
                {
                    board->found[k] = true;

                    bool won = false;

                    // check for all column/row wins
                    for (I32 x = 0; x < 5; x++)
                    {
                        bool row = true;
                        bool col = true;
                        for (I32 y = 0; y < 5; y++)
                        {
                            I32 row_wise = x * 5 + y;
                            I32 col_wise = y * 5 + x;
                            row &= board->found[row_wise];
                            col &= board->found[col_wise];
                        }
                        if (row)
                        {
                            won = true;
                        }
                        if (col)
                        {
                            won = true;
                        }
                    }
                    if (won)
                    {
                        I32 sum = 0;
                        for (I32 l = 0; l < 25; l++)
                        {
                            if (!board->found[l])
                                sum += board->values[l];
                        }
                        return sum * value;
                    }
                }
            }
        }
    }

    return 0;
}

I32 part2(I8 **lines)
{
    I32 len = 0;
    I32 first = to_int(lines[0], &len);
    I32 value_count = 1;
    I32 values[1024] = {first};
    Board boards[256] = {0};
    I32 board_count = 0;
    lines[0] += len;

    while (*lines[0] != '\0')
    {
        lines[0]++;
        I32 amt = to_int(lines[0], &len);
        lines[0] += len;
        values[value_count++] = amt;
    }

    for (I32 i = 0; lines[i] != NULL; i++)
    {
        I8 *line = lines[i];
        if (strlen(line) == 0)
        {
        }
        else
        {
            // board tiem
            Board board = {.found = {false}, .values = {0}, .won = false};
            for (I32 y = 0; y < 5; y++)
            {
                for (I32 x = 0; x < 5; x++)
                {
                    while (*line == ' ')
                        line++;
                    I32 j = x + y * 5;
                    I32 amt = to_int(line, &len);
                    board.values[j] = amt;
                    line += len;
                }
                i++;
                line = lines[i];
            }
            boards[board_count++] = board;
            i--;
        }
    }

    I32 amt_won = 0;

    for (I32 i = 0; i < value_count; i++)
    {
        I32 value = values[i];
        for (I32 j = 0; j < board_count; j++)
        {
            Board *board = &boards[j];
            for (I32 k = 0; k < 25; k++)
            {
                if (board->values[k] == value)
                {
                    board->found[k] = true;

                    bool won = false;

                    // check for all column/row wins
                    for (I32 x = 0; x < 5; x++)
                    {
                        bool row = true;
                        bool col = true;
                        for (I32 y = 0; y < 5; y++)
                        {
                            I32 row_wise = x * 5 + y;
                            I32 col_wise = y * 5 + x;
                            row &= board->found[row_wise];
                            col &= board->found[col_wise];
                        }
                        if (row)
                        {
                            won = true;
                        }
                        if (col)
                        {
                            won = true;
                        }
                    }
                    if (won)
                    {
                        if (!board->won)
                        {
                            amt_won++;
                            if (amt_won == board_count)
                            {
                                I32 sum = 0;
                                for (I32 l = 0; l < 25; l++)
                                {
                                    if (!board->found[l])
                                        sum += board->values[l];
                                }
                                return sum * value;
                            }
                            board->won = true;
                        }
                    }
                }
            }
        }
    }

    return 0;
}