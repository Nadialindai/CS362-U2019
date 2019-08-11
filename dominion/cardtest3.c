/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * cardtest3: cardtest3.c dominion.o rngs.o
 *      gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"

#define TESTCARD "endTurn"

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
    int numPlayer = 5;
    int maxBonus = 10;
    int p, r, c, h = 0, handCount;
    int bonus = 0;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};
    struct gameState G;
    int maxHandCount = 5;

    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
    for (p = 2; p < numPlayer; p++)
    {
        printf("Check %d player(s).\n", p);
        memset(&G, 23, sizeof(struct gameState));
        r = initializeGame(p, k, seed, &G);


        printf("Player increased by + 1\n");

        G.whoseTurn = 0;
        for (i = 0; i < p - 1; i++){
            temp = G.whoseTurn;
            endTurn(&G);
            count += assertTrue(G.whoseTurn, temp + 1);
            total++;
        }


        printf("Player increased by + 1\n");

        G.whoseTurn = p - 1;
        endTurn(&G);
        count += assertTrue(G.whoseTurn, 0);
        total++;

        printf("First action is 1\n");
        endTurn(&G);
        count += assertTrue(G.numActions, 1);
        total++;


        printf("First buy is 1\n");
        endTurn(&G);
        count += assertTrue(G.numBuys, 1);
        total++;
    }

    printf("%d out of %d passed.\n", count, total);

    return 0;
}