/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * unittest3: unittest3.c dominion.o rngs.o
 *      gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define TESTCARD "ambassador"

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
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel,
                 smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;

    // arrays of all estates and not estates
    int cards[MAX_HAND];
    for(i = 0; i < MAX_HAND; i++){
        cards[i] = copper;
    }

    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
    for (p = 0; p < numPlayer - 1; p++)
    {
        for (handCount = 1; handCount <= maxHandCount; handCount++)
        {
            printf("Test player %d with %d card(s) and %d bonus.\n", p, handCount, bonus);
            memset(&G, 23, sizeof(struct gameState));   // memory of new game
            r = initializeGame(numPlayer, k, seed, &G); // initialize the game
            G.handCount[p] = handCount;


            printf("Ensure player returns 2 or less cards\n");

            memcpy(G.hand[p], cards, sizeof(int) * handCount); // set all the cards to copper
            temp = G.handCount[p];
            if(G.handCount[p] >= 2){ // Greater than 2 cards in hand
                //playAmbassador(state, currentPlayer, choice1, choice2, handPos)
                playAmbassador(&G, p, 1, 2, h);
                count += assertTrue(G.handCount[p], temp - 2);
            } else if(G.handCount[p] == 1){ // One card in hand
                playAmbassador(&G, p, 1, 0, h);
                count += assertTrue(G.handCount[p], temp - 1);
            } else { // Zero cards in hand
                playAmbassador(&G, p, 0, 0, h);
                count += assertTrue(G.handCount[p], temp);
            }
            total++;


            printf("Player returns 2 or less copper coins\n");

            memcpy(G.hand[p], cards, sizeof(int) * handCount); // set all the cards to copper
            temp = G.supplyCount[p];
            if(G.handCount[p] >= 2){ // Greater than 2 cards in hand
                playAmbassador(&G, p, 1, 2, h);
                count += assertTrue(G.supplyCount[p], temp + 2);
            } else if(G.handCount[p] == 1){ // One card in hand
                playAmbassador(&G, p, 1, 0, h);
                count += assertTrue(G.supplyCount[p], temp + 1);
            } else { // Zero cards in hand
                playAmbassador(&G, p, 0, 0, h);
                count += assertTrue(G.supplyCount[p], temp);
            }
            total++;

            // Check that coins have not changed

            printf("Check that coins have not changed\n");

            memcpy(G.hand[p], cards, sizeof(int) * handCount); // set all the cards to copper
            temp = G.coins;
            //playAmbassador(state, currentPlayer, choice1, choice2, handPos)
            playAmbassador(&G, p, 0, 0, h);
            count += assertTrue(G.coins, temp);
            total++;

            // Check that each other player has an additional card

            printf("Additional card per player\n");

            memcpy(G.hand[p], cards, sizeof(int) * handCount); // set all the cards to silver
            for(i = 0; i < numPlayer; i++){
                if(i != p){
                    temp = G.handCount[i];
                    playAmbassador(&G, p, 0, 0, h);
                    count += assertTrue(G.handCount[i], temp + 1);
                    total++;
                }
            }
        }
    }

    printf("%d out of %d passed.\n", count, total);

    return 0;
}