#include "utils.h"

typedef struct Scanner Scanner;

typedef struct Vector3 Vector3;
typedef Vector3 Beacon;

struct Vector3
{
    I64 x, y, z;
};

struct Scanner
{
    U64 beacon_count;
    Beacon *beacons;
};

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

Scanner *parse_scanners(I8 **lines, U64 *scanner_count)
{
    static Scanner scanners[50];
    *scanner_count = 0;
    U64 line_idx = 0;
    for (; lines[line_idx] != NULL; line_idx++)
    {
        line_idx++;
        U64 beacon_count = 0;
        for (; lines[line_idx + beacon_count] != NULL && strlen(lines[line_idx + beacon_count]) != 0; beacon_count++)
        {
            //
        }
        Beacon *beacons = malloc(sizeof(Beacon) * beacon_count);
        for (U64 i = 0; i < beacon_count; i++)
        {
            I8 *line = lines[line_idx + i];
            I32 length;
            I64 x = to_int(line, &length);
            line += length + 1;
            I64 y = to_int(line, &length);
            line += length + 1;
            I64 z = to_int(line, &length);
            line += length + 1;
            beacons[i].x = x;
            beacons[i].y = y;
            beacons[i].z = z;
        }
        line_idx += beacon_count;
        Scanner scanner = {.beacon_count = beacon_count, .beacons = beacons};
        scanners[(*scanner_count)++] = scanner;
    }
    return scanners;
}

Vector3 rotate_vec3(Vector3 o, I32 rot)
{
    Vector3 v;
    switch (rot)
    {
    case 0:
        v.x = o.x;
        v.y = o.y;
        v.z = o.z;
        return v;
    case 1:
        v.x = o.x;
        v.y = -o.y;
        v.z = -o.z;
        return v;
    case 2:
        v.x = -o.x;
        v.y = o.y;
        v.z = -o.z;
        return v;
    case 3:
        v.x = -o.x;
        v.y = -o.y;
        v.z = o.z;
        return v;

    case 4:
        v.x = -o.y;
        v.y = o.x;
        v.z = o.z;
        return v;
    case 5:
        v.x = o.y;
        v.y = -o.x;
        v.z = o.z;
        return v;
    case 6:
        v.x = o.y;
        v.y = o.x;
        v.z = -o.z;
        return v;
    case 7:
        v.x = -o.y;
        v.y = -o.x;
        v.z = -o.z;
        return v;

    case 8:
        v.x = -o.z;
        v.y = o.y;
        v.z = o.x;
        return v;
    case 9:
        v.x = o.z;
        v.y = -o.y;
        v.z = o.x;
        return v;
    case 10:
        v.x = o.z;
        v.y = o.y;
        v.z = -o.x;
        return v;
    case 11:
        v.x = -o.z;
        v.y = -o.y;
        v.z = -o.x;
        return v;

    case 12:
        v.x = o.y;
        v.y = -o.z;
        v.z = -o.x;
        return v;
    case 13:
        v.x = -o.y;
        v.y = o.z;
        v.z = -o.x;
        return v;
    case 14:
        v.x = -o.y;
        v.y = -o.z;
        v.z = o.x;
        return v;
    case 15:
        v.x = o.y;
        v.y = o.z;
        v.z = o.x;
        return v;

    case 16:
        v.x = -o.x;
        v.y = o.z;
        v.z = o.y;
        return v;
    case 17:
        v.x = o.x;
        v.y = -o.z;
        v.z = o.y;
        return v;
    case 18:
        v.x = o.x;
        v.y = o.z;
        v.z = -o.y;
        return v;
    case 19:
        v.x = -o.x;
        v.y = -o.z;
        v.z = -o.y;
        return v;

    case 20:
        v.x = o.z;
        v.y = -o.x;
        v.z = -o.y;
        return v;
    case 21:
        v.x = -o.z;
        v.y = o.x;
        v.z = -o.y;
        return v;
    case 22:
        v.x = -o.z;
        v.y = -o.x;
        v.z = o.y;
        return v;
    case 23:
        v.x = o.z;
        v.y = o.x;
        v.z = o.y;
        return v;

    default:
        return o;
    }
}

Scanner rotate(Scanner scanner, I32 rot)
{
    Scanner new_scanner;
    new_scanner.beacon_count = scanner.beacon_count;
    new_scanner.beacons = malloc(sizeof(Beacon) * new_scanner.beacon_count);

    for (I32 i = 0; i < new_scanner.beacon_count; i++)
    {
        new_scanner.beacons[i] = rotate_vec3(scanner.beacons[i], rot);
    }
    return new_scanner;
}

Scanner *rotate_all_ways(Scanner scanner)
{
    Scanner *rotations = malloc(sizeof(Scanner) * 24);
    for (I32 i = 0; i < 24; i++)
    {
        rotations[i] = rotate(scanner, i);
    }
    return rotations;
}

Vector3 sub_vec3(Vector3 a, Vector3 b)
{
    Vector3 result = {.x = a.x - b.x, .y = a.y - b.y, .z = a.z - b.z};
    return result;
}

Vector3 add_vec3(Vector3 a, Vector3 b)
{
    Vector3 result = {.x = a.x + b.x, .y = a.y + b.y, .z = a.z + b.z};
    return result;
}

I32 find_overlap(Scanner a, Scanner b, Vector3 offset)
{
    I32 count = 0;
    for (I32 i = 0; i < a.beacon_count; i++)
    {
        Vector3 a_pos = a.beacons[i];
        for (I32 j = 0; j < b.beacon_count; j++)
        {
            Vector3 b_pos = add_vec3(b.beacons[j], offset);
            if (a_pos.x == b_pos.x && a_pos.y == b_pos.y && a_pos.z == b_pos.z)
            {
                count++;
            }
        }
    }
    return count;
}

bool find_translation(Scanner a, Scanner b, Vector3 *translation)
{
    for (I32 i1 = 0; i1 < a.beacon_count; i1++)
    {
        Vector3 a_left = a.beacons[i1];
        for (I32 i2 = 0; i2 < a.beacon_count; i2++)
        {
            if (i1 == i2)
                continue;
            Vector3 a_right = a.beacons[i2];

            Vector3 a_diff = sub_vec3(a_left, a_right);

            for (I32 j1 = 0; j1 < b.beacon_count; j1++)
            {
                Vector3 b_left = b.beacons[j1];
                for (I32 j2 = 0; j2 < b.beacon_count; j2++)
                {
                    if (j1 == j2)
                        continue;
                    Vector3 b_right = b.beacons[j2];

                    Vector3 b_diff = sub_vec3(b_left, b_right);
                    if (a_diff.x == b_diff.x && a_diff.y == b_diff.y && a_diff.z == b_diff.z)
                    {
                        Vector3 off = sub_vec3(a_left, b_left);
                        I32 overlapping = find_overlap(a, b, off);
                        if (overlapping >= 12)
                        {
                            *translation = off;
                            return true;
                        }
                        else
                        {
                            return false;
                        }
                    }
                }
            }
        }
    }

    return false;
}

Scanner *try_merge_scanners(Scanner a, Scanner b, Vector3 *offset)
{
    Scanner *b_rotations = rotate_all_ways(b);
    for (I32 i = 0; i < 24; i++)
    {
        Scanner *merged = malloc(sizeof(Scanner));
        Scanner b_prime = b_rotations[i];

        Vector3 translation;
        bool matching = find_translation(a, b_prime, &translation);
        if (matching)
        {
            printf("%d,%d,%d\n", translation.x, translation.y, translation.z);
            merged->beacon_count = 0;
            // do merging
            for (I32 i1 = 0; i1 < a.beacon_count; i1++)
            {
                Vector3 a_pos = a.beacons[i1];
                bool in_b = false;
                for (I32 i2 = 0; i2 < b_prime.beacon_count; i2++)
                {
                    Vector3 b_pos = add_vec3(b_prime.beacons[i2], translation);
                    if (a_pos.x == b_pos.x && a_pos.y == b_pos.y && a_pos.z == b_pos.z)
                    {
                        in_b = true;
                    }
                }
                if (in_b)
                    continue;

                merged->beacon_count++;
            }
            for (I32 i2 = 0; i2 < b_prime.beacon_count; i2++)
            {
                merged->beacon_count++;
            }
            merged->beacons = malloc(sizeof(Beacon) * merged->beacon_count);
            I32 beacon_idx = 0;
            for (I32 i1 = 0; i1 < a.beacon_count; i1++)
            {
                Vector3 a_pos = a.beacons[i1];
                bool in_b = false;
                for (I32 i2 = 0; i2 < b_prime.beacon_count; i2++)
                {
                    Vector3 b_pos = add_vec3(b_prime.beacons[i2], translation);
                    if (a_pos.x == b_pos.x && a_pos.y == b_pos.y && a_pos.z == b_pos.z)
                    {
                        in_b = true;
                    }
                }
                if (in_b)
                    continue;

                merged->beacons[beacon_idx++] = a_pos;
            }
            for (I32 i2 = 0; i2 < b_prime.beacon_count; i2++)
            {
                Vector3 b_pos = add_vec3(b_prime.beacons[i2], translation);
                merged->beacons[beacon_idx++] = b_pos;
            }

            *offset = translation;
            return merged;
        }

        free(merged);
    }
    return NULL;
}

void print_scanner(Scanner scanner)
{
    printf("--- scanner ---\n");
    for (I32 i = 0; i < scanner.beacon_count; i++)
        printf("%d,%d,%d\n", scanner.beacons[i].x, scanner.beacons[i].y, scanner.beacons[i].z);
}

void parts(I8 **lines)
{
    U64 scanner_count;
    Scanner *scanners = parse_scanners(lines, &scanner_count);
    U64 unused_scanners = scanner_count - 1;
    bool used[1024] = {0};
    Vector3 offsets[1024];
    for (I32 i = 0; i < scanner_count; i++)
        used[i] = false;
    Scanner total_scan = scanners[0];
    used[0] = true;
    while (unused_scanners > 0)
    {
        for (I32 j = 0; j < scanner_count; j++)
        {
            if (used[j])
                continue;
            Vector3 offset;
            Scanner *new_scanner = try_merge_scanners(total_scan, scanners[j], &offset);
            if (new_scanner != NULL)
            {
                printf("%d\n", j);
                used[j] = true;
                offsets[j] = offset;
                total_scan = *new_scanner;
                unused_scanners--;
                printf("unused: %d\n", unused_scanners);
                break;
            }
        }
    }
    printf("Part 1:\n=%llu\n", total_scan.beacon_count);
    U64 biggest_dist = 0;
    for (I32 i = 0; i < scanner_count; i++)
    {
        for (I32 j = 0; j < scanner_count; j++)
        {
            if (i==j)
                continue;
            Vector3 diff = sub_vec3(offsets[i], offsets[j]);
            U64 total_diff = abs(diff.x) + abs(diff.y) + abs(diff.z);
            if (total_diff > biggest_dist)
                biggest_dist = total_diff;
        }
    }
    printf("Part 2:\n=%llu\n", biggest_dist);
}