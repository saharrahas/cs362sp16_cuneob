#include "dominionTestUtilities.h"
#include <stdio.h>




int main(){

    printf("\n\n Unit Test 4 ----------------");
   
    struct gameState* game= newGame();
    initializeGame(2,kingdomCards(8,9,10,11,12,13,14,15,16,17),20,game);


    game->numBuys=2;
    game->coins=5;

    int pastDiscard=game->discardCount[game->whoseTurn];

    assertPrint(buyCard(silver,game)==0,
                "PASSED: buyCard does not return an error code for a basic buy",
                "FAILED: buyCard returns an error code for a basic buy");

    assertPrint(game->coins==2,
                "PASSED: buyCard charges right amount of money for a basic buy",
                "FAILED: buyCard does not charge the right amount of money for a basic buy");

    assertPrint(game->numBuys==1,
                "PASSED: buyCard decrements available buy actions",
                "FAILED: buyCard does not decrement available buy actions");

    assertPrint( (game->discardCount[game->whoseTurn]==pastDiscard+1) && game->discardCount[pastDiscard]==silver,
                "PASSED: buyCard places bought card in discard",
                "FAILED: buyCard does not place bought card in discard");

    assertPrint(buyCard(silver,game)==1,
                "PASSED: buyCard returns an error code when there are insufficient funds for a purchase",
                "FAILED: buyCard fails to return an error code when there are insufficient funds for a purchase");


    assertPrint( (game->discardCount[game->whoseTurn]==pastDiscard+1) &&
                 (game->discardCount[pastDiscard]==silver) &&
                 (game->coins==5) &&
                 (game->numBuys==1),
                "PASSED: buyCard failures don't effect anything",
                "FAILED: buyCard failures have side-effects");
    printf("\nchange in discard pile: %d \n coin change: %d \n buyChange: %d",game->discardCount[game->whoseTurn]==pastDiscard, game->coins-5, game->numBuys-1);


    game->embargoTokens[copper]=1;

    buyCard(copper,game);


    assertPrint(game->discard[0][game->discardCount[0]-1]==curse,
                "PASSED: buyCard gives curses to people who buy from embargoed supplies",
                "FAILED: buyCard fails to give curses to people who buy from embargoed supplies");


    assertPrint(buyCard(copper,game)==1,
                "PASSED: buyCard returns an error code when there are insufficient buys for a purchase",
                "FAILED: buyCard fails to return an error code when there are insufficient buys for a purchase");

    return 0;
}








