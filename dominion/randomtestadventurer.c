#include "dominionTestUtilities.h"
#include "dominion.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>




int tryAdventurer(struct gameState* game){


    int res=0;

    int handCoins=getHandCoinage(game);
    int otherCoins=getDeckCoinage(game)+getDiscardCoinage(game);
    int handCoinCount=getHandCoinCount(game);
    int otherCoinCount=getDeckCoinCount(game)+getDiscardCoinCount(game);


    addAndPlay(adventurer,0,0,0,game);

    

    if(getHandCoinage(game)<handCoins+2){
        res+=1;
    }

    if(getHandCoinage(game)+getDeckCoinage(game)+getDiscardCoinage(game)!=handCoins+otherCoins){
       res+=2; 
    }

    if(getHandCoinCount(game)!=handCoinCount+2){
       res+=4; 
       
    }


    if(getHandCoinCount(game)+getDeckCoinCount(game)+getDiscardCoinCount(game)!=handCoinCount+otherCoinCount){
       res+=8; 
    }
    


    if((int)Random()%2==0){
        endTurn(game);
    }


    return res;
}






int main(int argc, char *argv[]){

    if(argc<2){
        printf("Insufficient arguments");
        return 0;
    }

    int theSeed=atoi(argv[1]);
    int advFail[4];
    advFail[0]=0;
    advFail[1]=0;
    advFail[2]=0;
    advFail[3]=0;
   

    struct gameState* game=newGame();
    PlantSeeds(theSeed);
    initializeGame((int)Random()%3+2,getRandomKindomCards(),theSeed,game);

    unsigned int statePos=0;
    unsigned int tryPos;
    int trystat=0;
    unsigned int failpos;

    while(statePos<100){
        tryPos=0;
        messWithGameState(game);
        while(tryPos<10){
            trystat=tryAdventurer(game);
	    
	    failpos=0;
            while(failpos<4){
	       if((  trystat & ((int) pow(2,failpos)) )>0){
	           advFail[failpos]++;
	       }
	       failpos++;
	    }

            tryPos++;
        }
        statePos++;
    }

    trystat=trystat/(10*4);


    printf("\nCases run: 1000");
    printf("\nIn %d cases, adventurer did not increase the value of the player's hand by 2",advFail[0]);
    printf("\nIn %d cases, adventurer does not conserve value of overall deck",advFail[1]);
    printf("\nIn %d cases, adventurer does not increase the number of treasure cards in the player's hand by 2",advFail[2]);
    printf("\nIn %d cases, adventurer does not conserve the overall number of treasure cards in a plyaer's deck\n", advFail[3]);

    
    return 0;
}










