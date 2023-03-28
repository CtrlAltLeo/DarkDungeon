#include "graphics.h"
#include "explore.h"
#include <unistd.h>
#include <string>
#include <vector>
#include <fstream>

/* TODO
	
	-action context menu
		move to other room
		attack monster
		talk to npc
			
		
	-add combat
	
	-add character skills and HP

	-very rough NPC stuff

*/

using namespace std;



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
	
	
	int opt = 0;	
	for (edge door: rooms[id].doors){
	//	cout << "DOOR " <<opt << rooms[door.get_other_node(id)].door_desc << endl; 
		room_desc = room_desc + " (" + to_string(opt) + ") "+rooms[door.get_other_node(id)].door_desc ;
		opt += 1;	
	}

	rooms[id].visible = true;

	return room_desc;
	
}

string get_desc(vector<room> &rooms, int id){
	
	return rooms[id].desc;

}

int get_number(int low, int high){
		
	int in = -1;
		
	do {
		cout << "Input a number between " << low << " and " << high << endl;
		cin >> in;
				
	} while( in > high or in < low);
	
	return in;	

}

int get_player_action(){

	int act = get_number(1,3);
	cout << "Look (1) \n Go through door (2) \n Take item (3) \n" << endl;

	while (act > 3 or act < 1){
	int act = get_number(1,3);
	cout << "Look (1) \n Go through door (2) \n Take item (3) \n" << endl;


	}	

	return act;	

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

	d.rect(1, SCREEN_Y/1.5, SCREEN_X, SCREEN_Y, '=');	
	d.print_bounds(2,(SCREEN_Y/1.5)+1,SCREEN_X, SCREEN_Y, desc); 
	
}

int main(){
	
	srand(time(NULL));

	vector<room> ROOMS;
	int active_room = 0;
	
	generate_dungeon(ROOMS);	



	display_screen d;

	while(true){
		
		d.cls();

	
	//map
	  draw_map(d, ROOMS, active_room);

	//character stats
//	d.rect(SCREEN_X/1.5,1,SCREEN_X,SCREEN_Y/1.5,'$');
  	
		draw_text(d, ROOMS, active_room);

		d.print(0,0,to_string( ROOMS.size() )  );
	
   	d.draw();		
		int in = get_number(0,5);

		active_room = ROOMS[active_room].get_door_id(in);	
		ROOMS[active_room].visible = true;	


	}

	return 0;
}
