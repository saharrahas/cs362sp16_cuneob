#include "dominionTestUtilities.h"
#include <stdio.h>






int main(){

    
    printf("\n\n Card Test 2 ----------------");
   
    struct gameState* game= newGame();
    initializeGame(2,kingdomCards(7,8,9,10,11,12,13,14,15,16),20,game);

    game->hand[0][game->handCount[0]]=steward;
    game->handCount[0]++;
    int theHandCount=game->handCount[0];
    int theDeckCount=game->deckCount[0];

    assertPrint(playCard(game->handCount[0]-1,1,0,0,game)==0,"PASSED: No error value in steward draw test",
                                                      "FAILED: Error value in steward draw test");

    assertPrint(game->handCount[0]-theHandCount==2,"PASSED: Steward draw test put the right number of cards into the hand",
                                             "FAILED: Steward draw test put the wrong number of cards into the hand");

    assertPrint(theDeckCount-game->deckCount[0]==2,"PASSED: Steward draw test took the right number of cards from the deck",
                                             "FAILED: Steward draw test took the wrong number of cards from the deck");





    game->hand[0][game->handCount[0]]=steward;
    game->handCount[0]++;

    int coinCount=game->coins;

    assertPrint(playCard(game->handCount[0]-1,2,0,0,game)==0,"PASSED: No error value in steward coin test",
                                                      "FAILED: Error value in basic steward coin test");

    assertPrint(coinCount+2==game->coins,"PASSED: Steward coin test adds 2 coins",
                                         "FAILED: Steward coin test does not add 2 coins");





    theHandCount=game->handCount[0];
    int futureLastCard=game->hand[0][game->handCount[0]-4];

    assertPrint(playCard(game->handCount[0]-1,3,game->handCount[0]-2,game->handCount[0]-3,game)<0,
                                 "PASSED: No error value in steward trash test",
                                 "FAILED: Error value in basic steward trash test");

    assertPrint( (game->handCount[0]-3==game->handCount[0]) && (futureLastCard==game->hand[0][game->handCount[0]-1]),
                                                "PASSED: Steward trash test removes the proper cards",
                                                "FAILED: Steward coin test does not remove cards properly");

    return 0;

}








