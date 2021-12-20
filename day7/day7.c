#include "utils.h"

#include <stdint.h>

I32 part1(I32 *ints);
I32 part2(I32 *ints);

void run(bool real)
{
    I8 *content = get_file_content(real ? "input.txt" : "example.txt");
    I8 **numbers = split_by_comma(content);
    I32 *ints = convert_to_int(numbers);

    printf("Part 1\n");
    printf("= %u\n", part1(ints));

    printf("Part 2\n");
    printf("= %u\n", part2(ints));
}

I32 main(I32 argc, I8 **argv)
{
    printf("%s", argv[0]);
    printf("\nTEST:\n");
    run(false);
    printf("\nREAL:\n");
    run(true);
}

I32 part1(I32* ints) {
    I32 min = 0x7FFFFFFF;
    I32 max = 0;
    for (I32 i = 0; ints[i] != -1; i++) {
        I32 total_fuel = 0;
        if (ints[i] < min)
            min = ints[i];
        if (ints[i] > max)
            max = ints[i];
    }

    I32 min_fuel = 0x7FFFFFFF;
    for (I32 pos = min; pos <= max; pos++) {
        I32 total_fuel = 0;
        for (I32 i = 0; ints[i] != -1; i++) {
            I32 diff = abs(ints[i] - pos);
            total_fuel += diff;
        }
        if (total_fuel < min_fuel) {
            min_fuel = total_fuel;
        }
    }

    return min_fuel;
}

I32 part2(I32* ints) {
    I32 min = 0x7FFFFFFF;
    I32 max = 0;
    for (I32 i = 0; ints[i] != -1; i++) {
        I32 total_fuel = 0;
        if (ints[i] < min)
            min = ints[i];
        if (ints[i] > max)
            max = ints[i];
    }

    I32 min_fuel = 0x7FFFFFFF;
    for (I32 pos = min; pos <= max; pos++) {
        I32 total_fuel = 0;
        for (I32 i = 0; ints[i] != -1; i++) {
            I32 diff = abs(ints[i] - pos);
            I32 fuel_usage = (diff * diff + diff) / 2;
            total_fuel += fuel_usage;
        }
        if (total_fuel < min_fuel) {
            min_fuel = total_fuel;
        }
    }

    return min_fuel;
}