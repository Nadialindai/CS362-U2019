/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * cardtest2: cardtest2.c dominion.o rngs.o
 *      gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"

#define TESTCARD "Shuffle"

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
    int p, r, c, h = 0, handCount, deckCount;
    int bonus = 0;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};
    struct gameState G;
    int maxHandCount = 5;
    int maxDeckCount = 5;

    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
    for (p = 0; p < numPlayer; p++)
    {
        for (deckCount = 0; deckCount <= maxDeckCount; deckCount++)
        {
            printf("Test player %d with %d card(s) in deck and %d bonus.\n", p, deckCount, bonus);
            memset(&G, 23, sizeof(struct gameState));
            r = initializeGame(numPlayer, k, seed, &G);
            G.deckCount[p] = deckCount;

            printf("Check deck count has not changed\n");

            temp = G.deckCount[p];
            shuffle(p, &G);
            count += assertTrue(G.deckCount[p], temp);
            total++;
        }
    }

    printf("%d out of %d passed.\n", count, total);

    return 0;
}