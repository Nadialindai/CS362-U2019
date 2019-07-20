#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "initializeGame"
void assertEqual(int, int);

int main() {
  int seed = 1234;
  int i = 0;
  int j = 0;
  int numPlayers = 2;
	struct gameState state;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
  // ----------- TEST 1: --------------
	printf("TEST 1: \n");
  numPlayers = 2;
	initializeGame(numPlayers, k, seed, &state);


  assertEqual(state.supplyCount[curse], 10);
  assertEqual(state.supplyCount[estate], 8);
  assertEqual(state.supplyCount[duchy], 8);
  assertEqual(state.supplyCount[province], 8);
  assertEqual(state.supplyCount[copper], 60 - (numPlayers * 7));
  assertEqual(state.supplyCount[silver], 40);
  assertEqual(state.supplyCount[gold], 30);

  for (i = adventurer; i <= treasure_map; i++){      	//loop all cards
    for (j=0; j < 10; j++){      	//loop all cards
      if(k[j] == i){
        if (i != great_hall && i != gardens)
          assertEqual(state.supplyCount[i], 10);
        else
          assertEqual(state.supplyCount[i], 8);
      }
    }
  }

  assertEqual(state.outpostPlayed, 0);
  assertEqual(state.phase, 0);
  assertEqual(state.numActions, 1);
  assertEqual(state.numBuys, 1);
  assertEqual(state.playedCardCount, 0);
  assertEqual(state.whoseTurn, 0);
  assertEqual(state.handCount[0], 5);
 
  // ----------- TEST 2: --------------
	printf("TEST 2: \n");
  numPlayers = 3;
	initializeGame(numPlayers, k, seed, &state);

  assertEqual(state.supplyCount[curse], 20);
  assertEqual(state.supplyCount[estate], 12);
  assertEqual(state.supplyCount[duchy], 12);
  assertEqual(state.supplyCount[province], 12);
  assertEqual(state.supplyCount[copper], 60 - (numPlayers * 7));
  assertEqual(state.supplyCount[silver], 40);
  assertEqual(state.supplyCount[gold], 30);

  for (i = adventurer; i <= treasure_map; i++){      	//loop all cards
    for (j=0; j < 10; j++){      	//loop all cards
      if(k[j] == i){
        if (i != great_hall && i != gardens)
          assertEqual(state.supplyCount[i], 10);
        else
          assertEqual(state.supplyCount[i], 8);
      }
    }
  }

    // ----------- TEST 3: --------------
	printf("TEST 3: negative number of players \n");
  numPlayers = -1;
	int val = initializeGame(numPlayers, k, seed, &state);
  assertEqual(val, -1);

  printf("TEST 4: Too many players\n");
  numPlayers = 5;
	val = initializeGame(numPlayers, k, seed, &state);
  assertEqual(val, -1);

  printf("TEST 5: Max players\n");
  numPlayers = 4;
	val = initializeGame(numPlayers, k, seed, &state);
  assertEqual(val, 0);
  return 0;
}

void assertEqual(int a, int b){
  if(a == b)
    printf("\n >>>>> SUCCESS: %d = %d <<<<<\n\n", a, b);
  else
    printf("\n >>>>> Failure: %d != %d <<<<<\n\n", a, b);
}

