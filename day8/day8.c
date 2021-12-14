#include "utils.h"
#include <inttypes.h>
#include <stdint.h>

I32 part1(I8 **entries);
I32 part2(I8 **entries);

void run(bool real)
{
    I8 **entries = get_lines_from_file(real ? "input.txt" : "example.txt");

    printf("Part 1\n");
    printf("= %u\n", part1(entries));

    printf("Part 2\n");
    printf("= %u\n", part2(entries));
}

I32 main(I32 argc, I8 **argv)
{
    printf("%s", argv[0]);
    printf("\nTEST:\n");
    run(false);
    printf("\nREAL:\n");
    run(true);
}
I32 part1(I8 **entries)
{
    I32 distinct_count = 0;
    for (I32 i = 0; entries[i] != NULL; i++)
    {
        I8 *value = strchr(entries[i], '|') + 2;
        I32 len = 0;
        for (I32 j = 0; value[j] != '\0'; j++)
        {
            if (value[j] == ' ')
            {
                if (len == 2 || len == 3 || len == 4 || len == 7)
                {
                    distinct_count++;
                }
                len = 0;
            }
            else
            {
                len++;
            }
        }
        if (len == 2 || len == 3 || len == 4 || len == 7)
        {
            distinct_count++;
        }
    }
    return distinct_count;
}

typedef I8 segment;
#define TOP 1
#define TOP_LEFT 2
#define TOP_RIGHT 4
#define MIDDLE 8
#define BOTTOM_LEFT 16
#define BOTTOM_RIGHT 32
#define BOTTOM 64
#define ALL (TOP | TOP_LEFT | TOP_RIGHT | MIDDLE | BOTTOM_LEFT | BOTTOM_RIGHT | BOTTOM)

bool validate_digit(segment digit[7]);
I32 digit_from_segments(segment segments);

I32 part2(I8 **entries)
{
    I32 total = 0;
    for (I32 i = 0; entries[i] != NULL; i++)
    {
        segment digit[7] = {ALL, ALL, ALL, ALL, ALL, ALL, ALL};
        I8 *entry = entries[i];
        I32 bar_pos = strchr(entry, '|') - entry;
        I32 max_len = bar_pos - 1;
        I8 *recorded = strdup(entry);
        recorded[max_len] = '\0';
        I8 *actual = bar_pos + entry + 2;
        I8 **rec_entries = split_by_spaces(recorded);

        uint8_t shared_sixes = ALL;
        uint8_t shared_fives = ALL;
        uint8_t four;
        uint8_t seven;
        uint8_t one;

        for (I32 j = 0; rec_entries[j] != NULL; j++)
        {
            I8 *rec_entry = rec_entries[j];
            I32 len = strlen(rec_entry);
            uint8_t value = 0;
            for (I32 k = 0; k < len; k++)
            {
                I32 index = rec_entry[k] - 'a';
                value |= 1 << index;
            }
            if (len == 2)
            {
                one = value;
            }
            else if (len == 3)
            {
                seven = value;
            }
            else if (len == 4)
            {
                four = value;
            }
            else if (len == 5)
            {
                shared_fives &= value;
            }
            else if (len == 6)
            {
                shared_sixes &= value;
            }
        }

        for (I32 j = 0; j < 7; j++)
        {
            bool is_in_one = 1 & (one >> j);
            bool is_in_four = 1 & (four >> j);
            bool is_in_seven = 1 & (seven >> j);
            bool is_in_fives = 1 & (shared_fives >> j);
            bool is_in_sixes = 1 & (shared_sixes >> j);

            const segment in_one = TOP_RIGHT | BOTTOM_RIGHT;
            const segment in_four = TOP_RIGHT | BOTTOM_RIGHT | TOP_LEFT | MIDDLE;
            const segment in_seven = TOP_RIGHT | BOTTOM_RIGHT | TOP;
            const segment in_fives = TOP | MIDDLE | BOTTOM;
            const segment in_sixes = TOP | TOP_LEFT | BOTTOM_RIGHT | BOTTOM;

            digit[j] &= in_one ^ (is_in_one ? 0 : 0x7F);
            digit[j] &= in_four ^ (is_in_four ? 0 : 0x7F);
            digit[j] &= in_seven ^ (is_in_seven ? 0 : 0x7F);

            digit[j] &= in_fives ^ (is_in_fives ? 0 : 0x7F);
            digit[j] &= in_sixes ^ (is_in_sixes ? 0 : 0x7F);
        }

        while (!validate_digit(digit))
        {
            // do cleans here (turned out to be unnessecary but still implemented)
            for (I32 j = 0; j < 7; j++)
            {
                // count the bits
                 U32 v = digit[j];
                 U32 c = 0;
                for (c = 0; v; v >>= 1)
                {
                    c += v & 1;
                }

                if (c == 1) {
                    // wahoo!
                    segment value = digit[j];
                    for (I32 k = 0; k < 7; k++) {
                        if (k == j)
                            continue;
                        digit[k] &= value ^ 0x7F;
                    }
                }
            }
        }

        I8 **actual_entries = split_by_spaces(actual);
        I32 num = 0;
        for (I32 j = 0; actual_entries[j] != NULL; j++)
        {
            I8 *actual_entry = actual_entries[j];
            I32 len = strlen(actual_entry);
            segment segments = 0;
            for (I32 k = 0; k < len; k++)
            {
                I32 index = actual_entry[k] - 'a';
                segments |= digit[index];
            }
            I32 digit = digit_from_segments(segments);
            num *= 10;
            num += digit;
        }
        total += num;
    }
    return total;
}

#define ONE (TOP_RIGHT | BOTTOM_RIGHT)
#define TWO (TOP | TOP_RIGHT | MIDDLE | BOTTOM_LEFT | BOTTOM)
#define THREE (TOP | TOP_RIGHT | MIDDLE | BOTTOM_RIGHT | BOTTOM)
#define FOUR (TOP_LEFT | TOP_RIGHT | MIDDLE | BOTTOM_RIGHT)
#define FIVE (TOP | TOP_LEFT | MIDDLE | BOTTOM_RIGHT | BOTTOM)
#define SIX (TOP | TOP_LEFT | MIDDLE | BOTTOM_LEFT | BOTTOM_RIGHT | BOTTOM)
#define SEVEN (TOP | TOP_RIGHT | BOTTOM_RIGHT)
#define EIGHT ALL
#define NINE (TOP | TOP_LEFT | TOP_RIGHT | MIDDLE | BOTTOM_RIGHT | BOTTOM)
#define ZERO (TOP | TOP_LEFT | TOP_RIGHT | BOTTOM_LEFT | BOTTOM_RIGHT | BOTTOM)

I32 digit_from_segments(segment segments)
{
    switch (segments)
    {
    case ONE:
        return 1;
    case TWO:
        return 2;
    case THREE:
        return 3;
    case FOUR:
        return 4;
    case FIVE:
        return 5;
    case SIX:
        return 6;
    case SEVEN:
        return 7;
    case EIGHT:
        return 8;
    case NINE:
        return 9;
    case ZERO:
        return 0;
    default:
        fprintf(stderr, "UNKNOWN SEGMENTS: %02X", segments);
        exit(1);
    }
}

bool validate_digit(segment digit[7])
{
    segment complete = 0;
    for (I32 i = 0; i < 7; i++)
    {
        complete += digit[i];
    }
    if (complete == ALL)
    {
        return true;
    }
    else
    {
        return false;
    }
}