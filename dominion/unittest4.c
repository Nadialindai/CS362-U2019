/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * unittest4: unittest4.c dominion.o rngs.o
 *      gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define TESTCARD "tribute"

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
    int currentPlayer = 0;
    int nextPlayer = 1;
    int maxBonus = 10;
    int p, r, c, h = 0, handCount;
    int bonus = 0;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel,
                 smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;

    int treasures[MAX_DECK];
    int actions[MAX_DECK];
    int victories[MAX_DECK];
    int curses[MAX_DECK];
    for(i = 0; i < MAX_DECK; i++){
        treasures[i] = copper;
        actions[i] = tribute;
        victories[i] = estate;
        curses[i] = curse;
    }
    int tributeRevealedCards[2] = {-1, -1};

    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
    for (p = 0; p < numPlayer; p++)
    {
        for (handCount = 1; handCount <= maxHandCount; handCount++)
        {
            printf("Test player %d with %d card(s) and %d bonus.\n", p, handCount, bonus);
            memset(&G, 23, sizeof(struct gameState));
            r = initializeGame(numPlayer, k, seed, &G);
            G.handCount[p] = handCount;


            printf("Check that coins get +2\n");

            memcpy(G.deck[p], treasures, sizeof(int) * G.deckCount[p]);
            temp = G.coins;
            if(p == 0) playTribute(&G, currentPlayer, nextPlayer, tributeRevealedCards);
                //state, currentPlayer, nextPlayer, tributeRevealedCards
            else if(p == 1) playTribute(&G, currentPlayer, nextPlayer, tributeRevealedCards);
            count += assertTrue(G.coins, temp + 2);
            total++;


            printf("Check that actions get +2\n");

            memcpy(G.deck[p], actions, sizeof(int) * G.deckCount[p]);
            temp = G.numActions;
            if(p == 0) playTribute(&G, currentPlayer, nextPlayer, tributeRevealedCards);
            else if(p == 1) playTribute(&G, currentPlayer, nextPlayer, tributeRevealedCards);
            count += assertTrue(G.numActions, temp + 2);
            total++;


            printf("Check that player get +2 cards\n");

            memcpy(G.deck[p], victories, sizeof(int) * G.deckCount[p]);
            temp = G.handCount[p];
            if(p == 0) playTribute(&G, currentPlayer, nextPlayer, tributeRevealedCards);
            else if(p == 1) playTribute(&G, currentPlayer, nextPlayer, tributeRevealedCards);
            count += assertTrue(G.handCount[p], temp + 2);
            total++;

            printf("Check that there is no change in coins\n");
            memcpy(G.deck[p], curses, sizeof(int) * G.deckCount[p]);
            temp = G.coins;

            //playTributeRefactor(int currentPlayer, int nextPlayer, struct gameState *state)
            if(p == 0) playTribute(&G, currentPlayer, nextPlayer, tributeRevealedCards);
            else if(p == 1) playTribute(&G, currentPlayer, nextPlayer, tributeRevealedCards);
            count += assertTrue(G.coins, temp);
            total++;
        }
    }

    printf("%d out of %d passed.\n", count, total);

    return 0;
}

