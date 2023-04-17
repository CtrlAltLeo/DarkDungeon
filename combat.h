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

	
		int attack(){
			return Weapon.damage;	
		}
	
			

};

class orc: public enemy{

	public:
		
		orc(){
			weapon G(2,2,2);
			Weapon = G;	
			HP = 6;
		}

};


		


void do_combat (character *player, enemy *monster){

		
	display_screen d;	


	while ( player->get_hp() > 0 && monster->HP > 0){


		//graphical loop		
		d.cls();

		d.ascii_image(2,2,"Art/knight_combat");	
		d.ascii_image(30,2,"Art/monster_combat");		

		

		d.print(35,25, " Monster HP: " + to_string(monster->HP));
		d.print(10,25, "HP: " + to_string(player->get_hp()));

		d.draw();
	
		//mathematical loop

		int incoming_damage = monster->attack();

		cout << "Use Sword (1) Shield (2) Heal (3) ?" << endl;
		int p_attack = get_number(1,3);	

		if (p_attack == 1){
			monster->HP-=player->attack();
		} 
		
		if (p_attack == 2){
			incoming_damage -= (player->get_sanity() / 10) + 1;
		}		
		
		if (p_attack == 3){
			player->magic_heal();
		}
		
		player->damage(incoming_damage);	

	}	

	if (player->get_hp() <= 0){
		return;
	}

	int g = (rand() % 10) * (rand() % 10) + 1;

	player->add_gold(g);

	d.cls();
	
	d.ascii_image(15,2,"Art/knight_stand");
	
	d.print(10,25, "You survived! You got " + to_string(g) + " gold!");
	
	d.draw();
	
	sleep(5);
	

}



#endif
