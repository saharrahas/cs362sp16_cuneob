
#include "dominion.h"


int* getRandomKindomCards();

void assertPrint(int testValue, char* passMessage, char* failMessage);

void addRandomCard(int player, struct gameState *game);

void addRandomCardToDeck(int player, struct gameState *game);
 
int getHandCoinage(struct gameState* game);

int getHandCoinCount(struct gameState* game);

int getDeckCoinage(struct gameState* game);

int getDeckCoinCount(struct gameState* game);

int getDiscardCoinage(struct gameState* game);

int getDiscardCoinCount(struct gameState* game);

void messWithGameState(struct gameState* game);

int addAndPlay(int, int, int, int, struct gameState* game);



