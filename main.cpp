#include "graphics.h"
#include "explore.h"
#include <unistd.h>
#include <string>
#include <vector>


using namespace std;

void add_room(vector<room> & rooms, string desc){

	room R;

	R.id = rooms.size();
	R.desc = desc;	

	
	rooms.push_back(R);

}

void connect_rooms(vector<room> & rooms, int id_1, int id_2){
	
	edge door(id_1, id_2);

	rooms[id_1].doors.push_back(door);
	rooms[id_2].doors.push_back(door);
	

}

void print_desc(vector<room> & rooms, int id){

	cout << rooms[id].desc << endl;
	

	int opt = 0;	
	for (edge door: rooms[id].doors){
		cout << "DOOR " <<opt << rooms[door.get_other_node(id)].desc << endl; 
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

int main(){
	
	display_screen display;

/*	
	vector<room> ROOMS;
	active_room = 0;
	
	add_room(ROOMS, "You enter the suspicous chamber full of sussy bakas.");
	add_room(ROOMS, "Soup");
	add_room(ROOMS, "AMONG US");	
	
		
	connect_rooms(ROOMS,1,2);		
	connect_rooms(ROOMS,0,1);
	*/	

	display.cls();

	display.rect_fill(0,0,SCREEN_X,SCREEN_Y,'#');
	display.rect_fill(1,1,SCREEN_X-1,SCREEN_Y-1,'.');
	
	display.ascii_image(1,7,"Art/logo.txt");	

	display.print(20, 15, "Press ENTER to start!");	
	
	display.draw();
	
	get_number(-1000,1000);

	display.cls();	

	display.rect_fill(0,0,SCREEN_X,SCREEN_Y,'#');
	display.rect_fill(1,1,SCREEN_X-1,SCREEN_Y-1,'.');

	display.print_bounds(2,2,SCREEN_X-2,SCREEN_Y-2, "There is a dark and dangerous crypt deep underneath the city. It is filled with monsters and evil. but also treasure. You have been tasked to enter the darkness.");	

	display.draw();
	
	return 0;
}
