#include "dominionTestUtilities.h"
#include <stdio.h>



int main(){

    printf("\n\n Unit Test 2 ----------------");

    struct gameState* game = newGame();
    initializeGame(2,kingdomCards(7,8,9,10,11,12,13,14,15,16),20,game);

    assertPrint(supplyCount(0,game)==10,
                "PASSED: supplyCount gave an accurate count after initialization",
                "FAILED: supplyCount failed to give an accurate count after initialization");

    game->supplyCount[0]-=3;

    assertPrint(supplyCount(0,game)==7,
                "PASSED: supplyCount gave an accurate count after modification of supply",
                "FAILED: supplyCount failed to give an accurate count after modification of supply");

    assertPrint(supplyCount(-1,game)==-1,
                "PASSED: supplyCount gave an error code when negative index is supplied",
                "FAILED: supplyCount failed to give an error code when negative index is supplied");


    assertPrint(supplyCount(99999,game)==-1,
                "PASSED: supplyCount gave an error code when an overly large index is supplied",
                "FAILED: supplyCount failed to give an error code when an overly large index is supplied");

    return 0;
}




