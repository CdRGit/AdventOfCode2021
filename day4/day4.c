#include "utils.h"

typedef struct
{
    int values[25];
    bool found[25];
    bool won;
} Board;

int part1(char **lines);
int part2(char **lines);

void run(bool real)
{
    char **lines = get_lines_from_file(real ? "input.txt" : "example.txt");

    printf("Part 1\n");
    printf("= %u\n", part1(lines));

    lines = get_lines_from_file(real ? "input.txt" : "example.txt");

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
    int len = 0;
    int first = to_int(lines[0], &len);
    int value_count = 1;
    int values[1024] = {first};
    Board boards[256] = {0};
    int board_count = 0;
    lines[0] += len;

    while (*lines[0] != '\0')
    {
        lines[0]++;
        int amt = to_int(lines[0], &len);
        lines[0] += len;
        values[value_count++] = amt;
    }

    for (int i = 0; lines[i] != NULL; i++)
    {
        char *line = lines[i];
        if (strlen(line) == 0)
        {
        }
        else
        {
            // board tiem
            Board board = {.found = {false}, .values = {0}};
            for (int y = 0; y < 5; y++)
            {
                for (int x = 0; x < 5; x++)
                {
                    while (*line == ' ')
                        line++;
                    int j = x + y * 5;
                    int amt = to_int(line, &len);
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

    for (int i = 0; i < value_count; i++)
    {
        int value = values[i];
        for (int j = 0; j < board_count; j++)
        {
            Board *board = &boards[j];
            for (int k = 0; k < 25; k++)
            {
                if (board->values[k] == value)
                {
                    board->found[k] = true;

                    bool won = false;

                    // check for all column/row wins
                    for (int x = 0; x < 5; x++)
                    {
                        bool row = true;
                        bool col = true;
                        for (int y = 0; y < 5; y++)
                        {
                            int row_wise = x * 5 + y;
                            int col_wise = y * 5 + x;
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
                        int sum = 0;
                        for (int l = 0; l < 25; l++)
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

int part2(char **lines)
{
    int len = 0;
    int first = to_int(lines[0], &len);
    int value_count = 1;
    int values[1024] = {first};
    Board boards[256] = {0};
    int board_count = 0;
    lines[0] += len;

    while (*lines[0] != '\0')
    {
        lines[0]++;
        int amt = to_int(lines[0], &len);
        lines[0] += len;
        values[value_count++] = amt;
    }

    for (int i = 0; lines[i] != NULL; i++)
    {
        char *line = lines[i];
        if (strlen(line) == 0)
        {
        }
        else
        {
            // board tiem
            Board board = {.found = {false}, .values = {0}, .won = false};
            for (int y = 0; y < 5; y++)
            {
                for (int x = 0; x < 5; x++)
                {
                    while (*line == ' ')
                        line++;
                    int j = x + y * 5;
                    int amt = to_int(line, &len);
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

    int amt_won = 0;

    for (int i = 0; i < value_count; i++)
    {
        int value = values[i];
        for (int j = 0; j < board_count; j++)
        {
            Board *board = &boards[j];
            for (int k = 0; k < 25; k++)
            {
                if (board->values[k] == value)
                {
                    board->found[k] = true;

                    bool won = false;

                    // check for all column/row wins
                    for (int x = 0; x < 5; x++)
                    {
                        bool row = true;
                        bool col = true;
                        for (int y = 0; y < 5; y++)
                        {
                            int row_wise = x * 5 + y;
                            int col_wise = y * 5 + x;
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
                                int sum = 0;
                                for (int l = 0; l < 25; l++)
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