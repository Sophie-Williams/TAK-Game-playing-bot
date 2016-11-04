#include "class.h"
#include "nextstate.h"
#include "variables.h"
#include "evaluation.h"

#include<bits/stdc++.h>
using namespace std;

map<int, string> my_map2 = {{ 1,"a" },{2, "b"},{ 3,"c"},{ 4,"d"},{5, "e"},{6, "f"},{7, "g"}};
map<int,string> my_map3 = {{ 1,"1" },{2, "2"},{ 3,"3"},{ 4,"4"},{5, "5"},{6, "6"},{7, "7"},{8, "8"},{9, "9"},{10, "10"}};

void NsplitArrTop(state curr,int coverage , vector<int> rec, int present , vector<int> posi , state pre, vector<state> &temp, int cover, int row, int col)
{
  if(cover==coverage)
  { temp.push_back(pre); 
    return ; 
  }
  if(present==posi.size())
  {
    return  ;
  } 
  NsplitArrTop(curr,coverage,rec,present+1, posi,pre,temp,cover,row,col) ;

  int oldS= pre.boardState[row-cover][col].size() ; 
  for(int z= posi[present]+1 ;z<=posi[posi.size()-1] ;z++)
  { int stone ;
    if(pre.boardState[row-cover-1][col].size()==0)
    {
      goto l1  ;
    }
    stone=pre.boardState[row-cover-1][col][pre.boardState[row-cover-1][col].size()-1] ;
    if(stone ==3||stone ==4||stone ==5||stone ==6)
    {
      return ; 
    }
    l1: 
    pre.boardState[row-cover][col].pop_back();
    pre.boardState[row-cover-1][col].push_back(rec[z]); 
  }
  if(cover==0)
  { if(present==0)
    {
    pre.printM= my_map3[rec.size()]+my_map2[col+1]+my_map3[boardSize-row]+"+"; 
    }
    else
    {
      pre.printM= my_map3[rec.size()-posi[present]-1]+my_map2[col+1]+my_map3[boardSize-row]+"+";  
    }
  }
  else
  { 
    int te= pre.boardState[row-cover][col].size()-curr.boardState[row-cover][col].size() ; 
    pre.printM=pre.printM+ my_map3[te] ;
    //pre.printM=pre.printM+ my_map3[oldS-pre.boardState[row-cover][col].size()] ;  
  }
  if(cover+1==coverage)
  { 
    int te= pre.boardState[row-cover-1][col].size()-curr.boardState[row-cover-1][col].size() ; 
    if(te==0)
      return ;
    pre.printM=pre.printM+ my_map3[te] ;  
  }
    
    NsplitArrTop(curr,coverage,rec,present+1, posi,pre,temp,cover+1,row,col) ;
  
}
void NsplitArrDown(state curr, int coverage , vector<int> rec, int present , vector<int> posi , state pre, vector<state> &temp, int cover, int row, int col)
{
  if(cover==coverage)
  { 
    temp.push_back(pre); 
    return ; 
  }
  if(present==posi.size())
  {
    return  ;
  } 
  NsplitArrDown(curr,coverage,rec,present+1, posi,pre,temp,cover,row,col) ;

  int oldS= pre.boardState[row+cover][col].size() ; 
  for(int z= posi[present]+1 ;z<=posi[posi.size()-1] ;z++)
  { int stone ;
    if(pre.boardState[row+cover+1][col].size()==0)
    {
      goto l1 ;
    }
    stone=pre.boardState[row+cover+1][col][pre.boardState[row+cover+1][col].size()-1] ;
    if(stone ==3||stone ==4||stone ==5||stone ==6)
    {
      return ; 
    }
    l1: 
    pre.boardState[row+cover][col].pop_back();
    pre.boardState[row+cover+1][col].push_back(rec[z]); 
  }
  
  if(cover==0)
  { 
    if(present==0)
    {
      pre.printM= my_map3[rec.size()]+my_map2[col+1]+my_map3[boardSize-row]+"-";  
    }
    else
    {pre.printM= my_map3[rec.size()-posi[present]-1]+my_map2[col+1]+my_map3[boardSize-row]+"-";} 
  }
  else
  { int te= pre.boardState[row+cover][col].size()-curr.boardState[row+cover][col].size() ; 
    pre.printM=pre.printM+ my_map3[te] ;
  }
  if(cover+1==coverage)
  { 
    int te= pre.boardState[row+cover+1][col].size()-curr.boardState[row+cover+1][col].size() ; 
    if(te==0)
      return ;
    pre.printM=pre.printM+ my_map3[te] ;  
  }
    NsplitArrDown(curr,coverage,rec,present+1, posi,pre,temp,cover+1,row,col) ;
}
void NsplitArrRight(state curr,int coverage , vector<int> rec, int present , vector<int> posi , state pre, vector<state> &temp, int cover, int row, int col)
{
  if(cover==coverage)
  { temp.push_back(pre); 
    return ; 
  }
  if(present==posi.size())
  {
    return  ;
  } 
  NsplitArrRight(curr,coverage,rec,present+1, posi,pre,temp,cover,row,col) ;

  int oldS= pre.boardState[row][col+cover].size() ; 
  for(int z= posi[present]+1 ;z<=posi[posi.size()-1] ;z++)
  { int stone ;
    if(pre.boardState[row][col+cover+1].size()==0)
    {
      goto l1 ;
    }
    stone=pre.boardState[row][col+cover+1][pre.boardState[row][col+cover+1].size()-1] ;
    if(stone ==3||stone ==4||stone ==5||stone ==6)
    {
      return ; 
    }
    l1: 
    pre.boardState[row][col+cover].pop_back();
    pre.boardState[row][col+cover+1].push_back(rec[z]); 
  }
  

  if(cover==0)
  { if(present==0)
    {pre.printM= my_map3[rec.size()]+my_map2[col+1]+my_map3[boardSize-row]+">"; 
    }
    else
    {
      pre.printM= my_map3[rec.size()-posi[present]-1]+my_map2[col+1]+my_map3[boardSize-row]+">";  
    }
  }
  else
  { int te= pre.boardState[row][col+cover].size()-curr.boardState[row][col+cover].size() ; 
    pre.printM=pre.printM+ my_map3[te] ;
    //pre.printM=pre.printM+ my_map3[oldS-pre.boardState[row-cover][col].size()] ;  
  }
  if(cover+1==coverage)
  { 
    int te= pre.boardState[row][col+cover+1].size()-curr.boardState[row][col+cover+1].size() ; 
    if(te==0)
      return ;
    pre.printM=pre.printM+ my_map3[te] ;  
  }

    NsplitArrRight(curr,coverage,rec,present+1, posi,pre,temp,cover+1,row,col) ;
}
void NsplitArrLeft(state curr,int coverage , vector<int> rec, int present , vector<int> posi , state pre, vector<state> &temp, int cover, int row, int col)
{ //cout<<" "<<coverage<<" "<<present<<" "<<cover<<endl ;
  if(cover==coverage)
  { temp.push_back(pre); 
    return ; 
  }
  if(present==posi.size())
  {
    return  ;
  } 
  NsplitArrLeft(curr,coverage,rec,present+1, posi,pre,temp,cover,row,col) ;

  int oldS= pre.boardState[row][col-cover].size() ; 
  for(int z= posi[present]+1 ;z<=posi[posi.size()-1] ;z++)
  { int stone ; 
    if(pre.boardState[row][col-cover-1].size()==0)
    {
      goto l1 ;
    }
    stone=pre.boardState[row][col-cover-1][pre.boardState[row][col-cover-1].size()-1] ;
    if(stone ==3||stone ==4||stone ==5||stone ==6)
    {
      return ; 
    }
    l1: 
    pre.boardState[row][col-cover].pop_back();
    pre.boardState[row][col-cover-1].push_back(rec[z]); 
  }
  if(cover==0)
  { if(present==0)
    {
      pre.printM= my_map3[rec.size()]+my_map2[col+1]+my_map3[boardSize-row]+"<"; 
    }
    else
    {
      pre.printM= my_map3[rec.size()-posi[present]-1]+my_map2[col+1]+my_map3[boardSize-row]+"<";
    }
  }
  else
  {
    int te= pre.boardState[row][col-cover].size()-curr.boardState[row][col-cover].size() ; 
    pre.printM=pre.printM+ my_map3[te] ;
    //pre.printM=pre.printM+ my_map3[oldS-pre.boardState[row-cover][col].size()] ;  
  }
  if(cover+1==coverage)
  { 
    int te= pre.boardState[row][col-cover-1].size()-curr.boardState[row][col-cover-1].size() ; 
    if(te==0)
      return ;
    pre.printM=pre.printM+ my_map3[te] ;  
  }
    NsplitArrLeft(curr,coverage,rec,present+1, posi,pre,temp,cover+1,row,col) ;
}
void CsplitArrTop(state curr, int coverage , vector<int> rec, int present , vector<int> posi , state pre, vector<state> &temp, int cover, int row, int col)
{
  if(cover==coverage)
  { temp.push_back(pre); 
    return ; 
  }
  if(present==posi.size())
  {
    return  ;
  } 
  CsplitArrTop(curr,coverage,rec,present+1, posi,pre,temp,cover,row,col) ;

  int oldS= pre.boardState[row-cover][col].size() ;
  for(int z= posi[present]+1 ;z<=posi[posi.size()-1] ;z++)
  { int stone ; 
    if(pre.boardState[row-cover-1][col].size()==0)
    {
      goto l1 ;
    }
    stone=pre.boardState[row-cover-1][col][pre.boardState[row-cover-1][col].size()-1] ;
    if(stone ==3||stone ==4||stone ==5||stone ==6)
    { //cout<<"present"<<present<<"posi.size()"<<posi.size()<<" "<<posi[posi.size()-1]<<" "<<posi[posi.size()-2]<<" "<<endl;
      if((stone==3||stone==4)&&(present==posi.size()-2)&&((posi[posi.size()-1]-posi[posi.size()-2])==1))
      {

        goto l1 ;
      }
      return ; 
      
    }
    l1:
    pre.boardState[row-cover][col].pop_back();
    pre.boardState[row-cover-1][col].push_back(rec[z]); 
  }
  if(cover==0)
  { if(present==0)
    {
      pre.printM= my_map3[rec.size()]+my_map2[col+1]+my_map3[boardSize-row]+"+";
    }
    else
    {
      pre.printM= my_map3[rec.size()-posi[present]-1]+my_map2[col+1]+my_map3[boardSize-row]+"+";  
    }
  }
  else
  {
    int te= pre.boardState[row-cover][col].size()-curr.boardState[row-cover][col].size() ; 
    pre.printM=pre.printM+ my_map3[te] ;
    //pre.printM=pre.printM+ my_map3[oldS-pre.boardState[row-cover][col].size()] ;  
  }
  if(cover+1==coverage)
  { 
    int te= pre.boardState[row-cover-1][col].size()-curr.boardState[row-cover-1][col].size() ; 
    if(te==0)
      return ;
    pre.printM=pre.printM+ my_map3[te] ;  
  }
    CsplitArrTop(curr,coverage,rec,present+1, posi,pre,temp,cover+1,row,col) ;
  
}
void CsplitArrDown(state curr,int coverage , vector<int> rec, int present , vector<int> posi , state pre, vector<state> &temp, int cover, int row, int col)
{ //cout<<"started" ;
  if(cover==coverage)
  { temp.push_back(pre); 
    return ; 
  }
  if(present==posi.size())
  {
    return  ;
  } 
  CsplitArrDown(curr,coverage,rec,present+1, posi,pre,temp,cover,row,col) ;

  int oldS= pre.boardState[row+cover][col].size() ; 
  for(int z= posi[present]+1 ;z<=posi[posi.size()-1] ;z++)
  { int stone ;
    if(pre.boardState[row+cover+1][col].size()==0)
    {
      goto l1 ;
    }
    stone=pre.boardState[row+cover+1][col][pre.boardState[row+cover+1][col].size()-1] ;
    if(stone ==3||stone ==4||stone ==5||stone ==6)
    { if((stone==3||stone==4)&&(present==posi.size()-2)&&((posi[posi.size()-1]-posi[posi.size()-2])==1))
      {
        goto l1 ;
      }
      return ; 
    }
    l1: 
    pre.boardState[row+cover][col].pop_back();
    pre.boardState[row+cover+1][col].push_back(rec[z]); 
  }

  if(cover==0)
  { if(present==0)
    {

    pre.printM= my_map3[rec.size()]+my_map2[col+1]+my_map3[boardSize-row]+"-"; 
    }
    else
    {
      pre.printM= my_map3[rec.size()-posi[present]-1]+my_map2[col+1]+my_map3[boardSize-row]+"-";  
    }
  }
  else
  { int te= pre.boardState[row+cover][col].size()-curr.boardState[row+cover][col].size() ; 
    pre.printM=pre.printM+ my_map3[te] ;
    //pre.printM=pre.printM+ my_map3[oldS-pre.boardState[row-cover][col].size()] ;  
  }
  if(cover+1==coverage)
  { 
    int te= pre.boardState[row+cover+1][col].size()-curr.boardState[row+cover+1][col].size() ; 
    if(te==0)
      return ;
    pre.printM=pre.printM+ my_map3[te] ;  
  }
  
    CsplitArrDown(curr,coverage,rec,present+1, posi,pre,temp,cover+1,row,col) ;
}
void CsplitArrRight(state curr,int coverage , vector<int> rec, int present , vector<int> posi , state pre, vector<state> &temp, int cover, int row, int col)
{
  if(cover==coverage)
  { temp.push_back(pre); 
    return ; 
  }
  if(present==posi.size())
  {
    return  ;
  } 
  CsplitArrRight(curr,coverage,rec,present+1, posi,pre,temp,cover,row,col) ;

  int oldS= pre.boardState[row][col+cover].size() ; 
  for(int z= posi[present]+1 ;z<=posi[posi.size()-1] ;z++)
  { int stone ;
    if(pre.boardState[row][col+cover+1].size()==0)
    {
      goto l1 ;
    }
    stone=pre.boardState[row][col+cover+1][pre.boardState[row][col+cover+1].size()-1] ;
    if(stone ==3||stone ==4||stone ==5||stone ==6)
    { if((stone==3||stone==4)&&(present==posi.size()-2)&&((posi[posi.size()-1]-posi[posi.size()-2])==1))
      {
        goto l1 ;
      }
      return ; 
    }
    l1: 
    pre.boardState[row][col+cover].pop_back();
    pre.boardState[row][col+cover+1].push_back(rec[z]); 
  }

  if(cover==0)
  { if(present==0)
    {pre.printM= my_map3[rec.size()]+my_map2[col+1]+my_map3[boardSize-row]+">"; 
    }
    else
    {
      pre.printM= my_map3[rec.size()-posi[present]-1]+my_map2[col+1]+my_map3[boardSize-row]+">";
    }
  }
  else
  {
    int te= pre.boardState[row][col+cover].size()-curr.boardState[row][col+cover].size() ; 
    pre.printM=pre.printM+ my_map3[te] ;
    //pre.printM=pre.printM+ my_map3[oldS-pre.boardState[row-cover][col].size()] ;  
  }
  if(cover+1==coverage)
  { 
    int te= pre.boardState[row][col+cover+1].size()-curr.boardState[row][col+cover+1].size() ; 
    if(te==0)
      return ;
    pre.printM=pre.printM+ my_map3[te] ;  
  }
    CsplitArrRight(curr,coverage,rec,present+1, posi,pre,temp,cover+1,row,col) ;
}
void CsplitArrLeft(state curr,int coverage , vector<int> rec, int present , vector<int> posi , state pre, vector<state> &temp, int cover, int row, int col)
{
  if(cover==coverage)
  { temp.push_back(pre); 
    return ; 
  }
  if(present==posi.size())
  {
    return  ;
  } 
  CsplitArrLeft(curr,coverage,rec,present+1, posi,pre,temp,cover,row,col) ;

  int oldS= pre.boardState[row][col-cover].size() ; 
  for(int z= posi[present]+1 ;z<=posi[posi.size()-1] ;z++)
  { int stone ;
    if(pre.boardState[row][col-cover-1].size()==0)
    {
      goto l1 ;
    }
    stone=pre.boardState[row][col-cover-1][pre.boardState[row][col-cover-1].size()-1] ;
    if(stone ==3||stone ==4||stone ==5||stone ==6)
    { if((stone==3||stone==4)&&(present==posi.size()-2)&&((posi[posi.size()-1]-posi[posi.size()-2])==1))
      {
        goto l1 ;
      }
      return ; 
    }
    l1: 
    pre.boardState[row][col-cover].pop_back();
    pre.boardState[row][col-cover-1].push_back(rec[z]); 
  }
  if(cover==0)
  { if(present==0)
    {
    pre.printM= my_map3[rec.size()]+my_map2[col+1]+my_map3[boardSize-row]+"<"; 
    }
    else
    {
      pre.printM= my_map3[rec.size()-posi[present]-1]+my_map2[col+1]+my_map3[boardSize-row]+"<";  
    }
  }
  else
  {
    int te= pre.boardState[row][col-cover].size()-curr.boardState[row][col-cover].size() ; 
    pre.printM=pre.printM+ my_map3[te] ;
    //pre.printM=pre.printM+ my_map3[oldS-pre.boardState[row-cover][col].size()] ;  
  }
  if(cover+1==coverage)
  { 
    int te= pre.boardState[row][col-cover-1].size()-curr.boardState[row][col-cover-1].size() ; 
    if(te==0)
      return ;
    pre.printM=pre.printM+ my_map3[te] ;  
  }
    CsplitArrLeft(curr,coverage,rec,present+1, posi,pre,temp,cover+1,row,col) ;
}

vector<state> nextstate(state &curr)  //decide on the moves here
{ int t= 0 ;
  int p= 0 ;  
  int q =0 ;   
  vector<state> nextS ;
    
      t=1;
      p=3;  
      q=5 ;
    
    /*else
    {
      t=2 ;
      p=4; 
      q=6 ; 
    }*/
    state temp(boardSize) ;
    state temp1(boardSize) ;
    state temp2(boardSize) ;
    
    for(int i=0 ;i<boardSize;i++)                     //for placing new stone at empty place
    {
      for(int j=0;j<boardSize;j++)
      { tuple<int,int> v123= make_tuple(i,j);
        if(curr.boardState[i][j].size()==0)  //&&(!emptyneighbour(curr,make_tuple(i,j)))
        {  
             //for flatstone
           temp.boardState = curr.boardState ;
           temp.depth= curr.depth+1 ; 
           temp.parent= &curr ;
              //for wall stone
           temp1.boardState = curr.boardState ;
           temp1.depth= curr.depth+1 ;  
           temp1.parent= &curr ;
            //for Cap stone
           temp2.boardState = curr.boardState ;
           temp2.depth= curr.depth+1 ;  
           temp2.parent= &curr ;      
           if(ourStonesRem>0)
           {
            temp.boardState[i][j].push_back(t) ;    // flat stone
            temp.printM="F"+my_map2[j+1]+my_map3[boardSize-i]; 
            temp1.boardState[i][j].push_back(p) ;
            temp1.printM="S"+my_map2[j+1]+my_map3[boardSize-i];
            nextS.push_back(temp) ;
            nextS.push_back(temp1); 
           }        
           if(ourCapRem)
           {
            temp2.printM="C"+my_map2[j+1]+my_map3[boardSize-i];
            temp2.boardState[i][j].push_back(q) ;
            nextS.push_back(temp2) ;
           }        
           //cout<<" "<<nextS.size()<<" ";
        }
        else if(curr.boardState[i][j].size()!=0)   //for moving of stones
        {
          vector<int> pos ;
          pos.push_back(-1) ;
          for(int z=0; z<curr.boardState[i][j].size();z++)
            {
              if(curr.boardState[i][j][z]==t||curr.boardState[i][j][z]==p||curr.boardState[i][j][z]==q)
              {
                pos.push_back(z); 
              }   
            }
          if(pos.size()==1)
          {
            pos.pop_back();  
          } 
            int top= i ;
            int bottom=boardSize-1-i; 
            int right=boardSize-1-j; 
            int left =j;
            int tr;
            //cout<<" "<<pos.size()<<"i am here"<<curr.boardState[i][j][curr.boardState[i][j].size()-1]<<endl  ; 
            int z123= curr.boardState[i][j].size()-1 ;
          if(curr.boardState[i][j][z123]==t||curr.boardState[i][j][z123]==p) //if top stone is flatstone 
            {    tr= pos.size()-1 ;
              int y123; 
              for(y123=0;y123<=tr;y123++)
              {
                if((pos[tr]-pos[y123])<=5)
                  { //cerr<<"more stones "<<y123<<endl; 

                    break;
                  } 
              }
              //y123=tr-y123;
              for(int h=0;h<min(top,tr);h++)
              { state St(boardSize);
                St.boardState=curr.boardState; 
                St.parent=&curr ;
                St.depth=curr.depth+1; 
                /*if(true||St.boardState[i-1][j].size()==0)
                {

                }
                else*/
                {
                  NsplitArrTop(curr,h+1,curr.boardState[i][j],y123,pos,St,nextS,0,i,j); 
                }
              }

              for(int h=0;h<min(bottom,tr);h++)
              { state St(boardSize);
                St.boardState=curr.boardState; 
                St.parent=&curr ;
                St.depth=curr.depth+1; 
                /*if(true||St.boardState[i+1][j].size()==0)
                {

                }
                else*/
                {
                NsplitArrDown(curr,h+1,curr.boardState[i][j],y123,pos,St,nextS,0,i,j); 
                }
              } 
              for(int h=0;h<min(right,tr);h++)
              { state St(boardSize);
                St.boardState=curr.boardState; 
                St.parent=&curr ;
                St.depth=curr.depth+1; 
                /*if(St.boardState[i][j+1].size()==0)
                {

                }
                else*/
                {NsplitArrRight(curr,h+1,curr.boardState[i][j],y123,pos,St,nextS,0,i,j); 
                }
              }
              for(int h=0;h<min(left,tr);h++)
              { state St(boardSize);
                St.boardState=curr.boardState; 
                St.parent=&curr ;
                St.depth=curr.depth+1; 
                //cout<<"yo"<<endl;
                /*if(St.boardState[i][j-1].size()==0||true)
                {

                }
                else*/
                {NsplitArrLeft(curr,h+1,curr.boardState[i][j],y123,pos,St,nextS,0,i,j); 
                }
              }
            }
          if(curr.boardState[i][j][curr.boardState[i][j].size()-1]==q)
            {
             tr= pos.size()-1 ;
              int y123; 
              for(y123=0;y123<=tr;y123++)
              {
                if((pos[tr]-pos[y123])<=5)
                  break; 
              }
              for(int h=0;h<min(top,tr);h++)
              { state St(boardSize);
                St.boardState=curr.boardState; 
                St.parent=&curr ;
                St.depth=curr.depth+1; 
                /*if(true||St.boardState[i-1][j].size()==0)
                {

                }
                else*/
                {
                  CsplitArrTop(curr,h+1,curr.boardState[i][j],y123,pos,St,nextS,0,i,j); 
                }
              }

              for(int h=0;h<min(bottom,tr);h++)
              { state St(boardSize);
                St.boardState=curr.boardState; 
                St.parent=&curr ;
                St.depth=curr.depth+1; 
                /*if(true||St.boardState[i+1][j].size()==0)
                {

                }
                else*/
                {
                CsplitArrDown(curr,h+1,curr.boardState[i][j],y123,pos,St,nextS,0,i,j); 
                }
              } 
              for(int h=0;h<min(right,tr);h++)
              { state St(boardSize);
                St.boardState=curr.boardState; 
                St.parent=&curr ;
                St.depth=curr.depth+1; 
                /*if(St.boardState[i][j+1].size()==0)
                {

                }
                else*/
                {CsplitArrRight(curr,h+1,curr.boardState[i][j],y123,pos,St,nextS,0,i,j); 
                }
              }
              for(int h=0;h<min(left,tr);h++)
              { state St(boardSize);
                St.boardState=curr.boardState; 
                St.parent=&curr ;
                St.depth=curr.depth+1; 
                //cout<<"yo"<<endl;
                /*if(St.boardState[i][j-1].size()==0||true)
                {

                }
                else*/
                {CsplitArrLeft(curr,h+1,curr.boardState[i][j],y123,pos,St,nextS,0,i,j); 
                }
              }  
            }   
          
        }
      }
    }
    //cout<<" "<<f<<" "; 
  
    for(int i=0;i<nextS.size();i++)
    {
      nextS[i].eval= evalFxn(nextS[i]); 
    }

   sort(nextS.begin(), nextS.end());

    // for(int i=0;i<nextS.size();i++)
    // {
    //   cerr<<nextS[i].eval<<endl;//= evalFxn(nextS[i]); 
    // }
    // cerr<<"yes i have printed"<<endl;
  return nextS ;
}
struct greater1
{
    template<class T>
    bool operator()(T const &a, T const &b) const { return a.eval < b.eval; }
};
vector<state> nextstate2(state &curr) //decide on the moves here
{ int t= 0 ;
  int p= 0 ;  
  int q =0 ;   
  vector<state> nextS ;
    /*if(playerNum==1)               //returns the vector of next possible states .  
    {
      t=2 ;
      p=4; 
      q=6 ;
      //t=1;
      //p=3;  
      //q=5 ;
    }
    else*/
    {
      t=2 ;
      p=4; 
      q=6 ; 
    }
    
    state temp(boardSize) ;
     state temp1(boardSize) ; 
     state temp2(boardSize) ;
    for(int i=0 ;i<boardSize;i++)                     //for placing new stone at empty place
    {
      for(int j=0;j<boardSize;j++)
      {
        if(curr.boardState[i][j].size()==0)  //&&(!emptyneighbour(curr,make_tuple(i,j)))
        {  
             //for flatstone
           temp.boardState = curr.boardState ;
           temp.depth= curr.depth+1 ; 
           temp.parent= &curr ;
           //for wall stone
           temp1.boardState = curr.boardState ;
           temp1.depth= curr.depth+1 ;  
           temp1.parent= &curr ;
             //for Cap stone
           temp2.boardState = curr.boardState ;
           temp2.depth= curr.depth+1 ;  
           temp2.parent= &curr ;      
           if(oppoStonesRem>0)
           {
          temp.boardState[i][j].push_back(t) ;    // flat stone
          temp.printM="F"+my_map2[j+1]+my_map3[boardSize-i]; 
          temp1.boardState[i][j].push_back(p) ;
          temp1.printM="S"+my_map2[j+1]+my_map3[boardSize-i];
          nextS.push_back(temp) ;
          nextS.push_back(temp1); 
           }        
           if(oppoCapRem)
           {
            temp2.printM="C"+my_map2[j+1]+my_map3[boardSize-i];
            temp2.boardState[i][j].push_back(q) ;
            nextS.push_back(temp2) ;
           }        
           //cout<<" "<<nextS.size()<<" ";
        }
        else if(curr.boardState[i][j].size()!=0)  //for moving of stones
        {
          vector<int> pos ;
          pos.push_back(-1) ;
          for(int z=0; z<curr.boardState[i][j].size();z++)
            {
              if(curr.boardState[i][j][z]==t||curr.boardState[i][j][z]==p||curr.boardState[i][j][z]==q)
              {
                pos.push_back(z); 
              }   
            }
          if(pos.size()==1)
          {
            pos.pop_back();  
          } 
            int top= i ;
            int bottom=boardSize-1-i; 
            int right=boardSize-1-j; 
            int left =j;
            int tr;
            //cout<<" "<<pos.size()<<"i am here"<<curr.boardState[i][j][curr.boardState[i][j].size()-1]<<endl  ; 
          if(curr.boardState[i][j][curr.boardState[i][j].size()-1]==t||curr.boardState[i][j][curr.boardState[i][j].size()-1]==p) //if top stone is flatstone 
            {    tr= pos.size()-1 ;
              
              int y123; 
              for(y123=0;y123<=tr;y123++)
              {
                if((pos[tr]-pos[y123])<=5)
                  { //cerr<<"more stones "<<y123<<endl; 

                    break;
                  } 
              }
              for(int h=0;h<min(top,tr);h++)
              { state St(boardSize);
                St.boardState=curr.boardState; 
                St.parent=&curr ;
                St.depth=curr.depth+1; 
                /*if(St.boardState[i-1][j].size()==0)
                {

                }
                else*/ 
                  {NsplitArrTop(curr,h+1,curr.boardState[i][j],y123,pos,St,nextS,0,i,j); 
                    }
              }

              for(int h=0;h<min(bottom,tr);h++)
              { state St(boardSize);
                St.boardState=curr.boardState; 
                St.parent=&curr ;
                St.depth=curr.depth+1;
                /*if(St.boardState[i+1][j].size()==0)
                {

                } 
                else*/ {
                  NsplitArrDown(curr,h+1,curr.boardState[i][j],y123,pos,St,nextS,0,i,j); 
                }
              } 
              for(int h=0;h<min(right,tr);h++)
              { state St(boardSize);
                St.boardState=curr.boardState; 
                St.parent=&curr ;
                St.depth=curr.depth+1; 
                /*if(St.boardState[i][j+1].size()==0)
                {

                }
                else*/
                {NsplitArrRight(curr,h+1,curr.boardState[i][j],y123,pos,St,nextS,0,i,j); 
                }
              }
              for(int h=0;h<min(left,tr);h++)
              { state St(boardSize);
                St.boardState=curr.boardState; 
                St.parent=&curr ;
                St.depth=curr.depth+1; 
                //cout<<"yo"<<endl;
                /*if(St.boardState[i][j-1].size()==0)
                {

                }
                else*/
                {NsplitArrLeft(curr,h+1,curr.boardState[i][j],y123,pos,St,nextS,0,i,j); 
                }
              }
            }
          if(curr.boardState[i][j][curr.boardState[i][j].size()-1]==q)
            {
                tr= pos.size()-1 ;

              int y123; 
              for(y123=0;y123<=tr;y123++)
              {
                if((pos[tr]-pos[y123])<=5)
                  { //cerr<<"more stones "<<y123<<endl; 

                    break;
                  } 
              }
              for(int h=0;h<min(top,tr);h++)
              { state St(boardSize);
                St.boardState=curr.boardState; 
                St.parent=&curr ;
                St.depth=curr.depth+1; 
                /*if(St.boardState[i-1][j].size()==0)
                {

                }
                else*/ 
                  {CsplitArrTop(curr,h+1,curr.boardState[i][j],y123,pos,St,nextS,0,i,j); 
                    }
              }

              for(int h=0;h<min(bottom,tr);h++)
              { state St(boardSize);
                St.boardState=curr.boardState; 
                St.parent=&curr ;
                St.depth=curr.depth+1;
                /*if(St.boardState[i+1][j].size()==0)
                {

                } 
                else */{
                  CsplitArrDown(curr,h+1,curr.boardState[i][j],y123,pos,St,nextS,0,i,j); 
                }
              } 
              for(int h=0;h<min(right,tr);h++)
              { state St(boardSize);
                St.boardState=curr.boardState; 
                St.parent=&curr ;
                St.depth=curr.depth+1; 
                /*if(St.boardState[i][j+1].size()==0)
                {

                }
                else*/
                {CsplitArrRight(curr,h+1,curr.boardState[i][j],y123,pos,St,nextS,0,i,j); 
                }
              }
              for(int h=0;h<min(left,tr);h++)
              { state St(boardSize);
                St.boardState=curr.boardState; 
                St.parent=&curr ;
                St.depth=curr.depth+1; 
                //cout<<"yo"<<endl;
                /*if(St.boardState[i][j-1].size()==0)
                {

                }
                else*/
                {CsplitArrLeft(curr,h+1,curr.boardState[i][j],y123,pos,St,nextS,0,i,j); 
                }
              } 
            }   
          
        }
      }
    }
    //cout<<" "<<f<<" "; 
  
    for(int i=0;i<nextS.size();i++)
    {
      nextS[i].eval= evalFxn(nextS[i]); 
    }

   sort(nextS.begin(), nextS.end(),greater1());

    /*for(int i=0;i<nextS.size();i++)
    {
      cerr<<nextS[i].eval<<endl;//= evalFxn(nextS[i]); 
    }*/
  //cerr<<"yes i have printed"<<endl;    
  return nextS ;
}


/*vector<state> nextstate(state &curr)
{
  
  vector<state> ns ;


  for(int i=0;i<boardSize;i++)
  {
    for(int j=0;j<boardSize;j++)
    { int len=curr.boardState[i][j].size() ;
      if(len!=0)
      {
         if(curr.boardState[i][j][len-1]==1||curr.boardState[i][j][len-1]==3)
         {  int range =0 ;
            vector<int> posi ;  //cant be greater than 5  
            for(int z=max(0,len-5);z<=len-1;z++)
            {
              if(curr.boardState[i][j][z]=='1')
                {  posi.push_back(z-1); 
                   range++ ; 
                }
              state nextS(boardSize);
              nextS.depth=curr.depth+1; 
              nextS.boardState=curr.boardState; 
              nextS.parent=&curr;     
              
              myMovTop(posi,min(range,i),curr,0);     //position of splits , range , present position, current state , where i have reached  

            }

         }
         else if(curr.boardState[i][j][len-1]==5)
         {

         }

      }
      else
      {
        if(ourCapRem)
        {  state temp(boardSize);
           temp=curr; 
           temp.depth= curr.depth+1; 
           temp.parent=&curr ;
           temp.boardState[i][j].push_back(5);
           temp.printM="C"+my_map2[j+1]+my_map3[boardSize-i] ;
           ns.push_back(temp);
        }
        if(ourStonesRem>0)
        {  state temp(boardSize);
           temp=curr; 
           temp.depth= curr.depth+1; 
           temp.parent=&curr ;
           temp.boardState[i][j].push_back(1);
           temp.printM="F"+my_map2[j+1]+my_map3[boardSize-i] ;
           ns.push_back(temp);

           state temp1(boardSize);
           temp1=curr; 
           temp1.depth= curr.depth+1; 
           temp1.parent=&curr ;
           temp1.boardState[i][j].push_back(3);
           temp1.printM="S"+my_map2[j+1]+my_map3[boardSize-i] ;
           ns.push_back(temp1);
        } 
      }
    } 
  }

  return ns;  
} 

vector<state> nextstate2(state &curr)
{
    vector<state> ns ;
  

  for(int i=0;i<boardSize;i++)
  {
    for(int j=0;j<boardSize;j++)
    {
      if(curr.boardState[i][j].size()==0)
      {
       
       if(oppoCapRem)
        {  state temp(boardSize);
           temp=curr; 
           temp.depth= curr.depth+1; 
           temp.parent=&curr ;
           temp.boardState[i][j].push_back(6);
           ns.push_back(temp);
        }
      if(oppoStonesRem>0)
        {  state temp(boardSize);
           temp=curr; 
           temp.depth= curr.depth+1; 
           temp.parent=&curr ;
           temp.boardState[i][j].push_back(2);
           ns.push_back(temp);

           state temp1(boardSize);
           temp1=curr; 
           temp1.depth= curr.depth+1; 
           temp1.parent=&curr ;
           temp1.boardState[i][j].push_back(4);
           ns.push_back(temp1);
        }

      }
    } 
  }

  return ns; 
} */