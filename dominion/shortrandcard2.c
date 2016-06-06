#include "dominionTestUtilities.h"
#include "dominion.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int trySteward(struct gameState* game){

    int res=0;

    int player=game->whoseTurn;

    int choice1=(int)(Random()*4);
    int choice2=0;
    int choice3=0;


    int inHand=game->handCount[player];
    int inDeck=game->deckCount[player];
    int inDiscard=game->discardCount[player];
    int coins=game->coins;

    if(choice1==3 && inHand<2){
        choice1=(int)(Random()*2)+1;
    }

    if(choice1==3){
        choice2=(int)Random()%game->handCount[player];
        choice3=choice2;
        while(choice3==choice2){
            choice3=(int)(Random()*game->handCount[player]);
        }
    }

    addAndPlay(steward, choice1,choice2, choice3, game);

    switch (choice1){
        case 1:
        if(inDeck>=2){
                if(game->handCount[player]!=inHand+2){
               
                    res+=1;
                }
                if(game->deckCount[player]!=inDeck-2){
                    
                    res+=2;
                }
            }
            else if(inDeck+inDiscard>=2){
                if(game->discard!=0 && game->deckCount[player]!=inDeck+inDiscard-2){
                    
                    res+=4;
                }
                if(game->handCount[player]!=inHand+2){
                    
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
            break;
        case 2:
            if(game->coins!=coins+2){
	        
		
                res+=64;
            }
            break;
        case 3:
            if(game->handCount[player]!=inHand-2){
                
                res+=128;
            }
            if(game->discardCount[player]+game->deckCount[player]!=inDiscard+inDeck){
                
                res+=256;
            }
            break;
        default:
            break;
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
    int fails[9];
    int failpos=0;
    while(failpos<9){
       fails[failpos]=0;
       failpos++;
    }



    struct gameState* game=newGame();
    PlantSeeds(theSeed);
    initializeGame((int)Random()%3+2,getRandomKindomCards(),theSeed,game);

    
    int trystat=0;

    messWithGameState(game);
    trystat=trySteward(game);


    failpos=0;
    while(failpos<9){
       if(( trystat & ((int)pow(2,failpos))) > 0){
	  fails[failpos]++;
       }
       failpos++;
    }

    trystat/=20;
  
/*  
    printf("\nCases run: 1000");
    printf("\n In %d cases, steward does not add the right number of cards to the hand",fails[0]);
    printf("\n In %d cases, steward does not take the right number of cards from the deck when no shuffle is performed", fails[1]);
    printf("\n In %d cases, steward does not take the right number of cards when a shuffle is performed", fails[2]);
    printf("\n In %d cases, steward does not take add the right number of cards to hand whan a shuffle is performed", fails[3]);
    printf("\n In %d cases, steward does not exhaust deck and discard when there are 2 or fewer cards in them", fails[4]);
    printf("\n IN %d cases, steward does not give all deck and discard cardds to the hand when they have 2 or fewer cards in them", fails[5]);
    printf("\n In %d cases, steward does not add the proper amount of money to the player's coins", fails[6]);
    printf("\n In %d cases, steward does not remove cards from hand with trash option", fails[7]);
    printf("\n In %d cases, steward removes cards outside of the player's hand during the trash option\n", fails[8]);
*/


    failpos=0;
    while(failpos<9){
       if(fails[failpos]>0){
	  return 1;
       }
       failpos++;
    }

    return 0;

}


