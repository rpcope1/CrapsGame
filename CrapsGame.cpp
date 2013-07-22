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
        void set_shooter(bool s){
            shooter = s;
        }
        bool get_shooter(void){       
            return shooter;
        }
};     

class craps_game{
        dice * game_dice;
        char mode;
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
            cout << outcome << endl;
        }
        

};

int main() {
	srand(time(NULL));
	cout << "Craps Simulation v0.1" << endl;
	player my_player(100.0);
    craps_game game(&my_player);
    game.roll();
	return 0;
}
