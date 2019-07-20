#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "shuffle"
void assertEqual(int, int);

int main() {
  int seed = 1234;
  int currentPlayer = 0;
  int val, i;
  int numPlayers = 2;
	struct gameState state, originalState;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
  numPlayers = 2;
	initializeGame(numPlayers, k, seed, &originalState);

	// initialize a game state and player cards

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
  // ----------- TEST 1: can't shuffle deck with cards in hand --------------
	printf("TEST 1: can't shuffle deck with cards in hand \n");
	memcpy(&state, &originalState, sizeof(struct gameState));
  drawCard(currentPlayer, &state);//Draw a card
  drawCard(currentPlayer, &state);//Draw a card
  drawCard(currentPlayer, &state);//Draw a card
  drawCard(currentPlayer, &state);//Draw a card
  drawCard(currentPlayer, &state);//Draw a card

  val = shuffle(currentPlayer, &state);
  assertEqual(val, -1);

  // ----------- TEST 2: --------------
	printf("TEST 2:  \n");
	memcpy(&state, &originalState, sizeof(struct gameState));
  shuffle(currentPlayer, &state);
  for(i=0; i < state.deckCount[currentPlayer]; i++){
    if(state.deck[currentPlayer][i] != originalState.deck[currentPlayer][i])
      val = 1;
  }
  assertEqual(state.deckCount[currentPlayer], originalState.deckCount[currentPlayer]);
  assertEqual(val, 1);

  return 0;
}

void assertEqual(int a, int b){
  if(a == b)
    printf("\n >>>>> SUCCESS: %d = %d <<<<<\n\n", a, b);
  else
    printf("\n >>>>> Failure: %d != %d <<<<<\n\n", a, b);
}


