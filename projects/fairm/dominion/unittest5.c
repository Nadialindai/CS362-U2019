#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "playBaron"
void assertNotEqual(int, int);
void assertEqual(int, int);

int main() {
  int seed = 1234;
  int choice1 = 0;
  int numPlayers = 2;
  int currentPlayer = 0;
	struct gameState state, originalState;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &originalState);

	printf("----------------- Testing TESTCARD: %s ----------------\n", TESTCARD);
  // ----------- TEST 1: Choose to discard draws an estate card --------------
	printf("TEST 1: Choose to discard draws an estate card\n");

	memcpy(&state, &originalState, sizeof(struct gameState));
  playBaron(&state, currentPlayer, choice1);

  assertEqual(originalState.numBuys + 1, state.numBuys);
  assertEqual(originalState.supplyCount[estate] - 1, state.supplyCount[estate]);
  assertEqual(state.discard[currentPlayer][state.discardCount[currentPlayer]-1], estate);

  // ----------- TEST 2: --------------
	printf("TEST 2: \n");

	memcpy(&state, &originalState, sizeof(struct gameState));
  choice1 = 1;
  state.hand[currentPlayer][3] = estate;
  playBaron(&state, currentPlayer, choice1);

  assertEqual(originalState.numBuys + 1, state.numBuys);
  assertEqual(originalState.coins + 4, state.coins);

  printf("\n >>>>> Unit Test 5 SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);
  return 0;
}

void assertNotEqual(int a, int b){
  if(a != b)
    printf("\n >>>>> SUCCESS: %d != %d <<<<<\n\n", a, b);
  else
    printf("\n >>>>> Failure: %d = %d <<<<<\n\n", a, b);
}

void assertEqual(int a, int b){
  if(a == b)
    printf("\n >>>>> SUCCESS: %d = %d <<<<<\n\n", a, b);
  else
    printf("\n >>>>> Failure: %d != %d <<<<<\n\n", a, b);
}



