#include<bits/stdc++.h>
#include "class.h"
#include "variables.h"	
#include "evaluation.h"
#include "moveEvaluation.h"
	

using namespace std;


map<char, int> my_map6 = {{ 'a',1 },{'b',2},{'c',3},{'d',4},{'e',5},{'f',6},{'g',7}};
map<char,int> my_map7 = {{ '1',1 },{'2', 2},{ '3',3},{ '4',4},{'5',5},{'6', 6},{'7', 7},{'8', 8},{'9', 9}};

int tExpanded ;
int oppoCaptured ;
int capLeading ;
double weightsMove[7] ;
void init()
{
 weightsMove[0]= 150 ;  //oneremfor our player
 weightsMove[1]= -150; //oneremfor opponent
 weightsMove[2]= 50;  //roadblocked
 weightsMove[3]=  20 ;  //opponentcaptures
 weightsMove[4]=  10 ;   //terrotary expanded
 weightsMove[5]=  40 ;   //capLeading
 weightsMove[6]=  0 ;   //placing stones at empty neighbour
}


double blockingRoad(state &old , state &new1, int playNum )
{	
	int p1 ,q1, r1 ,p2 ,q2,r2 ;
	if(playNum==1)
	{
		p1=1; 
		q1=3; 
		r1=5; 
		p2=2; 
		q2=4; 
		r2=6; 
	}
	else
	{
		p1=2; 
		q1=4; 
		r1=6; 
		p2=1; 
		q2=3; 
		r2=5;
	}	
	int x= my_map7[new1.printM[2]] -1;
	int y= my_map6[new1.printM[1]] -1;
	state temp(boardSize);
	temp = old ;
	temp.boardState[x][y].push_back(p2);
	if(checkRoadWin(temp,playNum%2+1))
	 {
	 	if(new1.printM[0]=='C'||new1.printM[0]=='S')
	 		{
	 			if(playNum==1)
	 			return 100 ;                                //bascially a weight
	 			else
	 			return -100 ; 	
	 		}
		if(new1.printM[0]=='F')
			{
				if(playNum==1)
	 			return 10 ;                                //bascially a weight
	 			else
	 			return -10 ;
	 		}
	 }	 

	return 0 ; 
}
double emptyPlace(state &old , state &new1, int playNum)
{
	int p1 ,q1, r1 ,p2 ,q2,r2 ;
	if(playNum==1)
	{
		p1=1; 
		q1=3; 
		r1=5; 
		p2=2; 
		q2=4; 
		r2=6; 
	}
	else
	{
		p1=2; 
		q1=4; 
		r1=6; 
		p2=1; 
		q2=3; 
		r2=5;
	}
	int x= my_map7[new1.printM[2]] -1;
	int y= my_map6[new1.printM[1]] -1;
	if(new1.printM[0]=='F'||new1.printM[0]=='C'||new1.printM[0]=='S')
	{	
	if(neighboursnew(new1,make_tuple(x,y),playNum%2+1).size()>0||neighboursnew(new1,make_tuple(x,y),playNum).size()==0)
	{
		if(new1.printM[0]=='F')
		{	if(playNum==1)
			return -10 ;
			if(playNum==2)
			return 10 ;
		}
		else
		{	if(playNum==1)
			return -2 ;
			if(playNum==2)
			return 2 ;
		}
	}
	else 
	{
		if(new1.printM[0]=='F'||new1.printM[0]=='C')
		{	if(playNum==1)
			return 10 ;
			if(playNum==2)
			return -10 ;
		}
		else
		{	if(playNum==1)
			return 2 ;
			if(playNum==2)
			return -2 ;
		}
	}
	}
	else
	return 0 ;	
}
void capturingOppStack(state &old,  state &new1, int playNum )
{
	int p1 ,q1, r1 ,p2 ,q2,r2 ;
	if(playNum==1)
	{
		p1=1; 
		q1=3; 
		r1=5; 
		p2=2; 
		q2=4; 
		r2=6; 
	}
	else
	{
		p1=2; 
		q1=4; 
		r1=6; 
		p2=1; 
		q2=3; 
		r2=5;
	}	
	oppoCaptured=0 ;
	tExpanded= 0  ;
	capLeading= 0 ; 
	for(int i=0;i<boardSize;i++)
	{
		for(int j=0;j<boardSize;j++)
		{	int size1 = old.boardState[i][j].size() ;
			int size2 = new1.boardState[i][j].size() ;
			if(!(size1== size2)) 
			{
				if(size1==0&&size2>0)    //TODO:: donthttps://github.com/patman123/TAK-Game-playing-bot.git put next to opponent 
				{
					int piece2=new1.boardState[i][j][size2-1] ;
					if(piece2==p1||piece2==q1||piece2==r1)
						tExpanded++ ;
					if(piece2==r1)
						capLeading= capLeading+size2 ;	
				}
				else if(size1>0&&size2==0)
				{
					int piece2=old.boardState[i][j][size1-1] ;
					if(piece2==p1||piece2==q1||piece2==r1)
						tExpanded-- ;
					//if(piece2==r1)
					//	capLeading= capLeading-size1 ;
				}	
				else if(size1>0&&size2>0)
				{	int piece=old.boardState[i][j][size1-1] ;
					int piece2=new1.boardState[i][j][size2-1] ; 
					if((piece==p2||piece==q2||piece==r2)&&(piece2==p1||piece2==q1||piece2==r1))
						oppoCaptured++ ;                                                            //weight to be tuned
					if(piece2==r1)
						capLeading= capLeading+size2 ;
				}
			}
		} 
	}
	
	if(playNum==2)
	{
		oppoCaptured=(-1)*oppoCaptured; 
		tExpanded= (-1)*tExpanded;
		capLeading=(-1)*capLeading;
	}	
	
} 
double evaluateMove(state &old, state &new1,  int playNum)
{
	if(checkRoadWin(new1,playNum))
	{
		if(playNum==1)
		return 10000 ;
		if(playNum==2)
		return -10000  ;	
	}
	
	double oneremaining1= oneRemaining( new1 ,1);  
	double oneremaining2= oneRemaining( new1 ,2);
	capturingOppStack(old, new1, playNum); 
	double roadBlocked= blockingRoad(old , new1, playNum);  	
	double emptyPlaceval= emptyPlace(old, new1,playNum) ;
	return weightsMove[0]*oneremaining1 +weightsMove[1]*oneremaining2+ weightsMove[2]*roadBlocked+ weightsMove[3]*oppoCaptured+weightsMove[4]*tExpanded + weightsMove[5]*capLeading+weightsMove[6]*emptyPlaceval;  	

}