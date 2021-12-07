#include "utils.h"
#include <inttypes.h>
#include <stdint.h>

int part1(int *ints);
int part2(int *ints);

void run(bool real)
{
    char *content = get_file_content(real ? "input.txt" : "example.txt");
    char **numbers = split_by_comma(content);
    int *ints = convert_to_int(numbers);

    printf("Part 1\n");
    printf("= %u\n", part1(ints));

    printf("Part 2\n");
    printf("= %u\n", part2(ints));
}

int main(int argc, char **argv)
{
    printf("%s", argv[0]);
    printf("\nTEST:\n");
    run(false);
    printf("\nREAL:\n");
    run(true);
}

int part1(int* ints) {
    int min = 0x7FFFFFFF;
    int max = 0;
    for (int i = 0; ints[i] != -1; i++) {
        int total_fuel = 0;
        if (ints[i] < min)
            min = ints[i];
        if (ints[i] > max)
            max = ints[i];
    }

    int min_fuel = 0x7FFFFFFF;
    for (int pos = min; pos <= max; pos++) {
        int total_fuel = 0;
        for (int i = 0; ints[i] != -1; i++) {
            int diff = abs(ints[i] - pos);
            total_fuel += diff;
        }
        if (total_fuel < min_fuel) {
            min_fuel = total_fuel;
        }
    }

    return min_fuel;
}

int part2(int* ints) {
    int min = 0x7FFFFFFF;
    int max = 0;
    for (int i = 0; ints[i] != -1; i++) {
        int total_fuel = 0;
        if (ints[i] < min)
            min = ints[i];
        if (ints[i] > max)
            max = ints[i];
    }

    int min_fuel = 0x7FFFFFFF;
    for (int pos = min; pos <= max; pos++) {
        int total_fuel = 0;
        for (int i = 0; ints[i] != -1; i++) {
            int diff = abs(ints[i] - pos);
            int fuel_usage = (diff * diff + diff) / 2;
            total_fuel += fuel_usage;
        }
        if (total_fuel < min_fuel) {
            min_fuel = total_fuel;
        }
    }

    return min_fuel;
}