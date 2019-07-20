#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "Mine"
void assertNotEqual(int, int);
void assertEqual(int, int);

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
  // ----------- TEST 1: Mine Copper --------------
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
  assertEqual(val, 1);

  // ----------- TEST 2: Mine silver --------------
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
  assertEqual(val, 1);
  assertEqual(val2, 0);
  // ----------- TEST 3: Mine Non mineral fails --------------
	printf("TEST 3: mining non mineral returns error\n");

	memcpy(&state, &originalState, sizeof(struct gameState));
  choice1 = 3;
  choice2 = 6;
  handPos = choice1-1;
  state.hand[currentPlayer][choice1] = 0;
  state.hand[currentPlayer][handPos] = 11;
  val = playMine(&state, currentPlayer, choice1, choice2, handPos);
  assertEqual(-1, val);
  state.hand[currentPlayer][choice1] = 10;
  val = playMine(&state, currentPlayer, choice1, choice2, handPos);
  assertEqual(-1, val);
  //
  // ----------- TEST 4: Mine Copper to gold fails --------------
	printf("TEST 4: mining copper  to gold fails\n");

	memcpy(&state, &originalState, sizeof(struct gameState));
  choice1 = 3;
  choice2 = 6;
  handPos = choice1;
  state.hand[currentPlayer][choice1] = 4;
  state.hand[currentPlayer][handPos] = 11;
  val = playMine(&state, currentPlayer, choice1, choice2, handPos);
  assertEqual(val, -1);
  printf("\n >>>>> Unit Test 4 SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);
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


