/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * unittest2: unittest2.c dominion.o rngs.o
 *      gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"

#define TESTCARD "minion"

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
    int p, r, c, h, handCount;
    int bonus = 0;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel,
                 smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;

    int cards[MAX_HAND];
    for(i = 0; i < MAX_HAND; i++){
        cards[i] = copper;
    }

    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
    p = 0;
    for (handCount = 1; handCount <= maxHandCount; handCount++)
    {
        printf("Test player %d has %d card(s) and %d bonus?\n", p, handCount, bonus);
        memset(&G, 23, sizeof(struct gameState));
        r = initializeGame(numPlayer, k, seed, &G);
        G.handCount[p] = handCount;


        printf("Did G.numActions get an +1?\n");

        memcpy(G.hand[p], cards, sizeof(int) * handCount);
        temp = G.numActions;

        //(state, currentPlayer, choice1, choice2, handPos)
        playMinion(&G, p, 1, 0, h);
        count += assertTrue(G.numActions, temp + 1);
        total++;


        printf("Check that choice 2 gives +2 coins\n");

        memcpy(G.hand[p], cards, sizeof(int) * handCount);
        temp = G.coins;

        playMinion(&G, p, 1, 2, h);
        count += assertTrue(G.coins, temp + 2);
        total++;


        printf("Check that hand is now 4 cards\n");

        memcpy(G.hand[p], cards, sizeof(int) * handCount);
        playMinion(&G, p, 1, 2, h);
        count += assertTrue(G.handCount[p], 4);
        total++;



        printf("Check that other players hands have not changed (or are now 4 cards)\n");

        memcpy(G.hand[p], cards, sizeof(int) * handCount);
        if(p == 0){
            if(G.handCount[1] >= 5){
                playMinion(&G, p, 1, 0, h);
                count += assertTrue(G.handCount[1], 4);
            } else {
                temp = G.handCount[1];
                playMinion(&G, p, 1, 0, h);
                count += assertTrue(G.handCount[1], temp);
            }
        }
        else if(p == 1){
            if(G.handCount[0] >= 5){
                playMinion(&G, p, 1, 0, h);
                count += assertTrue(G.handCount[0], 4);
            } else {
                temp = G.handCount[0];
                playMinion(&G, p, 1, 0, h);
                count += assertTrue(G.handCount[0], temp);
            }
        }
        total++;

        printf("%d out of %d passed.\n", count, total);
    }


    return 0;
}