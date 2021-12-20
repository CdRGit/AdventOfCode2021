#include "utils.h"

I32 part1(I8 **lines);
I32 part2(I8 **lines);

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
    I32 bit_weight[16] = {0};

    for (I32 i = 0; lines[i] != NULL; i++)
    {
        I8 *line = lines[i];
        for (I32 j = 0; line[j] != '\0'; j++)
        {
            if (line[j] == '1')
                bit_weight[j]++;
            else if (line[j] == '0')
                bit_weight[j]--;
        }
    }

    I32 gamma = 0;
    I32 epsilon = 0;
    for (I32 i = 0; i < 16; i++)
    {
        if (bit_weight[i] == 0)
            continue;

        gamma <<= 1;
        epsilon <<= 1;
        if (bit_weight[i] > 0)
            gamma |= 1;
        else
            epsilon |= 1;
    }

    return gamma * epsilon;
}

I32 oxygen_generator_rating(I8 **lines, I32 depth)
{
    I32 ones = 0;
    I32 zeros = 0;

    for (I32 i = 0; lines[i] != NULL; i++)
    {
        I8 *line = lines[i];
        if (line[depth] == '1')
            ones++;
        else if (line[depth] == '0')
            zeros++;
    }
    
    I32 count = ones >= zeros ? ones : zeros;

    I8 expected_I8 = ones >= zeros ? '1' : '0';
    
    I8 **new_lines = malloc(sizeof(I8*) * (count + 1));

    I32 j = 0;
    for (I32 i = 0; lines[i] != NULL; i++)
    {
        I8 *line = lines[i];
        if (line[depth] == expected_I8)
            new_lines[j++] = line;
    }
    new_lines[j] = NULL;

    if (j == 1) {
        I8 *line = new_lines[0];
        return bin_str_to_int(line);
    }
    else {
        return oxygen_generator_rating(new_lines, depth + 1);
    }
}


I32 co2_scrubber_rating(I8 **lines, I32 depth)
{
    I32 ones = 0;
    I32 zeros = 0;

    for (I32 i = 0; lines[i] != NULL; i++)
    {
        I8 *line = lines[i];
        if (line[depth] == '1')
            ones++;
        else if (line[depth] == '0')
            zeros++;
    }
    
    I32 count = ones < zeros ? ones : zeros;

    I8 expected_I8 = ones < zeros ? '1' : '0';
    
    I8 **new_lines = malloc(sizeof(I8*) * (count + 1));

    I32 j = 0;
    for (I32 i = 0; lines[i] != NULL; i++)
    {
        I8 *line = lines[i];
        if (line[depth] == expected_I8)
            new_lines[j++] = line;
    }
    new_lines[j] = NULL;

    if (j == 1) {
        I8 *line = new_lines[0];
        return bin_str_to_int(line);
    }
    else {
        return co2_scrubber_rating(new_lines, depth + 1);
    }
}

I32 part2(I8 **lines)
{
    I32 oxygen = oxygen_generator_rating(lines, 0);
    I32 co2 = co2_scrubber_rating(lines, 0);

    return oxygen * co2;
}