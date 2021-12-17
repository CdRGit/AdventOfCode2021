#include "utils.h"

#include <stdint.h>

struct Vector2
{
    I32 x;
    I32 y;
};
typedef struct Vector2 Vector2;

U64 part1(I8 *content);
U64 part2(I8 *content);

void run(bool real)
{
    I8 *content = get_file_content(real ? "input.txt" : "example.txt");

    printf("Part 1\n");
    printf("= %llu           \n", part1(content));

    printf("Part 2\n");
    printf("= %llu           \n", part2(content));
}

I32 main(I32 argc, I8 **argv)
{
    printf("%s", argv[0]);
    printf("\nTEST:\n");
    run(false);
    printf("\nREAL:\n");
    run(true);
}

bool reaches_end(Vector2 vel, Vector2 goal_min, Vector2 goal_max, I32 *max_height)
{
    Vector2 pos = {.x = 0, .y = 0};
    Vector2 prev_pos = pos;
    while (pos.x < goal_max.x && pos.y > goal_min.y && !(pos.x >= goal_min.x && pos.x <= goal_max.x && pos.y >= goal_min.y && pos.y <= goal_max.y))
    {
        prev_pos = pos;
        pos.x += vel.x;
        pos.y += vel.y;
        if (pos.y > *max_height) {
            *max_height = pos.y;
        }
        if (vel.x > 0)
        {
            vel.x--;
        }
        else if (vel.x < 0)
        {
            vel.x++;
        }
        vel.y--;
    }
    return pos.x >= goal_min.x && pos.x <= goal_max.x && pos.y >= goal_min.y && pos.y <= goal_max.y;
}

U64 part1(I8 *content)
{
    content += 15;

    I32 len = 0;
    I32 x_min = to_int(content, &len);

    content += len + 2;

    I32 x_max = to_int(content, &len);

    content += len + 4;

    I32 y_min = to_int(content, &len);

    content += len + 2;

    I32 y_max = to_int(content, &len);

    content += len;

    Vector2 goal_min = {.x = x_min, .y = y_min};
    Vector2 goal_max = {.x = x_max, .y = y_max};

    I32 max_height = 0;

    for (I32 x = 0; x <= x_max; x++)
    {
        for (I32 y = y_min; y < 1000; y++)
        {
            I32 new_max = 0;
            Vector2 vel = {.x = x, .y = y};
            if (reaches_end(vel, goal_min, goal_max, &new_max))
            {
                if (new_max > max_height)
                {
                    max_height = new_max;
                }
            }
        }
    }

    return max_height;
}

U64 part2(I8 *content)
{
    content += 15;

    I32 len = 0;
    I32 x_min = to_int(content, &len);

    content += len + 2;

    I32 x_max = to_int(content, &len);

    content += len + 4;

    I32 y_min = to_int(content, &len);

    content += len + 2;

    I32 y_max = to_int(content, &len);

    content += len;

    Vector2 goal_min = {.x = x_min, .y = y_min};
    Vector2 goal_max = {.x = x_max, .y = y_max};

    U64 count = 0;

    for (I32 x = 0; x <= x_max; x++)
    {
        for (I32 y = y_min; y < 1000; y++)
        {
            I32 new_max = 0;
            Vector2 vel = {.x = x, .y = y};
            if (reaches_end(vel, goal_min, goal_max, &new_max))
            {
                count++;
            }
        }
    }

    return count;
}