#ifndef explore
#define explore

#include <string>
#include <vector>

class treasure{
	
	private:
		std::string name;
		std::string desc;

	public:
		treasure(std::string _name = "blank!",std::string desc = "blank!"){
			this->name = _name;
			this->desc = desc;
		}

	std::string get_name(){
		return name;
	}

	std::string get_desc(){
		return desc;
	}


};

class edge{
	//These are Room IDs
	int node1;
	int node2;

		
	public:	
	
	int checksum;

	edge(int node1, int node2){
		this->node1 = node1;
		this->node2 = node2;
		checksum = node1 * node2;
	}	

	//me is the room ID
	int get_other_node(int me){
		
		if (node1 == me){
			return node2;
		} else if (node2 == me){
			return node1;
		}

		return -1;

	}		

	bool has_id(int me){
		if (node1 == me or node2 == me){
			return true;
		} else {
			return false;
		}		
	}

};


class room{
	public:	
	std::string desc;
	std::string door_desc;	

	//room graphical positions
	int x;
	int y;
	int w;
	int h;
	
	bool visible = false;
	
	int id;	
		
	std::vector<edge> doors;
	
	int get_door_id(int index){
		return doors[index].get_other_node(id);
	}	


};


#endif
