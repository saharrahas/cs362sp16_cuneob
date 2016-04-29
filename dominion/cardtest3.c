#include "dominionTestUtilities.h"
#include <stdio.h>





int main(){

     
    printf("\n\n Card Test 3 ----------------");
   
   
    struct gameState* game= newGame();
    initializeGame(4,kingdomCards(7,8,9,10,11,12,13,14,15,16),20,game);

    game->whoseTurn=1;
    game->hand[1][game->handCount[0]]=sea_hag;
    game->handCount[1]++;

    game->supplyCount[curse]=2;
    game->deckCount[2]=0;
    game->discardCount[2]=1;
    game->discard[2][0]=duchy;
    game->deckCount[3]=0;
    game->discardCount[3]=0;

    assertPrint(playCard(game->handCount[0]-1,0,0,0,game)==0,"PASSED: No error value in sea hag test",
                                                       "FAILED: Error value in sea hag test");

    assertPrint(game->deck[0][game->deckCount[0]-1]!=curse,"PASSED: Curses added in order in sea hag test",
                                                           "FAILED: Curses added out of order in sea hag test");

    assertPrint( (game->deckCount[2]==1) && (game->deck[2][game->deckCount[0]-1]==curse),
                                                           "PASSED: Curse added to replace card in sea hag test",
                                                           "FAILED: Curse replacement in sea hag test failed");

    assertPrint( (game->deckCount[3]==1) && (game->deck[2][game->deckCount[0]-1]==curse),
                                                           "PASSED: Curses added to empty deck/discard in sea hag test",
                                                           "FAILED: Curses not added to empty deck/discard in sea hag test");

    return 0;
}







