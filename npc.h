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
		
		std::string name;
		
		void remove(){

		}				
	

};

const string NPC::name_list[30] = {"Jeanin the Mild","Bertrannus the Bane","Wymund the Poor","Nicolas the Reckless","Howard the Warm","Pierce the Selfish","Geronimus the Muscle","Miles the Mild","Ansellus the Hungry","Sewal the Allegiant","Guibe of the Dawn","Mainard the Dragonslayer","Nycolas the Brute","Reinfridus the Escort","Jehanel the Young","Alein the Warm","Doran the Dragonheart","Reinold the Resolute","Adkin the Swift","Lovell the Valiant","Bobbie of the Winter","Guillemot the Mighty","Talebot the Patrol","Federyc the Lionheart","Rotbert the Courteous","Seemannus the Harbinger","Abel the Resilient","Artheur the Yellow","Normann the Whisper","Averitt the Rich"};



class dialoge_option{

	public:

		dialoge_option(){
			
			effect_type = rand() % 4;
			effect_multiplier = (rand() % 3) + 1;

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



void npc_talk(NPC person, character *player){

	bool talking = true;

	while(talking){

		display_screen screen;

		screen.cls();

		screen.print(0,0, person.name);	

		
		dialoge_option d;

		screen.print(2,2, d.text);

		screen.print(2,3, std::to_string(d.effect_type));
	
		screen.draw();

		if (get_bool("Do you want the effect?")){
			d.apply_effect(player);
		}	
	
		talking = false;	

	

	}

}





#endif
