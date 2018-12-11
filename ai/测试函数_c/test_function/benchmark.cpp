#define _USE_MATH_DEFINES

#include "math.h"

#include "global.h"
#include "benchmark.h"
#include "malloc.h"
#include "stdlib.h"




void benchmark(population &pop,int func_num)
{
	for (int i = 0; i < NP; i++)
	{
		switch (func_num)
		{
		case 1:
			pop.indiv[i].fitness = F1(pop.indiv[i].dim);
			break;
		case 2:
			pop.indiv[i].fitness = F2(pop.indiv[i].dim);
			break;
		case 3:
			pop.indiv[i].fitness = F3(pop.indiv[i].dim);
			break;
		case 4:
			pop.indiv[i].fitness = F4(pop.indiv[i].dim);
			break;
		case 5:
			pop.indiv[i].fitness = F5(pop.indiv[i].dim);
			break;
		case 6:
			pop.indiv[i].fitness = F6(pop.indiv[i].dim);
			break;
		case 7:
			pop.indiv[i].fitness = F7(pop.indiv[i].dim);
			break;
		case 8:
			pop.indiv[i].fitness = F8(pop.indiv[i].dim);
			break;
		case 9:
			pop.indiv[i].fitness = F9(pop.indiv[i].dim);
			break;
		case 10:
			pop.indiv[i].fitness = F10(pop.indiv[i].dim);
			break;
		case 11:
			pop.indiv[i].fitness = F11(pop.indiv[i].dim);
			break;
		case 12:
			pop.indiv[i].fitness = F12(pop.indiv[i].dim);
			break;
		case 13:
			pop.indiv[i].fitness = F13(pop.indiv[i].dim);
			break;
		default:
			break;
		}
	}
}

double F1(double *x)
{
	double value = 0;
	for(int i=0; i<D; i++)
		value += x[i]*x[i];
	return value;
}
double F2(double *x)
{
	double value = 0.0;
	double temp1 = 0.0;
	double temp2 = 1.0;
	for(int i=0; i<D; i++){
		temp1 += fabs(x[i]);
		temp2 *= fabs(x[i]);
	}	
	value =temp1+temp2;
	return value;
}
double F3(double *x)
{
	double value = 0;
	double temp = 0.0;
	for(int i=0; i<D; i++){
		temp = 0.0;
		for(int j=0; j<i; j++)
			temp += x[j];
		value += temp*temp;
	}
	return value;
}
double F4(double *x)
{
	double value = fabs(x[0]);
	for(int i=1; i<D; i++){
		if(fabs(x[i])>value)	value = fabs(x[i]);
	}
	return value;
}
double F5(double *x)
{
	double value = 0;
	for(int i=0; i<D-1; i++)
		value += 100*(x[i+1]-x[i]*x[i])*(x[i+1]-x[i]*x[i])+(1-x[i])*(1-x[i]);
	return value;
}
double F6(double *x)
{
	double value = 0;
	double t1 = 0.0;
	double t2 = 0.0;
	for(int i=0; i<D; i++){
		t1 = x[i]+0.5;
		t2 = (int)t1;
		value += t2*t2;
	}
	return value;
}
double F7(double *x)
{
	double value = 0;
	for(int i=0; i<D; i++){
		value += i*pow(x[i], 4);
	}
	value = value + rand();
	return value;
}
double F8(double *x)
{
	double value = 0;
	for(int i=0; i<D; i++)
		value += -x[i]*sin(sqrt(fabs(x[i])));
	//value += D*418.9828872724337;
	return value;
}
double F9(double *x)
{
	double value = 0;
	for(int i=0; i<D; i++)
		value += x[i]*x[i]-10*cos(2*M_PI*x[i])+10;
	return value;
}
double F10(double *x)
{
	double value = 0;
	double temp1, temp2;
	temp1 = 0.0;
	temp2 = 0.0;
	for(int i=0; i<D; i++){
		temp1 += x[i]*x[i];
		temp2 += cos(2*M_PI*x[i]);
	}
	temp1/=D;
	temp1=-0.2*sqrt(temp1);
	temp1=-20*exp(temp1);
	temp2/=D;
	temp2=exp(temp2);
	value=temp1-temp2+20+M_E;
	return value;
}
double F11(double *x)
{
	double value = 0.0;
	double temp1, temp2;
	temp1 = 0.0;
	temp2 = 1.0;
	for(int i=0; i<D; i++){
		temp1 += x[i]*x[i];
		temp2 *= cos(x[i]/sqrt((double)(i+1)));
	}
	value = temp1/4000-temp2+1;
	return value;
}
double F12(double *x)
{
	double value = 0.0;
	double f1=0.0;
	double f2=0;
	double *u, *y;
	u=(double *)malloc(D*sizeof(double));
	y=(double *)malloc(D*sizeof(double));
	for(int i=0; i<D; i++){
		if(x[i]>10){u[i] = 100*pow(x[i]-10, 4);}
		else if(x[i]<-10){u[i]=100*pow((-x[i]-10), 4);}
		else {u[i]=0;}
		f1=f1+u[i];
	}
	for(int i=0; i<D; i++){
		y[i]=1+(1/4.0)*(x[i]+1);
	}
	for(int i=0; i<D-1; i++){ 
		f2=f2+((y[i]-1)*(y[i]-1))*(1+10*sin(M_PI*y[i+1])*sin(M_PI*y[i+1]));
	}
	f2=(M_PI/(D+0.0))*(f2+10*sin(M_PI*y[0])*sin(M_PI*y[0])+(y[D-1]-1)*(y[D-1]-1));
	value = f1 + f2;
	free(u);
	free(y);
	return value;;
}
double F13(double *x)
{
	double value = 0;
	double f1=0.0;
	double f2=0.0;
	double u[D];	

	for(int i=0; i<D; i++){
		if(x[i]>5){u[i] = 100*pow(x[i]-5, 4);}
		else if(x[i]<-5){u[i]=100*pow((-x[i]-5), 4);}
		else {u[i]=0;}
		f1=f1+u[i];
	}
	for(int i=0; i<D-1; i++){
		f2=f2+(x[i]-1)*(x[i]-1)*(1+sin(3*M_PI*x[i+1])*sin(3*M_PI*x[i+1]));
	}
	f2 = f2 + sin(3*M_PI*x[0])*sin(3*M_PI*x[0])+(x[D-1]-1)*(x[D-1]-1)*(1+sin(2*M_PI*x[D-1])*sin(2*M_PI*x[D-1]));
	value = 0.1*f2 + f1; 
	return value;
}