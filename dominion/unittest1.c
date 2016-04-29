#include <stdio.h>
#include <stdlib.h>

#include "dominionTestUtilities.h"
#include "dominion.h"
#include "rngs.h"



int main(){

    printf("\n\n Unit Test 1 ---------------");

    struct gameState* game=newGame();

    int* theCards=kingdomCards(8,9,10,11,12,13,14,15,16,17);

    assertPrint(initializeGame(1,theCards,20,game)<0,
                "PASSED: initializeGame returns an error when given a bad number of players (1)",
                "FAILED: initializeGame does not return an error when given a bad number of players (1)");

    free(game);

    game=newGame();
    theCards=kingdomCards(8,9,10,11,12,13,14,15,16,17);

    assertPrint(initializeGame(5,theCards,20,game)<0,
                "PASSED: initializeGame returns an error when given a bad number of players (5)",
                "FAILED: initializeGame does not return an error when given a bad number of players (5)");

    free(game);

    game=newGame();
    theCards=kingdomCards(8,9,10,11,12,13,14,15,16,8);

    assertPrint(initializeGame(2,theCards,20,game)<0,
                "PASSED: initializeGame returns an error when given duplicate cards",
                "FAILED: initializeGame does not return an error when given duplicate cards");

    free(game);

    game=newGame();
    theCards=kingdomCards(8,9,10,11,12,13,14,15,16,84);

    assertPrint(initializeGame(2,theCards,20,game)<0,
                "PASSED: initializeGame returns an error when given a bad card",
                "FAILED: initializeGame does not return an error when given a bad card");

    free(game);

    game=newGame();
    
    theCards=kingdomCards(7,8,9,10,11,12,13,14,15,16);


    int test=initializeGame(2,theCards,20,game);

    assertPrint(test==0,
                "PASSED: initializeGame does not return an error when given valid input",
                "FAILED: initializeGame returns an error when given valid input");

    assertPrint(game->numPlayers==2,
                "PASSED: initializeGame made there be 2 players when it should have",
                "FAILED: initializeGame failed to make the number of players 2 when it should have");


    unsigned int pos=0;
    char failed;
    while(pos<treasure_map+1){
        failed=0;
        if(pos==curse){
            if(game->supplyCount[pos]!=10){
                failed=1;
            }
        }
        else if(pos==copper){
            if(game->supplyCount[pos]!=46){
                failed=1;
            }
        }
        else if(pos==silver){
            if(game->supplyCount[pos]!=40){
                failed=1;
            }
        }
        else if(pos==gold){
            if(game->supplyCount[pos]!=30){
                failed=1;
            }
        }
        else if( (pos>=estate && pos<=province) || pos==gardens || pos==great_hall){
            if(game->supplyCount[pos]!=8 && pos<17){
                failed=1;
            }
        }
        else{
            if(game->supplyCount[pos]!=10 && pos<17){
                failed=1;
            }
        }


        assertPrint(failed==0,
            "PASSED: initializeGame inserted the proper number of cards of type",
            "FAILED: initializeGame failed to insert the proper number of cards of type");
        printf("%d",pos);

        pos++;
    }

    return 0;
}



