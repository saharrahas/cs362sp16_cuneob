#include "dominionTestUtilities.h"
#include <stdio.h>





int main(){


    printf("\n\n Card Test 4 ---------------");


    struct gameState* game= newGame();
    initializeGame(4,kingdomCards(8,9,10,11,12,13,14,15,16,17),20,game);

    game->hand[0][game->handCount[0]++]=embargo;

    int pastCoin=game->coins;
    int pastEmbargoes=game->embargoTokens[silver];

    assertPrint(playCard(game->handCount[0]-1,silver,0,0,game)==0,
                "PASSED: embargo does not return error for a basic test",
                "FAILED: embargo returns an error for a basic test");

    assertPrint(game->coins=pastCoin+2,
                "PASSED: embargo gives the user 2 extra coins",
                "FAILED: embargo does not give the user 2 extra coins");

    assertPrint(game->embargoTokens[silver]=pastEmbargoes+1,
                "PASSED: embargo increments the proper supply's embargo tokens",
                "FAILED: embargo does not increment the proper supply's embargo tokens");

    return 0;
}





