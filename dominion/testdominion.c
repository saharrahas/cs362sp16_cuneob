#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rngs.h"
#include "dominion.c"
#include "dominionTestUtilities.h"



const char* sayCard(int theCard){
    switch(theCard){

        case curse:
            return "curse";
        case estate:
            return "estate";
        case duchy:
            return "duchy";
        case province:
            return "province";
        case copper:
            return "copper";
        case silver:
            return "silver";
        case gold:
            return "gold";
        case adventurer:
            return "adventurer";
        case council_room:
            return "council room";
        case feast:
            return "feast";
        case gardens:
            return "gardens";
        case mine:
            return "mine";
        case remodel:
            return "remodel";
        case smithy:
            return "smithy";
        case village:
            return "village";
        case baron:
            return "baron";
        case great_hall:
            return "great hall";
        case minion:
            return "minion";
        case steward:
            return "steward";
        case tribute:
            return "tribute";
        case ambassador:
            return "ambassador";
        case cutpurse:
            return "cutpurse";
        case embargo:
            return "embargo";
        case outpost:
            return "outpost";
        case salvager:
            return "salvager";
        case sea_hag:
            return "sea hag";
        case treasure_map:
            return "treasure map";
        default:
            return "INVALID CARD";

    }
}


void buyCards(struct gameState* game){

    int done=0;
    int theCard;
    while(done==0){

        int succ;

        if((Random()>0.50)){
            theCard=(int)(Random()*1.9999)+silver;
        }
        else{
            theCard=(int)(Random()*(treasure_map+0.9999));
	}


        succ=buyCard(theCard,game);
        
	if(succ!=-1){
	   printf("\n    Bought card %s, numBuys is %d",sayCard(theCard),game->numBuys);
	}
        if( ( (game->coins<2) && (Random()*2>1) ) ||  game->numBuys<=0 ){
            done=1;
        }

    }

}


void useCard(struct gameState* game){

    int otherCard;
    int pos;
    int theHandCard;
    int theSuppCard;
    int lim;
    int theFirst;
    int cardOne;
    int cardTwo;
    int handPos;

    int tryCounter=0;

    do{
        handPos=(int)(Random()*(game->handCount[game->whoseTurn]-0.001));
	tryCounter++;
    }
    while(game->hand[game->whoseTurn][handPos]<adventurer && tryCounter<10);
    if(tryCounter==10){
       printf("Bluh");
       game->numActions--;
       return;
    }

    int theCard=game->hand[game->whoseTurn][handPos];

    switch(theCard){
        case feast:
            //Ch1: Extant card in supply with cost 5 or less
            do{
                otherCard=(int)(Random()*(treasure_map+0.9999));
		tryCounter++;
            }
            while( supplyCount(otherCard,game)>0 && getCost(otherCard)>5 && tryCounter<15);
	    if(tryCounter==15){
	       game->numActions--;
	       return;
	    }
            playCard(handPos,otherCard,0,0,game);
            break;

        case baron:
            //Ch1: 0 or 1
            playCard(handPos,(int)(Random()*1.9999),0,0,game);
            break;

        case embargo:
            //Ch1: Card in supply
            playCard(handPos,(int)(Random()*(treasure_map+0.9999)),0,0,game);
            break;

        case salvager:
            //Ch1: Card in hand
            playCard(handPos,(int)(Random()*(game->handCount[game->whoseTurn]+0.9999)),0,0,game);
            break;

        case mine: //Requires treasure in hand
            //Ch1: Treasure we're tossing (in hand)
            //Ch2: Treasure we're getting (in supply)
            pos=0;
            theHandCard=-1;
            lim=game->handCount[game->whoseTurn];
            while(pos<lim){
                if(game->hand[game->whoseTurn][pos]==copper){
                    theHandCard=pos;
                    theSuppCard=silver;
                    break;
                }
                if(game->hand[game->whoseTurn][pos]==silver){
                    theHandCard=pos;
                    theSuppCard=gold;
                    break;
                }
                pos++;
            }
            if(theHandCard==-1){
                return;
            }
            playCard(handPos,theHandCard,theSuppCard,0,game);
            break;

        case remodel:
            //Ch1: Card we're tossing (in hand)
            //Ch2: Card we're getting (in supply)
            playCard(handPos,
                     (int)(Random()*(game->handCount[game->whoseTurn]+0.9999)),
                     (int)(Random()*(treasure_map+0.9999)),
                     0,
                     game);
            break;
        case minion:
            //Ch1 xor Ch2, first gets 2 gold, other does weird BS
            if(Random()>0.5){
                playCard(handPos,1,0,0,game);
            }
            else{
                playCard(handPos,0,1,0,game);
            }
            break;
        case ambassador:
            //Ch1: a card in hand
            //Ch2= [0,2]
            playCard(handPos,
                     (int)(Random()*(game->handCount[game->whoseTurn]+0.9999)),
                     (int)(Random()*2.9999),0,game);
            break;
        case steward:
            //Ch1= [1,3]
            //Ch2: if Ch1=3, a card in hand
            //Ch3: if Ch1=3, a card in hand
            theFirst=1+(int)(Random()*2.9999);
            if(theFirst==3){
                cardOne=(int)(Random()*(game->handCount[game->whoseTurn]+0.9999));
                cardTwo=(int)(Random()*(game->handCount[game->whoseTurn]+0.9999));
                playCard(handPos,theFirst,cardOne,cardTwo,game);
            }
            else{
                playCard(handPos,theFirst,0,0,game);
            }
            break;
        default:
            playCard(handPos,0,0,0,game);
    }

    printf("\nPlayed card %s",sayCard(theCard));

}



void playATurn(struct gameState* game){

    while(game->numActions>0){
        printf("Trying to use card");
        useCard(game);
	getCount(game);
    }
    printf("Trying to buy");
    buyCards(game);

    printf("Ending Turn");
    endTurn(game);
    getCount(game);

}


void playAGame(){

    struct gameState* game=newGame();
    int* theKingdomCards=getRandomKindomCards();
    int pos=0;
    printf("Initialization Card List:");
    while(pos<10){
       printf("\n   -%s",sayCard(theKingdomCards[pos]));
       pos++;
    }

    initializeGame((int)(Random()*2.99999)+2,theKingdomCards,(int)(Random()*1000000),game);


    gamePrint(game);


    pos=-10000000;
    while(pos<100000000){
       pos++;
    }


    while(isGameOver(game)==0){
        pos=0;
	while(pos<10000000){
	   pos++;
	}
        printf("\n-----Next Turn-----");
        playATurn(game);
    }
    gamePrint(game);
    pos=0;
    while(pos<=treasure_map){
       printf("\n  %s: %d",sayCard(pos),supplyCount(pos,game));
       pos++;
    }
    free(game);

}



int main(int argc,char** argv){

    PlantSeeds(atoi(argv[1]));
    playAGame();
    printf("\nGame completed\n");
    return 0;

}





