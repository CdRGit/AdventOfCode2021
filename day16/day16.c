#include "utils.h"

#include <stdint.h>

struct Position
{
    U16 x;
    U16 y;
};
typedef struct Position Position;

U64 part1(I8 *content);
U64 part2(I8 *content);

#define SIZE 500

void run(bool real)
{
    I8 *content = get_file_content(real ? "input.txt" : "example.txt");

    // printf("Part 1\n");
    // printf("= %llu           \n", part1(content));

    printf("Part 2\n");
    printf("= %llu           \n", part2(content));
}

I8 *hex_to_bin(I8 *hex_string)
{
    I8 *bin = malloc((strlen(hex_string) + 1) * sizeof(char));
    for (I32 i = 0; hex_string[i] != '\0'; i++)
    {
        I8 value = 0;
        if (hex_string[i] <= '9')
            value = hex_string[i] - '0';
        else
            value = 10 + hex_string[i] - 'A';
        bin[i * 4 + 0] = value & 8 ? '1' : '0';
        bin[i * 4 + 1] = value & 4 ? '1' : '0';
        bin[i * 4 + 2] = value & 2 ? '1' : '0';
        bin[i * 4 + 3] = value & 1 ? '1' : '0';
        bin[i * 4 + 4] = '\0';
    }
    return bin;
}

I32 main(I32 argc, I8 **argv)
{
    printf("%s", argv[0]);
    // printf("\nTEST:\n");
    // run(false);
    printf("\nREAL:\n");
    run(true);
}

U64 get_num_from_bin(I8 **bin, U8 length)
{
    U64 num = 0;
    for (U8 len = 0; len < length; len++)
    {
        num <<= 1;
        num |= *(*bin)++ - '0';
    }
    return num;
}

U64 total_packet_version(I8 **bin)
{
    U8 version = get_num_from_bin(bin, 3);
    U8 type = get_num_from_bin(bin, 3);
    if (type == 4)
    {
        U64 value = 0;
        printf("Literal: ");
        bool has_next;
        do
        {
            has_next = *(*bin)++ - '0';

            value <<= 4;
            value |= get_num_from_bin(bin, 4);
        } while (has_next);
        printf("%d\n", value);
        return version;
    }
    else
    {
        U64 total_version = version;
        bool is_number_of_packets = *(*bin)++ - '0';
        if (is_number_of_packets)
        {
            U16 number = get_num_from_bin(bin, 11);
            printf("Operator num_packet: %d\n", number);
            for (U16 n = 0; n < number; n++)
            {
                total_version += total_packet_version(bin);
            }
        }
        else
        {
            U16 length = get_num_from_bin(bin, 15);
            I8 *temp = *bin;
            printf("Operator length: %d\n", length);
            while (*bin - temp < length)
            {
                total_version += total_packet_version(bin);
            }
        }
        return total_version;
    }
}

U64 packet_value(I8 **bin, U64 depth)
{
    for (U64 i = 0; i < depth; i++)
        printf(" ");
    U8 version = get_num_from_bin(bin, 3);
    U8 type = get_num_from_bin(bin, 3);
    if (type == 4)
    {
        U64 value = 0;
        bool has_next;
        do
        {
            has_next = *(*bin)++ - '0';

            value <<= 4;
            value |= get_num_from_bin(bin, 4);
        } while (has_next);
        printf("%llu\n", value);
        return value;
    }
    else
    {
        U64 total_value = 0;
        bool is_number_of_packets = *(*bin)++ - '0';
        if (type == 1)
            total_value = 1;
        else if (type == 2)
            total_value = 0xFFFFFFFFFFFFFFFF;
        U64 first = 0;
        U64 second = 0;

        switch (type)
        {
        case 0:
            printf("+\n");
            break;
        case 1:
            printf("*\n");
            break;
        case 2:
            printf("min\n");
            break;
        case 3:
            printf("max\n");
            break;
        case 5:
            printf(">\n");
            break;
        case 6:
            printf("<\n");
            break;
        case 7:
            printf("=\n");
            break;
        }

        if (is_number_of_packets)
        {
            U16 number = get_num_from_bin(bin, 11);
            for (U16 n = 0; n < number; n++)
            {
                first = second;
                U64 value = packet_value(bin, depth + 1);
                second = value;
                switch (type)
                {
                case 0:
                    total_value += value;
                    break;
                case 1:
                    total_value *= value;
                    break;
                case 2:
                    if (value < total_value)
                        total_value = value;
                    break;
                case 3:
                    if (value > total_value)
                        total_value = value;
                    break;
                case 5:
                    if (first > second)
                        total_value = 1;
                    else
                        total_value = 0;
                    break;
                case 6:
                    if (first < second)
                        total_value = 1;
                    else
                        total_value = 0;
                    break;
                case 7:
                    if (first == second)
                        total_value = 1;
                    else
                        total_value = 0;
                    break;
                }
            }
        }
        else
        {
            U16 length = get_num_from_bin(bin, 15);
            I8 *temp = *bin;
            while (*bin - temp < length)
            {
                first = second;
                U64 value = packet_value(bin, depth + 1);
                second = value;
                switch (type)
                {
                case 0:
                    total_value += value;
                    break;
                case 1:
                    total_value *= value;
                    break;
                case 2:
                    if (value < total_value)
                        total_value = value;
                    break;
                case 3:
                    if (value > total_value)
                        total_value = value;
                    break;
                case 5:
                    if (first > second)
                        total_value = 1;
                    else
                        total_value = 0;
                    break;
                case 6:
                    if (first < second)
                        total_value = 1;
                    else
                        total_value = 0;
                    break;
                case 7:
                    if (first == second)
                        total_value = 1;
                    else
                        total_value = 0;
                    break;
                }
            }
        }

        for (U64 i = 0; i < depth; i++)
            printf(" ");
        printf("%llu\n", total_value);
        return total_value;
    }
}

U64 part1(I8 *content)
{
    I8 *bin = hex_to_bin(content);
    I8 *start = bin;

    U64 total = total_packet_version(&bin);

    return total;
}

U64 part2(I8 *content)
{
    I8 *bin = hex_to_bin(content);
    I8 *start = bin;

    U64 total = packet_value(&bin, 0);

    return total;
}