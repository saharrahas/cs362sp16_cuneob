#include "dominionTestUtilities.h"
#include <stdio.h>



int main(){


    printf("\n\n Card Test 1 ----------------");

    struct gameState* game= newGame();
    initializeGame(2,kingdomCards(7,8,9,10,11,12,13,14,15,16),20,game);
    game->hand[0][game->handCount[0]]=smithy;
    game->handCount[0]++;

    assertPrint(playCard(game->handCount[0]-1,0,0,0,game)==0,"PASSED: No error value in basic smithy test",
                                                      "FAILED: Error value in basic smithy test");

    assertPrint(game->handCount[0]==8,"PASSED: Basic smithy test added correct number of cards to hand",
                                      "FAILED: Basic smithy test did not add correct number of cards to hand");

    assertPrint(game->deckCount[0]==2,"PASSED: Basic smithy test took correct number of cards from deck",
                                      "FAILED: Basic smithy test did not take correct number of cards from deck");



    game->hand[0][game->handCount[0]]=smithy;
    game->handCount[0]++;


    assertPrint(playCard(game->handCount[0]-1,0,0,0,game)<0,"PASSED: Error value in smithy-less smithy test",
                                                      "FAILED: No error value in smithy-less smithy test");

    game->deckCount[0]=0;

    game->hand[0][game->handCount[0]]=smithy;
    game->handCount[0]++;

    assertPrint(playCard(game->handCount[0]-1,0,0,0,game)==0,"PASSED: No error value in empty-deck smithy test",
                                                     "FAILED: Error value in empty-deck smithy test");

    return 0;
}





