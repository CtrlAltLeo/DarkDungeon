#ifndef CHARACTER
#define CHARACTER

#include <string>

class character{
	
	public:
	
		enum stats {STRENGTH = 1, MAGIC, SANITY};
	
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

		int get_hp(){
			return HP;
		}

		int get_sanity(){
			return SAN;
		}
		
		void heal(int hp){
			HP += hp;
		}
		
		void damage(int hp){
			HP -= hp;
		}
		
		void change_san(int san){
			SAN += san;
		}
		
		int get_san(){
			return SAN;
		}
		
	
		std::string get_stats(){
			
			std::string player_stats = "";	
					
			std::string end = " ";

			player_stats += end + name + end;

			player_stats += "HP: " + std::to_string(HP) + end;
	
			player_stats += "Strength: " + std::to_string(STR) + end;
			player_stats += "Magic: " + std::to_string(MAG) + end;
			player_stats += "Sanity: " + std::to_string(SAN) + end;
			player_stats += "Gold Pieces: " + std::to_string(gold) + end;
			
			return player_stats;
		}	

		void add_gold(int g){
			gold += g;
		}

		int get_gold(){
			return gold;
		}
		
				

	private:
		
		std::string name;
	
		int STR; //strength
		int MAG; //Magic
		int SAN; //Sanity	
		int HP; //hit points
		int gold = 0;			
			


};

character make_character(){

	std::string name;
	int str = 10;
	int mag = 10;
	int san = 10;
	
	cout << "Enter your character's name" << endl;
	getline(cin, name);

	bool str_mag = get_bool("Do you usually let your sword do the talking?");
	bool mag_san = get_bool("Are you afraid of forbidden knowledge?");
	bool str_san = get_bool("Do you put taking care of your mind over your muscles?");

	if (str_mag){
		str += 2;
		mag -= 1;
	} else {
		mag += 2;
		str -= 1;
	}	

	if (mag_san){
		mag += 2;
		san -= 1;
	} else {
		san += 2;
		mag -= 1;
	}

	if (str_san){
		str += 2;
		san -= 1;
	} else {
		san += 2;
		str -= 1;
	}
	character player(name, str, mag, san, 10);

	return player;

}


#endif
