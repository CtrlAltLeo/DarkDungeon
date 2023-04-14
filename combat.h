#ifndef combat
#define combat



class weapon{
	public:
		int damage;
		int hit;
		int crit;
	
		weapon(int damage = 1, int hit = 1, int crit = 1 ){
			this->damage = damage;
			this->hit = hit;
			this->crit = crit;
			

		}


};


class enemy{


	public:

		int HP;
	
		weapon Weapon;

	
		void attack(){
			cout << "The Monster Attacks!" << endl;
		}
		

};

class orc: public enemy{

	public:
		
		orc(){
			weapon G(2,2,2);
			Weapon = G;	
			HP = 10;
		}

};

		


void do_combat (character *player, enemy *monster){

		
	display_screen d;	


	while ( player->get_hp() > 0 && monster->HP > 0){
		
		d.cls();

		d.ascii_image(2,2,"Art/knight_combat");	
		d.ascii_image(30,2,"Art/monster_combat");		

		d.print(10,10, to_string(monster->HP));

		d.draw();
		
	

		int choice = get_number(1,10);
		player->damage(choice);
	}	

}



#endif
