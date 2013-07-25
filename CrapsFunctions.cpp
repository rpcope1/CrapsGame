using namespace std;

bool isCharInString(char c, string s){
    for(unsigned i = 0; i < s.length(); i++){
        if(c == s[i]) return true;
        if(DEBUG) cout << c << " " << s[i] << endl;
    }
    return false;
}



void ListBets(void){
    //Basic Pass Line Bets..
    cout << "--Pass Line Bets--" << endl;
    cout << "-[p] -> Pass (1:1)" << endl << "-[d] -> Don't Pass (1:1)" << endl;
    //Propostion bets..
    cout << "--Proposition Bets--" << endl;
    cout << "-[c] -> Any Craps (2,3,12) (8:1)" << endl << "-[7] -> Any 7 (5:1)" << endl;
    cout << "-[3] -> Ace-Duece (16:1)" << endl << "-[2] -> Aces (31:1)" << endl;
    cout << "-[1] -> Twelve (31:1)" << endl;
    
    return;
}
