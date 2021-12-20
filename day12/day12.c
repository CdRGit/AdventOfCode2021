#include "utils.h"

#include <stdint.h>

typedef struct Cave Cave;

struct Cave
{
    I8 *name;
    I32 *neighbours;
    bool is_big;
    I32 neighbour_count;
};

I32 part1(I8 **lines); 
I32 part2(I8 **lines);
I32 path_count1(Cave caves[32], I32 cave_count, bool visited[32], I32 curr_idx, I32 end_idx);
I32 path_count2(Cave caves[32], I32 cave_count, bool visited[32], I32 start_idx, I32 end_idx, I32 curr_idx, bool double_dipped);

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
    Cave caves[32] = {0};
    I32 cave_count = 0;
    for (I32 i = 0; lines[i] != NULL; i++)
    {
        I8 *line = lines[i]; 
        I8 *dash_ptr = strchr(line, '-');
        I32 length = dash_ptr - line;
        I8 *first_cave = (I8 *)malloc(length + 1); 
        I8 *second_cave = dash_ptr + 1;
        memcpy(first_cave, line, length);
        first_cave[length] = '\0';

        bool first_exists = false;
        I32 first;

        bool second_exists = false;
        I32 second;

        for (I32 j = 0; j < cave_count; j++)
        {
            Cave cave = caves[j];
            if (strcmp(cave.name, first_cave) == 0)
            {
                first = j;
                first_exists = true;
            }
            if (strcmp(cave.name, second_cave) == 0)
            {
                second = j;
                second_exists = true;
            }
        }
        if (first_exists == false)
        {
            Cave cave;
            cave.name = first_cave;
            cave.is_big = (*first_cave < 'a');
            cave.neighbours = malloc(sizeof(I32) * 32);
            cave.neighbour_count = 0;
            first = cave_count;
            caves[cave_count++] = cave;
        }
        if (second_exists == false)
        {
            Cave cave;
            cave.name = second_cave;
            cave.is_big = (*second_cave < 'a');
            cave.neighbours = malloc(sizeof(I32) * 32);
            cave.neighbour_count = 0;
            second = cave_count;
            caves[cave_count++] = cave;
        }

        caves[first].neighbours[caves[first].neighbour_count++] = second;
        caves[second].neighbours[caves[second].neighbour_count++] = first;
    }

    I32 start_idx = 0;
    I32 end_idx = 0;

    for (I32 i = 0; i < cave_count; i++)
    {
        if (strcmp(caves[i].name, "start") == 0)
            start_idx = i;
        if (strcmp(caves[i].name, "end") == 0)
            end_idx = i;
    }
    printf("%d %d\n", start_idx, end_idx);
    bool visited[32] = {0};
    return path_count1(caves, cave_count, visited, start_idx, end_idx);
}

I32 path_count1(Cave caves[32], I32 cave_count, bool visited[32], I32 curr_idx, I32 end_idx)
{
    Cave cave = caves[curr_idx];

    if (visited[curr_idx] && !cave.is_big)
        return 0;

    if (curr_idx == end_idx)
    {
        return 1;
    }

    visited[curr_idx] = true;
    bool next_visited[32];
    I32 total = 0;
    for (I32 i = 0; i < cave.neighbour_count; i++)
    {
        memcpy(next_visited, visited, 32);
        total += path_count1(caves, cave_count, next_visited, cave.neighbours[i], end_idx);
    }
    return total;
}

I32 part2(I8 **lines)
{
    Cave caves[32] = {0};
    I32 cave_count = 0;
    for (I32 i = 0; lines[i] != NULL; i++)
    {
        I8 *line = lines[i];
        I8 *dash_ptr = strchr(line, '-');
        I32 length = dash_ptr - line;
        I8 *first_cave = (I8 *)malloc(length + 1);
        I8 *second_cave = dash_ptr + 1;
        memcpy(first_cave, line, length);
        first_cave[length] = '\0';

        bool first_exists = false;
        I32 first;

        bool second_exists = false;
        I32 second;

        for (I32 j = 0; j < cave_count; j++)
        {
            Cave cave = caves[j];
            if (strcmp(cave.name, first_cave) == 0)
            {
                first = j;
                first_exists = true;
            }
            if (strcmp(cave.name, second_cave) == 0)
            {
                second = j;
                second_exists = true;
            }
        }
        if (first_exists == false)
        {
            Cave cave;
            cave.name = first_cave;
            cave.is_big = (*first_cave < 'a');
            cave.neighbours = malloc(sizeof(I32) * 32);
            cave.neighbour_count = 0;
            first = cave_count;
            caves[cave_count++] = cave;
        }
        if (second_exists == false)
        {
            Cave cave;
            cave.name = second_cave;
            cave.is_big = (*second_cave < 'a');
            cave.neighbours = malloc(sizeof(I32) * 32);
            cave.neighbour_count = 0;
            second = cave_count;
            caves[cave_count++] = cave;
        }

        caves[first].neighbours[caves[first].neighbour_count++] = second;
        caves[second].neighbours[caves[second].neighbour_count++] = first;
    }

    I32 start_idx = 0;
    I32 end_idx = 0;

    for (I32 i = 0; i < cave_count; i++)
    {
        if (strcmp(caves[i].name, "start") == 0)
            start_idx = i;
        if (strcmp(caves[i].name, "end") == 0)
            end_idx = i;
    }
    printf("%d %d\n", start_idx, end_idx);
    bool visited[32] = {0};
    return path_count2(caves, cave_count, visited, start_idx, end_idx, start_idx, false);
}

I32 path_count2(Cave caves[32], I32 cave_count, bool visited[32], I32 start_idx, I32 end_idx, I32 curr_idx, bool double_dipped)
{
    Cave cave = caves[curr_idx];
    bool next_dipped = double_dipped;

    if (visited[curr_idx] && !cave.is_big)
    {
        if (double_dipped || curr_idx == start_idx)
        {
            return 0;
        }
        else
        {
            next_dipped = true;
        }
    }

    if (curr_idx == end_idx)
    {
        return 1;
    }

    visited[curr_idx] = true;
    bool next_visited[32];
    I32 total = 0;
    for (I32 i = 0; i < cave.neighbour_count; i++)
    {
        memcpy(next_visited, visited, 32);
        total += path_count2(caves, cave_count, next_visited, start_idx, end_idx, cave.neighbours[i], next_dipped);
    }
    return total;
}