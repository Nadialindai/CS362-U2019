#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "drawCard"
void assertEqual(int, int);

int main() {
  int seed = 1234;
  int val;
  int nextPlayer = 1;
  int i = 1;
  int numPlayers = 2;
	struct gameState state, originalState;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	initializeGame(numPlayers, k, seed, &originalState);

	// initialize a game state and player cards

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
  // ----------- TEST 1: --------------
	printf("TEST 1: Correctly gets next card\n");
	memcpy(&state, &originalState, sizeof(struct gameState));
  for(; i<=10; i++){
    drawCard(nextPlayer, &state);
    assertEqual(originalState.deckCount[nextPlayer]-i, state.deckCount[nextPlayer]);
    assertEqual(originalState.deck[nextPlayer][10-i], state.hand[nextPlayer][i-1]);
    assertEqual(i, state.handCount[nextPlayer]);
  }

  i = 0;
  for(; i < state.handCount[nextPlayer]; i++){
    discardCard(0, nextPlayer, &state, 0);
  }
  val = drawCard(nextPlayer, &state);
  assertEqual(0, state.discardCount[nextPlayer]);
  assertEqual(originalState.deckCount[nextPlayer]-1, state.deckCount[nextPlayer]);
  assertEqual(1, state.handCount[nextPlayer]);
  assertEqual(val, 0);

  // ----------- TEST 2: --------------
	printf("TEST 2: errors when no cards in deck or discard\n");
	memcpy(&state, &originalState, sizeof(struct gameState));
  state.deckCount[nextPlayer] = 0;
  state.discardCount[nextPlayer] = 0;
  val = drawCard(nextPlayer, &state);
  assertEqual(val, -1);

  return 0;
}

void assertEqual(int a, int b){
  if(a == b)
    printf("\n >>>>> SUCCESS: %d = %d <<<<<\n\n", a, b);
  else
    printf("\n >>>>> Failure: %d != %d <<<<<\n\n", a, b);
}

