CFLAGS = -Wall -fpic -coverage -lm

all: playdom player unittestresults.out

almost_all: playdom player

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c rngs.o
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

dominionTestUtilities.o: dominionTestUtilities.h dominion.o rngs.o
	gcc -c dominionTestUtilities.c -g  dominion.o rngs.o $(CFLAGS)

unittestresults.out: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 dominionTestUtilities.o player dominion.o
	unittest1 > unittestresults.out
	unittest2 >> unittestresults.out
	unittest3 >> unittestresults.out
	unittest4 >> unittestresults.out
	cardtest1 >> unittestresults.out
	cardtest2 >> unittestresults.out
	cardtest3 >> unittestresults.out
	cardtest4 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out



unittest1: dominionTestUtilities.o
	gcc -o  unittest1 unittest1.c -g dominionTestUtilities.o dominion.o rngs.o $(CFLAGS)

unittest2: dominionTestUtilities.o
	gcc -o  unittest2 unittest2.c -g dominionTestUtilities.o dominion.o rngs.o $(CFLAGS)

unittest3: dominionTestUtilities.o
	gcc -o  unittest3 unittest3.c -g dominionTestUtilities.o dominion.o rngs.o $(CFLAGS)

unittest4: dominionTestUtilities.o
	gcc -o  unittest4 unittest4.c -g dominionTestUtilities.o dominion.o rngs.o $(CFLAGS)

cardtest1: dominionTestUtilities.o
	gcc -o  cardtest1 cardtest1.c -g dominionTestUtilities.o dominion.o rngs.o $(CFLAGS)

cardtest2: dominionTestUtilities.o
	gcc -o  cardtest2 cardtest2.c -g dominionTestUtilities.o dominion.o rngs.o $(CFLAGS)

cardtest3: dominionTestUtilities.o
	gcc -o  cardtest3 cardtest3.c -g dominionTestUtilities.o dominion.o rngs.o $(CFLAGS)

cardtest4: dominionTestUtilities.o
	gcc -o  cardtest4 cardtest4.c -g dominionTestUtilities.o dominion.o rngs.o $(CFLAGS)




clean:
	rm -f *.o playdom.exe playdom test.exe test player unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so *.a *.dSYM
