CFLAGS = -Wall -fpic -coverage -lm

all: playdom player unittestresults.out randomtestadventurer.out randomtestcard1.out randomtestcard2.out testdominion.out testdominion diffdominion

.PHONY: dumbClean


dumbClean:
	rm -f *.o *.gcov *.gcda *.gsno *.so *.a *.dSYM


-include dumbClean

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

unittestresults.out: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 randomtestadventurer randomtestcard1 randomtestcard2 dominionTestUtilities.o player dominion.o
	rm -f *.gcda
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

randomtestadventurer.out: randomtestadventurer
	rm -f *.gcda
	randomtestadventurer 42 > randomtestadventurer.out
	gcov dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out
	
randomtestcard1.out: randomtestcard1
	rm -f *.gcda
	randomtestcard1 42 > randomtestcard1.out
	gcov dominion.c >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out
	
randomtestcard2.out: randomtestcard2
	rm -f *.gcda
	randomtestcard2 42 > randomtestcard2.out
	gcov dominion.c >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out

testdominion.out: testdominion
	rm -f *.gcda
	testdominion 42 > testdominion.out
	gcov testdominion.c >> testdominion.out
	cat dominion.c.gcov >> testdominion.out



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

randomtestadventurer: dominionTestUtilities.o
	gcc -o randomtestadventurer randomtestadventurer.c -g dominionTestUtilities.o dominion.o rngs.o $(CFLAGS)

randomtestcard1: dominionTestUtilities.o
	gcc -o randomtestcard1 randomtestcard1.c -g dominionTestUtilities.o dominion.o rngs.o $(CFLAGS)

randomtestcard2: dominionTestUtilities.o
	gcc -o randomtestcard2 randomtestcard2.c -g dominionTestUtilities.o dominion.o rngs.o $(CFLAGS)

testdominion: dominionTestUtilities.o
	gcc -o testdominion testdominion.c -g rngs.o dominionTestUtilities.o $(CFLAGS)

diffdominion: 
	gcc -o diffdominion diffdominion.c $(CFLAGS)



clean:
	rm -f *.o *.out *.exe playdom.exe playdom test.exe diffdominion testdiff1 testdiff2 test player randomtestadventurer randomtestcard1 randomtestcard2 unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so *.a *.dSYM
