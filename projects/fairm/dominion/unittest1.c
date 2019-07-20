#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "Minion"
void assertEqual(int, int);

int main() {
  int handPos = 0, choice1 = 0, choice2 = 0;
  int seed = 1234;
  int numPlayers = 2;
  int currentPlayer = 0;
  int nextPlayer = 1;
	struct gameState state, originalState;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &originalState);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
  // ----------- TEST 1: choice1--------------
	printf("TEST 1: numAction +2 \n");

	memcpy(&state, &originalState, sizeof(struct gameState));
	choice1 = 1;
  playMinion(&state, currentPlayer, choice1, choice2, handPos);

  assertEqual(originalState.numActions + 1, state.numActions);
  assertEqual(originalState.coins + 2, state.coins);

  // ----------- TEST 2: choice 2 --------------
	printf("TEST 2: choice 2  \n");

	memcpy(&state, &originalState, sizeof(struct gameState));
  int i=0;
	choice1 = 0;
	choice2 = 1;
  drawCard(0, &state);
  for(; i < 6; i++)
    drawCard(nextPlayer, &state);
  playMinion(&state, currentPlayer, choice1, choice2, handPos);

  assertEqual(state.handCount[0], 4);
  assertEqual(state.handCount[1], 4);
  printf("\n >>>>> Unit Test 1 SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

  return 0;
}

void assertEqual(int a, int b){
  if(a == b)
    printf("\n >>>>> SUCCESS: %d = %d <<<<<\n\n", a, b);
  else
    printf("\n >>>>> Failure: %d != %d <<<<<\n\n", a, b);
}
