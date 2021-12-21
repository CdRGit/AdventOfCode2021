#include "utils.h"


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
    I8 *player_1_line = lines[0] + 28;
    I8 *player_2_line = lines[1] + 28;

    I32 len = 0;

    U64 rolls = 0;

    U16 player_1_score = 0;
    U16 player_1_pos = to_int(player_1_line, NULL);

    U16 player_2_score = 0;
    U16 player_2_pos = to_int(player_2_line, NULL);

    bool player_1_won = false;
    while (true) {
        // player 1 turn
        U16 player_1_roll = 0;
        for (I32 i = 0; i < 3; i++) {
            player_1_roll += (rolls++ % 100) + 1;
        }
        player_1_pos = (((player_1_pos + player_1_roll) - 1) % 10) + 1;
        player_1_score += player_1_pos;
        if (player_1_score >= 1000) {
            player_1_won = true;
            break;
        }
        // player 2 turn
        U16 player_2_roll = 0;
        for (I32 i = 0; i < 3; i++) {
            player_2_roll += (rolls++ % 100) + 1;
        }
        player_2_pos = (((player_2_pos + player_2_roll) - 1) % 10) + 1;
        player_2_score += player_2_pos;
        if (player_2_score >= 1000) {
            player_1_won = false;
            break;
        }
    }

    printf("Part 1\n= %llu (%llu * %llu)\n", (player_1_won ? player_2_score : player_1_score) * rolls, (player_1_won ? player_2_score : player_1_score), rolls);
}

// just in case
static U64 win_count[10 * 10 * 100 * 100 * 2];
static bool seen_before[10 * 10 * 100 * 100];

void most_won_universes(U8 player_1_pos, U8 player_1_score, U8 player_2_pos, U8 player_2_score, U64 *player_1_wins, U64 *player_2_wins)
{
    if (player_1_pos > 10 || player_2_pos > 10) {
        fprintf(stderr, "WTF\n");
        exit(1);
    }

    U64 player_1_ws = 0;
    U64 player_2_ws = 0;

    if (player_1_score >= 21)
    {
        *player_1_wins = 1;
        *player_2_wins = 0;
        return;
    }
    
    if (player_2_score >= 21)
    {
        *player_2_wins = 1;
        *player_1_wins = 0;
        return;
    }
    I32 idx = (player_1_pos - 1) + (player_2_pos - 1) * 10 + (player_1_score) * 100 + (player_2_score) * 10000;
    if (seen_before[idx]) {
        *player_1_wins = win_count[idx * 2];
        *player_2_wins = win_count[idx * 2 + 1];
        return;
    }

    // welp, time to quantum mechanics
    U64 player_1_add_ws = 0;
    U64 player_2_add_ws = 0;

    U8 new_pos = (player_1_pos + 2) % 10 + 1;
    most_won_universes(player_2_pos, player_2_score, new_pos, player_1_score + new_pos, &player_2_add_ws, &player_1_add_ws);
    player_1_ws += player_1_add_ws * 1;
    player_2_ws += player_2_add_ws * 1;
    
    new_pos = (player_1_pos + 3) % 10 + 1;
    most_won_universes(player_2_pos, player_2_score, new_pos, player_1_score + new_pos, &player_2_add_ws, &player_1_add_ws);
    player_1_ws += player_1_add_ws * 3;
    player_2_ws += player_2_add_ws * 3;
    
    new_pos = (player_1_pos + 4) % 10 + 1;
    most_won_universes(player_2_pos, player_2_score, new_pos, player_1_score + new_pos, &player_2_add_ws, &player_1_add_ws);
    player_1_ws += player_1_add_ws * 6;
    player_2_ws += player_2_add_ws * 6;
    
    new_pos = (player_1_pos + 5) % 10 + 1;
    most_won_universes(player_2_pos, player_2_score, new_pos, player_1_score + new_pos, &player_2_add_ws, &player_1_add_ws);
    player_1_ws += player_1_add_ws * 7;
    player_2_ws += player_2_add_ws * 7;
    
    new_pos = (player_1_pos + 6) % 10 + 1;
    most_won_universes(player_2_pos, player_2_score, new_pos, player_1_score + new_pos, &player_2_add_ws, &player_1_add_ws);
    player_1_ws += player_1_add_ws * 6;
    player_2_ws += player_2_add_ws * 6;
    
    new_pos = (player_1_pos + 7) % 10 + 1;
    most_won_universes(player_2_pos, player_2_score, new_pos, player_1_score + new_pos, &player_2_add_ws, &player_1_add_ws);
    player_1_ws += player_1_add_ws * 3;
    player_2_ws += player_2_add_ws * 3;
    
    new_pos = (player_1_pos + 8) % 10 + 1;
    most_won_universes(player_2_pos, player_2_score, new_pos, player_1_score + new_pos, &player_2_add_ws, &player_1_add_ws);
    player_1_ws += player_1_add_ws * 1;
    player_2_ws += player_2_add_ws * 1;

    seen_before[idx] = true;
    win_count[idx * 2] = player_1_ws;
    win_count[idx * 2 + 1] = player_2_ws;

    *player_1_wins = player_1_ws;
    *player_2_wins = player_2_ws;
}

void part2(I8 **lines) {
    memset(win_count, 0, true);
    memset(seen_before, 0, true);

    I8 *player_1_line = lines[0] + 28;
    I8 *player_2_line = lines[1] + 28;

    U64 rolls = 0;

    U8 player_1_score = 0;
    U8 player_1_pos = to_int(player_1_line, NULL);

    U8 player_2_score = 0;
    U8 player_2_pos = to_int(player_2_line, NULL);

    U64 player_1_wins = 0;
    U64 player_2_wins = 0;

    most_won_universes(player_1_pos, player_1_score, player_2_pos, player_2_score, &player_1_wins, &player_2_wins);

    printf("Part 2\n= %llu\n", MAX(player_1_wins, player_2_wins));
}