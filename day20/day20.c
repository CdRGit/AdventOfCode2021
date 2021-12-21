#include "utils.h"


void parts(I8 **lines);

void run(bool real)
{
    I8 **lines = get_lines_from_file(real ? "input.txt" : "example.txt");

    parts(lines);
}

I32 main(I32 argc, I8 **argv)
{
    printf("%s", argv[0]);
    printf("\nTEST:\n");
    run(false);
    printf("\nREAL:\n");
    run(true);
}

U16 get_neighbours(bool* grid, I32 x, I32 y, I32 width, I32 height, bool outside)
{
    U16 neighbours = 0;
    if (x == 0) {
        neighbours |= (outside ? 1 : 0) << 8;
        neighbours |= (outside ? 1 : 0) << 5;
        neighbours |= (outside ? 1 : 0) << 2;
    }
    if (x == width - 1) {
        neighbours |= (outside ? 1 : 0) << 6;
        neighbours |= (outside ? 1 : 0) << 3;
        neighbours |= (outside ? 1 : 0) << 0;
    }
    if (y == 0) {
        neighbours |= (outside ? 1 : 0) << 8;
        neighbours |= (outside ? 1 : 0) << 7;
        neighbours |= (outside ? 1 : 0) << 6;
    }
    if (y == height - 1) {
        neighbours |= (outside ? 1 : 0) << 2;
        neighbours |= (outside ? 1 : 0) << 1;
        neighbours |= (outside ? 1 : 0) << 0;
    }
    for (I32 dy = y - 1; dy <= y + 1; dy++) {
        if (dy < 0 || dy >= height)
            continue;
        for (I32 dx = x - 1; dx <= x + 1; dx++) {
            if (dx < 0 || dx >= width)
                continue;
            I32 y_val = 2 - (dy - y + 1);
            I32 x_val = 2 - (dx - x + 1);
            I8 idx = y_val * 3 + x_val;
            neighbours |= (grid[dx + dy * width] ? 1 : 0) << idx;
        }
    }
    return neighbours;
}

void print_grid(bool *grid, I32 width, I32 height) {
    for (I32 y = 0; y < height; y++) {
        for (I32 x = 0; x < width; x++) {
            printf("%c", grid[x + y * width] ? '#' : '.');
        }
        printf("\n");
    }
}

bool* enhance(bool enhancement[512], bool* grid, I32 *width, I32 *height, I32 iterations, bool *outside_grid)
{
    for (I32 i = 0; i < iterations; i++) {
        bool *next_grid = malloc(sizeof(bool) * (*width + 2) * (*height + 2));
        memset(next_grid, enhancement[*outside_grid ? 511 : 0], sizeof(bool) * (*width + 2) * (*height + 2));
        for (I32 y = 0; y < *height; y++) {
            for (I32 x = 0; x < *width; x++) {
                U16 neighbours = get_neighbours(grid, x, y, *width, *height, *outside_grid);
                next_grid[(x + 1) + (y + 1) * (*width + 2)] = enhancement[neighbours];
            }
        }
        *outside_grid = enhancement[*outside_grid ? 511 : 0];
        free(grid);
        grid = next_grid;
        *width += 2;
        *height += 2;
    }
    return grid;
}

void parts(I8 **lines)
{
    bool enhancement[512];
    for (I32 i = 0; i < 512; i++)
        enhancement[i] = lines[0][i] == '#';

    printf("0: %c 511: %c\n", enhancement[0] ? '#' : '.', enhancement[511] ? '#' : '.');

    lines += 2;
    I32 grid_width = 0, grid_height = 0;
    for (grid_height = 0; lines[grid_height] != NULL; grid_height++) {
        I8 *line = lines[grid_height];
        for (grid_width = 0; line[grid_width] != '\0'; grid_width++) {
            printf("%d %d\r", grid_height, grid_width);
        }
    }
    grid_height += 2;
    grid_width += 2;
    printf("%d %d\n", grid_height, grid_width);
    bool *grid = malloc(sizeof(bool) * grid_height * grid_width);
    memset(grid, 0, sizeof(bool) * grid_height * grid_width);
    for (I32 y = 1; y < grid_height - 1; y++) {
        I8 *line = lines[y - 1];
        for (I32 x = 1; x < grid_width - 1; x++) {
            grid[x + y * grid_width] = line[x - 1] == '#';
        }
    }
    bool outside_grid = false;
    grid = enhance(enhancement, grid, &grid_width, &grid_height, 2, &outside_grid);

    U64 count = 0;
    for (I32 x = 0; x < grid_width; x++) {
        for (I32 y = 0; y < grid_height; y++) {
            bool lit = grid[x + y * grid_width];
            count += lit ? 1 : 0;
        }
    }
    printf("Part 1\n= %llu\n", count);

    // 48 more times to get to 50
    grid = enhance(enhancement, grid, &grid_width, &grid_height, 48, &outside_grid);
    count = 0;
    for (I32 x = 0; x < grid_width; x++) {
        for (I32 y = 0; y < grid_height; y++) {
            bool lit = grid[x + y * grid_width];
            count += lit ? 1 : 0;
        }
    }
    printf("Part 2\n= %llu\n", count);
}