#ifndef CHARACTER
#define CHARACTER

#include <string>

class character{
	
	public:
		
		character(std::string name, int STR, int MAG, int SAN){
		
			this->name = name;
	
			this->STR = STR;
			this->MAG = MAG;
			this->SAN = SAN;
		}			

		std::string get_name(){
			return name;
		}
				

	private:
		
		std::string name;
	
		int STR; //strength
		int MAG; //Magic
		int SAN; //Sanity	
		
			


};

#endif
