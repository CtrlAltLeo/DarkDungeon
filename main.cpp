#include "graphics.h"
#include "inputs.h"
#include "npc.h"
#include "explore.h"
#include "character.h"
#include "combat.h"


#include <unistd.h>
#include <string>
#include <vector>
#include <fstream>

/* TODO
	
	-action context menu
		attack monster

		
	-add combat

*/

using namespace std;

string print_actions(const vector<room> &rooms, int active_room);

int active_room; 
int last_room;
vector<room> ROOMS;

int game_running = true;

character *pPlayer = 0;


 
void add_room(vector<room> & rooms, string desc, string door_desc = "AA", int x=0, int y=0, int h=0, int w = 0){

	room R;
	
	R.x = x;
	R.y = y;
	R.h = h;
	R.w = w;

	R.id = rooms.size();
	R.desc = desc;	
	R.door_desc = door_desc;
	
	rooms.push_back(R);

}

void connect_rooms(vector<room> & rooms, int id_1, int id_2){
	
	edge door(id_1, id_2);

	rooms[id_1].doors.push_back(door);
	rooms[id_2].doors.push_back(door);
	
}

string print_desc(vector<room> & rooms, int id){

	string room_desc = "";

	room_desc = room_desc + rooms[id].desc + "\n";
	
	room_desc = room_desc + print_actions(rooms, id);
	
	
	int opt = 0;	
	for (edge door: rooms[id].doors){
	//	cout << "DOOR " <<opt << rooms[door.get_other_node(id)].door_desc << endl; 
		room_desc = room_desc + " (" + to_string(opt) + ") "+rooms[door.get_other_node(id)].door_desc ;
		opt += 1;	
	}
	

	rooms[id].visible = true;

	return room_desc;
	
}

//gives the player hints for available actions
string print_actions(const vector<room> &rooms, int active_room){

	string response = "";	

	room R = rooms[active_room];

	if (R.has_npc){

		response += R.guy->name + " is standing in the room. ";

	} else {
		response = response + "There is no one in the room. ";
	}

	if (R.has_monster){
		response = response + "There is a monster in here! ";
	} else {
		response = response + "There are no monsters in the room. ";
	}

	return response;

}



void action_process(){

	cout << "enter an action. (type help for help!)" << endl;
	
	string act = get_player_action();

	room *R = &ROOMS[active_room];

	if (act == "door"){

		int in = get_number(0, R->doors.size()-1);	
	
		last_room = active_room;	
		active_room = R->get_door_id(in);

	} else if (act == "help"){
		
		cout << "try door, fight, talk, last, or help." << endl;		
		sleep(3);
	} else if (act == "talk"){
		
		if (R->has_npc){

			npc_talk(R->guy, pPlayer);
			R->remove_npc();

		} else {
			cout << "There's no one in the room" << endl;
			sleep(1);	
		}		

	
	} else if (act == "last"){
		active_room = last_room;
	}	

}



void generate_dungeon(vector<room> &rooms){
	
	int room_count = (rand() % 10)+6;
	
	vector<string> descs;	
	vector<string> doors;

	string in;

	ifstream desc_in;
	desc_in.open("Text/Room_Descs");
	while(desc_in){	
		getline(desc_in, in);
		descs.push_back(in);
	}
	desc_in.close();

	desc_in.open("Text/Door_Descs");
	while(desc_in){	
		getline(desc_in, in);
		doors.push_back(in);
	}	

	for (int i = 0; i < room_count; i++){
		
		add_room(rooms, descs[rand() % (descs.size()-1)], doors[rand() % (doors.size()-1)],(rand()%35)+5, (rand()%10)+5, 2,2);
	}

	//connect rooms	
	
	for (auto i : rooms){
		
		int current_room = i.id;

		int connections = (rand() % 2)+1;
	

			

		for (int i = 0; i < connections; i++){
		
			int connect = rand() % rooms.size();					
		
			do {
				connect = rand() % rooms.size();
			} while(connect == current_room);
		
			for (edge door : rooms[connect].doors){
				if (door.checksum == (current_room * connect)){
					break;
				}	
			}	
	
			if (rooms[connect].doors.size() > 3){
				break;
			}			

			connect_rooms(rooms, current_room, connect);	
		}

	}

	
	rooms[0].visible = true;		
}


void draw_map(display_screen &d,const vector<room> &rooms,const int active_room){
	
	d.rect(1,1,SCREEN_X/1.5,SCREEN_Y/1.5,'#');
	
	for (room r: rooms){

		char texture = '.';

		if (r.id == active_room){
			texture = '@';
		}
		
		if (r.visible == false){
			texture = ' ';
		}

		d.rect_fill(r.x, r.y, r.x+r.w, r.y+r.h, texture);
	}
	
}

void draw_text(display_screen &d, vector<room> &rooms, int &active_room){

	string desc = print_desc(rooms, active_room);

	//d.rect(1, SCREEN_Y/1.5, SCREEN_X, SCREEN_Y, '=');	
	d.print_bounds(0,(SCREEN_Y/1.5),SCREEN_X, SCREEN_Y, desc); 
	
}

void draw_character(display_screen &d , character &c){

		int x = SCREEN_X/1.5;
		int y = SCREEN_Y/1.5;

		d.rect(x,1,SCREEN_X,y,'$');
	
		d.print_bounds(x+3,3,x+15,y,c.get_stats());
}

void check_lose(character &c){

	if (c.get_hp() <= 0 || c.get_sanity() <= 0){
		game_running = false;

		display_screen d;
		
		d.cls();
		d.ascii_image(SCREEN_X/3,0,"Art/skull");
		d.ascii_image(7, SCREEN_Y-7, "Art/death");
		d.draw();	

	}

}

void check_combat(character *player){

	if (ROOMS[active_room].has_monster){

		orc ORC;
		do_combat(player, &ORC);
		
		ROOMS[active_room].has_monster = false;

	}

}

int main(){



	
	
	srand(time(NULL));

	active_room = 0;
	last_room = 0;
	
	generate_dungeon(ROOMS);	

	ROOMS[active_room].has_monster = false;

	character player = make_character();

	pPlayer = &player;	
	


	display_screen d;

	while(game_running){
		
		d.cls();

	  draw_map(d, ROOMS, active_room);

		draw_character(d, player);
  	
		draw_text(d, ROOMS, active_room);


		d.draw();		

		action_process();

		check_combat(pPlayer);
		
		check_lose(player);	
	
	}



	return 0;
}
