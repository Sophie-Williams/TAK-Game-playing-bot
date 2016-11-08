#include<bits/stdc++.h>
#include<time.h>
#include "variables.h"
#include "class.h"
#include "evaluation.h"
#include "nextstate.h"
using namespace std;

int ply=5;
int boardSize=5; 
bool ourCapRem =true;
bool oppoCapRem=true;  
int ourStonesRem=21; 
int oppoStonesRem=21;
int playerNum=1;
double myremTime;
double totalTime; 
int movNumber=0;
int totState=0;  
state nextMov(boardSize);
bool isTerminal(state &s)
{
	if(s.depth>=ply)
	{
		return true ;
	}
	else
	{
		return false ;
	}
}

map<char, int> my_map = {{ 'a', 1 },{ 'b', 2 },{ 'c', 3 },{ 'd', 4 },{ 'e', 5 },{ 'f', 6 },{ 'g', 7 }};



state changeArray(state &temp,int playerNum,string s)
{

   if(s.at(0)=='F' || s.at(0)=='S' || s.at(0)=='C')
   {
      int column=my_map[s.at(1)];
      //cout<<column<<endl; 
      int row=s.at(2)-48;
      int num=0;
      if(s.at(0)=='F')
      {
         if(playerNum==1)
            num=1;
         else
            num=2;   
      }
      else if(s.at(0)=='S')
      {
         if(playerNum==1)
            num=3;
         else
            num=4;   
      }
      else if(s.at(0)=='C')
      {
         if(playerNum==1)
            num=5;
         else
            num=6;
      }
      temp.boardState[temp.boardState.size()-row][column-1].push_back(num);
   }
   else
   {
      int numStones=s.at(0)-48;
      int column=my_map[s.at(1)];
      int row=s.at(2)-48;
      row=boardSize-row;
      row=row+1; 
      int temp1=0;
      char operat=s.at(3);
      int i=4;
      vector<int> v;
      for(int k=0;k<numStones;k++)
      {
         int j=temp.boardState[row-1][column-1].back();
         v.push_back(j);
         temp.boardState[row-1][column-1].pop_back();
      }
      while (temp1<numStones){
         int t=s.at(i)-48;
         temp1+=t;
         switch(operat)
         {
            case '<':
               column-=1;
               for(int i=0;i<t;i++)
               {
                  if(temp.boardState[row-1][column-1].size()!=0)
                  {
                    int n = temp.boardState[row-1][column-1][temp.boardState[row-1][column-1].size()-1];
                    if((n==4 and v.back()==5) || (n==3 and v.back()==6))
                      temp.boardState[row-1][column-1][temp.boardState[row-1][column-1].size()-1]=n-2;
                  }
                    temp.boardState[row-1][column-1].push_back(v.back());
                    v.pop_back();  
               }
            break;
            case '>':
               column+=1;
               for(int i=0;i<t;i++)
               {
                  if(temp.boardState[row-1][column-1].size()!=0)
                  {
                    int n = temp.boardState[row-1][column-1][temp.boardState[row-1][column-1].size()-1];
                    if((n==4 and v.back()==5) || (n==3 and v.back()==6))
                      temp.boardState[row-1][column-1][temp.boardState[row-1][column-1].size()-1]=n-2;
                  }
                  temp.boardState[row-1][column-1].push_back(v.back());
                  v.pop_back();  
               }
            break;
            case '-':
               row+=1;
               for(int i=0;i<t;i++)
               {
                  if(temp.boardState[row-1][column-1].size()!=0)
                  {
                    int n = temp.boardState[row-1][column-1][temp.boardState[row-1][column-1].size()-1];
                    if((n==4 and v.back()==5) || (n==3 and v.back()==6))
                      temp.boardState[row-1][column-1][temp.boardState[row-1][column-1].size()-1]=n-2;
                  }
                  temp.boardState[row-1][column-1].push_back(v.back());
                  v.pop_back();  
               }
            break;
            case '+':
               row-=1;
               for(int i=0;i<t;i++)
               {
                  if(temp.boardState[row-1][column-1].size()!=0)
                  {
                    int n = temp.boardState[row-1][column-1][temp.boardState[row-1][column-1].size()-1];
                    if((n==4 and v.back()==5) || (n==3 and v.back()==6))
                      temp.boardState[row-1][column-1][temp.boardState[row-1][column-1].size()-1]=n-1;
                  }
                  temp.boardState[row-1][column-1].push_back(v.back());
                  v.pop_back();  
               } 
            break;
         }
         i++;
      }
   }
   return temp ;
}

state firstMove(state &initial,int num)
{   
    int boardSize=initial.boardState.size();
    if(num==1)
    {
        int temp=rand()%4;
        if(temp==0) 
        {
            initial.boardState[boardSize-1][0].push_back(2) ;
            cout<<"Fa1"<<endl;
        }
        else if(temp==1)
        {
            initial.boardState[boardSize-1][boardSize-1].push_back(2);
            string o="Fe1";
            cout<<o<<endl;
        }
        else if(temp==2)
        {
            initial.boardState[0][boardSize-1].push_back(2);
            string o = "Fe5";
            cout<<o<<endl;
        }
        else{
            initial.boardState[0][0].push_back(2);
            string o = "Fa5";
            cout<<o<<endl;
        }
        string str; 
        cin>>str; 
        initial= changeArray(initial,1,str);
    }
    else
    {   string s ;
        cin>>s ;
         
        char a = s[0];
        int r=s[2]-49;
        int c=s[1]-97;
        if(a=='F')
            initial.boardState[boardSize-r-1][c].push_back(1);   //=changeArray(initial,1,s) ;
        else if(a=='S')
            initial.boardState[boardSize-r-1][c].push_back(3);   //=changeArray(initial,1,s) ;
        else if(a=='F')
            initial.boardState[boardSize-r-1][c].push_back(5);   //=changeArray(initial,1,s) ;
        
        string out;
        if(r==0)
        {
            if(c==0)
            {
                initial.boardState[boardSize-r-1][c+1].push_back(2);        
                out="F";
                out+=(char)(97+c+1);
                out+=(char)(49+r);
            }
            else
            {
                initial.boardState[boardSize-r-2][c].push_back(2);      
                out="F";
                out+=(char)(97+c);
                out+=(char)(49+r+1);
            }
        }
        else
        {
            initial.boardState[boardSize-r][c].push_back(2) ;
            out="F";
            out+=(char)(97+c);
            out+=(char)(49+r-1);
        }
        cout<<out<<endl;
    }   

    ourStonesRem=ourStonesRem-1; 
    return initial;
}

state myMove(state curr)
{
    //do tree search 
    vector<state> v= nextstate(curr);
    double maxi= -10000 ;
    state best(boardSize)  ;  
    for(int i= 0;i<v.size();i++)
    {   double temp =evalFxn(v[i]) ;
         
        if(maxi<temp)
        {   //cout<<v[i].printM<<endl;  
            maxi=temp ;
            best= v[i];  
        }
    }  
    return best ;
}

double minVal(state &curr, double alpha, double beta);
double maxVal(state &curr, double alpha, double beta)
{
   if(checkRoadWin(curr,2))  //oppnonent road win
   {     totState++; 
         return -10000000;
   }
   if(checkRoadWin(curr,1))   // our road win
   {	totState++; 
   		return 10000000 ;
   }
   if(isTerminal(curr))
   {	totState++; 
   		//call state evaluation fxn; 
   		return evalFxn(curr);  //return state evaluation fxn
   }
   vector<state> next= nextstate(curr);
   double currEval =LONG_MIN;
   double temp ;
   for(int i=0;i<next.size();i++)
   {
   	  temp=minVal(next[i],alpha,beta) ;
   	  if(currEval<temp)
   	  	{
            currEval=temp ;
   	      if(curr.depth==0)
            {	//cerr<<"MoVe Selected"<<endl; 
               nextMov=next[i]; 
            } 
         } 
   	  if(currEval>=beta)
   	  	return currEval; 
   	  
         alpha=max(alpha,currEval);
        
   }
   
   return currEval; 
}
double minVal(state &curr, double alpha, double beta)
{
	if(checkRoadWin(curr,1))   // our road win
   {	totState++; 
   		return 10000000 ;
   }
   if(checkRoadWin(curr,2))  //oppnonent road win
   {	totState++; 
   		return -10000000;
   }
   if(isTerminal(curr))
   {	totState++; 
   		//call state evaluation fxn; 
   		return evalFxn(curr) ;  //return state evaluation fxn
   }
   vector<state> v= nextstate2(curr);
   double currEval=LONG_MAX;
   double temp ;
   for(int i=0;i<v.size();i++)
   {
   	  temp=maxVal(v[i],alpha,beta) ;
   	  if(currEval>temp)
   	  {
   	  	currEval=temp ;
   	  }
   	  if(currEval<=alpha)
   	  	return currEval; 
   	  
        beta= min(beta, currEval);
   }

return currEval;
}

state alphabetaPruning(state curr)
{  totState= 0 ;   
   curr.depth=0 ;
   state temp(boardSize);
   nextMov=temp; 
     //check in transposition tables
     //if not found , call for maxVal
    double result =maxVal(curr,LONG_MIN,LONG_MAX) ;
    cerr<<"value of state"<<result<<endl; 
    train(curr, result);
    cerr<<"Ply Followed"<<ply<<endl ;
    cerr<<"Total States: "<<totState<<endl; 

   
    return nextMov ;
}

void printMove(state &curr)
{
   if(curr.printM[0]=='C')
   {
      ourCapRem=false;
   }
   if(curr.printM[0]=='F'||curr.printM[0]=='S')
   {
      ourStonesRem=ourStonesRem-1; 
   }
   cout<<curr.printM<<endl; 
}

int main()
{  
   time_t seconds;
   time(&seconds);
   srand((unsigned int) seconds);
 
   string ab=""; //1 5 100
   getline(cin,ab);
   initialWeights(ab[0]-48);
   playerNum=1;
   int opponentNum= 2;//(playerNum%2)+1;
   boardSize=ab[2]-48;
   state initial(boardSize); 
    
   for(int i=0;i<ab.size()-4;i++)
   {
      myremTime= myremTime*10+ (int)(ab[i+4]-48) ;
   }
   totalTime=myremTime; 
   clock_t start = clock();
   state current= firstMove(initial,(ab[0]-48));
   clock_t end = clock();
   myremTime=myremTime-(end-start)/CLOCKS_PER_SEC;
   cerr<<myremTime<<endl;
   movNumber=1;
   //state present(boardSize);
   while(true)
   {	
       string opponentmove; 
        if(movNumber!=1||ab[0]-48==2)
        {
            cin>>opponentmove;
           	start = clock();
            current = changeArray(current, opponentNum, opponentmove);
        }
        
        try
        {
        	if(myremTime<0.9*totalTime && myremTime>0.1*totalTime)
        	{
        		ply= 3; 
        	}
        	else 
        	{
        		ply= 3; 
        	}
            current= alphabetaPruning(current);
            if(checkRoadWin(current,1))
            {
            	cerr<<"winning"<<endl;
               writeWeights(); 
            }
            printMove(current);

        }
        catch(exception& e)
        {
            current= myMove(current);
        }
        end = clock();
        //cerr<<start<<" "<<end<<" "<<CLOCKS_PER_SEC<<endl ;
        myremTime=myremTime-(double)(end-start)/CLOCKS_PER_SEC;
        cerr<<myremTime<<endl;
        movNumber=movNumber+1; 
      
      /*string s1; 
      string s2; 
      cin>>s1;
      cin>>s2;
      changeArray(present,1,s1) ;
      changeArray(present,2,s2) ;
      cout<<"RoadWin"<<checkRoadWin(present,1)<<" opp"<<checkRoadWin(present,2)<<endl; 
      //present=alphabetaPruning(present);
      vector <state> ns = nextstate2(present) ;
      /*for(int i=0;i<ns.size();i++)
      {
        cout<<ns[i].printM<<endl; 
      }*/

      //printMove(present) ;
      //cout<<endl; 
   } 
   
	return 0;
}

//return array in facefeat and add the learning part in facefaet as well
//TODO - 1) time initial 
//2) sorted order of children