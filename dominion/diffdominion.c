#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


void doSetup(char* imp1,char* imp2){

   char move1_4[300];
   char cp2[300];
   char cp3[300];
   char move4_1[300];
   //char move5_6[300];
   //char move6_5[300];

   sprintf(move1_4,"mv dominion.c Temporary_Dominion_%d.c",getpid());
   //sprintf(move5_6,"mv testdominion Temporary_Testdominion_%d.c",getpid());
   sprintf(cp2,"cp %s temp_dominion1.c",imp1);
   sprintf(cp3,"cp %s temp_dominion2.c",imp2);
   sprintf(move4_1,"mv Temporary_Dominion_%d.c dominion.c",getpid());
   //sprintf(move6_5,"mv Temporary_Testdominion_%d.c testdominion",getpid());



   system(cp2);
   system(cp3);


   system(move1_4);
   //system(move5_6);
   system("rm -f dominion.c");
   system("rm temp_dominion1.c dominion.c");
   system("make testdominion");
   system("mv testdominion testdiff1");
   system("rm -f dominion.c");
   system("mv temp_dominion2.c dominion.c");
   system("make testdominion");
   system("mv testdominion testdiff2");
   system("rm -f dominion.c temp_dominion1.c temp_dominion2.c");
   system(move4_1);
   //system(move6_5);
   


}


int runTest(int theSeed){


   char test1[300];
   char test2[300];

   system("rm testdiff1.out testdiff2.out diffdominion.out");

   sprintf(test1,"timeout 5 testdiff1 %d > testdiff1.out",theSeed);
   sprintf(test2,"timeout 5 testdiff2 %d > testdiff2.out",theSeed);

   printf("\n\n\n\n--- Wait for 10 seconds in case of timeout ---\n\n\n");
   fflush(stdout);
   system(test1);
   system(test2);
   system("diff testdiff1.out testdiff2.out > diffdominion.out");

   FILE * theFile=fopen("diffdominion.out","r");

   if(theFile==0){
      return 0;
   }
   fseek(theFile,0,SEEK_END);
   if(ftell(theFile)==0){
      fclose(theFile);
      return 0;
   }
   fclose(theFile);
   return 1;

}



int main(int argc, char** argv){


   if(argc!=4){
      printf("\nBad arguments given, arguments must be: diffdominion [implementation 1] [implementation 2] [seed]\n");
      return -1;
   }

   doSetup(argv[1],argv[2]);

   int result=runTest(atoi(argv[3]));

   if(result==0){
      printf("\n\n --- TEST PASSED --- \n\n\n\n");
      return 0;
   }
   printf("\n\n --- TEST FAILED --- \n\n\n\n");

   return 0;

}





