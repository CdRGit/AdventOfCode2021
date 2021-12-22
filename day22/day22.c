#include "utils.h"

struct Vector3 {
    I64 x;
    I64 y;
    I64 z;
};

struct Line {
    I64 start;
    I64 end;
};

typedef struct Line Line;

typedef struct Vector3 Vector3;

struct Cuboid {
    Vector3 min;
    Vector3 max;
};

typedef struct Cuboid Cuboid;

void part1(I8 **lines);
void part2(I8 **lines);

void run(bool real)
{
    I8 **lines = get_lines_from_file(real ? "input.txt" : "example.txt");

    part1(lines);
    part2(lines);
}

I32 main(I32 argc, I8 **argv)
{
    printf("%s", argv[0]);
    printf("\nTEST:\n");
    run(false);
    printf("\nREAL:\n");
    run(true);
}

void part1(I8 **lines) {
    bool cubes[101][101][101];
    memset(cubes, 0, sizeof(cubes));
    
    for (I32 i = 0; lines[i] != NULL; i++) {
        I8 *line = lines[i];
        bool is_on = line[1] == 'n';

        if (is_on)
            line += 5;
        else
            line += 6;

        I32 len = 0;

        I32 x_min = to_int(line, &len);

        line += len + 2;

        I32 x_max = to_int(line, &len);

        line += len + 3;

        I32 y_min = to_int(line, &len);

        line += len + 2;

        I32 y_max = to_int(line, &len);

        line += len + 3;

        I32 z_min = to_int(line, &len);

        line += len + 2;

        I32 z_max = to_int(line, &len);

        line += len;

        assert(x_min <= x_max);
        assert(y_min <= y_max);
        assert(z_min <= z_max);
        
        for (I32 x = MAX(x_min, -50); x <= MIN(x_max, 50); x++) {
            for (I32 y = MAX(y_min, -50); y <= MIN(y_max, 50); y++) {
                for (I32 z = MAX(z_min, -50); z <= MIN(z_max, 50); z++) {
                    if (x < -50 || x > 50 || y < -50 || y > 50 || z < -50 || z > 50)
                        continue;
                    cubes[x + 50][y + 50][z + 50] = is_on;
                }
            }
        }
    }

    U64 count = 0;
    for (I32 x = -50; x <= 50; x++) {
        for (I32 y = -50; y <= 50; y++) {
            for (I32 z = -50; z <= 50; z++) {
                if (cubes[x + 50][y + 50][z + 50])
                    count++;
            }
        }
    }

    printf("Part 1\n= %llu\n", count);
}

Vector3 sub_vec3(Vector3 a, Vector3 b)
{
    Vector3 result = {.x = a.x - b.x, .y = a.y - b.y, .z = a.z - b.z};
    return result;
}

U64 volume(Cuboid cuboid) {
    Vector3 size = sub_vec3(cuboid.max, cuboid.min);
    return (size.x + 1) * (size.y + 1) * (size.z + 1);
}

Line overlap_line(I32 min0, I32 max0, I32 min1, I32 max1) {
    Line l = {.start = MAX(min0, min1), .end = MIN(max0, max1)};
    return l;
}

U64 overlap(Cuboid box, Cuboid *boxes, I32 box_count, I32 box_start) {
    U64 total = 0;
    for (I32 i = box_start; i < box_count; i++) {
        Cuboid b = boxes[i];
        Line x_line = overlap_line(box.min.x, box.max.x, b.min.x, b.max.x);
        Line y_line = overlap_line(box.min.y, box.max.y, b.min.y, b.max.y);
        Line z_line = overlap_line(box.min.z, box.max.z, b.min.z, b.max.z);
        if (x_line.end - x_line.start >= 0 && y_line.end - y_line.start >= 0 && z_line.end - z_line.start >= 0) {
            Cuboid temp_box = {.min = {.x = x_line.start, .y = y_line.start, .z = z_line.start}, .max = {.x = x_line.end, .y = y_line.end, .z = z_line.end}};
            total += volume(temp_box) - overlap(temp_box, boxes, box_count, 1 + i);
        }
    }   
    return total;
}

void part2(I8 **lines)
{
    I32 instruction_count = ptr_arr_len((void**) lines);
    I32 cuboid_count = 0;
    U64 total_on = 0;
    Cuboid cuboids[500];
    for (I32 i = instruction_count - 1; i >= 0; i--) {
        I8 *line = lines[i];
        bool is_on = line[1] == 'n';

        if (is_on)
            line += 5;
        else
            line += 6;

        I32 len = 0;

        I32 x_min = to_int(line, &len);

        line += len + 2;

        I32 x_max = to_int(line, &len);

        line += len + 3;

        I32 y_min = to_int(line, &len);

        line += len + 2;

        I32 y_max = to_int(line, &len);

        line += len + 3;

        I32 z_min = to_int(line, &len);

        line += len + 2;

        I32 z_max = to_int(line, &len);

        line += len;

        assert(x_min <= x_max);
        assert(y_min <= y_max);
        assert(z_min <= z_max);
        
        Cuboid new_cuboid = {.min = {.x = x_min, .y = y_min, .z = z_min}, .max = {.x = x_max, .y = y_max, .z = z_max}};
        if (is_on) {
            total_on += volume(new_cuboid) - overlap(new_cuboid, cuboids, cuboid_count, 0);
        }
        cuboids[cuboid_count++] = new_cuboid;
    }

    printf("Part 2\n= %llu\n", total_on);
}