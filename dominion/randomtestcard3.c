#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>
#define TESTCARD "TRIBUTE CARD"

int assertTrue(int a, int b) {
    if(a != b) {
        printf("%s failed\n", TESTCARD);
        return -1;
    } else {
        printf("%s passed\n", TESTCARD);
        return 1;
    }

}

int main()
{
    srand(time(0));
    clock_t begin;
    clock_t finish;
    double time;
    int seed = 1000;
    int failedTests = 0;
    int testScore;


    int playerNumber = (rand() % (4 - 1 + 1)) + 1;
    int currentPlayerRandom = (rand() % (3-0 + 1)) + 0;

    int player1 = 0, player2 = 1, player3 = 2, player4 = 3;
    int estateCount = 0;

    struct gameState gT;
    struct gameState g;

    int tributeRevealedCards[2] = {-1, -1};

    int k[10] = {adventurer, council_room, feast, tribute, minion, remodel, smithy, village, baron, great_hall};
    int coinsPre;
    int coinsPost;

    initializeGame(2, k, seed, &g);

    endTurn(&g);
    endTurn(&g);

    memcpy(&gT, &g, sizeof(struct gameState));

    begin = clock();

    for (int index = 0; index < 10000; index++)
    {
        int currentPlayer = (rand() % (1-0 + 1)) + 0;
        int nextPlayer;

        int card1, card2 = (rand() % (2-0 + 1)) + 0;

        int tributeCards[2] = {card1, card2};

        if (currentPlayer == 1)
        {
            nextPlayer = 0;
        }
        else nextPlayer = 1;

        printf("----------Test Card Suite: %s ----------\n", TESTCARD);

        printf("Testing tributeRefactor()\n");
        printf("Round: %d\n", index);

        coinsPre= gT.coins;

        //(struct gameState *state, int currentPlayer, int nextPlayer, int tributeRevealedCards[2])
        playTribute(&g, currentPlayer, nextPlayer, tributeRevealedCards);
        coinsPre = gT.coins;

        printf("Player turn: %d\n", whoseTurn(&gT));
        printf("Hand current player: %d\n",  gT.handCount[currentPlayer]);
        printf("Hand of next player: %d\n", gT.handCount[nextPlayer]);
        testScore = assertTrue(gT.handCount[currentPlayer], g.handCount[currentPlayer]-2);
        if(testScore == -1)
        {
            failedTests = -1;
        }

        printf("Action count of player: %d\n", gT.numActions);
        if (card1 == 0 && card2 == 0)
        {
            testScore=assertTrue(gT.numActions, g.numActions+ 4);
        }

        if (card1 == 0 || card2 == 0)
        {
            testScore = assertTrue(gT.numActions, g.numActions + 2);
        }
        if (testScore == -1)
        {
            failedTests = -1;
        }

        printf("Coin count of player: %d\n", gT.coins);
        if (card1 == 1 && card2 == 1)
        {
            testScore=assertTrue (gT.coins, (g.coins) + 4);
        }

        if (card1 == 1 || card2 == 1)
        {
            testScore = assertTrue (gT.coins, (g.coins+ 2));
        }
        if (testScore == -1)
            failedTests =-1;

        printf("Card count of player: %d\n", gT.handCount[currentPlayer]);
        if (card1 == 2 && card2 == 2)
        {
            testScore = assertTrue(gT.handCount[currentPlayer], g.handCount[currentPlayer]+4);
        }

        if (card1 == 2 || card2 == 2)
            testScore = assertTrue(gT.handCount[currentPlayer], g.handCount[currentPlayer]+2);

        if (testScore == -1)
            failedTests = -1;

        printf("Discard count of next player: %d\n", gT.discardCount[nextPlayer]);
        testScore = assertTrue(gT.discardCount[nextPlayer], g.discardCount[nextPlayer] + 2);
        if (testScore == -1)
        {
            failedTests = -1;
        }


        printf("\n");
        coinsPre = 0;
        coinsPost = 0;

        if (playerNumber == 2)
        {
            endTurn(&gT);
            endTurn(&gT);
        }

        if (playerNumber ==3)
        {
            endTurn(&gT);
            endTurn(&gT);
            endTurn(&gT);
        }
        if (playerNumber ==4)
        {
            endTurn(&gT);
            endTurn(&gT);
            endTurn(&gT);
            endTurn(&gT);
        }

    }

    finish = clock();
    printf("---------------Tribute Refactor: ---------------\n");
    printf("tributeRefactor\n");
    time = ((double) (finish-begin))/CLOCKS_PER_SEC;
    printf("Time for execution of randomtestcard3.c in seconds: %f\n", time);
    printf("Number of rounds: 10000 \n");
    printf("TESTS COMPLETED \n");
    if (failedTests == -1)
        printf("NOT ALL TESTS PASSED\n");
    printf("branch coverage: \n");

    return 0;
}