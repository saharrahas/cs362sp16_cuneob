#include <stdlib.h>
#include <stdio.h>
#include "dominionTestUtilities.h"




int main(){

    
    printf("\n\n Unit Test 3 ----------------");
   
    struct gameState* game= newGame();

    initializeGame(4,kingdomCards(10,11,12,13,14,15,16,17,18,19),20,game);

    endTurn(game);

    assertPrint(game->whoseTurn==1,
                "PASSED: endTurn increments the whoseTurn value forward",
                "FAILED: endTurn fails to increment the whoseTurn value forward");

    int* theHand = malloc(sizeof(int)*game->handCount[0]);
    unsigned int pos=0;
    while(pos<game->handCount[0]){
        theHand[pos]=game->hand[0][pos];
        pos++;
    }

    assertPrint(game->whoseTurn==1,
                "PASSED: endTurn increments the whoseTurn value forward",
                "FAILED: endTurn fails to increment the whoseTurn value forward");

    endTurn(game);


    char different=0;
    pos=0;
    while(pos<game->handCount[0]){
        if(theHand[pos]!=game->hand[0][pos]){
            different=1;
        }
        pos++;
    }


    assertPrint(different,
                "PASSED: endTurn results in a new hand",
                "FAILED: endTurn fails to result in a new hand)");

    endTurn(game);
    endTurn(game);


    assertPrint(game->whoseTurn==0,
                "PASSED: endTurn loops back to first player from last player",
                "FAILED: endTurn fails to loop back to first player");

    return 0;
}



