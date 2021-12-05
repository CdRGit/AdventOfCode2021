#include "utils.h"

int part1(char **lines);
int part2(char **lines);

void run(bool real)
{
    char **lines = get_lines_from_file(real ? "input.txt" : "example.txt");

    printf("Part 1\n");
    printf("= %u\n", part1(lines));

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
    static int board[1024 * 1024] = {0};
    memset(board, 0, 1024 * 1024 * sizeof(int));

    int len = 0;

    for (int i = 0; lines[i] != NULL; i++)
    {
        char *line = lines[i];

        int x1 = to_int(line, &len);
        line += len;
        line++;
        int y1 = to_int(line, &len);
        line += len;
        line += 4;
        int x2 = to_int(line, &len);
        line += len;
        line++;
        int y2 = to_int(line, &len);

        if (x1 == x2)
        {
            int x = x1;
            for (int y = MIN(y1, y2); y <= MAX(y1, y2); y++)
            {
                board[x + y * 1024]++;
            }
        }
        else if (y1 == y2)
        {
            int y = y1;
            for (int x = MIN(x1, x2); x <= MAX(x1, x2); x++)
            {
                board[x + y * 1024]++;
            }
        }
    }

    int count = 0;
    for (int x = 0; x < 1024; x++)
    {
        for (int y = 0; y < 1024; y++)
        {
            if (board[x + y * 1024] >= 2)
                count++;
        }
    }
    return count;
}

int part2(char **lines)
{
    static int board[1024 * 1024] = {0};
    memset(board, 0, 1024 * 1024 * sizeof(int));

    int len = 0;

    for (int i = 0; lines[i] != NULL; i++)
    {
        char *line = lines[i];

        int x1 = to_int(line, &len);
        line += len;
        line++;
        int y1 = to_int(line, &len);
        line += len;
        line += 4;
        int x2 = to_int(line, &len);
        line += len;
        line++;
        int y2 = to_int(line, &len);

        if (x1 == x2)
        {
            int x = x1;
            for (int y = MIN(y1, y2); y <= MAX(y1, y2); y++)
            {
                board[x + y * 1024]++;
            }
        }
        else if (y1 == y2)
        {
            int y = y1;
            for (int x = MIN(x1, x2); x <= MAX(x1, x2); x++)
            {
                board[x + y * 1024]++;
            }
        }
        else
        {
            int dx = x1 < x2 ? 1 : -1;
            int dy = y1 < y2 ? 1 : -1;
            int delta = MAX(x1, x2) - MIN(x1, x2);
            int y = y1;
            int x = x1;
            for (int i = 0; i <= delta; i++) {
                board[x + y * 1024]++;
                x += dx;
                y += dy;
            }
        }
    }

    int count = 0;
    for (int x = 0; x < 1024; x++)
    {
        for (int y = 0; y < 1024; y++)
        {
            if (board[x + y * 1024] >= 2)
                count++;
        }
    }
    return count;
}