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


void npc_talk(NPC person, character *player){

	bool talking = true;

	while(talking){

		display_screen screen;

		screen.cls();

		screen.print(0,0, person.name);	

		screen.print_bounds(2,2,15,15,"Hey guys, it's me, mark");
	
		screen.draw();
		
		int num = get_number(1,100);

		player->add_gold(num);

		talking = false;	

	

	}

}






#endif
