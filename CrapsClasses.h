using namespace std;
class die{
    private:		
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
    private:        
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

class player{
    private:        
        string name;
        float money;
        bool shooter;
    public:
        player(float money_init){
            money = money_init;
            name = "Player";
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
        void set_name(string n){
            name = n;
        }
        string get_name(void){
            return name;
        }
};     



class craps_game{
    private:
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
        void roll_point(unsigned point){
            unsigned reroll = game_dice->roll_and_sum();
            cout << "Re-rolled " << game_dice->get_nth_face(0) << "," << game_dice->get_nth_face(1) << " (" << reroll << ")" << endl;            
            switch(bet){
              case 'p':
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
                break;
              case 'd':
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
                break;
            }                
        }        
        void roll(void){
            unsigned outcome = game_dice->roll_and_sum();
            cout << "Rolled " << game_dice->get_nth_face(0) << "," << game_dice->get_nth_face(1) << " (" << outcome << ")" << endl;
            switch(bet){ 
              case'p':
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
                break;
              case 'd':
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
                break;
              case 'c':
                cout << "Bet Craps" << endl;
                switch(outcome){                
                    case 2:
                    case 3:
                    case 12:
                        cout << "Craps: WIN" << endl;
                        cout << "Won $" << 8.0*bet_amount << endl;
                        p1->add_money(8.0*bet_amount);
                        break;
                    default:
                        cout << "Not Craps: LOSE" << endl;
                        cout << "Lost $" << bet_amount << endl;
                        p1->remove_money(bet_amount);
                        break;
                }
                break;
              case '7':
                cout << "Bet Sevens" << endl;
                switch(outcome){                
                    case 7:                    
                        cout << "Seven: WIN" << endl;
                        cout << "Won $" << 5.0*bet_amount << endl;
                        p1->add_money(5.0*bet_amount);
                        break;
                    default:
                        cout << "Not Seven: LOSE" << endl;
                        cout << "Lost $" << bet_amount << endl;
                        p1->remove_money(bet_amount);
                        break;
                }
                break;
              case '3':
                cout << "Bet Ace-Duece" << endl;
                switch(outcome){
                    case 3:
                        cout << "Ace-Duece: WIN" << endl;
                        cout << "Won $" << 16.0*bet_amount << endl;
                        p1->add_money(16.0*bet_amount);
                        break;
                    default:
                        cout << "Not Ace-Duece: LOSE" << endl;
                        cout << "Lost $" << bet_amount << endl;
                        p1->remove_money(bet_amount);
                        break;
                }
                break;
              case '2':
                cout << "Bet Aces" << endl;
                switch(outcome){
                    case 2:
                        cout << "Aces: WIN" << endl;
                        cout << "Won $" << 31.0*bet_amount << endl;
                        p1->add_money(31.0*bet_amount);
                        break;
                    default:
                        cout << "Not Aces: LOSE" << endl;
                        cout << "Lost $" << bet_amount << endl;
                        p1->remove_money(bet_amount);
                        break;
                }
                break;
              case '1':
                cout << "Bet Twelve" << endl;
                switch(outcome){
                    case 2:
                        cout << "Twelve: WIN" << endl;
                        cout << "Won $" << 31.0*bet_amount << endl;
                        p1->add_money(31.0*bet_amount);
                        break;
                    default:
                        cout << outcome << ": LOSE" << endl;
                        cout << "Lost $" << bet_amount << endl;
                        p1->remove_money(bet_amount);
                        break;
                }
                break;
            }        
        }
};
