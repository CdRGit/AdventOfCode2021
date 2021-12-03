#include "utils.h"

int part1(char **lines);
int part2(char **lines);

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
    int bit_weight[16] = {0};

    for (int i = 0; lines[i] != NULL; i++)
    {
        char *line = lines[i];
        for (int j = 0; line[j] != '\0'; j++)
        {
            if (line[j] == '1')
                bit_weight[j]++;
            else if (line[j] == '0')
                bit_weight[j]--;
        }
    }

    int gamma = 0;
    int epsilon = 0;
    for (int i = 0; i < 16; i++)
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

int oxygen_generator_rating(char **lines, int depth)
{
    int ones = 0;
    int zeros = 0;

    for (int i = 0; lines[i] != NULL; i++)
    {
        char *line = lines[i];
        if (line[depth] == '1')
            ones++;
        else if (line[depth] == '0')
            zeros++;
    }
    
    int count = ones >= zeros ? ones : zeros;

    char expected_char = ones >= zeros ? '1' : '0';
    
    char **new_lines = malloc(sizeof(char*) * (count + 1));

    int j = 0;
    for (int i = 0; lines[i] != NULL; i++)
    {
        char *line = lines[i];
        if (line[depth] == expected_char)
            new_lines[j++] = line;
    }
    new_lines[j] = NULL;

    if (j == 1) {
        char *line = new_lines[0];
        return bin_str_to_int(line);
    }
    else {
        return oxygen_generator_rating(new_lines, depth + 1);
    }
}


int co2_scrubber_rating(char **lines, int depth)
{
    int ones = 0;
    int zeros = 0;

    for (int i = 0; lines[i] != NULL; i++)
    {
        char *line = lines[i];
        if (line[depth] == '1')
            ones++;
        else if (line[depth] == '0')
            zeros++;
    }
    
    int count = ones < zeros ? ones : zeros;

    char expected_char = ones < zeros ? '1' : '0';
    
    char **new_lines = malloc(sizeof(char*) * (count + 1));

    int j = 0;
    for (int i = 0; lines[i] != NULL; i++)
    {
        char *line = lines[i];
        if (line[depth] == expected_char)
            new_lines[j++] = line;
    }
    new_lines[j] = NULL;

    if (j == 1) {
        char *line = new_lines[0];
        return bin_str_to_int(line);
    }
    else {
        return co2_scrubber_rating(new_lines, depth + 1);
    }
}

int part2(char **lines)
{
    int oxygen = oxygen_generator_rating(lines, 0);
    int co2 = co2_scrubber_rating(lines, 0);

    return oxygen * co2;
}