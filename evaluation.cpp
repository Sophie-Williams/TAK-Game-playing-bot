#include<bits/stdc++.h>
#include "class.h"
#include "variables.h"	
#include "evaluation.h"


using namespace std;

vector<int> weights;
double learningR=0.00025; 
double influence10;
double influence11;

double influence20;
double influence21;

double facefeat10;
double facefeat11;
double facefeat12;
double facefeat13;
double facefeat14;

double facefeat20;
double facefeat21;
double facefeat22;
double facefeat23;
double facefeat24;

double ss;
double oneremaining1;
double oneremaining2;
void writeWeights()
{
  /*ofstream myfile;
  myfile.open ("weights.txt");
  for(int i=0;i<weights.size();i++)
  { myfile <<weights[i] <<" ";
   	cerr<<weights[i]<<" ";
   }
   cerr<<weights.size()<<endl; 
  myfile.close();*/

}
void initialWeights(int player)
{	
	////weights.resize(10); 
	//std::ifstream ifile;
	std::ifstream ifile("weights.txt", std::ios::in);
	if(player==2)
	std::ifstream ifile("weights2.txt", std::ios::in);
	//else
	//ifile	std::ifstream ifile2("weights1.txt", std::ios::in);
    std::vector<double> scores;

    //check to see that the file was opened correctly:
    if (!ifile.is_open()) {
        std::cerr << "There was a problem opening the input file!\n";
        exit(1);//exit or do additional error checking
    }

    double num = 0.0;
    //keep storing values from the text file so long as data exists:
    while (ifile >> num) {
        weights.push_back(num);
        cerr<<num<<endl; 
    }
    ifile.close();
    cerr<<weights.size()<<endl;
}

void train(state s, double trueVal)
{
	/*double evaluation= evalFxn(s); 

//val=weights[0]*influence0+weights[1]*influence1+weights[2]*influence2+weights[3]*(facefeat10-facefeat20)+weights[4]*(facefeat11-facefeat21)+weights[5]*(facefeat12-facefeat22)+weights[6]*(facefeat13-facefeat23)+weights[7]*ss+weights[8]*oneremaining1+weights[9]*oneremaining2;
	if(trueVal==10000000)
	{
		trueVal=9000; 
	}
	else if(trueVal==-10000000)
	{
		trueVal=-9000;
	}	
	weights[0]=weights[0]+learningR*2*(trueVal-evaluation)*influence0;
	weights[1]=weights[1]+learningR*2*(trueVal-evaluation)*influence1; 
	weights[2]=weights[2]+learningR*2*(trueVal-evaluation)*influence2; 
	weights[3]=weights[3]+learningR*2*(trueVal-evaluation)*(facefeat10);  //-facefeat20
	weights[4]=weights[4]+learningR*2*(trueVal-evaluation)*(facefeat11);  //-facefeat21
	weights[5]=weights[5]+learningR*2*(trueVal-evaluation)*(facefeat12);  //-facefeat22 
	weights[6]=weights[6]+learningR*2*(trueVal-evaluation)*(facefeat13);  //-facefeat23
	weights[7]=weights[7]+learningR*2*(trueVal-evaluation)*(facefeat14);  //-facefeat24


	weights[8]=weights[8]+learningR*2*(trueVal-evaluation)*ss;	
	weights[9]=weights[9]+learningR*2*(trueVal-evaluation)*oneremaining1;
	weights[10]=weights[10]+learningR*(2)*(trueVal-evaluation)*oneremaining2;

	weights[11]=weights[11]+learningR*(2)*(trueVal-evaluation)*(facefeat20);  //-facefeat20
	weights[12]=weights[12]+learningR*(2)*(trueVal-evaluation)*(facefeat21);  //-facefeat21
	weights[13]=weights[13]+learningR*(2)*(trueVal-evaluation)*(facefeat22);  //-facefeat22 
	weights[14]=weights[14]+learningR*(2)*(trueVal-evaluation)*(facefeat23);  //-facefeat23
	weights[15]=weights[15]+learningR*(2)*(trueVal-evaluation)*(facefeat24);  //-facefeat24
	cerr<<"own features values"<<facefeat10<<" "<<facefeat11<<" "<<facefeat12<<" "<<facefeat13<<endl;
	cerr<<"ffeatures values"<<facefeat20<<" "<<facefeat21<<" "<<facefeat22<<" "<<facefeat23<<endl;
*/
}

void influence(state &s, int num)
{
	double numEmpty=0.0;
	double numMyStones=0.0;
	double numOppStones=0.0;
	double numMySurrOpp=0.0;

	double flat = 0.0 ; 	//represents number of flatstones on top
	double standing= 0.0 ;
	double cap= 0.0 ;
	double hard = 0.0;
	double soft=0.0;
	int mystack=0;
	
	int n= s.boardState.size();

	int p,q,r;
	if(num==1)
	{
		p= 1 ;
		q= 3;
		r= 5 ;	
	}  
	else{
		p= 2 ;
		q= 4;
		r= 6 ;	
	}
	for (int i=0;i<n;i++)
	{
		for (int j=0;j<n;j++)
		{
			double cum=0.0;
			double cumopponent=0.0;
			vector<int> temp=s.boardState[i][j];
			if(temp.size()!=0)
			{
				int stoneNumber=temp[temp.size()-1];
				if(stoneNumber==p || stoneNumber==q || stoneNumber==r)
				{
					if(stoneNumber==p)
						flat+=1;
					else if(stoneNumber==q)
						standing+=1;
					else if(stoneNumber==r)
						cap=1;

					if(i!=0){
						vector<int> t= s.boardState[i-1][j];
						if(t.size()==0)
							numEmpty+=1;
						else{
							stoneNumber=t[t.size()-1];
							if(stoneNumber==p || stoneNumber==q || stoneNumber==r)
								numMyStones+=1;
							else
								numOppStones+=1;
						}
					}
					if(i!=n-1){
						vector<int> t= s.boardState[i+1][j];
						if(t.size()==0)
							numEmpty+=1;
						else{
							stoneNumber=t[t.size()-1];
							if(stoneNumber==p || stoneNumber==q || stoneNumber==r)
								numMyStones+=1;
							else
								numOppStones+=1;
						}
					}
					if(j!=0){
						vector<int> t = s.boardState[i][j-1];
						if(t.size()==0)
							numEmpty+=1;
						else{
							stoneNumber=t[t.size()-1];
							if(stoneNumber==p || stoneNumber==q || stoneNumber==r)
								numMyStones+=1;
							else
								numOppStones+=1;
						}
					}
					if(j!=n-1){
						vector<int> t = s.boardState[i][j+1];
						if(t.size()==0)
							numEmpty+=1;
						else{
							stoneNumber=t[t.size()-1];
							if(stoneNumber==p || stoneNumber==q || stoneNumber==r)
								numMyStones+=1;
							else
								numOppStones+=1;
						}
					}
				}
				/*else
				{
					if(i!=0){
						vector<int> t= s.boardState[i-1][j];
						if(t.size()!=0){
							stoneNumber=t[t.size()-1];
							if(stoneNumber==p || stoneNumber==q || stoneNumber==r)
								numMySurrOpp+=1;
						}
					}
					if(i!=n-1){
						vector<int> t= s.boardState[i+1][j];
						if(t.size()!=0){
							stoneNumber=t[t.size()-1];
							if(stoneNumber==p || stoneNumber==q || stoneNumber==r)
								numMySurrOpp+=1;
						}
					}
					if(j!=0){
						vector<int> t = s.boardState[i][j-1];
						if(t.size()!=0){
							stoneNumber=t[t.size()-1];
							if(stoneNumber==p || stoneNumber==q || stoneNumber==r)
								numMySurrOpp+=1;
						}
					}
					if(j!=n-1){
						vector<int> t = s.boardState[i][j+1];
						if(t.size()!=0){
							stoneNumber=t[t.size()-1];
							if(stoneNumber==p || stoneNumber==q || stoneNumber==r)
								numMySurrOpp+=1;
						}
					}
				}*/
				if(temp.size()>=2)
				{
					int top=0; //top 1 means my 

					if(temp[temp.size()-1]==p||temp[temp.size()-1]==q||temp[temp.size()-1]==r)
					{
						top=1;
						mystack+=1;
					}
					if(top==1)
					{
						int x = temp.size()-boardSize;
						for(int d=max(0,x);d<temp.size();d++)
						{
							if(temp[d]==p||temp[d]==q||temp[d]==r)
								cum+=1;
							else
								cumopponent+=1;
						}
					}
					
					if(cum>=cumopponent)
						hard+=cum-cumopponent/2;
					else
						soft+=cumopponent-cum/2;
				}
			}
		}
	}
	//double result[3];

	if(num==1)
	{
		influence10=numEmpty;
		influence11=numMyStones-numOppStones;

		facefeat10=flat;
		facefeat11=standing;
		facefeat12=cap;
		facefeat13=hard;
		facefeat14=soft;

		//cerr<<influence10<<" "<<influence11<<" "<<facefeat10<<" "<<facefeat11<<" "<<facefeat12<<" "<<facefeat13<<" "<<facefeat14<<endl;
	}
	else
	{
		influence20=numEmpty;
		influence21=numMyStones-numOppStones;

		facefeat20=flat;
		facefeat21=standing;
		facefeat22=cap;
		facefeat23=hard;
		facefeat24=soft;

		//cerr<<influence20<<" "<<influence21<<" "<<facefeat20<<" "<<facefeat21<<" "<<facefeat22<<" "<<facefeat23<<" "<<facefeat24<<endl;
	}
}

/*void facefeat(state &s, int num) //returns the number of facing stones
{	
	int p,q,r;
	if(num==1)
	{
		p= 1 ;
		q= 3;
		r= 5 ;	
	}  
	else{
		p= 2 ;
		q= 4;
		r= 6 ;	
	}
	double flat = 0.0 ; 	//represents number of flatstones on top
	double standing= 0.0 ;
	double cap= 0.0 ;
	double hard = 0.0;
	double soft=0.0;
	//double cum= 0.0 ;		
	//double cumopponent=0.0;
	int mystack=0;
	
	int boardSize=s.boardState.size();
	for(int i= 0 ;i<boardSize;i++)
	{   for(int j=0;j<boardSize;j++)
		{	
			double cum= 0.0 ;		// in my controlled stack the total number of my stones
			double cumopponent=0.0;
			int numstones=s.boardState[i][j].size();
			if(numstones>0)
			{	 
				int y= s.boardState[i][j][numstones-1] ;
				if(y==p)
				flat=flat+1;
				else if(y==q)
				standing=standing+1;
				else if(y==r)
				cap=1;			
			}
			if(numstones>=2)
			{	
				int top=0; //top 1 means my and 2 means opponent

				if(s.boardState[i][j][numstones-1]==p||s.boardState[i][j][numstones-1]==q||s.boardState[i][j][numstones-1]==r)
				{
					top=1;
					mystack+=1;
				}

				if(top==1)
				{
					for(int d=max(0,numstones-boardSize);d<numstones;d++)
					{
						if(s.boardState[i][j][d]==p||s.boardState[i][j][d]==q||s.boardState[i][j][d]==r)
							cum+=1;
						else
							cumopponent+=1;
					}
				}
				
				if(cum>=cumopponent)
					hard+=cum-cumopponent;
				else
					soft+=cumopponent-cum;
			}
		}
	}

	if(num==1)
	{
		facefeat10=flat;
		facefeat11=standing;
		facefeat12=cap;
		facefeat13=hard;
		facefeat14=soft;
	}
	else
	{
		facefeat20=flat;
		facefeat21=standing;
		facefeat22=cap;
		facefeat23=hard;
		facefeat24=soft;
	}

	//TODO - return hard and soft values, and also mystack; something like mystack*(hard-soft)
	//return result;
	//return weights[3]*flat+weights[4]*standing+weights[5]*cap+weights[6]*cum;
}
*/

vector<tuple<int,int> > neighboursnew(state &s, tuple<int,int> t, int who)		//returns neighbours with flat or standing or cap
{
	int n= s.boardState.size();
	vector<tuple<int,int> > result;
	int stoneNum;
	int row=get<0>(t);
	int column=get<1>(t);
	int p,q,r;
	if(who==1){
		p=1;
		q=3;
		r=5;
	}
	else{
		p=2;
		q=4;
		r=6;
	}

	if(row!=0)
	{
		if(s.boardState[row-1][column].size()==0)
			goto l2 ;
		stoneNum=s.boardState[row-1][column][s.boardState[row-1][column].size()-1];	
		if(stoneNum==p  ||  stoneNum==q || stoneNum==r)
		{
			result.push_back(make_tuple(row-1,column));
		}
	}
	l2: ;
	if(row!=n-1)
	{
		if(s.boardState[row+1][column].size()==0)
			goto l3 ;
		
		stoneNum=s.boardState[row+1][column][s.boardState[row+1][column].size()-1];	
		if(stoneNum==p  ||  stoneNum==q || stoneNum==r)
		{
			result.push_back(make_tuple(row+1,column));
		}
	}
	l3:;

	if(column!=0)
	{
		if(s.boardState[row][column-1].size()==0)
			goto l4 ;
		
		stoneNum=s.boardState[row][column-1][s.boardState[row][column-1].size()-1];	
		if(stoneNum==p  || stoneNum==q || stoneNum==r)
		{
			result.push_back(make_tuple(row,column-1));
		}
	}
	l4:;

	if(column!=n-1)
	{	
		if(s.boardState[row][column+1].size()==0)
			goto l5 ;
		
		stoneNum=s.boardState[row][column+1][s.boardState[row][column+1].size()-1];	
		if(stoneNum==p || stoneNum==q || stoneNum==r)
		{
			result.push_back(make_tuple(row,column+1));
		}
	}
	l5:;
	return result;
	
}
vector<tuple<int,int> > neighbours(state &s, tuple<int,int> t, int who)		//returns neighbours with flat or cap
{
	int n= s.boardState.size();
	vector<tuple<int,int> > result;
	int stoneNum;
	int row=get<0>(t);
	int column=get<1>(t);
	int p,q;
	if(who==1){
		p=1;
		q=5;
	}
	else{
		p=2;
		q=6;
	}

	if(row!=0)
	{
		if(s.boardState[row-1][column].size()==0)
			goto l2 ;
		stoneNum=s.boardState[row-1][column][s.boardState[row-1][column].size()-1];	
		if(stoneNum==p  ||  stoneNum==q)
		{
			result.push_back(make_tuple(row-1,column));
		}
	}
	l2: ;
	if(row!=n-1)
	{
		if(s.boardState[row+1][column].size()==0)
			goto l3 ;
		
		stoneNum=s.boardState[row+1][column][s.boardState[row+1][column].size()-1];	
		if(stoneNum==p  ||  stoneNum==q)
		{
			result.push_back(make_tuple(row+1,column));
		}
	}
	l3:;

	if(column!=0)
	{
		if(s.boardState[row][column-1].size()==0)
			goto l4 ;
		
		stoneNum=s.boardState[row][column-1][s.boardState[row][column-1].size()-1];	
		if(stoneNum==p  || stoneNum==q)
		{
			result.push_back(make_tuple(row,column-1));
		}
	}
	l4:;

	if(column!=n-1)
	{	
		if(s.boardState[row][column+1].size()==0)
			goto l5 ;
		
		stoneNum=s.boardState[row][column+1][s.boardState[row][column+1].size()-1];	
		if(stoneNum==p || stoneNum==q)
		{
			result.push_back(make_tuple(row,column+1));
		}
	}
	l5:;
	return result;
	
}

vector<tuple<int,int> > notNeighbours(state &s, tuple<int,int> t, int who)	//returns neighbours which are not mine
{
	int n= s.boardState.size();
	vector<tuple<int,int> > result;
	int stoneNum;
	int row=get<0>(t);
	int column=get<1>(t);
	int p,q,r;
	if(who==1){
		p=1;
		q=5;
		r=3;
	}
	else{
		p=2;
		q=6;
		r=4;
	}

	if(row!=0)
	{
		if(s.boardState[row-1][column].size()==0)
		{
			result.push_back(make_tuple(row-1,column));
			goto l2 ;
		}
			
		stoneNum=s.boardState[row-1][column][s.boardState[row-1][column].size()-1];	
		if(stoneNum!=p && stoneNum!=q && stoneNum!=r)
		{
			result.push_back(make_tuple(row-1,column));
		}
	}
	l2:; 
	if(row!=n-1)
	{
		if(s.boardState[row+1][column].size()==0)
		{
			result.push_back(make_tuple(row+1,column));
			goto l3 ;
		}
			
		stoneNum=s.boardState[row+1][column][s.boardState[row+1][column].size()-1];	
		if(stoneNum!=p && stoneNum!=q && stoneNum!=r)
		{
			result.push_back(make_tuple(row+1,column));
		}
	}
	l3:;

	if(column!=0)
	{
		if(s.boardState[row][column-1].size()==0)
		{
			result.push_back(make_tuple(row,column-1));
			goto l4 ;
		}
		
		stoneNum=s.boardState[row][column-1][s.boardState[row][column-1].size()-1];	
		if(stoneNum!=p  && stoneNum!=q && stoneNum!=r)
		{
			result.push_back(make_tuple(row,column-1));
		}
	}
	l4:;

	if(column!=n-1)
	{	
		if(s.boardState[row][column+1].size()==0)
		{
			result.push_back(make_tuple(row,column+1));
			goto l5 ;
		}
		stoneNum=s.boardState[row][column+1][s.boardState[row][column+1].size()-1];	
		if(stoneNum!=p  && stoneNum!=q && stoneNum!=r)
		{
			result.push_back(make_tuple(row,column+1));
		}
	}
	l5:;
	return result;
}

double straightStones(state &s)
{
	double out=0;
	int n = s.boardState.size();
	set< tuple<int,int> > visited;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			double inout=0;

			tuple< int, int > t1 = make_tuple(i,j);
			int init=visited.size();
			visited.insert(t1);

			if(visited.size()!=init && s.boardState[i][j].size()!=0)
			{

				int tem=s.boardState[i][j][s.boardState[i][j].size()-1];
				if(tem==1||tem==5)
				{
				//cout<<s.boardState[i][j][s.boardState[i][j].size()-1]<<'\n';
				tuple< int, int > t = make_tuple(i,j);

				//cout<<"size="<<neighbours(s,t).size()<<'\n';
				vector<tuple<int,int> > neigh123= neighbours(s,t,1);
				if(neigh123.size()==1)
				{
					double sizeLine=0;
					stack< tuple<int,int> > mystack;
					set< tuple<int,int> > myset;
					mystack.push(neigh123[0]);
					//sizeLine+=1;
					while(!mystack.empty())
					{
						//tuple< int, int > centre;
						tuple< int, int > current = mystack.top();
						mystack.pop();

						int initialSize=myset.size();
						myset.insert(current);
						visited.insert(current);
						if(initialSize!=myset.size())
						{
							sizeLine+=1;
							vector<tuple<int,int> > neigh= neighbours(s,current,1);
							for(int i=0;i<neigh.size();i++)
							{
								mystack.push(neigh[i]);
							}
						}	
					inout+=sizeLine;
					}
					out+=sizeLine;
				}
				}
			}
		}
	}
	return out;
}


bool checkRoadWin(state &s, int num)
{	
	int p,q;
	if(num==1)
		{p=1;q=5;}
	else
		{p=2;q=6;}
	int n= boardSize;
	bool f = false;
	
	for(int i=0;i<n && f==false;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(i==0 || i==n-1)
			{
				if(s.boardState[i][j].size()!=0)
				{
					int numStone = s.boardState[i][j][s.boardState[i][j].size()-1];
					if(numStone==p  || numStone==q)
					{
						f= true;
						goto l6;
						break;
					}
				}		
			}else if(j==0 || j==n-1)
			{			
				if( s.boardState[i][j].size()!=0)
				{
					int numStone = s.boardState[i][j][s.boardState[i][j].size()-1];
					if(numStone==p || numStone==q)
					{
						f= true;
						goto l6;
						break;
					}
				}
			}
		}
		if(i==n-1)
			return false;
	}
	l6:;

	int numStone;
	for(int t1=0;t1<n;t1++)
	{
		if(s.boardState[t1][0].size()==0)
			continue ;
		numStone = s.boardState[t1][0][s.boardState[t1][0].size()-1];	
		if(numStone!=p && numStone!=q)
			continue;

		stack< tuple<int,int> > mystack;
		set< tuple<int,int> > myset;
		
		mystack.push(make_tuple(t1,0));
		while(!mystack.empty())
		{
			tuple<int,int> current = mystack.top();
			mystack.pop();
			int initialSize=myset.size();
			myset.insert(current);
			if(myset.size()==initialSize)
				continue;
			else{
				if(get<1>(current)==n-1)
					return true;
				
				vector<tuple<int,int> > n=neighbours(s,current,num);
				for(int j=0;j<n.size();j++)
					mystack.push(n[j]);		
				
			}
		}
		
	}
	
	for(int t2=0;t2<n;t2++)
	{
		if(s.boardState[0][t2].size()==0)
			continue ;
		numStone = s.boardState[0][t2][s.boardState[0][t2].size()-1];	
		if(numStone!=p && numStone!=q)
			continue;
		stack< tuple<int,int> > mystack;
		set< tuple<int,int> > myset;
		
		mystack.push(make_tuple(0,t2));
		while(!mystack.empty())
		{
			tuple<int,int> current = mystack.top();
			mystack.pop() ;
			int initialSize=myset.size();
			myset.insert(current);
			if(myset.size()==initialSize)
				continue;
			else{
				if(get<0>(current)==n-1)
					return true;
					
				vector<tuple<int,int> > n=neighbours(s,current,num);
				for(int j=0;j<n.size();j++)
					mystack.push(n[j]);
			}
		}
	
	}

	return false;
}



tuple<int,int> newcheckRoadWin(state &s)
{
	int player1=0;
	int player2=0;

	int p,q,r,t;
	p=1; q=5; r=2; t=6;

	int n= boardSize;
	//bool f = false;


	bool checkplayer1=false;
	bool checkplayer2=false;	
	int numStone;

	bool onefirstrow=false;
	bool secondfirstrow=false;
	bool one=false;
	bool two=false;

	
	for(int t1=0;t1<n && (checkplayer1==false || checkplayer2==false);t1++)
	{
		if(s.boardState[t1][0].size()==0)
			continue ;
		numStone = s.boardState[t1][0][s.boardState[t1][0].size()-1];

		if((numStone==p || numStone==q) && checkplayer1==false)	//means player1 stone
		{
			stack< tuple<int,int> > mystack;
			set< tuple<int,int> > myset;
		
			mystack.push(make_tuple(t1,0));
			while(!mystack.empty() && checkplayer1==false)
			{
				tuple<int,int> current = mystack.top();
				mystack.pop();
				int initialSize=myset.size();
				myset.insert(current);
				if(myset.size()==initialSize)
					continue;
				else
				{
					if(get<1>(current)==n-1)	//TODO make  VAriable to true
						{
							checkplayer1=true;
							player1=1;
						}
					
					vector<tuple<int,int> > n=neighbours(s,current,1);
					for(int j=0;j<n.size();j++)
						mystack.push(n[j]);		
					
				}
			}
		}


		else if((numStone==r || numStone==t) && checkplayer2==false)	//means player2 stone
		{
			stack< tuple<int,int> > mystack;
			set< tuple<int,int> > myset;
		
			mystack.push(make_tuple(t1,0));
			while(!mystack.empty() && checkplayer2==false)
			{
				tuple<int,int> current = mystack.top();
				mystack.pop();
				int initialSize=myset.size();
				myset.insert(current);
				if(myset.size()==initialSize)
					continue;
				else{
					if(get<1>(current)==n-1)	//TODO make  VAriable to true
					{
						checkplayer2=true;
						player2=1;
					}	
					
					vector<tuple<int,int> > n=neighbours(s,current,2);
					for(int j=0;j<n.size();j++)
						mystack.push(n[j]);		
					
				}
			}
		}
	}

	for(int t2=0;t2<n && (checkplayer1==false || checkplayer2==false);t2++)
	{
		if(s.boardState[0][t2].size()==0)
			continue ;
		numStone = s.boardState[0][t2][s.boardState[0][t2].size()-1];
		if((numStone==p || numStone==q) && checkplayer1==false)
		{
			stack< tuple<int,int> > mystack;
			set< tuple<int,int> > myset;
		
			mystack.push(make_tuple(0,t2));
			while(!mystack.empty() && checkplayer1==false)
			{
				tuple<int,int> current = mystack.top();
				mystack.pop();
				int initialSize=myset.size();
				myset.insert(current);
				if(myset.size()==initialSize)
					continue;
				else
				{
					if(get<0>(current)==n-1)
					{
						checkplayer1=true;
						player1=1;
					}	
						
					
					vector<tuple<int,int> > n=neighbours(s,current,1);
					for(int j=0;j<n.size();j++)
						mystack.push(n[j]);		
					
				}
			}
		}
		else if((numStone==r || numStone==t) && checkplayer2==false)
		{
			stack< tuple<int,int> > mystack;
			set< tuple<int,int> > myset;
		
			mystack.push(make_tuple(0,t2));
			while(!mystack.empty() && checkplayer2==false)
			{
				tuple<int,int> current = mystack.top();
				mystack.pop();
				int initialSize=myset.size();
				myset.insert(current);
				if(myset.size()==initialSize)
					continue;
				else
				{
					if(get<0>(current)==n-1)	//TODO make  VAriable to true
					{
						checkplayer2=true;
						player2=1;
					}
					vector<tuple<int,int> > n=neighbours(s,current,2);
					for(int j=0;j<n.size();j++)
						mystack.push(n[j]);		
					
				}
			}
		}
	}
	return make_tuple(player1,player2);
}


double oneLess1(state &s,int i,int a, int who)
{
	int n=s.boardState.size();
	double result=0;
	int p,q;
	if(who==1)
	{
		p=1;
		q=5;
	}else{
		p=2;
		q=6;
	}
	for(int j=0;j<n;j++)
	{
		
		if(s.boardState[i][j].size()!=0)
		{
			int num=s.boardState[i][j][s.boardState[i][j].size()-1];
			if(num==p||num==q)
			{
				stack< tuple<int,int> > mystack;
				set< tuple<int,int> > myset;
				mystack.push(make_tuple(i,j));
				while(!mystack.empty())
				{
					tuple<int,int> current = mystack.top();
					mystack.pop();
					int initialSize=myset.size();
					myset.insert(current);
					if(myset.size()!=initialSize)
					{
						if(get<0>(current)==a)
						{
							result+=1;
							goto a1;//TODO
						}
						vector<tuple<int,int> > v1=neighbours(s,current,who);
						for(int k=0;k<v1.size();k++)
						{
							mystack.push(v1[k]);		
						}
					}
		
				}
			}

		}
		a1:;
	}
	return result;
}

double oneLess2(state &s,int j,int a, int who)
{
	int n=s.boardState.size();
	double result=0;
	int p,q;
	if(who==1)
	{
		p=1;
		q=5;
	}else{
		p=2;
		q=6;
	}
	for(int i=0;i<n;i++)
	{
		if(s.boardState[i][j].size()!=0)
		{
			int num=s.boardState[i][j][s.boardState[i][j].size()-1];
			if(num==p||num==q)
			{
				stack< tuple<int,int> > mystack;
				set< tuple<int,int> > myset;
				mystack.push(make_tuple(i,j));
				while(!mystack.empty())
				{
					tuple<int,int> current = mystack.top();
					mystack.pop();
					int initialSize=myset.size();
					myset.insert(current);
					if(myset.size()!=initialSize)
					{
						if(get<1>(current)==a)
						{
							result+=1;
							goto a1;//TODO
						}
						vector<tuple<int,int> > v1=neighbours(s,current,who);
						for(int k=0;k<v1.size();k++)
						{
							mystack.push(v1[k]);		
						}
					}
		
				}
			}

		}
		a1:;
	}
	return result;
}


vector < vector<tuple<int,int> > > aux1(state &s, int t, int who)
{
	int n = s.boardState.size();
	vector< vector<tuple<int,int> > > out;
	int p,q;
	if(who==1){
		p=1;
		q=5;
	}else{
		p=2;
		q=6;
	}

	for(int i=0;i<n;i++)
	{
		if(s.boardState[i][t].size()!=0)
		{
			int num=s.boardState[i][t][s.boardState[i][t].size()-1];
			if(num==p || num ==q)
			{
				vector< tuple<int,int> > v2;
				stack< tuple<int,int> > mystack;
				set< tuple<int,int> > myset;
	
				mystack.push(make_tuple(i,t));
				while(!mystack.empty())
				{
					tuple<int,int> current = mystack.top();
					mystack.pop();
					int initialSize=myset.size();
					myset.insert(current);
					if(myset.size()!=initialSize)
					{
						int flag=0;
						vector<tuple<int,int> > v1=neighbours(s,current,who);
						for(int j=0;j<v1.size();j++)
						{
							int sizen=myset.size();
							myset.insert(v1[j]);
							if(myset.size()!=sizen)
							{
								mystack.push(v1[j]);
								myset.erase(v1[j]);
								flag=1;
							}				
						}
						if(flag==0)
						{
							//v2=notNeighbours(s,current);
							/*for(int t=0;t<v2.size();t++)
							{
								cout<<get<0>(v2[t])<<get<1>(v2[t])<<'\n';
							}*/
							//out.push_back(v2);
							std::set<tuple<int,int> >::iterator it;
							for (it = myset.begin(); it != myset.end(); ++it)
							{
								out.push_back(notNeighbours(s,*it,who));
							}
						}
					}
				}
			}
		}
	}
	return out;
}


vector < vector<tuple<int,int> > > aux2(state &s, int t, int who)
{
	int n = s.boardState.size();
	vector< vector<tuple<int,int> > > out;
	int p,q;
	if(who==1){
		p=1;
		q=5;
	}else{
		p=2;
		q=6;
	}

	for(int i=0;i<n;i++)
	{
		if(s.boardState[t][i].size()!=0)
		{
			int num=s.boardState[t][i][s.boardState[t][i].size()-1];
			if(num==p || num==q)
			{
				vector<tuple<int,int> > v2;
				stack< tuple<int,int> > mystack;
				set< tuple<int,int> > myset;
	
				mystack.push(make_tuple(t,i));
				while(!mystack.empty())
				{
					tuple<int,int> current = mystack.top();
					mystack.pop();
					int initialSize=myset.size();
					myset.insert(current);
					if(myset.size()!=initialSize)
					{
						int flag=0;
						vector<tuple<int,int> > v1=neighbours(s,current,who);
						for(int j=0;j<v1.size();j++)
						{
							int sizen=myset.size();
							myset.insert(v1[j]);
							if(myset.size()!=sizen)
							{
								mystack.push(v1[j]);
								myset.erase(v1[j]);
								flag=1;
							}
										
						}
						if(flag==0)
						{
							std::set<tuple<int,int> >::iterator it;
							for (it = myset.begin(); it != myset.end(); ++it)
							{
								out.push_back(notNeighbours(s,*it, who));
							}
						}
					}
					
				}
			}
		}
	}
	return out;
}


double intersection(vector < vector<tuple<int,int> > > &a, vector < vector<tuple<int,int> > > &b)
{
	double answer=0;
	for(int i=0;i<a.size();i++)
	{
		for(int j=0;j<b.size();j++)
		{
			for(int k=0;k<a[i].size();k++)
			{
				for(int l=0;l<b[j].size();l++)
				{
					if(get<0>(a[i][k])==get<0>(b[j][l]) && get<1>(a[i][k])==get<1>(b[j][l]))
						answer+=1;
				}
			}
		}
	}
	return answer;
}


double oneRemaining(state &s, int num)
{
	int n = s.boardState.size();
	double result=0;

	result+=oneLess1(s,0,n-2,num);
	//cout<<"oneless1"<<oneLess1(s,0,n-2)<<'\n';
	result+=oneLess1(s,n-1,1,num);
	//cout<<"oneless1"<<oneLess1(s,n-1,1)<<'\n';
	result+=oneLess2(s,0,n-2,num);
	//cout<<"oneless2"<<oneLess2(s,0,n-2)<<'\n';
	result+=oneLess2(s,n-1,1,num);
	//cout<<"oneless2"<<oneLess2(s,n-1,1)<<'\n';

	vector < vector<tuple<int,int> > > side1 = aux1(s, 0, num);
	vector < vector<tuple<int,int> > > side2 = aux1(s, n-1, num);
	vector < vector<tuple<int,int> > > side3 = aux2(s, 0, num);
	vector < vector<tuple<int,int> > > side4 = aux2(s, n-1, num);
	
	//cout<<"size 1 = "<<side1.size()<<"size 2 = "<<side2.size()<<'\n';
	if(side1.size()!=0 && side2.size()!=0)
	{
		
		//cout<<"intersection1"<<intersection(side1,side2)<<'\n';
		result+=intersection(side1,side2);
	}

	if(side3.size()!=0 && side4.size()!=0)
	{
		
		//cout<<"intersection3"<<intersection(side3,side4)<<'\n';
		result+=intersection(side3,side4);
	}

	return result;
}


double evalFxn(state s)
{
	//cerr<<"yoyo"<<endl;
	double val = 0.0 ;
	tuple<int,int> rw = newcheckRoadWin(s);
	if(get<1>(rw)==1)
	{	//cout<<"yes its happening"<<endl;
		return -10000000.00;
	}
	if(get<0>(rw)==1)
	{	
		//cout<<"yes its happening 2"<<endl;
		return 10000000.00 ;
	}
	//-facefeat(s,2)
	/*double * facefeatures;
	facefeatures=facefeat(s,1);
	double * facefeatures2;
	facefeatures2=facefeat(s,2);
	double * influenceval;
	influenceval=influence(s);
	*/
	influence(s,1);
	influence(s,2);
	//facefeat(s,1);
	//facefeat(s,2);
	ss=straightStones(s);
	oneremaining1=oneRemaining(s,1);
	oneremaining2=oneRemaining(s,2);
	//facefeat(s,1);
	//facefeat(s,2);
	/*cerr<<"facefeatures= "<<facefeat10<<endl;
	cerr<<"influence= "<<influence0<<endl;
	cerr<<"straightstones= "<<ss<<endl;
	*/
	val=weights[0]*influence10+weights[1]*influence11+weights[2]*influence20+weights[3]*influence21+weights[4]*facefeat10+weights[5]*facefeat11+weights[6]*facefeat12+weights[7]*facefeat13+weights[8]*facefeat14+weights[9]*facefeat20+weights[10]*facefeat21+weights[11]*facefeat22+weights[12]*facefeat23+weights[13]*facefeat24+weights[14]*ss+weights[15]*oneremaining1+weights[16]*oneremaining2;
	//cerr<<val<<endl;
	return val ;   //returns a evaluation of state
}

//TODO check for standing stone in straightstones function
//add some evaluation value for number of stacks controlled