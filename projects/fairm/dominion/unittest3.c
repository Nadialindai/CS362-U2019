#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "Tribute"
void assertNotEqual(int, int);
void assertEqual(int, int);

int main() {
  int seed = 1234;
  int numPlayers = 2;
  int currentPlayer = 0;
  int nextPlayer = 1;
  int tributeRevealedCards[2] = {-1, -1};
	struct gameState state, originalState;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &originalState);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
  // ----------- TEST 1:  --------------
	printf("TEST 2: \n");

	memcpy(&state, &originalState, sizeof(struct gameState));
  state.deck[nextPlayer][state.deckCount[nextPlayer]-1] = 6; // gold
  state.deck[nextPlayer][state.deckCount[nextPlayer]-2] = 2; //duchy
  playTribute(&state, currentPlayer, nextPlayer, tributeRevealedCards);
  assertNotEqual(-1, tributeRevealedCards[0]);
  assertNotEqual(-1, tributeRevealedCards[1]);
  assertEqual(originalState.deckCount[nextPlayer] - 2, state.deckCount[nextPlayer]); 
  assertEqual(originalState.coins + 2, state.coins); 
  assertEqual(originalState.handCount[currentPlayer] + 2, state.handCount[currentPlayer]); 
 
  // ----------- TEST 1:  --------------
	printf("TEST 2: \n");

	memcpy(&state, &originalState, sizeof(struct gameState));
  int i = 0;
  for(; i<9; i++){
    drawCard(nextPlayer, &state);
    discardCard(0, nextPlayer, &state, 0);
  }

  state.deck[nextPlayer][state.deckCount[nextPlayer]-1] = 16; // great hall
  playTribute(&state, currentPlayer, nextPlayer, tributeRevealedCards);
  assertNotEqual(-1, tributeRevealedCards[0]);
  assertEqual(-1, tributeRevealedCards[1]);
  assertEqual(originalState.numActions + 2, state.numActions); 
  printf("\n >>>>> Unit Test 3 SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);
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

