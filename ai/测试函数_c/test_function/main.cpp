#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "global.h"
#include "Algorithm.h"


int main()
{
    clock_t start,finish;
    double totaltime;
    start=clock();
	srand( (unsigned)time(NULL) );
	printf("\nwait_begin....\n");

    for (int i = 1; i<=13; i++)
    {
       
		
			printf("Function%d:-----------\n",i);
				alg(i);
		

    } 
	printf("wait_end");

    finish=clock();
    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
    printf("%f",totaltime);
    system("pause");
    return 0;
}