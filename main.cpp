#include "graphics.h"
#include "explore.h"
#include <unistd.h>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

void add_room(vector<room> & rooms, string desc, string door_desc = "AA"){

	room R;

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

void print_desc(vector<room> & rooms, int id){

	cout << "ID: " << id << endl;

	cout << rooms[id].desc << endl;
	

	int opt = 0;	
	for (edge door: rooms[id].doors){
		cout << "DOOR " <<opt << rooms[door.get_other_node(id)].door_desc << endl; 
		opt += 1;	
	}
	
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
	
	int room_count = rand() % 10+5;
	
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
		
		add_room(rooms, descs[rand() % descs.size()], doors[rand() % doors.size()]);
	}
	
	for (auto i : rooms){
		
		int current_room = i.id;

		int connections = rand() % 3;
		

		for (int i = 0; i < connections; i++){
			
			int connect;
			do {
				connect = rand() % rooms.size();
						
			} while (current_room == connect);	

			connect_rooms(rooms, current_room, connect);	
		}

	}	
		


}

int main(){
	
	srand(time(NULL));

	vector<room> ROOMS;
	int active_room = 0;
	
	generate_dungeon(ROOMS);	
	
	while(true){
		print_desc(ROOMS, active_room);

		int in = get_number(0,5);

		active_room = ROOMS[active_room].get_door_id(in);	

	}


	return 0;
}
