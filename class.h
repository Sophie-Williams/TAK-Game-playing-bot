#include<bits/stdc++.h>
using namespace std; 
class state{
public:
	state* parent; 
	vector< vector< vector< int > > > boardState;
	double eval ;			
	double alpha, beta ;
	int depth;
	string printM ;
	//define a constructor function
	//error vecotr 
	state(int size);
	state() ;
	bool operator < (const state& st) const
    {
        return (eval > st.eval);
    }
};
