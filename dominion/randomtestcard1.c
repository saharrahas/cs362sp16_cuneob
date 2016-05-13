#include "dominionTestUtilities.h"
#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int trySmithy (struct gameState* game){

    int res=0;

    int player=game->whoseTurn;
    int inHand=game->handCount[player];
    int inDeck=game->deckCount[player];
    int inDiscard=game->discardCount[player];


    addAndPlay(smithy,0,0,0,game);


    if(inDeck>=3){
        if(game->handCount[player]!=inHand+3){
	    res+=1;
        }
        if(game->deckCount[player]!=inDeck-3){
	    res+=2;
	}
    }
    else if(inDeck+inDiscard>=3){
        if(game->discard!=0 && game->deckCount[player]!=inDeck+inDiscard-3){
	    res+=4;
        }
        
        if(game->handCount[player]!=inHand+3){
	    res+=8;
        }

    }
    else{
        if(game->discardCount[player] + game->deckCount[player]!=0){
	    res+=16;
        }
        if(game->handCount[player]!=inHand+inDeck+inDiscard){
	    res+=32;
        }
    }

    if((int)Random()%2==0){
        endTurn(game);
    }

    return res;

}




int  main(int argc, char *argv[]){

    if(argc<2){
        printf("Insufficient arguments");
        return 0;
    }

    int theSeed=atoi(argv[1]);
    int smithyfail[6];
    smithyfail[0]=0;
    smithyfail[1]=0;
    smithyfail[2]=0;
    smithyfail[3]=0;
    smithyfail[4]=0;
    smithyfail[5]=0;


    struct gameState* game=newGame();
    PlantSeeds(theSeed);
    initializeGame((int)Random()%3+2,getRandomKindomCards(),theSeed,game);

    unsigned int statePos=0;
    unsigned int tryPos;
    unsigned int failpos;
    int tryStat=0;

    while(statePos<100){
        tryPos=0;
        messWithGameState(game);
        while(tryPos<10){
            tryStat=trySmithy(game);

	    failpos=0;
	    while(failpos<6){
	       if((tryStat & ((int)pow(2,failpos)))>0){
	          smithyfail[failpos]++;
	       }
	       failpos++;
	    }


            tryPos++;
        }
        statePos++;
    }

    printf("\nCases run: 1000");
    printf("\nIn %d cases, smithy failed to properly add cards to the player's hand.", smithyfail[0]+smithyfail[3]);
    printf("\nIn %d cases, smithy failed to properly take cards from the deck when there were enough in the deck", smithyfail[1]);
    printf("\nIn %d cases, smithy failed to properly take cards from the deck when there had to be a re-shuffle", smithyfail[2]);
    printf("\nIn %d cases, smithy failed to properly take cards from thec deck and discard when there were not enough cards", smithyfail[4]);
    printf("\nIn %d cases, smithy failed to properly exhaust the deck and discard when they were too small and failed to transfer the cards to the player's hand\n", smithyfail[5]);

    return 0;

}
