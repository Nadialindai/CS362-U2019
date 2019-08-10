/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * unittest5: unittest5.c dominion.o rngs.o
 *      gcc -o unittest5 -g  unittest5.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "mine"

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
    int seed = 1234;
    int handPos = 0, choice1 = 0, choice2 = 0;
    int numPlayers = 2;
    int currentPlayer = 0;
    int val = 0;
    int i = 0;
    struct gameState state, originalState;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &originalState);

    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

    printf("TEST 1: mining copper returns silver in hand\n");

    memcpy(&state, &originalState, sizeof(struct gameState));
    choice1 = 3;
    choice2 = 5;
    handPos = choice1-1;
    state.hand[currentPlayer][choice1] = 4;
    state.hand[currentPlayer][handPos] = 11;
    playMine(&state, currentPlayer, choice1, choice2, handPos);
    for (; i < state.handCount[currentPlayer]; i++) {
        if(state.hand[currentPlayer][i] == 5)
            val = 1;
    }
    assertTrue(val, 1);

    printf("TEST 2: mining silver returns gold in hand\n");

    memcpy(&state, &originalState, sizeof(struct gameState));
    choice1 = 3;
    choice2 = 6;
    handPos = choice1-1;
    state.hand[currentPlayer][choice1] = 5;
    state.hand[currentPlayer][handPos] = 11;
    int val2 = playMine(&state, currentPlayer, choice1, choice2, handPos);
    for (; i < state.handCount[currentPlayer]; i++) {
        if(state.hand[currentPlayer][i] == 6)
            val = 1;
    }
    assertTrue(val, 1);
    assertTrue(val2, 0);

    printf("TEST 3: mining non mineral returns error\n");

    memcpy(&state, &originalState, sizeof(struct gameState));
    choice1 = 3;
    choice2 = 6;
    handPos = choice1-1;
    state.hand[currentPlayer][choice1] = 0;
    state.hand[currentPlayer][handPos] = 11;

    //(state, currentPlayer, choice1, choice2, handPos)
    val = playMine(&state, currentPlayer, choice1, choice2, handPos);
    assertTrue(-1, val);
    state.hand[currentPlayer][choice1] = 10;
    val = playMine(&state, currentPlayer, choice1, choice2, handPos);
    assertTrue(-1, val);

    printf("TEST 4: mining copper  to gold fails\n");

    memcpy(&state, &originalState, sizeof(struct gameState));
    choice1 = 3;
    choice2 = 6;
    handPos = choice1;
    state.hand[currentPlayer][choice1] = 4;
    state.hand[currentPlayer][handPos] = 11;
    val = playMine(&state, currentPlayer, choice1, choice2, handPos);
    assertTrue(val, -1);

    printf("\n >>>>> Unit Test 4 SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);
    return 0;
}



