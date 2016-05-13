#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "dominionTestUtilities.h"
#include "rngs.h"
#include "dominion.h"


int* getRandomKindomCards(){

    int* k = malloc(10 * sizeof(int));
    srand(clock()+time(0));

    int pos=0;
    int checkPos;
    while(pos<10){
        checkPos=pos-1;
        k[pos]=(rand())%treasure_map+1;
        while(checkPos>=0){
            if(k[checkPos]==k[pos]){
                checkPos=pos-1;
                k[pos]=(rand())%(treasure_map+1);
            }
            else{
                checkPos--;
            }
        }
        pos++;
    }

    return k;

}




void assertPrint(int testValue, char* passMessage, char* failMessage){

    if(testValue!=0){
        printf("\n%s",passMessage);
    }
    else{
        printf("\n%s",failMessage);
    }

}



void addRandomCard(int player, struct gameState *game) {

    //PlantSeeds(clock() xor time());
    int handTop = game->handCount[player];
    game->hand[player][handTop] = (int)(Random()*(treasure_map+1));
    game->handCount[player]++;

}


void addRandomCardToDeck(int player, struct gameState *game) {

    //PlantSeeds(clock() xor time());
    int deckTop = game->deckCount[player];
    game->deck[player][deckTop] =(int)(Random()*(treasure_map+1));
    game->deckCount[player]++;

}

void addRandomCardToDiscard(int player, struct gameState *game) {

    int discTop = game->discardCount[player];
    game->discard[player][discTop] =(int)(Random()*(treasure_map+1));
    game->discardCount[player]++;

}

int addAndPlay(int theCard, int choice1, int choice2, int choice3, struct gameState* game){

    if(theCard<adventurer || theCard>treasure_map){
        return -1;
    }

    game->phase=0;

    int thePlayer= game->whoseTurn;
    game->hand[thePlayer][game->handCount[thePlayer]++]= theCard;
    game->numActions++;

    playCard(game->handCount[thePlayer]-1,choice1,choice2,choice3,game);


    return 0;

}


int randomAddAndPlay(int theCard, struct gameState* game){

    //PlantSeeds(clock() xor time());

    game->phase=0;
    game->whoseTurn=(int)(Random()*game->numPlayers);
    addAndPlay(theCard,Random()*200,Random()*200,Random()*200,game);

    return 0;

}


int superRandomAddAndPlay(struct gameState* game){

    //PlantSeeds(clock() xor time());

    game->phase=0;
    game->whoseTurn=(int)(Random()*game->numPlayers);
    int theCard=(int)(Random()*(treasure_map-adventurer)+adventurer);
    addAndPlay(theCard,Random()*200,Random()*200,Random()*200,game);

    return 0;

}




void gamePrint(struct gameState* game){


    printf("\n----------GAME STATE----------");
    int pos=0;
    int inpos;
    printf("\n\tCurrent Player: %d",game->whoseTurn);
    printf("\n\t\tActions: %d",game->numActions);
    printf("\n\t\tBuys: %d", game->numBuys);
    printf("\n\t\tCoins: %d", game->coins);
    printf("\n\t\tPhase: %d", game->phase);

    while(pos<game->numPlayers){
    	inpos=0;
	printf("\n\tPlayer: %d",pos);
	printf("\n\tHandCount: %d",game->handCount[pos]);
	printf("\n\tHand:");
	while(inpos<game->handCount[pos]){
	   printf("\n\t\t%d : %d ",inpos,game->hand[pos][inpos]);
	   inpos++;
	}
	inpos=0;
	printf("\n\tDeckCount: %d",game->deckCount[pos]);
	printf("\n\tDeck:");
	while(inpos<game->deckCount[pos]){
	    printf("\n\t\t%d : %d",inpos,game->deck[pos][inpos]);
	    inpos++;
	}
	inpos=0;
	printf("\n\tDiscardCount %d",game->discardCount[pos]);
	printf("\n\tDiscard:");
	while(inpos<game->discardCount[pos]){
	
	   printf("\n\t\t%d : %d",inpos,game->discard[pos][inpos]);
	   inpos++;	
	}
    	pos++;
    }
    printf("\n------------------------------");

}






void messWithGameState(struct gameState* game){


    unsigned int pos=0;
    game->whoseTurn=((int)Random())%(game->numPlayers);

    while(pos<=treasure_map){
        game->supplyCount[pos]=(int)(Random()*10.99);
        if(game->supplyCount[pos]==0){
            game->supplyCount[pos]=-1;
        }
        pos++;
    }

    pos=0;
    while(pos<=treasure_map){
        game->embargoTokens[pos]=(int)(Random()*19.99)-10;
        if(game->embargoTokens[pos]<0){
            game->embargoTokens[pos]=0;
        }
        pos++;
    }

    if((int)(Random()*24.99)==0){
        game->outpostPlayed=1;
    }
    else{
        game->outpostPlayed=0;
    }


    if((int)(Random()*24.99)==0){
        game->outpostTurn=1;
    }
    else{
        game->outpostTurn=0;
    }

    game->phase=0;

    game->numActions=(int)(Random()*4.99);

    game->coins=(int)(Random()*20)-5;
    if(game->coins<0){
        game->coins=0;
    }

    game->numBuys=(int)(Random()*5);

    pos=0;
    while(pos<game->numPlayers){
        game->handCount[pos]=0;
        game->discardCount[pos]=0;
        game->deckCount[pos]=0;
        pos++;
    }

    int lim= (int)(Random()*(game->numPlayers * 5));
    pos=0;
    while(pos<lim){
        addRandomCard((int)(Random()*(game->numPlayers)),game);
        pos++;
    }


    lim= (int)(Random()*(game->numPlayers * 10));
    pos=0;
    while(pos<lim){
        addRandomCardToDeck((int)(Random()*(game->numPlayers)),game);
        pos++;
    }

    lim= (int)(Random()*(game->numPlayers * 10));
    pos=0;
    while(pos<lim){
        addRandomCardToDiscard((int)(Random()*(game->numPlayers)),game);
        pos++;
    }

    //gamePrint(game);

}


int getHandCoinage(struct gameState* game){

    int pos=0;
    int player=game->whoseTurn;
    int lim=game->handCount[player];
    int coinage=0;
    while (pos<lim){
        switch(game->hand[player][pos]){
            case gold:
                coinage++;
            case silver:
                coinage++;
            case copper:
                coinage++;
            default:
                break;
        }
        pos++;
    }
    return coinage;

}

int getDeckCoinage(struct gameState* game){

    int pos=0;
    int player=game->whoseTurn;
    int lim=game->deckCount[player];
    int coinage=0;
    while (pos<lim){
        switch(game->deck[player][pos]){
            case gold:
                coinage++;
            case silver:
                coinage++;
            case copper:
                coinage++;
            default:
                break;
        }
        pos++;
    }
    return coinage;
}

int getDiscardCoinage(struct gameState* game){

    int pos=0;
    int player=game->whoseTurn;
    int lim=game->discardCount[player];
    int coinage=0;
    while (pos<lim){
        switch(game->discard[player][pos]){
            case gold:
                coinage++;
            case silver:
                coinage++;
            case copper:
                coinage++;
            default:
                break;
        }
        pos++;
    }
    return coinage;
}


int getHandCoinCount(struct gameState* game){

    int pos=0;
    int player=game->whoseTurn;
    int lim=game->handCount[player];
    int coinage=0;
    while (pos<lim){
        switch(game->hand[player][pos]){
            case gold:
                coinage++;
                break;
            case silver:
                coinage++;
                break;
            case copper:
                coinage++;
                break;
            default:
                break;
        }
        pos++;
    }
    return coinage;

}

int getDeckCoinCount(struct gameState* game){

    int pos=0;
    int player=game->whoseTurn;
    int lim=game->deckCount[player];
    int coinage=0;
    while (pos<lim){
        switch(game->deck[player][pos]){
            case gold:
                coinage++;
                break;
            case silver:
                coinage++;
                break;
            case copper:
                coinage++;
                break;
            default:
                break;
        }
        pos++;
    }
    return coinage;
}

int getDiscardCoinCount(struct gameState* game){

    int pos=0;
    int player=game->whoseTurn;
    int lim=game->discardCount[player];
    int coinage=0;
    while (pos<lim){
        switch(game->discard[player][pos]){
            case gold:
                coinage++;
                break;
            case silver:
                coinage++;
                break;
            case copper:
                coinage++;
                break;
            default:
                break;
        }
        pos++;
    }
    return coinage;
}






