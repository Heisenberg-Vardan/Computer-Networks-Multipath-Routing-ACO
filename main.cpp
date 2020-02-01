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

#include "ANT_INIT.h"


#define ITERATIONS		(int) 5
#define NUMBEROFANTS	(int) 4
#define ALPHA			(double) 0.5
#define BETA			(double) 0.8
// Estimation of the suspected best route.
#define Q				(double) 8
// Pheromones evaporation. 
#define RO				(double) 0.2
// Maximum pheromone random number.
#define TAUMAX			(int) 2
#define INITIALNODE		(int) 1
#define AREA_LENGTH 200
#define AREA_BREADTH 200
#define SINK 0
#define DEFAULT_SERVICE_RATE 320
#define MAX_ROUTERS 	(int) 8
#define ROUTER_RANGE 	(int) 5

using namespace std;


class node{
	public:

	int ID; 
	int servRate;
	int inpRate;
	int posX;
	int posY;
	int TR;
	double enrg;
	double depth;
	double ratio;
	vector<int> neighSet;

	public:

	node(){

		ID=0;
		inpRate=0;
		posX=0;
		posY=0;
		servRate=DEFAULT_SERVICE_RATE;
		TR=ROUTER_RANGE;
		enrg=1;
		depth=1;
		ratio=enrg/depth;
	}

	node(int id, int ir, int x, int y,double e, double d){
		ID=id;
		inpRate=ir;
		posX=x;
		posY=y;
		servRate=DEFAULT_SERVICE_RATE;
		TR=ROUTER_RANGE;
		enrg=e;	
		depth=d;
		ratio=enrg/depth;

	}
	bool isNeighbor(node j){
		double dist= pow((pow(posX-j.posX,2.0)+pow(posY-j.posY,2.0)),0.5);
		if(dist<=TR)
			return true;
		else return false;
	}	

};
node routers[MAX_ROUTERS];
int visited[MAX_ROUTERS];

void findNeighbors(int nR){

	int i=0;
	for(;i<nR;i++){			
		int j=i+1;
		for(;j<nR;j++){

			if(routers[i].isNeighbor(routers[j])){
				routers[i].neighSet.push_back(j);
				routers[j].neighSet.push_back(i);

			}

		}
	}

}



int main() {

		
	int noRtrs=MAX_ROUTERS;
	cout<<"No of Nodes: "<<noRtrs<<"\n";

	int i;

	for(i=1;i<noRtrs;i++){
		int tempIR, tempX, tempY;
		double tempD, tempE;
		tempIR=rand()%212+32;
		tempX=rand()%6+1;
		tempY=rand()%6+1;
		tempE=rand() % 100 + 1;
		tempD=rand() % 10+1;
		node temp(i,tempIR,tempX,tempY,tempE,tempD);
		routers[i]=temp;
	}
	
	int srcID=INITIALNODE;

	cout<<"\n Source Node: "<<srcID;
 
	int destID=6;
	cout<<"\n Destination Node: "<<destID;

    findNeighbors(noRtrs);
  
	for(int i=0;i<noRtrs;i++)
	{
		cout<<"\n Neighbour Of "<<i<<": ";
     	vector<int>::iterator it;
        for(it= (routers[i].neighSet).begin();it!=routers[i].neighSet.end();it++)
        {
        	cout<<" "<<*it;
		}
			   
    }


	
	ACO *ANTS = new ACO (NUMBEROFANTS, MAX_ROUTERS, ALPHA, BETA, Q, RO, TAUMAX,1);

	ANTS -> init();
	

for(i=0;i<noRtrs;i++)
{
	vector<int>::iterator it;
	it= (routers[i].neighSet).begin();
    for(;it!=routers[i].neighSet.end();it++)
		{
			int j=*it;
			ANTS -> connectCITIES (i, j);

		}
}


for(i=0;i<noRtrs;i++)
{
	ANTS -> setCITYPOSITION (routers[i].ID,  routers[i].posX, routers[i].posY, routers[i].ratio);
}

	ANTS -> printGRAPH ();
	ANTS -> printPHEROMONES ();
	ANTS -> optimize (ITERATIONS,destID);
	ANTS -> printRESULTS ();
	
}
