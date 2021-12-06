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
    int x = 0, depth = 0;

    for (int i = 0; lines[i] != NULL; i++)
    {
        char* line = lines[i];
        char* space = strchr(line, ' ');
        if (space == NULL)
        {
            fprintf(stderr, "SPACE NOT FOUND ON LINE %d\n", i + 1);
            exit(1);
        }
        char* num = space + 1;
        int value = to_int(num, NULL);
        char first = *line;
        switch (first)
        {
            case 'f':
                x += value;
                break;
            case 'u':
                depth -= value;
                break;
            case 'd':
                depth += value;
                break;
        }
    }

    return x * depth;
}

int part2(char **lines)
{
    int x = 0, depth = 0, aim = 0;

    for (int i = 0; lines[i] != NULL; i++)
    {
        char* line = lines[i];
        char* space = strchr(line, ' ');
        if (space == NULL)
        {
            fprintf(stderr, "SPACE NOT FOUND ON LINE %d\n", i + 1);
            exit(1);
        }
        char* num = space + 1;
        int value = to_int(num, NULL);
        char first = *line;
        switch (first)
        {
            case 'f':
                x += value;
                depth += value * aim;
                break;
            case 'u':
                aim -= value;
                break;
            case 'd':
                aim += value;
                break;
        }
    }

    return x * depth;
}