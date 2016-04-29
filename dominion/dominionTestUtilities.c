#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "dominionTestUtilities.h"
#include "rngs.h"
#include "dominion.h"


int* getRandomKindomCards(){

    int* k = malloc(10 * sizeof(int));
    srand(clock()+time(0));

    unsigned int pos=0;
    unsigned int checkPos;
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

    int handTop = game->handCount[player];
    game->hand[player][handTop] = ((int)Random())%(treasure_map+1);;
    game->handCount[player]++;

}


void addRandomCardToDeck(int player, struct gameState *game) {

    int deckTop = game->deckCount[player];
    game->deck[player][deckTop] =((int)Random())%(treasure_map+1);;
    game->deckCount[player]++;

}



