/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * cardtest1: cardtest1.c dominion.o rngs.o
 *      gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"

#define TESTCARD "InitializeGame"

int assertTrue(int a, int b) {
    if(a != b) {
        printf("%s failed\n", TESTCARD);
        return -1;
    } else {
        printf("%s passed\n", TESTCARD);
        return 1;
    }

}

int main (int argc, char** argv) {

    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;
    int expectedEstates = 0;

    int i, j, m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;

    int seed = 1000;

    int number_players = 2;

    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};

    int total, count = 0;
    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);


    int kingdomCards[10] = {adventurer, gardens, embargo, village, minion, mine, baron, ambassador, tribute};

    initializeGame(number_players, k, seed, &testG);
    printf ("Initializing game.\n");

    printf("number of curse cards 10, actual: %d\n", G.supplyCount[curse]);
    total++;
    count += assertTrue(G.supplyCount[curse], 10);

    printf("number of estate victory 8, actual: %d\n", G.supplyCount[estate]);
    total++;
    count += assertTrue(G.supplyCount[estate], 8);

    printf("number of copper cards 46, actual: %d\n", G.supplyCount[copper]);
    total++;
    count += assertTrue(G.supplyCount[copper], 46);

    printf("number of silver cards 40, actual: %d\n", G.supplyCount[silver]);
    total++;
    count += assertTrue(G.supplyCount[silver], 40);

    printf("number of gold cards 30, actual: %d\n", G.supplyCount[gold]);
    total++;
    count += assertTrue(G.supplyCount[gold], 30);

    printf("number of duchy cards 8, actual: %d\n", G.supplyCount[duchy]);
    total++;
    count += assertTrue(G.supplyCount[duchy], 8);

    printf("number of province cards 8, actual: %d\n", G.supplyCount[province]);
    total++;
    count += assertTrue(G.supplyCount[province], 8);

    printf("number of players is 2, actual: %d", G.numPlayers);
    total++;
    count += assertTrue(G.numPlayers, 2);


    printf("%d out of %d passed.\n", count, total);
    return 0;
}
