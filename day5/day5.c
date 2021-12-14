#include "utils.h"

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
    static I32 board[1024 * 1024] = {0};
    memset(board, 0, 1024 * 1024 * sizeof(I32));

    I32 len = 0;

    for (I32 i = 0; lines[i] != NULL; i++)
    {
        I8 *line = lines[i];

        I32 x1 = to_int(line, &len);
        line += len;
        line++;
        I32 y1 = to_int(line, &len);
        line += len;
        line += 4;
        I32 x2 = to_int(line, &len);
        line += len;
        line++;
        I32 y2 = to_int(line, &len);

        if (x1 == x2)
        {
            I32 x = x1;
            for (I32 y = MIN(y1, y2); y <= MAX(y1, y2); y++)
            {
                board[x + y * 1024]++;
            }
        }
        else if (y1 == y2)
        {
            I32 y = y1;
            for (I32 x = MIN(x1, x2); x <= MAX(x1, x2); x++)
            {
                board[x + y * 1024]++;
            }
        }
    }

    I32 count = 0;
    for (I32 x = 0; x < 1024; x++)
    {
        for (I32 y = 0; y < 1024; y++)
        {
            if (board[x + y * 1024] >= 2)
                count++;
        }
    }
    return count;
}

I32 part2(I8 **lines)
{
    static I32 board[1024 * 1024] = {0};
    memset(board, 0, 1024 * 1024 * sizeof(I32));

    I32 len = 0;

    for (I32 i = 0; lines[i] != NULL; i++)
    {
        I8 *line = lines[i];

        I32 x1 = to_int(line, &len);
        line += len;
        line++;
        I32 y1 = to_int(line, &len);
        line += len;
        line += 4;
        I32 x2 = to_int(line, &len);
        line += len;
        line++;
        I32 y2 = to_int(line, &len);

        if (x1 == x2)
        {
            I32 x = x1;
            for (I32 y = MIN(y1, y2); y <= MAX(y1, y2); y++)
            {
                board[x + y * 1024]++;
            }
        }
        else if (y1 == y2)
        {
            I32 y = y1;
            for (I32 x = MIN(x1, x2); x <= MAX(x1, x2); x++)
            {
                board[x + y * 1024]++;
            }
        }
        else
        {
            I32 dx = x1 < x2 ? 1 : -1;
            I32 dy = y1 < y2 ? 1 : -1;
            I32 delta = MAX(x1, x2) - MIN(x1, x2);
            I32 y = y1;
            I32 x = x1;
            for (I32 i = 0; i <= delta; i++) {
                board[x + y * 1024]++;
                x += dx;
                y += dy;
            }
        }
    }

    I32 count = 0;
    for (I32 x = 0; x < 1024; x++)
    {
        for (I32 y = 0; y < 1024; y++)
        {
            if (board[x + y * 1024] >= 2)
                count++;
        }
    }
    return count;
}