#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "Ambassador"
void assertEqual(int, int);

int main() {
  int handPos = 0, choice1 = 0, choice2 = 0;
  int seed = 1234;
  int numPlayers = 2;
  int currentPlayer = 0;
	struct gameState state, originalState;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &originalState);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
  // ----------- TEST 1: numActions + 2 --------------
	printf("TEST 1: numActions + 2 \n");

	memcpy(&state, &originalState, sizeof(struct gameState));
	choice1 = 2;
	choice2 = 1;
  playAmbassador(&state, currentPlayer, choice1, choice2, handPos);

  assertEqual(originalState.supplyCount[originalState.hand[currentPlayer][choice1]] + choice2, state.supplyCount[state.hand[currentPlayer][choice1]]);

  // ----------- TEST 2: choice2 less than 0 returns error  --------------
	printf("TEST 2: Choice 2 less than 0 returns error \n");

	memcpy(&state, &originalState, sizeof(struct gameState));
	choice2 = -3;
  int val = playAmbassador(&state, currentPlayer, choice1, choice2, handPos);

  assertEqual(val, -1);

  // ----------- TEST 2: choice2 larger than 2 returns error  --------------
	printf("TEST 2: Choice 2 greater than 2 returns error \n");

	memcpy(&state, &originalState, sizeof(struct gameState));
	choice2 = 3;
  val = playAmbassador(&state, currentPlayer, choice1, choice2, handPos);

  assertEqual(val, -1);
  printf("\n >>>>> Unit Test 2 SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);
  return 0;
}

void assertEqual(int a, int b){
  if(a == b)
    printf("\n >>>>> SUCCESS: %d = %d <<<<<\n\n", a, b);
  else
    printf("\n >>>>> Failure: %d != %d <<<<<\n\n", a, b);
}
