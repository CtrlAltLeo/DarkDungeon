#ifndef _NPC
#define _NPC

#include "character.h"
#include <string>
#include <fstream>

class NPC {

	private:
		
		static const string name_list[30]; 

	

	public:

		NPC(){
			
			name = name_list[ rand() % 30 ];

		}
		
		~NPC(){
			
		 }
		
		std::string name;
		
		void remove(){
			talked_to = true;
		}				
	
		bool talked_to = false;
	

};

const std::string NPC::name_list[30] = {"Jeanin the Mild","Bertrannus the Bane","Wymund the Poor","Nicolas the Reckless","Howard the Warm","Pierce the Selfish","Geronimus the Muscle","Miles the Mild","Ansellus the Hungry","Sewal the Allegiant","Guibe of the Dawn","Mainard the Dragonslayer","Nycolas the Brute","Reinfridus the Escort","Jehanel the Young","Alein the Warm","Doran the Dragonheart","Reinold the Resolute","Adkin the Swift","Lovell the Valiant","Bobbie of the Winter","Guillemot the Mighty","Talebot the Patrol","Federyc the Lionheart","Rotbert the Courteous","Seemannus the Harbinger","Abel the Resilient","Artheur the Yellow","Normann the Whisper","Averitt the Rich"};



class dialoge_option{

	public:

		dialoge_option(){
			
			effect_type = rand() % 4;
			effect_multiplier = (rand() % 3) + 1;
			
			switch (effect_type){

				case 0:
					text = "I have something shiny for you..";
					break;
				case 1:
					text = "Let me help with that wound..";
					break;
				case 2:
					text = "This knife might come in handy..";
					break;
				case 3:
					text = "Listen to my words..";
					break;
				default:
					text = "AMONG US";
					break;
			}
			
		}

		std::string text = "This is a sample text";
		
		
	
		enum effect {GOLD, HEALTH, DAMAGE, SANITY};

		int effect_type;

		int effect_multiplier = 1;

		void apply_effect(character *player){
			
			if (effect_type == GOLD){

				player->add_gold(10 * effect_multiplier);

			} else if (effect_type == HEALTH){

				player->heal(3*effect_multiplier);

			} else if (effect_type == DAMAGE){

				player->damage(3*effect_multiplier);

			} else if (effect_type == SANITY){
				player->change_san(2*effect_multiplier);
			}

		}	


};



void npc_talk(NPC *person, character *player){

	bool talking = true;

	while(talking){

		display_screen screen;

		screen.cls();

		screen.print(0,0, person->name);	
	
		vector<dialoge_option> dialoges;
		for (int i = 0; i<3; i++){
			dialoge_option o;
			dialoges.push_back(o);
			
			screen.print(2, (3*i)+ 2, to_string((i+1)) +" " + o.text);
		}
		
		screen.print(2, 10, "(4) Do Nothing");
	
		screen.draw();
	
		int opt = get_number(1,4);	

		if (opt > 0 && opt < 4){
			dialoges[opt-1].apply_effect(player);
		}	

		talking = false;	


	}

}





#endif
