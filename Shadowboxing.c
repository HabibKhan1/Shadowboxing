// This program interprets all the elements of real-life shadowboxing to play a game of it against the computer.

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>

int main (void)
{
    srand(time(NULL));

    char user_rps[9], comp_rps[9];
    char user_dir[6], comp_dir[6];
    char *choices[3] = {"rock", "paper", "scissors"};
    char *directions[4] = {"up", "down", "left", "right"};
    char prev_dir[6];
    int rps_index, dir_index, x = 0;
    int user_wins = 0, comp_wins = 0;
    bool victor_found = false, user_first_move = false;
    bool on_off_switch = true, valid_dir;

    rps:
        user_rps[8] = '\0';
        comp_rps[8] = '\0';
        prev_dir[5] = '\0';
        rps_index = rand() % 3;

        // Obviously, in shadowboxing, the players play rock, paper, scissors to determine who goes first.

        printf("Rock, paper, or scissors? ");
        scanf("%8s", user_rps);

        // We are making every letter of the string lowercase to make string comparisons easier.

        for (x = 0; x < 8; ++x) user_rps[x] = tolower(user_rps[x]);

        // Computer's choice

        strcpy(comp_rps, choices[rps_index]);

        // USER CHOICE: ROCK

        if (strcmp(user_rps, "rock") == 0)
        {
            if (strcmp(comp_rps, "rock") == 0) printf("It was tied, let's go again.\n"); // COMPUTER CHOICE: ROCK
            else if (strcmp(comp_rps, "paper") == 0) // COMPUTER CHOICE: PAPER
            {
                printf("I win (I had paper), I go first.\n");
                user_first_move = false;
                victor_found = true;
            }
            else // COMPUTER CHOICE: SCISSORS
            {
                printf("You win (I had scissors), you go first.\n");
                user_first_move = true;
                victor_found = true;
            }
        }

        // USER CHOICE: PAPER

        else if (strcmp(user_rps, "paper") == 0)
        {
            if (strcmp(comp_rps, "rock") == 0) // COMPUTER CHOICE: ROCK
            {
                printf("You win (I had rock), you go first.\n");
                user_first_move = true;
                victor_found = true;
            }
            else if (strcmp(comp_rps, "paper") == 0) printf("It was tied, let's go again.\n"); // COMPUTER CHOICE: PAPER
            else // COMPUTER CHOICE: SCISSORS
            {
                printf("I win (I had scissors), I go first.\n");
                user_first_move = false;
                victor_found = true;
            }
        }

        // USER CHOICE: SCISSORS

        else if (strcmp(user_rps, "scissors") == 0)
        {
            if (strcmp(comp_rps, "rock") == 0) // COMPUTER CHOICE: ROCK
            {
                printf("I win (I had rock), I go first.\n");
                user_first_move = false;
                victor_found = true;
            }
            else if (strcmp(comp_rps, "paper") == 0)
            {
                printf("You win (I had paper), you go first.\n"); // COMPUTER CHOICE: PAPER
                user_first_move = true;
                victor_found = true;
            }
            else printf("It was tied, let's go again.\n"); // COMPUTER CHOICE: SCISSORS
        }

        // If the program comes to this clause, it means the user has not chosen any of RPS and has chosen something completely bogus.

        else printf("Invalid choice.\n");

    // If the victor has not yet been determined, repeat.

    if (! victor_found) goto rps;

    // On to the actual shadowboxing

    while (true)
    {
        if (user_first_move) goto user_turn; // FIRST MOVE: USER
        else goto comp_turn; // FIRST MOVE: COMPUTER

        user_turn:
            if (user_wins == 3) break; // If you got them 3 straight times, you win

            dir_index = rand() % 3;
            valid_dir = true;

            if (on_off_switch) on_off_switch = false;
            else on_off_switch = true;

            if (dir_index == 2 && on_off_switch) ++dir_index; // The program seems to ignore choosing right. This is a way to make it more likely to pick it for randomization.

            strcpy(comp_dir, directions[dir_index]);
            printf("Choose a direction: ");
            scanf("%5s", user_dir);

            for (x = 0; x < 8; ++x) user_dir[x] = tolower(user_dir[x]);

            // Can't go the same direction twice in a row

            if (strcmp(user_dir, prev_dir) == 0)
            {
                printf("Can't go the same direction twice in a row.\n");
                goto user_turn;
            }
            if (strcmp(comp_dir, prev_dir) == 0)
            {
                if (dir_index > 0) --dir_index;
                else ++dir_index;
                strcpy(comp_dir, directions[dir_index]);
            }

            // Checking if the user selected a bogus direction (it happens...)

            for (x = 0; x < 4; ++x)
            {
                if (strcmp(user_dir, directions[x]) == 0)
                {
                    valid_dir = true;
                    break;
                }
                else valid_dir = false;
            }
            if (! valid_dir)
            {
                printf("Invalid direction.\n");
                goto user_turn;
            }

            // USER DIRECTION: UP

            if (strcmp(user_dir, "up") == 0)
            {
                // COMP DIRECTION: UP

                if (strcmp(comp_dir, "up") == 0)
                {
                    printf("You got me!\n");
                    ++user_wins;
                    strcpy(prev_dir, "up");
                    goto user_turn;
                }
                else
                {
                    printf("I went %s, my turn.\n", comp_dir);
                    user_wins = 0;
                    strcpy(prev_dir, "n/a");
                    goto comp_turn;
                }
            }

            // USER DIRECTION: DOWN

            if (strcmp(user_dir, "down") == 0)
            {
                // COMP DIRECTION: DOWN

                if (strcmp(comp_dir, "down") == 0)
                {
                    printf("You got me!\n");
                    ++user_wins;
                    strcpy(prev_dir, "down");
                    goto user_turn;
                }
                else
                {
                    printf("I went %s, my turn.\n", comp_dir);
                    user_wins = 0;
                    strcpy(prev_dir, "n/a");
                    goto comp_turn;
                }
            }

            // USER DIRECTION: LEFT

            if (strcmp(user_dir, "left") == 0)
            {
                // COMP DIRECTION: LEFT

                if (strcmp(comp_dir, "left") == 0)
                {
                    printf("You got me!\n");
                    ++user_wins;
                    strcpy(prev_dir, "left");
                    goto user_turn;
                }
                else
                {
                    printf("I went %s, my turn.\n", comp_dir);
                    user_wins = 0;
                    strcpy(prev_dir, "n/a");
                    goto comp_turn;
                }
            }

            // USER DIRECTION: RIGHT

            if (strcmp(user_dir, "right") == 0)
            {
                // COMP DIRECTION: DOWN

                if (strcmp(comp_dir, "right") == 0)
                {
                    printf("You got me!\n");
                    ++user_wins;
                    strcpy(prev_dir, "right");
                    goto user_turn;
                }
                else
                {
                    printf("I went %s, my turn.\n", comp_dir);
                    user_wins = 0;
                    strcpy(prev_dir, "n/a");
                    goto comp_turn;
                }
            }

        comp_turn:
            if (comp_wins == 3) break;

            dir_index = rand() % 3;
            valid_dir = true;

            strcpy(comp_dir, directions[dir_index]);
            printf("I locked in my direction, what's yours? ");
            scanf("%5s", user_dir);

            for (x = 0; x < 8; ++x) user_dir[x] = tolower(user_dir[x]);

            if (strcmp(user_dir, prev_dir) == 0)
            {
                printf("Can't go the same direction twice in a row.\n");
                goto comp_turn;
            }
            if (strcmp(comp_dir, prev_dir) == 0)
            {
                if (dir_index > 0) --dir_index;
                else ++dir_index;
                strcpy(comp_dir, directions[dir_index]);
            }

            for (x = 0; x < 4; ++x)
            {
                if (strcmp(user_dir, directions[x]) == 0)
                {
                    valid_dir = true;
                    break;
                }
                else valid_dir = false;
            }
            if (! valid_dir)
            {
                printf("Invalid direction.\n");
                goto comp_turn;
            }

            // COMP DIRECTION: UP

            if (strcmp(comp_dir, "up") == 0)
            {
                // USER DIRECTION: UP

                if (strcmp(user_dir, "up") == 0)
                {
                    printf("I got you!\n");
                    ++comp_wins;
                    strcpy(prev_dir, "up");
                    goto comp_turn;
                }
                else
                {
                    printf("I missed you (I had %s), your turn.\n", comp_dir);
                    comp_wins = 0;
                    strcpy(prev_dir, "n/a");
                    goto user_turn;
                }
            }

            // COMP DIRECTION: DOWN

            if (strcmp(comp_dir, "down") == 0)
            {
                // USER DIRECTION: DOWN

                if (strcmp(user_dir, "down") == 0)
                {
                    printf("I got you!\n");
                    ++comp_wins;
                    strcpy(prev_dir, "down");
                    goto comp_turn;
                }
                else
                {
                    printf("I missed you (I had %s), your turn.\n", comp_dir);
                    comp_wins = 0;
                    strcpy(prev_dir, "n/a");
                    goto user_turn;
                }
            }

            // COMP DIRECTION: LEFT

            if (strcmp(comp_dir, "left") == 0)
            {
                // USER DIRECTION: LEFT

                if (strcmp(user_dir, "left") == 0)
                {
                    printf("I got you!\n");
                    ++comp_wins;
                    strcpy(prev_dir, "left");
                    goto comp_turn;
                }
                else
                {
                    printf("I missed you (I had %s), your turn.\n", comp_dir);
                    comp_wins = 0;
                    strcpy(prev_dir, "n/a");
                    goto user_turn;
                }
            }

            // COMP DIRECTION: RIGHT

            if (strcmp(comp_dir, "right") == 0)
            {
                // USER DIRECTION: RIGHT

                if (strcmp(user_dir, "right") == 0)
                {
                    printf("I got you!\n");
                    ++comp_wins;
                    strcpy(prev_dir, "right");
                    goto comp_turn;
                }
                else
                {
                    printf("I missed you (I had %s), your turn.\n", comp_dir);
                    comp_wins = 0;
                    strcpy(prev_dir, "n/a");
                    goto user_turn;
                }
            }
    }

    if (user_wins == 3) printf("You win!\n");
    else printf("I win!\n");

    return 0;
}