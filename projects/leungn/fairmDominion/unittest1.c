#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

#define TESTCARD "Baron"

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
    int i, temp = 0, total = 0, pass= 0;
    int seed = 1000;
    int numPlayer = 2;
    int maxBonus = 10;
    int p, r, c, h, handCount;
    int bonus = 0;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel,
                 smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;

    int estates[MAX_HAND];
    int not_estates[MAX_HAND];
    for(i = 0; i < MAX_HAND; i++){
        estates[i] = estate;
        not_estates[i] = copper;
    }

    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
    for (p = 0; p < numPlayer; p++)
    {
        for (handCount = 1; handCount <= maxHandCount; handCount++)
        {
            printf("Test 1: Player %d has %d card(s) and %d bonus?\n", p, handCount, bonus);
            memset(&G, 23, sizeof(struct gameState));
            r = initializeGame(numPlayer, k, seed, &G);
            G.handCount[p] = handCount;

            printf("Test 2: Numbuys has +1?\n");
            memcpy(G.hand[p], estates, sizeof(int) * handCount);
            temp = G.numBuys;
            //struct gameState *state, int currentPlayer, int choice1)
            playBaron(&G, p, 0);
            pass+= assertTrue(G.numBuys, temp + 1);
            total++;

            printf("Test 3: Estate card given?\n");
            memcpy(G.hand[p], estates, sizeof(int) * handCount);
            temp = G.handCount[p];
            playBaron(&G, p, 0);
            pass+= assertTrue(G.handCount[p], temp + 1);
            total++;


            printf("Test 3: Coins get +4?\n");
            memcpy(G.hand[p], estates, sizeof(int) * handCount);
            temp = G.coins;
            playBaron(&G, p, 1);
            pass+= assertTrue(G.coins, temp + 4);
            total++;

            printf("Test 4: Estate card discarded?\n");
            memcpy(G.hand[p], estates, sizeof(int) * handCount);
            temp = G.handCount[p];
            playBaron(&G, p, 1);
            pass+= assertTrue(G.handCount[p], temp - 1);
            total++;

            printf("Test 5: Estate card given?\n");
            memcpy(G.hand[p], not_estates, sizeof(int) * handCount);
            temp = G.handCount[p];
            playBaron(&G, p, 1);
            pass+= assertTrue(G.handCount[p], temp + 1);
            total++;
        }
    }

    int average = (float) pass/total * 100;
    printf("%d percent passed.\n", average);

    return 0;
}
