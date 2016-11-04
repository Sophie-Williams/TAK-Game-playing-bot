#include "class.h"
#include "evaluation.h"

#include<bits/stdc++.h>
using namespace std;

state::state(int size)
{
	alpha=double(LONG_MIN);
	beta=double(LONG_MAX);
	boardState.resize(size);
	depth= 0 ;
	printM=""; 
	for(int i=0;i<size;i++)
	{
		boardState[i].resize(size);	
	}
	
}
state::state()
{
	alpha=double(LONG_MIN);
	beta=double(LONG_MAX);
	
}