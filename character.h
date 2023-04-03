#ifndef CHARACTER
#define CHARACTER

#include <string>

class character{
	
	public:
		
		character(std::string name, int STR, int MAG, int SAN, int HP){
		
			this->name = name;
	
			this->STR = STR;
			this->MAG = MAG;
			this->SAN = SAN;
			this->HP = HP;

		}			

		std::string get_name(){
			return name;
		}
		
		void heal(int hp){
			HP += hp;
		}
		
		void damage(int hp){
			HP -= hp;
		}		
	
		std::string get_stats(){
			
			std::string player_stats = "";	
					
			std::string end = " ";

			player_stats += end + name + end;

			player_stats += "HP: " + std::to_string(HP) + end;
	
			player_stats += "Strength: " + std::to_string(STR) + end;
			player_stats += "Magic: " + std::to_string(MAG) + end;
			player_stats += "Sanity: " + std::to_string(SAN) + end;
			


			return player_stats;
		}	
		
				

	private:
		
		std::string name;
	
		int STR; //strength
		int MAG; //Magic
		int SAN; //Sanity	
		int HP; //hit points
			
			


};

character make_character(){

	std::string name;
	
	cout << "Enter your character's name" << endl;
	getline(cin, name);

	character player(name, 10, 10, 10, 10);

	return player;

}


#endif
