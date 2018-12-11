#ifndef _GLOBAL_H
#define _GLOBAL_H

#define NP 10
#define D 30

#define MAXFEs 200000
#define SubSetSize 1

struct individual
{
	double dim[D];   
	double fitness; 
	double F; 
	double CR;
	int strategy;
	int stagation;
};

struct population
{
	individual indiv[NP];
	individual bestIndiv;
};

#endif