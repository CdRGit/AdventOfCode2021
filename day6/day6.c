#include "utils.h"

#include <stdint.h>

uint64_t fish_sim(I32 *ints, I32 max_days);

void run(bool real)
{
    I8 *content = get_file_content(real ? "input.txt" : "example.txt");
    I8 **numbers = split_by_comma(content);
    I32 *ints = convert_to_int(numbers);

    printf("Part 1\n");
    printf("= %llu\n", fish_sim(ints, 80));

    printf("Part 2\n");
    printf("= %llu\n", fish_sim(ints, 256));
}

I32 main(I32 argc, I8 **argv)
{
    printf("%s", argv[0]);
    printf("\nTEST:\n");
    run(false);
    printf("\nREAL:\n");
    run(true);
}

uint64_t fish_sim(I32 *ints, I32 max_days)
{
    uint64_t days_until_repro[9] = {0};
    for (I32 i = 0; ints[i] != -1; i++)
    {
        days_until_repro[ints[i]]++;
    }

    for (I32 day = 0; day < max_days; day++)
    {
        uint64_t new_fishes = days_until_repro[0];
        for (I32 i = 0; i < 8; i++) {
            days_until_repro[i] = days_until_repro[i + 1];
        }
        days_until_repro[8] = new_fishes;
        days_until_repro[6] += new_fishes;
        
        uint64_t fish_count = 0;
        for (I32 i = 0; i < 9; i++) {
            fish_count += days_until_repro[i];
        }
    }
    uint64_t fish_count = 0;
    for (I32 i = 0; i < 9; i++) {
        fish_count += days_until_repro[i];
    }
    return fish_count;
}