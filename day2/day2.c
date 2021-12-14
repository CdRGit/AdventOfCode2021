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
    I32 x = 0, depth = 0;

    for (I32 i = 0; lines[i] != NULL; i++)
    {
        I8* line = lines[i];
        I8* space = strchr(line, ' ');
        if (space == NULL)
        {
            fprintf(stderr, "SPACE NOT FOUND ON LINE %d\n", i + 1);
            exit(1);
        }
        I8* num = space + 1;
        I32 value = to_int(num, NULL);
        I8 first = *line;
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

I32 part2(I8 **lines)
{
    I32 x = 0, depth = 0, aim = 0;

    for (I32 i = 0; lines[i] != NULL; i++)
    {
        I8* line = lines[i];
        I8* space = strchr(line, ' ');
        if (space == NULL)
        {
            fprintf(stderr, "SPACE NOT FOUND ON LINE %d\n", i + 1);
            exit(1);
        }
        I8* num = space + 1;
        I32 value = to_int(num, NULL);
        I8 first = *line;
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