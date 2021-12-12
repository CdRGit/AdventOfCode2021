#include "utils.h"
#include <inttypes.h>
#include <stdint.h>

typedef unsigned char byte;

typedef struct Cave Cave;

struct Cave
{
    char *name;
    int *neighbours;
    bool is_big;
    int neighbour_count;
};

int part1(char **lines);
int part2(char **lines);
int path_count1(Cave caves[32], int cave_count, bool visited[32], int curr_idx, int end_idx);
int path_count2(Cave caves[32], int cave_count, bool visited[32], int start_idx, int end_idx, int curr_idx, bool double_dipped);

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
    Cave caves[32] = {0};
    int cave_count = 0;
    for (int i = 0; lines[i] != NULL; i++)
    {
        char *line = lines[i];
        char *dash_ptr = strchr(line, '-');
        int length = dash_ptr - line;
        char *first_cave = (char *)malloc(length + 1);
        char *second_cave = dash_ptr + 1;
        memcpy(first_cave, line, length);
        first_cave[length] = '\0';

        bool first_exists = false;
        int first;

        bool second_exists = false;
        int second;

        for (int j = 0; j < cave_count; j++)
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
            cave.neighbours = malloc(sizeof(int) * 32);
            cave.neighbour_count = 0;
            first = cave_count;
            caves[cave_count++] = cave;
        }
        if (second_exists == false)
        {
            Cave cave;
            cave.name = second_cave;
            cave.is_big = (*second_cave < 'a');
            cave.neighbours = malloc(sizeof(int) * 32);
            cave.neighbour_count = 0;
            second = cave_count;
            caves[cave_count++] = cave;
        }

        caves[first].neighbours[caves[first].neighbour_count++] = second;
        caves[second].neighbours[caves[second].neighbour_count++] = first;
    }

    int start_idx = 0;
    int end_idx = 0;

    for (int i = 0; i < cave_count; i++)
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

int path_count1(Cave caves[32], int cave_count, bool visited[32], int curr_idx, int end_idx)
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
    int total = 0;
    for (int i = 0; i < cave.neighbour_count; i++)
    {
        memcpy(next_visited, visited, 32);
        total += path_count1(caves, cave_count, next_visited, cave.neighbours[i], end_idx);
    }
    return total;
}

int part2(char **lines)
{
    Cave caves[32] = {0};
    int cave_count = 0;
    for (int i = 0; lines[i] != NULL; i++)
    {
        char *line = lines[i];
        char *dash_ptr = strchr(line, '-');
        int length = dash_ptr - line;
        char *first_cave = (char *)malloc(length + 1);
        char *second_cave = dash_ptr + 1;
        memcpy(first_cave, line, length);
        first_cave[length] = '\0';

        bool first_exists = false;
        int first;

        bool second_exists = false;
        int second;

        for (int j = 0; j < cave_count; j++)
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
            cave.neighbours = malloc(sizeof(int) * 32);
            cave.neighbour_count = 0;
            first = cave_count;
            caves[cave_count++] = cave;
        }
        if (second_exists == false)
        {
            Cave cave;
            cave.name = second_cave;
            cave.is_big = (*second_cave < 'a');
            cave.neighbours = malloc(sizeof(int) * 32);
            cave.neighbour_count = 0;
            second = cave_count;
            caves[cave_count++] = cave;
        }

        caves[first].neighbours[caves[first].neighbour_count++] = second;
        caves[second].neighbours[caves[second].neighbour_count++] = first;
    }

    int start_idx = 0;
    int end_idx = 0;

    for (int i = 0; i < cave_count; i++)
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

int path_count2(Cave caves[32], int cave_count, bool visited[32], int start_idx, int end_idx, int curr_idx, bool double_dipped)
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
    int total = 0;
    for (int i = 0; i < cave.neighbour_count; i++)
    {
        memcpy(next_visited, visited, 32);
        total += path_count2(caves, cave_count, next_visited, start_idx, end_idx, cave.neighbours[i], next_dipped);
    }
    return total;
}