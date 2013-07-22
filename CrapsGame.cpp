//============================================================================
// Name        : Craps.cpp
// Author      : Robert Cope
// Version     : 0.1 (Alpha)
// Copyright   : Protected by GPL v3
// Description : Craps Simulation
//============================================================================

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

class die{
		unsigned short face;
	public:
		unsigned short get_face(void){
			return face;
		}
		void roll(void){
			face = (rand() % 6) + 1;
		}
        void dice(void){
            roll();
        }
};

class dice{
        unsigned number;
        die * the_dice;
    public:
        dice(unsigned n){
            number = n;
            the_dice = new die[n];        
        }
        unsigned get_number(void){
            return number;
        }
        void roll_all_dice(void){
            for(unsigned i = 0; i < number; i++){
                the_dice[i].roll();
            }
        }
        void roll_nth_dice(unsigned n){
            if( n < number) the_dice[n].roll();
        }
        unsigned get_nth_face(unsigned n){
            if( n < number) return the_dice[n].get_face();
            else return 0;
        }    
        vector<unsigned> get_all_faces(void){
            vector<unsigned> faces(number);
            for(unsigned i = 0; i < number; i++){
                faces[i] = the_dice[i].get_face();
            }
            return faces;
        }
        vector<unsigned> get_all_faces(vector<unsigned> f){
            if(f.size() >= number){
                for(unsigned i = 0; i < number; i++){
                    f[i] = the_dice[i].get_face();
                }
                return f;
            }
            else return f;
        }
        unsigned roll_and_sum(void){
            unsigned sum = 0;
            for(unsigned i = 0; i < number; i++){
                the_dice[i].roll();
                sum += the_dice[i].get_face();
            }
            return sum;
        }
        ~dice(void){
            delete(the_dice);
        }
};


//Two modes
//First mode --> Game mode. Actually play craps.
//Second mode --> Simulation mode. Place a generic bet, simulation over MANY games, look at odds.

class player{
        float money;
        bool shooter;
    public:
        player(float money_init){
            money = money_init;
        }
        void set_money(float m){
            money = m;
        }
        float get_money(void){
            return money;
        }
        void add_money(float amount){
            money += amount;
        }
        void remove_money(float amount){
            money -= amount;
        }
        void set_shooter(bool s){
            shooter = s;
        }
        bool get_shooter(void){       
            return shooter;
        }
};     

class craps_game{
        dice * game_dice;
        char mode; unsigned point;
        char bet; float bet_amount;
        player * p1;
    public:
        craps_game(player * p){
            p1 = p;
            p1->set_shooter(true);
            game_dice = new dice(2);
        }
        void set_bet(char type, float amount){
            bet = type;
            bet_amount = amount;
        }
        void roll(void){
            unsigned outcome = game_dice->roll_and_sum();
            cout << "Rolled " << outcome << endl;
            if(bet == 'p'){
                cout << "Bet Pass" << endl;
                switch(outcome){                
                    case 7:
                    case 11:
                        cout << "Natural: WIN" << endl;
                        cout << "Won $" << bet_amount << endl;
                        p1->add_money(bet_amount);
                        break;
                    case 2:
                    case 3:
                    case 12:
                        cout << "Craps: LOSE" << endl;
                        cout << "Lost $" << bet_amount << endl;
                        p1->remove_money(bet_amount);
                        break;
                    default:
                        point = outcome;
                        cout << "Point set at: " << outcome << endl;
                        roll_point(outcome);
                        break;
                }
            }
            else if(bet == 'd'){
                cout << "Bet Don't Pass" << endl;
                switch(outcome){                
                    case 2:
                    case 3:
                    case 12:
                        cout << "Craps: WIN" << endl;
                        cout << "Won $" << bet_amount << endl;
                        p1->add_money(bet_amount);
                        break;
                    case 7:
                    case 11:
                        cout << "Natural: LOSE" << endl;
                        cout << "Lost $" << bet_amount << endl;
                        p1->remove_money(bet_amount);
                        break;
                    default:
                        point = outcome;
                        cout << "Point set at: " << outcome << endl;
                        roll_point(outcome);
                        break;
                }

            }
        }
        void roll_point(unsigned point){
            if(bet == 'p'){
                unsigned reroll = game_dice->roll_and_sum();
                cout << "Re-rolled " << reroll << endl;
                if(reroll == point){
                    cout << "Rolled point: WIN" << endl;
                    cout << "Won $" << bet_amount << endl;
                    p1->add_money(bet_amount);
                }
                else if(reroll == 7){
                    cout << "Rolled 7: LOSE" << endl;
                    cout << "Lost $" << bet_amount << endl;
                    p1->remove_money(bet_amount);
                }
                else{
                    roll_point(point);
                }
            }
            else if(bet == 'd'){
                unsigned reroll = game_dice->roll_and_sum();
                cout << "Re-rolled " << reroll << endl;
                if(reroll == 7){
                    cout << "Rolled 7: WIN" << endl;
                    cout << "Won $" << bet_amount << endl;
                    p1->add_money(bet_amount);
                }
                else if(reroll == point){
                    cout << "Rolled point: LOSE" << endl;
                    cout << "Lost $" << bet_amount << endl;
                    p1->remove_money(bet_amount);
                }
                else if(reroll == 12){
                    cout << "Rolled 12: LOSE" << endl;
                    cout << "House wins." << endl;
                    cout << "Lost $" << bet_amount << endl;
                    p1->remove_money(bet_amount);
                }
                else{
                    roll_point(point);
                }
            }
        }
};

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
            cout << "Set Bet: " << endl << "-[p] -> Pass (1:1)" << endl << "-[d] -> Don't Pass (1:1)" << endl;
            cout << "Bet: ";
            cin >> bet;
            cin.clear();       
       }while(bet != 'p' && bet != 'd');
       cout << "Set amount to bet: $";
       cin >> amount;
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
