
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <vector>
#include <algorithm>

#include "global.h"
#include "benchmark.h"


double LOWBOUND[21] = {-100,-10,-100,-100,-30,-100,-1.28,-500,-5.12,-32,-600,-50,-50,-65.536,-5,-5,-5,-2,-10,-10,-10};
double UPBOUND[21] = {100,10,100,100,30,100,1.28,500,5.12,32,600,50,50,65.536,-5,-5,-2,-10,-10,-10};


void alg(int funNum)
{
    int FEs;
    population pop;

    /********Initialization**********/
    FEs = 0;

    for (int i = 0; i < NP; i++)
    {
        for (int j = 0; j < D; j++)
        {
            pop.indiv[i].dim[j] = LOWBOUND[funNum-1] + rand() * (UPBOUND[funNum-1] - LOWBOUND[funNum-1]);
        }	
       
		
    }
    benchmark(pop, funNum);
	for (int i = 0; i < NP; i++)
		printf("%.6f\n", pop.indiv[i].fitness);

    
}
