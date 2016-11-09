
void nextstate(state &curr);

void nextstate2(state &curr);

extern vector<state> myMoveVec;
extern vector<state> oppoMoveVec;
extern int myMoveNum; 
extern int oppoMoveNum; 
extern bool prune  ; 
state GoingtoLoose(state s); 