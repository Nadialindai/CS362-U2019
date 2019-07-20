#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "getWinners"
void assertEqual(int, int);

int main() {
  int seed = 1234;
  int val;
  int players[4] = {3, 4, 6, 5};
  int numPlayers = 4;
	struct gameState state, originalState;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
  numPlayers = 2;
	initializeGame(numPlayers, k, seed, &originalState);

	// initialize a game state and player cards

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
  // ----------- TEST 2: --------------
	printf("TEST 2: Correctly gets single winner\n");
	memcpy(&state, &originalState, sizeof(struct gameState));
  val = getWinners(&players, &state);

  assertEqual(players[0], 0);
  assertEqual(players[1], 0);
  assertEqual(players[2], 1);
  assertEqual(players[3], 0);
  assertEqual(val, 0);

  // ----------- TEST 2: --------------
	printf("TEST 1: Correctly gets two winners\n");
	memcpy(&state, &originalState, sizeof(struct gameState));
  players[0] = 3;
  players[1] = 6;
  players[2] = 6;
  players[3] = 5;
  val = getWinners(players, &state);

  assertEqual(players[0], 0);
  assertEqual(players[1], 1);
  assertEqual(players[2], 1);
  assertEqual(players[3], 0);
  assertEqual(val, 0);

  // ----------- TEST 3: --------------
	printf("TEST 3: adjusts scores based on turn\n");
	memcpy(&state, &originalState, sizeof(struct gameState));
  state.whoseTurn = 1;
  players[0] = -33;
  players[1] = 6;
  players[2] = 6;
  players[3] = 5;
  val = getWinners(players, &state);

  assertEqual(players[0], 0);
  assertEqual(players[1], 0);
  assertEqual(players[2], 1);
  assertEqual(players[3], 0);
  assertEqual(val, 0);
  return 0;
}

void assertEqual(int a, int b){
  if(a == b)
    printf("\n >>>>> SUCCESS: %d = %d <<<<<\n\n", a, b);
  else
    printf("\n >>>>> Failure: %d != %d <<<<<\n\n", a, b);
}

