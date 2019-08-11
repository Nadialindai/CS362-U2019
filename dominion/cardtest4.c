/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * cardtest4: cardtest4.c dominion.o rngs.o
 *      gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"

#define TESTCARD "getWinners"

int assertTrue(int a, int b) {
    if(a != b) {
        printf("%s failed\n", TESTCARD);
        return -1;
    } else {
        printf("%s passed\n", TESTCARD);
        return 1;
    }

}

int main() {
    int i, temp = 0, total = 0, count = 0;
    int seed = 1000;
    int numPlayer = 2;
    int maxBonus = 10;
    int p, r, c, h = 0, handCount;
    int bonus = 0;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};
    struct gameState G;
    int maxHandCount = 5;

    int estates[MAX_HAND];
    int curses[MAX_HAND];
    for(i = 0; i < MAX_HAND; i++){
        estates[i] = estate;
        curses[i] = curse;
    }
    int players[MAX_PLAYERS];

    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
    for (p = 0; p < numPlayer; p++)
    {
        for (handCount = 1; handCount <= maxHandCount; handCount++)
        {
            printf("Check if %d with %d card(s) and %d bonus.\n", p, handCount, bonus);
            memset(&G, 23, sizeof(struct gameState));
            r = initializeGame(numPlayer, k, seed, &G);
            G.handCount[p] = handCount;



            printf("Player should have a top score\n");

            for (i = 0; i < numPlayer; i++){
                if (i != p) memcpy(G.hand[i], curses, sizeof(int) * handCount);
            }
            memcpy(G.hand[p], estates, sizeof(int) * handCount);
            getWinners(players, &G);
            count += assertTrue(players[p], 1);
            total++;


            printf("Player shouldn't have a top score\n");

            for (i = 0; i < numPlayer; i++){
                if (i != p) memcpy(G.hand[i], estates, sizeof(int) * handCount);
            }
            memcpy(G.hand[p], curses, sizeof(int) * handCount);
            getWinners(players, &G);
            count += assertTrue(players[p], 0);
            total++;
        }
    }

    printf("%d out of %d passed.\n", count, total);

    return 0;
}