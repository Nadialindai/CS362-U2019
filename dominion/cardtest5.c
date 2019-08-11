/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * cardtest5: cardtest5.c dominion.o rngs.o
 *      gcc -o cardtest5 -g  cardtest5.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"

#define TESTCARD "drawCard"

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
    // arrays of all estates and not estates
    int cards[MAX_HAND];
    for(i = 0; i < MAX_HAND; i++){
        cards[i] = copper;
    }
    int deck[MAX_DECK];
    for(i = 0; i < MAX_DECK; i++){
        cards[i] = copper;
    }

    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
    for (p = 0; p < numPlayer; p++)
    {
        for (handCount = 1; handCount <= maxHandCount; handCount++)
        {
            for (deckCount = 0; deckCount <= maxDeckCount; deckCount++)
            {
                printf("Check if player %d with %d card(s) and %d card(s) in deck.\n", p, handCount, deckCount);
                memset(&G, 23, sizeof(struct gameState));
                r = initializeGame(numPlayer, k, seed, &G);
                G.handCount[p] = handCount;
                G.deckCount[p] = deckCount;
                G.discardCount[p] = 5;


                printf("Player receives another card - check hand and deck totals\n");

                memcpy(G.hand[p], cards, sizeof(int) * handCount);
                memcpy(G.deck[p], cards, sizeof(int) * handCount);
                temp = G.handCount[p];
                drawCard(p, &G);
                count += assertTrue(G.handCount[p], temp + 1);
                total++;

                if(deckCount > 1){


                    printf("Check deck loses a card - check hand and deck totals\n");

                    memcpy(G.hand[p], cards, sizeof(int) * handCount);
                    memcpy(G.deck[p], cards, sizeof(int) * handCount);
                    temp = G.deckCount[p];
                    drawCard(p, &G);
                    count += assertTrue(G.deckCount[p], temp - 1);
                    total++;
                } else {


                    printf("Reshuffled deck - check hand and deck totals\n");

                    memcpy(G.hand[p], cards, sizeof(int) * handCount);
                    memcpy(G.deck[p], cards, sizeof(int) * handCount);
                    G.discardCount[p] = 5;
                    temp = G.discardCount[p];
                    drawCard(p, &G);
                    count += assertTrue(G.deckCount[p], temp - 1);
                    total++;
                }
            }
        }
    }

    printf("%d out of %d passed.\n", count, total);

    return 0;
}