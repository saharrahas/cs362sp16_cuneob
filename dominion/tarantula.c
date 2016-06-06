#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "rngs.c"


char* rip(char* theName){

   //printf("Attempting to rip %s",theName);
   
   FILE* theFile=fopen(theName,"r");
   if(theFile==0){
      fclose(theFile);
      printf("Failed to rip file %s",theName);
      return 0;
   }
   else{
      fseek(theFile,0,SEEK_END);
      unsigned int theEnd=ftell(theFile);

      rewind(theFile);
      char* result=malloc(sizeof(char)*(theEnd+10));

      fread(result,sizeof(char),theEnd,theFile);
      result[theEnd]=0;

      fclose(theFile);
      //printf("Succeeded in ripping file %s",theName);
      return result;
   }

}


int cut (char* theContents, int** target){

   unsigned int pos=0;
   unsigned int theSize=0;
   char primed=1;


   while(theContents[pos]!=0){
      if(primed==1 && theContents[pos]==':'){
	 theSize++;
	 primed=0;
      }
      else if(theContents[pos]=='\n'){
	 primed=1;      
      }
      pos++;
   }

   
   
   int* theArray=malloc(sizeof(int)*theSize);
   unsigned int arrayPos=0;
   theArray[arrayPos]=0;
   pos=0;
   primed=1;
   while(theContents[pos]!=0 && arrayPos<theSize){
      if(primed==1){
	 if(theContents[pos]==':'){
	    primed=0;
	    arrayPos++;
	    //printf("----TheArray [%d]=%d----",arrayPos-1,theArray[arrayPos-1]);
	 }
	 else if(theContents[pos]>='0' && theContents[pos]<='9'){
	    theArray[arrayPos]=10*theArray[arrayPos];
	    theArray[arrayPos]+=theContents[pos]-'0';
	    //printf(" [%c~%d] ",theContents[pos],theArray[arrayPos]);
	 }
      }
      else if (theContents[pos]=='\n'){
	 primed=1;
	 theArray[arrayPos]=0;
      }
      //printf("%c",theContents[pos]);
      pos++;
   }

   *target=theArray;
   return theSize;

}




void combine(int theSize, int* array1, int* array2){

   unsigned int pos=0;
   while(pos<theSize){
      array1[pos]=array1[pos]+array2[pos];
      pos++;
   }

}


void boolify(int theSize, int* theArray){
   unsigned int pos=0;
   while(pos<theSize){
      theArray[pos]= theArray[pos]!=0;
      pos++;
   }
}


float* suspicion(int theSize,int passed,int failed, int* passedArray, int* failedArray){
   float* result=malloc(sizeof(float)*theSize);
   unsigned int pos=0;
   while(pos<theSize){
      if(failed!=0 && passed!=0 && (passedArray[pos]+failedArray[pos]!=0)){
	 result[pos]=(((float)failedArray[pos])/((float)failed)) / ( (((float)passedArray[pos])/((float)passed)) + (((float)failedArray[pos])/((float)failed)) );
      }
      else{
	 if(passedArray[pos]+failedArray[pos]==0){
	    result[pos]=0;
	 }
	 else if(failed!=0){
	    result[pos]=1;
	 }
	 else if(passed!=0){
	    result[pos]=0;	 
	 }
      
      }
      //printf("\n%d:%g",pos-5,result[pos]);
      pos++;   
   }
   return result;
}

/**
void sortRank(int theSize, int* rank, float* susp){

   if(theSize<=1){
      return;
   }
      
   int lim=theSize/2;
   int* left=malloc(sizeof(int)*(lim));
   int* right=malloc(sizeof(int)*(theSize-lim));



   printf("\n\nsortRank:\n Size:%d\n lim:%d",theSize, lim);

   memcpy(left,rank,(size_t)sizeof(int)*lim);
   memcpy(right,rank+lim,(size_t)sizeof(int)*(theSize-lim));
   sortRank(lim,left,susp);
   sortRank(theSize-lim,right,susp);

   int lpos=0;
   int rpos=0;
   int pos=0;
   while( (lpos<lim || rpos<theSize-lim) && pos<theSize ){
      if(rpos>=theSize-lim || susp[right[rpos]]<susp[left[lpos]]){
	 rank[pos]=left[lpos];
	 lpos++;
      }
      else{
	 rank[pos]=right[rpos];
	 rpos++;
      }
      pos++;
   }


   free(right);
   free(left);

   return;

}
**/

void sortRank(int theSize, int* rank, float* susp){

   unsigned int pos=0;
   unsigned int scan;
   int maxim;
   int holder;
   while(pos<theSize){
      scan=pos+1;
      maxim=pos;
      while(scan<theSize-1){
	 if(susp[rank[maxim]]<susp[rank[scan]]){
	    //printf("-%g",susp[rank[pos]]);
	    maxim=scan;
	 }
	 scan++;
      }
      holder=rank[pos];
      rank[pos]=rank[maxim];
      rank[maxim]=holder;
      //printf("--%d:%g--\n",rank[pos],susp[rank[pos]]);
      pos++;
   }

}



int* rankSusp(int theSize,float*susp){

   int pos=0;
   int* rank=malloc(sizeof(int)*theSize);
   while(pos<theSize){
      rank[pos]=pos+1;
      //printf("\n%d:%g",rank[pos]-5,susp[rank[pos]]);
      pos++;
   }

   sortRank(theSize,rank,susp);
   return rank;

}


void printRanking(int theSize, int* ranking, float* susp, float thresh){


   printf("\n\n\n\n --- Most Suspicious to Least Suspicious Lines ( Suspicion >= %g )---\n\n",thresh);
   int pos=0;
   while(pos<theSize && susp[ranking[pos]]>=thresh ){
      if(ranking[pos]>5){
	 printf("\n   %d: %g",ranking[pos]-4,susp[ranking[pos]]);
      }
      pos++;
   }

   printf("\n\n - - - - - - - - - - - - - - - - - - - - - - -\n\n");

}



int main(int argc, char** argv){

   if(argc<7 || argc>7){
      printf("\n\n --- Invalid arguments --- \n Command must take the form: \ntarantula <test program> <gcov target> <sourcefile> <number of executions> <ranking threshhold> <seed> \n\n");
      return 1;
   }

   int execs=atoi(argv[4]);
   int seed=atoi(argv[6]);
   float thresh=atof(argv[5]);
   PlantSeeds(seed);

   int pos=0;

   char * command=malloc(sizeof(char)*400);
   char * covCommand=malloc(sizeof(char)*400);
   char * covFile=malloc(sizeof(char)*400);
   sprintf(covCommand,"gcov %s > /dev/null",argv[2]);
   sprintf(covFile,"%s.gcov",argv[3]);



   sprintf(command,"%s %d",argv[1],(int)(Random()*100000000));
   system(command);
   system(covCommand);

   
   char* contents=rip(covFile);
   
   int result;
   int* theArray;
   int* errorArray;

   int theSize=cut(contents,&errorArray);

   int* passArray=malloc(sizeof(int)*theSize);
   theArray=malloc(sizeof(int)*theSize);

   while(pos<theSize){
      errorArray[pos]=0;
      passArray[pos]=0;
      pos++;
   }

   system("rm -f *.gcda");



   unsigned int lastTime=clock();
   unsigned int theTime;
   unsigned int loadFrame=0;
   unsigned int load;
   unsigned int loadPos;
   unsigned int failed=0;
   unsigned int passed=0;

   printf("\n\n\n\n\n\n\n\n\nTESTING...\n\n");

   pos=0;
   while(pos<execs){

      system("rm -f *.gcda");

      theTime=clock();
      if(theTime>lastTime+10000){
	 load=pos*40/execs;
	 loadPos=0;
	 printf("\r");
	 printf("[");
	 while(loadPos<load){
	    printf("|");
	    loadPos++;
	 }
	 load=4*((pos*40)%execs)/execs;
	 if(load==1){
	    printf(".");
	 }
	 if(load==2){
	    printf(":");
	 }
	 if(load==3){
	    printf("!");
	 }
	 if(load!=0){
	    loadPos++;
	 }
	 while(loadPos<40){
	    if((loadPos+loadFrame)%4==0){
	       printf("-");
	    }
	    else{
	       printf(" ");
	    }
	    loadPos++;
	 }
	 loadFrame++;
	 printf("]");
	 fflush(stdout);
	 lastTime=theTime;
      }


      sprintf(command,"%s %d",argv[1],(int)(Random()*100000000));
      result=system(command);
      system(covCommand);

      
      free(contents);
      

      contents=rip(covFile);

      if(contents==0){
	 printf("\nBad file open");
      }

      
      free(theArray);
      cut(contents,&theArray);
      boolify(theSize,theArray);

      if(result==0){
	 passed++;
	 combine(theSize,passArray,theArray);
      }
      else{
	 failed++;
	 combine(theSize,errorArray,theArray);
      }

      pos++;
   }

   float* susp = suspicion(theSize, passed, failed, passArray, errorArray);
   int* rank = rankSusp(theSize, susp);

   printRanking(theSize,rank,susp,thresh);

   free(theArray);
   free(command);
   free(covCommand);
   free(covFile);
   free(passArray);
   free(errorArray);
   free(rank);
   free(susp);
   free(contents);

   return 0;

}


