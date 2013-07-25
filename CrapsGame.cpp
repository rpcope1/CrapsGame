//============================================================================
// Name        : Craps.cpp
// Author      : Robert Cope
// Version     : 0.1 (Alpha)
// Copyright   : Protected by GPL v3
// Description : Craps Simulation
//============================================================================

#define DEBUG false

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <vector>
#include <string>

#include "CrapsClasses.h"
#include "CrapsFunctions.cpp"

using namespace std;

int main() {
	srand(time(NULL));
	cout << "Craps Simulation v0.1" << endl;	
    player my_player(100.0);
    craps_game game(&my_player);
    while(true){    
       cout << endl << "----------" << endl << "Current Money: $" << my_player.get_money() << endl;
       char bet; float amount;
       char play;    
       do{ 
            ListBets();
            cout << "Bet: ";
            cin >> bet;
            cin.clear();       
       }while(!isCharInString(bet, "pdc7321"));
       do{            
            cout << "Set amount to bet: $";
            cin >> amount;
            if(cin.fail()){
                cout << "Please enter a valid dollar value." << endl;
                cin.clear(); cin.ignore(INT_MAX,'\n');
            }
            else if(amount > my_player.get_money()){
                cout << "Insufficient cash to wager bet!" << endl;
                cin.clear();
            }
            else{
                break;
            }
       }while(true);
       cout << endl;
       cin.clear();
       game.set_bet(bet, amount);
       game.roll();
       cout << "Keep playing? [y/n] ";
       cin >> play;
       cin.clear();
       if(play == 'n'){
            break;
       }
    }
    cout << "Final earnings $" << my_player.get_money() << endl;
	return 0;
}

