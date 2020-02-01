#include<cstdlib>
#include<cstdio>
#include<iostream>
#include<math.h>
#include<vector>
#include<fstream>
#include<time.h>
#include<stdlib.h>
#include <cmath>
#include <limits>
#include <climits>

#include "INIT.cpp"






class ACO {

public:

	ACO (int nAnts, int nCities, double alpha, double beta, double q, double ro, double taumax,	int initCity);
		
	virtual ~ACO ();

	void init ();
	
	void connectCITIES (int cityi, int cityj);

	void setCITYPOSITION (int city, double x, double y,double z);

	void printPHEROMONES ();

	void printGRAPH ();

	void printRESULTS ();
	
    double maxer(int x);
    
    double ratio (int x);
    
	void optimize (int ITERATIONS,int dest);



private:

	double distance (int cityi, int cityj);

	bool exists (int cityi, int cityc);

	bool vizited (int antk, int c);

	double PHI (int cityi, int cityj, int antk);
	
	double length (int antk);

	int city ();

	void route (int antk);

	int valid (int antk, int iteration);

	void updatePHEROMONES ();

	int NUMBEROFANTS, NUMBEROFCITIES, INITIALCITY;

	double ALPHA, BETA, Q, RO, TAUMAX;
	
	double BESTLENGTH,BESTRATIO;
	

	int *BESTROUTE;
	
	int **GRAPH, **ROUTES,**BR,**PRINT;

	double  **PHEROMONES, **DELTAPHEROMONES, **PROBS;
	
	double  **CITIES;
	
	Randoms *randoms;

};

