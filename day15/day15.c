#include "utils.h"

#include <stdint.h>

struct Position
{
    U16 x;
    U16 y;
};
typedef struct Position Position;

U64 part1(I8 **lines);
U64 part2(I8 **lines);

#define SIZE 500

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

U64 dijkstra(U16 start_x, U16 start_y, U16 goal_x, U16 goal_y, U8 values[SIZE * SIZE])
{
    Position start = {.x = start_x, .y = start_y};
    Position goal = {.x = goal_x, .y = goal_y};

    static U64 dist[SIZE * SIZE];
    static Position prev[SIZE * SIZE];

    static Position open[SIZE * SIZE];
    I32 open_count = 0;

    for (U16 x = 0; x < SIZE; x++)
    {
        for (U16 y = 0; y < SIZE; y++)
        {
            Position current = {.x = x, .y = y};
            if (values[x + y * SIZE] != 0xFF)
                open[open_count++] = current;
            Position prev_p = {.x = 0, .y = 0};
            prev[x + y * SIZE] = current;
            dist[x + y * SIZE] = 0xFFFFFFFFFFFFFFFF;
        }
    }

    dist[start.x + start.y * SIZE] = 0;

    while (open_count > 0)
    {
        Position current;
        U64 shortest_dist = 0xFFFFFFFFFFFFFFFF;
        I32 current_i;
        for (I32 i = 0; i < open_count; i++)
        {
            Position investigated = open[i];

            if (dist[investigated.x + investigated.y * SIZE] < shortest_dist)
            {
                current = investigated;
                shortest_dist = dist[investigated.x + investigated.y * SIZE];
                current_i = i;
            }
        }

        open_count--;

        for (I32 i = current_i; i < open_count; i++)
        {
            open[i] = open[i + 1];
        }

        const U16 offsets[8] = {0xFFFF, 0, 1, 0, 0, 0xFFFF, 0, 1};
        for (I32 i = 0; i < 4; i++)
        {
            U16 x = current.x + offsets[i];
            U16 y = current.y + offsets[i + 4];
            Position neighbour = {.x = x, .y = y};

            bool in_open_set = false;
            for (I32 j = 0; j < open_count; j++)
            {
                Position open_p = open[j];
                if (open_p.x == neighbour.x && open_p.y == neighbour.y)
                {
                    in_open_set = true;
                    break;
                }
            }
            if (!in_open_set)
                continue;

            U64 alt = shortest_dist + values[x + y * SIZE];
            if (alt < dist[x + y * SIZE])
            {
                dist[x + y * SIZE] = alt;
                prev[x + y * SIZE] = current;
                printf("         \r %3d, %3d\r", x, y);
            }
        }
    }

    Position current = goal;
    U64 total = 0;
    while (current.x != start.x || current.y != start.y)
    {
        total += values[current.x + current.y * SIZE];
        current = prev[current.x + current.y * SIZE];
    }

    return dist[goal_x + goal_y * SIZE];
}

U64 part1(I8 **lines)
{
    static U8 values[SIZE * SIZE];
    memset(values, 0xFF, sizeof(values));

    I32 height = 0, width = 0;

    for (height = 0; lines[height] != NULL; height++)
    {
        I8 *line = lines[height];
        for (width = 0; line[width] != '\0'; width++)
        {
            values[width + height * SIZE] = line[width] - '0';
        }
    }

    U64 score = dijkstra(0, 0, width - 1, height - 1, values);
    return score;
}

U64 part2(I8 **lines)
{
    static U8 values[SIZE * SIZE];
    memset(values, 0xFF, sizeof(values));

    I32 height = 0, width = 0;

    for (height = 0; lines[height] != NULL; height++)
    {
        I8 *line = lines[height];
        for (width = 0; line[width] != '\0'; width++)
        {
            values[width + height * SIZE] = line[width] - '0';
        }
    }

    for (I32 i = 0; i < 5; i++) {
        for (I32 j = 0; j < 5; j++) {
            for (I32 x = 0; x < width; x++) {
                I32 actual_x = x + i * width;
                for (I32 y = 0; y < height; y++) {
                    I32 actual_y = y + j * height;
                    U8 value = values[x + y * SIZE];
                    value += i + j;
                    value -= 1;
                    value %= 9;
                    value += 1;
                    values[actual_x + actual_y * SIZE] = value;
                }
            }
        }
    }

    U64 score = dijkstra(0, 0, width * 5 - 1, height * 5 - 1, values);
    return score;
}