#ifndef explore.h
#define explore.h

#include <string>
#include <vector>


class edge{

	int node1;
	int node2;
		
	public:	
	
	edge(int node1, int node2){
		this->node1 = node1;
		this->node2 = node2;

	}	

	int get_other_node(int me){
		
		if (node1 == me){
			return node2;
		} else if (node2 == me){
			return node1;
		}

		return -1;

	}		

};


class room{
	public:	
	std::string desc;
	std::string door_desc;	

	
	int id;	
		
	std::vector<edge> doors;
	

};
 

#endif
