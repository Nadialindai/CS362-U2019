#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "endTurn"
void assertEqual(int, int);

int main() {
  int seed = 1234;
  int currentPlayer = 0;
  int val;
  int numPlayers = 2;
	struct gameState state, originalState;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
  numPlayers = 2;
	initializeGame(numPlayers, k, seed, &originalState);

	// initialize a game state and player cards

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
  // ----------- TEST 1: --------------
	printf("TEST 1: test values ste\n");
	memcpy(&state, &originalState, sizeof(struct gameState));

  val = endTurn(&state);
  assertEqual(state.whoseTurn, 1);
  assertEqual(state.handCount[currentPlayer], 0);
  assertEqual(originalState.handCount[currentPlayer], state.discardCount[currentPlayer]);
  assertEqual(state.outpostPlayed, 0);
  assertEqual(state.phase, 0);
  assertEqual(state.numActions, 1);
  assertEqual(state.numBuys, 1);
  assertEqual(state.playedCardCount, 0);
  assertEqual(state.handCount[state.whoseTurn], 5);
  assertEqual(val, 0);
 
  // ----------- TEST 2: --------------
	printf("TEST 2: next player wraps if last in array \n");
  val = endTurn(&state);
  assertEqual(state.whoseTurn, 0);

  return 0;
}

void assertEqual(int a, int b){
  if(a == b)
    printf("\n >>>>> SUCCESS: %d = %d <<<<<\n\n", a, b);
  else
    printf("\n >>>>> Failure: %d != %d <<<<<\n\n", a, b);
}
